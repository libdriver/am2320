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
 * @file      raspberrypi4b_driver_am2320_interface.c
 * @brief     raspberrypi4b driver am2320 interface source file
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

#include "driver_am2320_interface.h"
#include "wire.h"
#include "iic.h"
#include <sys/time.h>
#include <stdarg.h>

/**
 * @brief iic device name definition
 */
#define IIC_DEVICE_NAME "/dev/i2c-1"        /**< iic device name */

/**
 * @brief iic device handle definition
 */
static int gs_fd;                           /**< iic handle */

/**
 * @brief  interface bus init
 * @return status code
 *         - 0 success
 *         - 1 bus init failed
 * @note   none
 */
uint8_t am2320_interface_bus_init(void)
{
    return wire_init();
}

/**
 * @brief  interface bus deinit
 * @return status code
 *         - 0 success
 *         - 1 bus deinit failed
 * @note   none
 */
uint8_t am2320_interface_bus_deinit(void)
{
    return wire_deinit();
}

/**
 * @brief      interface bus read
 * @param[out] *value points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t am2320_interface_bus_read(uint8_t *value)
{
    return wire_read(value);
}

/**
 * @brief     interface bus write
 * @param[in] value is the written value
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t am2320_interface_bus_write(uint8_t value)
{
    return wire_write(value);
}

/**
 * @brief  interface iic init
 * @return status code
 *         - 0 success
 *         - 1 iic init failed
 * @note   none
 */
uint8_t am2320_interface_iic_init(void)
{
    return iic_init(IIC_DEVICE_NAME, &gs_fd);
}

/**
 * @brief  interface iic deinit
 * @return status code
 *         - 0 success
 *         - 1 iic deinit failed
 * @note   none
 */
uint8_t am2320_interface_iic_deinit(void)
{
    return iic_deinit(gs_fd);
}

/**
 * @brief      interface iic read command
 * @param[in]  addr is the iic device write address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t am2320_interface_iic_read_cmd(uint8_t addr, uint8_t *buf, uint16_t len)
{
    return iic_read_cmd(gs_fd, addr, buf, len);
}

/**
 * @brief     interface iic write command
 * @param[in] addr is the iic device write address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t am2320_interface_iic_write_cmd(uint8_t addr, uint8_t *buf, uint16_t len)
{
    if (len == 0)
    {
        iic_write_cmd(gs_fd, addr, buf, len);
        
        am2320_interface_delay_us(1000);

        return 0;
    }
    else
    {
        return iic_write_cmd(gs_fd, addr, buf, len);
    }
}

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void am2320_interface_delay_ms(uint32_t ms)
{
    am2320_interface_delay_us(ms * 1000);
}

/**
 * @brief     interface delay us
 * @param[in] us
 * @note      none
 */
void am2320_interface_delay_us(uint32_t us)
{
    struct timeval now;
    struct timeval before;
    
    /* get the before time */
    if (gettimeofday(&before, NULL) < 0)
    {
        return;
    }
    
    /* loop */
    while (1)
    {
        /* get time */
        if (gettimeofday(&now, NULL) < 0)
        {
            return;
        }
        
        /* check the time */
        if ((now.tv_sec - before.tv_sec) * 1000 * 1000 + (now.tv_usec - before.tv_usec) >= us)
        {
            break;
        }
    }
}

/**
 * @brief interface enable the interrupt
 * @note  none
 */
void am2320_interface_enable_irq(void)
{
    return;
}

/**
 * @brief interface disable the interrupt
 * @note  none
 */
void am2320_interface_disable_irq(void)
{
    return;
}

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void am2320_interface_debug_print(const char *const fmt, ...)
{
    char str[256];
    uint16_t len;
    va_list args;
    
    memset((char *)str, 0, sizeof(char) * 256); 
    va_start(args, fmt);
    vsnprintf((char *)str, 255, (char const *)fmt, args);
    va_end(args);
    
    len = strlen((char *)str);
    (void)printf((uint8_t *)str, len);
}
