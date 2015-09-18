/****************************************************************************
 *
 *   Copyright (c) 2015 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/*
 * @file persistence.h
 *
 * @author David Sidrane <david_s5@nscdg.com>
 *
 */

#include <px4_macros.h>
#include <px4_log.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <systemlib.h>
#include "param_if.h"
#include "flashfs.h"

/* Compile time Ensure that the FFHEADER_SIZE and PERSISTANCE__HEADER_SIZE are the same*/
CHECK_PERSISTANCE_SIZE();

static sector_descriptor_t  sector_map[] = {
        {1, 16 * 1024, 0x08004000},
        {2, 16 * 1024, 0x08008000},
        {0, 0, 0},
};

/****************************************************************************
 * Name: persistence_init
 *
 * Description:
 *   Called at start up to initialize the flash file system
 *   and initialize in memory image from the flash file system
 *
 * Input Parameters:
 * None
 *
 * Returned value:
 * None
 *
 ****************************************************************************/

void persistence_init()
{

        /* Give the Flash FS a buffer to allocate */

        size_t buf_size;
        size_t param_size;

        uint8_t *buffer =  (uint8_t *)get_param_instance(&buf_size);

        parameter_flashfs_init(sector_map, buffer, buf_size);

        /* Get the abstract allocation back as  nv_params_t */

        if (0 != parameter_flashfs_alloc(parameters_token, &buffer, &param_size)) {
            PX4_PANIC("Flash File System: Allocation Failed!");
            panic(FlashFSError);
        }

        buf_size = param_size;

        float version = get_param_version();

        /* Read parameters into ram */

        uint8_t *flash_buffer;

        int rv = parameter_flashfs_read(parameters_token, &flash_buffer, &buf_size);

        /* If there is no entry or the version has changed the save defaults. */

        if (rv == -ENOENT || param_size != buf_size || ((uavcan_param_data_t*)flash_buffer)->version != version) {

            /* Ensure we have a sane FS */

            rv = parameter_flashfs_erase();
            if (rv < 0) {
              PX4_PANIC("Flash File System: Erase failed!");
              panic(FlashFSError);
          }

            default_all_param();

            /* Write default setting to Flash FS */

            rv = parameter_flashfs_write(parameters_token, buffer, param_size);
            if (rv < 0) {
              PX4_PANIC("Flash File System: Write failed!");
              panic(FlashFSError);
          }
        }
}


/****************************************************************************
 * Name: persistence_save
 *
 * Description:
 *   Called to commit persitant data to flashfs
 *
 * Input Parameters:
 * None
 *
 * Returned value:
 * 0 on success
 *
 ****************************************************************************/

int persistence_save(void)
{

  size_t param_size;
  uint8_t *buffer;

  /* Get the abstract allocation back as  nv_params_t */

  int rv  = parameter_flashfs_alloc(parameters_token, &buffer, &param_size);;

  if (rv == 0) {

      rv = parameter_flashfs_write(parameters_token, buffer, param_size);
  }
  return rv;
}
