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
 * @file param_if.h
 *
 * @author David Sidrane <david_s5@nscdg.com>
  *
 */

#ifndef PARAM_IF_H_
#define PARAM_IF_H_

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define UAVCAN_STRING_SIZE 65          /* Not reserving the 128 */

typedef enum uavcan_param_type_t {
  uavcan_empty,
  uavcan_uint8,
  uavcan_int64,
  uavcan_float32,
  uavcan_string
} uavcan_param_type_t;

#define define_uavcan_param(var_name, uavcan_name, type, min, max, default_value)  var_name##_id,
typedef enum uavcan_param_id_t {
#include "param_def.h"
  uavcan_param_id_size
} uavcan_param_id_t;
#undef define_uavcan_param

/*  Native type mapping */

typedef uint8_t define_native_uavcan_uint8;
typedef int64_t define_native_uavcan_int64;
typedef float define_native_uavcan_float32;
typedef char * define_native_uavcan_string;

#define define_uavcan_uint8_type(var_name, uavcan_name, type, min, max, default_value) define_native_##type var_name;
#define define_uavcan_int64_type(var_name, uavcan_name, type, min, max, default_value) define_native_##type var_name;
#define define_uavcan_float32_type(var_name, uavcan_name, type, min, max, default_value) define_native_##type var_name;
#define define_uavcan_string_type(var_name, uavcan_name, type, min, max, default_value) define_native_##type var_name [UAVCAN_STRING_SIZE];

#define define_uavcan_param(var_name, uavcan_name, type, min, max, default_value)  define_##type##_type(var_name, uavcan_name, type, min, max, default_value)
typedef struct uavcan_param_data_t {
#include "param_def.h"
} uavcan_param_data_t;
#undef define_uavcan_param

/****************************************************************************
 * Public Functions
 ****************************************************************************/
__BEGIN_DECLS

/****************************************************************************
 * Name: get_param_th_by_index
 *
 * Description:
 *   This function is used to return the uavcan name given an index
 *
 * Input Parameters:
 *   index - uavcan_param_id_t
 *
 * Returned value:
 *  On success a pointer to the name
 *  On Failure NULL
 *
 ****************************************************************************/

__EXPORT
const char * get_param_name_by_index(uavcan_param_id_t index);


/****************************************************************************
 * Name: get_param_by_index
 *
 * Description:
 *   Used to get the current value of a parameter by index
 *
 * Input Parameters:
 *   index - uavcan_param_id_t
 *   value - is a pointer to a pointer to a null type to return the value
 *           in.
 *
 * Returned value:
 *  O On success
 *  On Failure reason
 *
 ****************************************************************************/

__EXPORT
int get_param_by_index(uavcan_param_id_t index, void **value);

/****************************************************************************
 * Name: get_param_by_name
 *
 * Description:
 *   Used to get the current value of a parameter by name
 *
 * Input Parameters:
 *   name - a pointer the uavcan name
 *   value - is a pointer to a pointer to a null type to return the value
 *           in.
 *
 * Returned value:
 *  O On success
 *  On Failure reason
 *
 ****************************************************************************/

__EXPORT
int get_param_by_name(const char * name, void  **value);

/****************************************************************************
 * Name: get_param_defaults_by_name
 *
 * Description:
 *   Used to get the default value and range of a parameter by name
 *
 * Input Parameters:
 *   name - a pointer the uavcan name
 *   def - is a pointer to a pointer a null type to return the default value
 *         in.
 *   min - is a pointer to a pointer a null type to return the min value
 *         in.
 *   max - is a pointer to a pointer a null type to return the max value
 *         in.
 *
 * Returned value:
 *  O On success
 *  On Failure reason
 *
 ****************************************************************************/

__EXPORT
uavcan_param_type_t get_param_defaults_by_name(const char *name, void **def, void **min, void **max);

/****************************************************************************
 * Name: get_param_type_index_by_name
 *
 * Description:
 *   Used to get the type and index of a parameter by name
 *
 * Input Parameters:
 *   name - a pointer the uavcan name
 *   type - is a pointer to return the type in
 *
 * Returned value:
 *  O to  uavcan_param_id_size-1 On success
 *  uavcan_param_id_size on Error
 *
 ****************************************************************************/

__EXPORT
uavcan_param_id_t get_param_type_index_by_name(const char *name, uavcan_param_type_t *type);

/****************************************************************************
 * Name: set_param_by_index
 *
 * Description:
 *   Used to set the value of a parameter by index
 *
 * Input Parameters:
 *   index - uavcan_param_id_t
 *   value - is a pointer to a null type.
 *
 * Returned value:
 *  O On success
 *  On Failure reason
 *
 ****************************************************************************/

__EXPORT
int set_param_by_index(uavcan_param_id_t index, const void * value);

/****************************************************************************
 * Name: set_param_by_name
 *
 * Description:
 *   Used to set the value of a parameter by name
 *
 * Input Parameters:
 *   name - a pointer the uavcan name
 *   value - is a pointer to a null type.
 *
 * Returned value:
 *  O On success
 *  On Failure reason
 *
 ****************************************************************************/

__EXPORT
int set_param_by_name(const char * name, const void * value);

/****************************************************************************
 * Name: default_all_param
 *
 * Description:
 *   Used to set all the parameters to the default value
 *
 * Input Parameters:
 * None
 *
 * Returned value:
 *  O On success
 *  On Failure reason
 *
 ****************************************************************************/

__EXPORT
int default_all_param(void);

/****************************************************************************
 * Name: get_param_buffer
 *
 * Description:
 *   Used to get retrieve a buffer suitable for use with the
 *   flahs fs
 *
 * Input Parameters:
 * size - input to a pointer to return the size in bytes of
 * uavcan_param_data_t object + the overhead for the flahsfs
 * interface
 *
 * Returned value:
 *  Returns a pointer to the current values. The is suitable
 *  for use with the fashfs.
 *
 *
 ****************************************************************************/

__EXPORT
uint8_t * get_param_buffer(size_t *size);

/****************************************************************************
 * Name: get_param_instance
 *
 * Description:
 *   Used to get all the instance of the current parameters
 *
 * Input Parameters:
 * size - input to a pointer to return the size in bytes of
 * uavcan_param_data_t;
 *
 * Returned value:
 *  Returns a pointer to the current values.
 *
 *
 ****************************************************************************/

uavcan_param_data_t * get_param_instance(size_t *size);

/****************************************************************************
 * Name: get_param_version
 *
 * Description:
 *   Used to get  all the parameters to the default value
 *
 * Input Parameters:
 *  None
 * Returned value:
 *  Returns a the version of the stored parameters.
 *
 *
 ****************************************************************************/

__EXPORT
int64_t get_param_version(void);


__END_DECLS

#endif /* PARAM_IF_H_ */
