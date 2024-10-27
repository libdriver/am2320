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
 * @file      driver_am2320_basic.c
 * @brief     driver am2320 basic source file
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

#include "driver_am2320_basic.h"

static am2320_handle_t gs_handle;        /**< am2320 handle */

/**
 * @brief     basic example init
 * @param[in] interface is the chip interface
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t am2320_basic_init(am2320_interface_t interface)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_AM2320_LINK_INIT(&gs_handle, am2320_handle_t);
    DRIVER_AM2320_LINK_BUS_INIT(&gs_handle, am2320_interface_bus_init);
    DRIVER_AM2320_LINK_BUS_DEINIT(&gs_handle, am2320_interface_bus_deinit);
    DRIVER_AM2320_LINK_BUS_READ(&gs_handle, am2320_interface_bus_read);
    DRIVER_AM2320_LINK_BUS_WRITE(&gs_handle, am2320_interface_bus_write);
    DRIVER_AM2320_LINK_IIC_INIT(&gs_handle, am2320_interface_iic_init);
    DRIVER_AM2320_LINK_IIC_DEINIT(&gs_handle, am2320_interface_iic_deinit);
    DRIVER_AM2320_LINK_IIC_WRITE_COMMAND(&gs_handle, am2320_interface_iic_write_cmd);
    DRIVER_AM2320_LINK_IIC_READ_COMMAND(&gs_handle, am2320_interface_iic_read_cmd);
    DRIVER_AM2320_LINK_DELAY_MS(&gs_handle, am2320_interface_delay_ms);
    DRIVER_AM2320_LINK_DELAY_US(&gs_handle, am2320_interface_delay_us);
    DRIVER_AM2320_LINK_ENABLE_IRQ(&gs_handle, am2320_interface_enable_irq);
    DRIVER_AM2320_LINK_DISABLE_IRQ(&gs_handle, am2320_interface_disable_irq);
    DRIVER_AM2320_LINK_DEBUG_PRINT(&gs_handle, am2320_interface_debug_print);
    
    /* set interface */
    res = am2320_set_interface(&gs_handle, interface);
    if (res != 0)
    {
        am2320_interface_debug_print("am2320: set interface.\n");
        
        return 1;
    }
    
    /* am2320 init */
    res = am2320_init(&gs_handle);
    if (res != 0)
    {
        am2320_interface_debug_print("am2320: init failed.\n");
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *temperature points to a converted temperature buffer
 * @param[out] *humidity points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t am2320_basic_read(float *temperature, float *humidity)
{
    uint16_t temperature_raw;
    uint16_t humidity_raw;
    
    /* read temperature and humidity */
    if (am2320_read_temperature_humidity(&gs_handle, (uint16_t *)&temperature_raw, temperature, 
                                        (uint16_t *)&humidity_raw, humidity) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t am2320_basic_deinit(void)
{
    /* deinit am2320 and close bus */
    if (am2320_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set user reg1
 * @param[in] reg is the set reg value
 * @return    status code
 *            - 0 success
 *            - 1 set user reg1 failed
 * @note      only iic can use this function
 */
uint8_t am2320_basic_set_user_reg1(uint16_t reg)
{
    /* set user reg1 */
    if (am2320_set_user_reg1(&gs_handle, reg) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get user reg1
 * @param[out] *reg points to a reg value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get user reg1 failed
 * @note       only iic can use this function
 */
uint8_t am2320_basic_get_user_reg1(uint16_t *reg)
{
    /* get user reg1 */
    if (am2320_get_user_reg1(&gs_handle, reg) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set user reg2
 * @param[in] reg is the set reg value
 * @return    status code
 *            - 0 success
 *            - 1 set user reg2 failed
 * @note      only iic can use this function
 */
uint8_t am2320_basic_set_user_reg2(uint16_t reg)
{
    /* set user reg2 */
    if (am2320_set_user_reg2(&gs_handle, reg) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get user reg2
 * @param[out] *reg points to a reg value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get user reg2 failed
 * @note       only iic can use this function
 */
uint8_t am2320_basic_get_user_reg2(uint16_t *reg)
{
    /* get user reg2 */
    if (am2320_get_user_reg2(&gs_handle, reg) != 0)
    {
        return 1;
    }
    
    return 0;
}
