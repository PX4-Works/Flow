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

#pragma once

#include <px4_config.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <uavcan/uavcan.hpp>

/*
 * Implementations for the standard application-level functions are located in uavcan/protocol/.
 * The same path also contains the standard data types uavcan.protocol.*.
 */

#include "param_if.h"
#include <uavcan/protocol/param_server.hpp>


/**
 * @file uavcan_parammgt.hpp
 *
 * Defines Adds  support for Parameter Management
 *
 * @author Pavel Kirienko <pavel.kirienko@gmail.com>
 *         David Sidrane <david_s5@nscdg.com>
 */

/**
 * A UAVCAN node.
 */
class ParamManager: public uavcan::IParamManager
{
  void getParamNameByIndex(Index index, Name& out_name) const override
  {
    out_name = get_param_name_by_index(static_cast<uavcan_param_id_t>(index));
  }

  void assignParamValue(const Name& name, const Value& value) override
  {
      uavcan_param_type_t type;
      uavcan_param_id_t id = get_param_type_index_by_name(name.c_str(), &type);
      if (uavcan_param_id_size == id) {
          return;
      }

      switch (type)
      {
      case uavcan_int64:
        set_param_by_index(id, &value.integer_value);
        break;
      case uavcan_float32:
        set_param_by_index(id, &value.real_value);
        break;
      case uavcan_uint8:
        set_param_by_index(id, &value.boolean_value);
        break;
      case uavcan_string:
        set_param_by_index(id, value.string_value.c_str());
        break;
      default:
        break;
      }
  }

  void readParamValue(const Name& name, Value& out_value) const override
  {
    void * p = nullptr;
    uavcan_param_type_t type;
    uavcan_param_id_t id = get_param_type_index_by_name(name.c_str(), &type);
    if (uavcan_param_id_size == id) {
        return;
    }

    get_param_by_index(id, &p);

    switch (type)
    {
    case uavcan_empty:
      return;

    case uavcan_int64:
      out_value.integer_value = *static_cast<int64_t*>(p);
      break;
    case uavcan_float32:
      out_value.real_value = *static_cast<float*>(p);
      break;
    case uavcan_uint8:
      out_value.boolean_value = *static_cast<uint8_t*>(p);
      break;
    case uavcan_string:
      out_value.string_value = static_cast<const char*>(p);
      break;
    }
  }

  int saveAllParams() override
  {
      return 0;     // Zero means that everything is fine.
  }

  int eraseAllParams() override
  {
      return 0;
  }

  /**
   * Note that this method is optional. It can be left unimplemented.
   */
  void readParamDefaultMaxMin(const Name& name, Value& out_default,
                              NumericValue& out_max, NumericValue& out_min) const override
  {

    void * def = nullptr;
    void * min = nullptr;
    void * max = nullptr;

    uavcan_param_type_t t = get_param_defaults_by_name(name.c_str(), &def, &min, &max);
    switch (t)
    {
    case uavcan_empty:
      return;

    case uavcan_int64:
      out_default.integer_value  = *static_cast<int64_t*>(def);
      out_max.integer_value = *static_cast<int64_t*>(max);
      out_min.integer_value = *static_cast<int64_t*>(min);
      break;
    case uavcan_float32:
      out_default.real_value = *static_cast<float*>(def);
      out_max.real_value = *static_cast<float*>(max);
      out_min.real_value = *static_cast<float*>(min);
      break;
    case uavcan_uint8:
      out_default.boolean_value = *static_cast<uint8_t*>(def);
      break;
    case uavcan_string:
      out_default.string_value = static_cast<char*>(def);
      break;
    }
  }
};
