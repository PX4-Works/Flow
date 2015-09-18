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
 * @file param_if.c
 *
 * @author David Sidrane <david_s5@nscdg.com>
  *
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "param_if.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Types
 ****************************************************************************/


typedef struct uavcan_uint8_param_t {
  const uint8_t min;
  const uint8_t max;
  const uint8_t vdefault;
  uint8_t  value;
} uavcan_uint8_param_t;


typedef struct uavcan_int64_param_t {
  const int64_t min;
  const int64_t  max;
  const int64_t  vdefault;
  int64_t  value;
} uavcan_int64_param_t;

typedef struct uavcan_float32_param_t {
  const float min;
  const float  max;
  const float  vdefault;
  float  value;
} uavcan_float32_param_t;

typedef struct uavcan_string_param_t {
  const int    min;
  const int  max;
  const char *vdefault;
  char *   value;
} uavcan_string_param_t;


typedef struct uavcan_param_t {
  uavcan_param_type_t           t;
  const char *                  name;
  union {
    uavcan_uint8_param_t          b;
    uavcan_int64_param_t          i;
    uavcan_float32_param_t        f;
    uavcan_string_param_t         s;
  };
} uavcan_param_t;

/****************************************************************************
 * Private data
 ****************************************************************************/

#define define_uavcan_param(var_name, uavcan_name, type, min, max, default_value)  uavcan_name,
char * uavcan_param_uavcan_names[] = {
#include "param_def.h"
};
#undef define_uavcan_param

#define define_uavcan_uint8_param(var_name, uavcan_name, type, vmin, vmax, vdefault) \
{                                                                                   \
 .t = type,                                                                         \
 .name = uavcan_name,                                                               \
  .b = {                                                                            \
    .min =  vmin,                                                                   \
    .max =  vmax,                                                                   \
    .value = vdefault,                                                              \
    },                                                                              \
},

#define define_uavcan_int64_param(var_name, uavcan_name, type, vmin, vmax, vdefault) \
{                                                                                   \
 .t = type,                                                                         \
 .name = uavcan_name,                                                               \
  .i = {                                                                            \
    .min =  vmin,                                                                   \
    .max =  vmax,                                                                   \
    .value = vdefault,                                                              \
    },                                                                              \
},

#define define_uavcan_float32_param(var_name, uavcan_name, type, vmin, vmax, vdefault) \
{                                                                                   \
 .t = type,                                                                         \
 .name = uavcan_name,                                                               \
  .f = {                                                                            \
    .min =  vmin,                                                                   \
    .max =  vmax,                                                                   \
    .value = vdefault,                                                              \
    },                                                                              \
},

#define define_uavcan_string_param(var_name, uavcan_name, type, vmin, vmax, vdefault) \
{                                                                                   \
 .t = type,                                                                         \
 .name = uavcan_name,                                                               \
  .s = {                                                                            \
    .min =  vmin,                                                                   \
    .max =  vmax,                                                                   \
    .value = vdefault,                                                              \
    },                                                                              \
},

#define define_uavcan_param(var_name, uavcan_name, type, vmin, vmax, vdefault) \
  define_##type##_param(var_name, uavcan_name, type, vmin, vmax, vdefault)



uavcan_param_t param_[] = {

#include "param_def.h"


};
#undef define_uavcan_param


/****************************************************************************
 * Name: get_param_name_by_index
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
const char * get_param_name_by_index(uavcan_param_id_t index)
{
  if ( index < uavcan_param_id_size)
    {
      return param_[index].name;
    }
  return NULL;
}

/****************************************************************************
 * Name: get_param_by_index
 *
 * Description:
 *   Used to get the current value of a parameter by index
 *
 * Input Parameters:
 *   index - uavcan_param_id_t
 *   value - is a pointer to a pinter to a null type to return the value
 *   in.
 *
 * Returned value:
 *  O On success
 *  On Failure reason
 *
 ****************************************************************************/

