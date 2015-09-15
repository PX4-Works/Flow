/****************************************************************************
 *
 *   Copyright (C) 2013 PX4 Development Team. All rights reserved.
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
#include <px4_macros.h>
#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"

TODO(Need to inject board.h or board_config.h via symlink);

#define STM32_PCLK1_FREQUENCY (168000000ul/4)
#define STM32_TIMCLK1          (2*STM32_PCLK1_FREQUENCY)

TODO(STM32_SYSMEM_FSIZE should be in the SPL);
#define STM32_SYSMEM_UID     0x1fff7a10     /* The 96-bit unique device identifier */

#define CONFIG_STM32_FLASH_CONFIG_I
#define CONFIG_STM32_STM32F40XX
#define CONFIG_STM32_STM32F427
#define STM32_FLASH_BASE 0x8000000

#define STM32_RCC_BASE       0x40023800     /* 0x40023800-0x40023bff: Reset and Clock control RCC */
#define STM32_RCC_CR_OFFSET         0x0000  /* Clock control register */

#define STM32_FLASHIF_BASE   0x40023c00     /* 0x40023c00-0x40023fff: Flash memory interface */

#define getreg32(addr) (*(uint32_t *)(addr))
#define putreg32(regval, addr) ((*(uint32_t *)(addr)) = (regval))
#define getreg16(addr) (*(uint16_t *)(addr))
#define putreg16(regval, addr) ((*(uint16_t *)(addr)) = (regval))
#define getreg8(addr) (*(uint8_t *)(addr))
#define putreg8(regval, addr) ((*(uint8_t *)(addr)) = (regval))
