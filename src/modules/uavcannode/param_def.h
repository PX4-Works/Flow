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
 * @file panic_defs.h
 *
 * @author David Sidrane <david_s5@nscdg.com>
 *
 * This file not a typical h file, is defines the uavcan parameters
 * uses in the system and may be included several times in header or source
 * file
 *
 *
 * Single parameter value.
 *
 * This is a union, which means that this structure can contain either one of the fields below.
 * The structure is prefixed with tag - a selector value that indicates which particular field is encoded.
 *
 * int64        integer_value
 * float32      real_value         # 32-bit type is used to simplify implementation on low-end systems
 * uint8        boolean_value      # 8-bit value is used for alignment reasons
 * uint8[<=128] string_value       # Length prefix is exactly one byte long, which ensures proper alignment of payload
 */

/*                  varName             uavcan Name                     type            min              max            default */
define_uavcan_param(test_bool,          "3dr.int_bool",          uavcan_uint8,              0,              1,          1)
define_uavcan_param(test_int,           "3dr.int_test",          uavcan_int64,            -12,              12,          6 )
define_uavcan_param(test_float,         "3dr.float_test",        uavcan_float32,        1.412,             4.2,          12.1)
define_uavcan_param(test_string,        "3dr.string_test",       uavcan_string,             1,             128,         "default_value")