__EXPORT
int get_param_by_index(uavcan_param_id_t index, void **value)
{
  if ( index < uavcan_param_id_size)
    {
      switch(param_[index].t)
      {
      case uavcan_uint8:
        *(uint8_t**)value = &param_[index].b.value;
      break;
      case uavcan_int64:
        *(int64_t**)value = &param_[index].i.value;
      break;
      case uavcan_float32:
        *(float**)value = &param_[index].f.value;
      break;
      case uavcan_string:
        *(char**)value = param_[index].s.value;
      break;
      default:
        return -2;

      }
      return 0;
    }
  return -1;
}


/****************************************************************************
 * Name: get_param_by_name
 *
 * Description:
 *   Used to get the current value of a parameter by name
 *
 * Input Parameters:
 *   name - a pointer the uavcan name
 *   value - is a pointer to a pinter to a null type to return the value
 *   in.
 *
 * Returned value:
 *  O On success
 *  On Failure reason
 *
 ****************************************************************************/

__EXPORT
int get_param_by_name(const char * name, void  **value)
{
  for (int n = 0; n < uavcan_param_id_size; n++) {
      if (0 == strcmp(name, param_[n].name)) {
         return get_param_by_index(n, value);
      }
  }
  return -1;
}

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
uavcan_param_type_t get_param_defaults_by_name(const char *name, void **def, void **min, void **max)
{
  uavcan_param_type_t rv = uavcan_empty;
  for (int index = 0; index < uavcan_param_id_size; index++) {
      if (0 == strcmp(name, param_[index].name)) {
          rv = param_[index].t;
          switch(rv)
          {
          case uavcan_uint8:
            *(const uint8_t**)def = &param_[index].b.vdefault;
            *(const uint8_t**)min = &param_[index].b.min;
            *(const uint8_t**)max = &param_[index].b.max;
          break;
          case uavcan_int64:
            *(const int64_t**)def = &param_[index].i.vdefault;
            *(const int64_t**)min = &param_[index].i.min;
            *(const int64_t**)max = &param_[index].i.max;
          break;
          case uavcan_float32:
            *(const float**)def = &param_[index].f.vdefault;
            *(const float**)min = &param_[index].f.min;
            *(const float**)max = &param_[index].f.max;
          break;
          case uavcan_string:
            *(const char**)def = param_[index].s.vdefault;
            *(const int**)min = &param_[index].s.min;
            *(const int**)max = &param_[index].s.max;
          break;

          default:
            break;
          }
      }
  }
  return rv;
}

/****************************************************************************
 * Name: get_param_type_index_by_name
 *
 * Description:
 *   Used to get the default value and range of a parameter by name
 *
 * Input Parameters:
 *   name - a pointer the uavcan name
 *   type - is a pointer to return the type in
 *
 * Returned value:
 *  O to  uavcan_param_id_size-1 On success
 *  uavcan_param_id_size On Failure reason
 *
 ****************************************************************************/

__EXPORT
uavcan_param_id_t get_param_type_index_by_name(const char *name, uavcan_param_type_t *type)
{
  for (int n = 0; n < uavcan_param_id_size; n++) {
      if (0 == strcmp(name, param_[n].name)) {
          *type = param_[n].t;
         return n;
      }
  }
  return uavcan_param_id_size;
}


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
int set_param_by_index(uavcan_param_id_t index, const void * value)
{
  if ( index < uavcan_param_id_size)
    {
      switch(param_[index].t)
      {
      case uavcan_uint8:
        param_[index].b.value  = *(uint8_t*)value;
      break;
      case uavcan_int64:
        param_[index].i.value  = *(int64_t*)value;
      break;
      case uavcan_float32:
        param_[index].f.value  = *(float*)value;
      break;
      case uavcan_string:
        param_[index].s.value = (char*) value;
      break;
      default:
        return -2;

      }
      return 0;
    }
  return -1;

  return 0;
}

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
int set_param_by_name(const char * name, const void * value)
{
  for (int n = 0; n < uavcan_param_id_size; n++) {
      if (0 == strcmp(name, param_[n].name)) {
         return set_param_by_index(n, value);
      }
  }
  return -1;
}

