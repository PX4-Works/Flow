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

/**
 * @file systemlib.h
 *
 *
 * This provides the mechanisms to interface to the PX4
 * system  lib
 */

#ifndef _SYSTEMLIB__H
#define _SYSTEMLIB__H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
#include <stdbool.h>



/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#undef define_panic_code
#define define_panic_code(pclass, led, code) code,

typedef enum panic_code_t {
  FirstPanicCode,
#include "modules/systemlib/panic_defs.h"
  FirstPanicSize,

} panic_code_t;
#undef define_panic_code

/****************************************************************************
 * Public Functions
 ****************************************************************************/
__BEGIN_DECLS

/****************************************************************************
 * Name: panic
 *
 * Description:
 *   This function to indicate a system failure
 *
 * Input Parameters:
 *   code - a panic Code
 *
 * Returned value:
 *  None
 ****************************************************************************/

__EXPORT void panic(panic_code_t code);


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

__EXPORT void persistence_init(void);

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
 * None
 *
 ****************************************************************************/

__EXPORT int persistence_save(void);


__END_DECLS



#endif /* _SYSTEMLIB__H */
