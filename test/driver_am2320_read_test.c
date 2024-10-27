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
 * @file      driver_am2320_read_test.c
 * @brief     driver am2320 read test source file
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

#include "driver_am2320_read_test.h"
#include <stdlib.h>

static am2320_handle_t gs_handle;        /**< am2320 handle */

/**
 * @brief     read test
 * @param[in] interface is the chip interface
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 read failed
 * @note      none
 */
uint8_t am2320_read_test(am2320_interface_t interface, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    uint16_t temperature_raw;
    uint16_t humidity_raw;
    float temperature;
    float humidity;
    am2320_info_t info;
   
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

    /* get am2320 information */
    res = am2320_info(&info);
    if (res != 0)
    {
        am2320_interface_debug_print("am2320: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print am2320 information */
        am2320_interface_debug_print("am2320: chip is %s.\n", info.chip_name);
        am2320_interface_debug_print("am2320: manufacturer is %s.\n", info.manufacturer_name);
        am2320_interface_debug_print("am2320: interface is %s.\n", info.interface);
        am2320_interface_debug_print("am2320: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        am2320_interface_debug_print("am2320: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        am2320_interface_debug_print("am2320: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        am2320_interface_debug_print("am2320: max current is %0.2fmA.\n", info.max_current_ma);
        am2320_interface_debug_print("am2320: max temperature is %0.1fC.\n", info.temperature_max);
        am2320_interface_debug_print("am2320: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start basic read test */
    am2320_interface_debug_print("am2320: start read test.\n");
    
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
    
    if (interface == AM2320_INTERFACE_IIC)
    {
        uint8_t status;
        uint8_t version;
        uint16_t type;
        uint16_t reg;
        uint16_t reg_check;
        uint32_t id;
        
        /* get device type */
        res = am2320_get_device_type(&gs_handle, &type);
        if (res != 0)
        {
            am2320_interface_debug_print("am2320: get device type failed.\n");
            (void)am2320_deinit(&gs_handle);
           
            return 1;
        }
        
        /* print result */
        am2320_interface_debug_print("am2320: type is 0x%04X.\n", type);
        
        /* delay 2000 ms*/
        am2320_interface_delay_ms(2000);
        
        /* get version */
        res = am2320_get_version(&gs_handle, &version);
        if (res != 0)
        {
            am2320_interface_debug_print("am2320: get version failed.\n");
            (void)am2320_deinit(&gs_handle);
           
            return 1;
        }
        
        /* print result */
        am2320_interface_debug_print("am2320: version is 0x%02X.\n", version);
        
        /* delay 2000 ms*/
        am2320_interface_delay_ms(2000);
        
        /* get status */
        res = am2320_get_status(&gs_handle, &status);
        if (res != 0)
        {
            am2320_interface_debug_print("am2320: get status failed.\n");
            (void)am2320_deinit(&gs_handle);
           
            return 1;
        }
        
        /* print result */
        am2320_interface_debug_print("am2320: status is 0x%02X.\n", status);
        
        /* delay 2000 ms*/
        am2320_interface_delay_ms(2000);
        
        /* get device id */
        res = am2320_get_device_id(&gs_handle, &id);
        if (res != 0)
        {
            am2320_interface_debug_print("am2320: get device id failed.\n");
            (void)am2320_deinit(&gs_handle);
           
            return 1;
        }
        
        /* print result */
        am2320_interface_debug_print("am2320: device id is 0x%08X.\n", id);
        
        /* delay 2000 ms*/
        am2320_interface_delay_ms(2000);
        
        reg = rand() % 0xFFFFUL;
        res = am2320_set_user_reg1(&gs_handle, reg);
        if (res != 0)
        {
            am2320_interface_debug_print("am2320: set user reg1 failed.\n");
            (void)am2320_deinit(&gs_handle);
           
            return 1;
        }
        am2320_interface_debug_print("am2320: set user reg1 0x%04X.\n", reg);
        
        /* delay 2000 ms*/
        am2320_interface_delay_ms(2000);
        
        /* get user reg1 */
        res = am2320_get_user_reg1(&gs_handle, &reg_check);
        if (res != 0)
        {
            am2320_interface_debug_print("am2320: get user reg1 failed.\n");
            (void)am2320_deinit(&gs_handle);
           
            return 1;
        }
        
        am2320_interface_debug_print("am2320: check reg1 %s.\n", reg == reg_check ? "ok" : "error");
        
        /* delay 2000 ms*/
        am2320_interface_delay_ms(2000);
        
        reg = rand() % 0xFFFFUL;
        res = am2320_set_user_reg2(&gs_handle, reg);
        if (res != 0)
        {
            am2320_interface_debug_print("am2320: set user reg2 failed.\n");
            (void)am2320_deinit(&gs_handle);
           
            return 1;
        }
        am2320_interface_debug_print("am2320: set user reg2 0x%04X.\n", reg);
        
        /* delay 2000 ms*/
        am2320_interface_delay_ms(2000);
        
        /* get user reg2 */
        res = am2320_get_user_reg2(&gs_handle, &reg_check);
        if (res != 0)
        {
            am2320_interface_debug_print("am2320: get user reg2 failed.\n");
            (void)am2320_deinit(&gs_handle);
           
            return 1;
        }
        
        am2320_interface_debug_print("am2320: check reg2 %s.\n", reg == reg_check ? "ok" : "error");
    }
    
    /* output */
    am2320_interface_debug_print("am2320: read temperature and humidity.\n");
    
    /* delay 2000 ms for read */
    am2320_interface_delay_ms(2000);
    
    for (i = 0; i < times; i++)
    {
        /* read temperature and humidity */
        res = am2320_read_temperature_humidity(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature, 
                                              (uint16_t *)&humidity_raw, (float *)&humidity);
        if (res != 0)
        {
            am2320_interface_debug_print("am2320: read failed.\n");
            (void)am2320_deinit(&gs_handle);
           
            return 1;
        }
        
        /* print result */
        am2320_interface_debug_print("am2320: temperature: %.01fC.\n", temperature);
        am2320_interface_debug_print("am2320: humidity: %.01f%%.\n", humidity);

        /* delay 2000 ms*/
        am2320_interface_delay_ms(2000);
    }
    
    /* output */
    am2320_interface_debug_print("am2320: read temperature.\n");
    
    /* delay 2000 ms for read */
    am2320_interface_delay_ms(2000);
    
    for (i = 0; i < times; i++)
    {
        /* read temperature */
        res = am2320_read_temperature(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature);
        if (res != 0)
        {
            am2320_interface_debug_print("am2320: read failed.\n");
            (void)am2320_deinit(&gs_handle);
           
            return 1;
        }
    
        /* print result */
        am2320_interface_debug_print("am2320: temperature: %.01fC.\n", temperature);

        /* delay 2000 ms*/
        am2320_interface_delay_ms(2000);
    }
    
    /* output */
    am2320_interface_debug_print("am2320: read humidity.\n");
    
    /* delay 2000 ms for read */
    am2320_interface_delay_ms(2000);
    
    for (i = 0; i < times; i++)
    {
        /* read humidity */
        res = am2320_read_humidity(&gs_handle, (uint16_t *)&humidity_raw, (float *)&humidity);
        if (res != 0)
        {
            am2320_interface_debug_print("am2320: read failed.\n");
            (void)am2320_deinit(&gs_handle);
           
            return 1;
        }
    
        /* print result */
        am2320_interface_debug_print("am2320: humidity: %.01f%%.\n", humidity);

        /* delay 2000 ms*/
        am2320_interface_delay_ms(2000);
    }
    
    /* finish read test and exit */
    am2320_interface_debug_print("am2320: finish read test.\n");
    (void)am2320_deinit(&gs_handle);
    
    return 0;
}
