/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_am2320_basic.h
 * @brief     driver am2320 basic header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-10-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/10/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_AM2320_BASIC_H
#define DRIVER_AM2320_BASIC_H

#include "driver_am2320_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup am2320_example_driver am2320 example driver function
 * @brief    am2320 example driver modules
 * @ingroup  am2320_driver
 * @{
 */

/**
 * @brief     basic example init
 * @param[in] interface is the chip interface
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t am2320_basic_init(am2320_interface_t interface);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t am2320_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *temperature points to a converted temperature buffer
 * @param[out] *humidity points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t am2320_basic_read(float *temperature, float *humidity);

/**
 * @brief     basic example set user reg1
 * @param[in] reg is the set reg value
 * @return    status code
 *            - 0 success
 *            - 1 set user reg1 failed
 * @note      only iic can use this function
 */
uint8_t am2320_basic_set_user_reg1(uint16_t reg);

/**
 * @brief      basic example get user reg1
 * @param[out] *reg points to a reg value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get user reg1 failed
 * @note       only iic can use this function
 */
uint8_t am2320_basic_get_user_reg1(uint16_t *reg);

/**
 * @brief     basic example set user reg2
 * @param[in] reg is the set reg value
 * @return    status code
 *            - 0 success
 *            - 1 set user reg2 failed
 * @note      only iic can use this function
 */
uint8_t am2320_basic_set_user_reg2(uint16_t reg);

/**
 * @brief      basic example get user reg2
 * @param[out] *reg points to a reg value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get user reg2 failed
 * @note       only iic can use this function
 */
uint8_t am2320_basic_get_user_reg2(uint16_t *reg);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
