/*
 * param_if.h
 *
 *  Created on: Sep 17, 2015
 *      Author: david_s5
 */

#ifndef PARAM_IF_H_
#define PARAM_IF_H_

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

__END_DECLS

#endif /* PARAM_IF_H_ */
