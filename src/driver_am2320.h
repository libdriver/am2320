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
 * @file      driver_am2320.h
 * @brief     driver am2320 header file
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

#ifndef DRIVER_AM2320_H
#define DRIVER_AM2320_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup am2320_driver am2320 driver function
 * @brief    am2320 driver modules
 * @{
 */

/**
 * @addtogroup am2320_base_driver
 * @{
 */

/**
 * @brief am2320 interface enumeration definition
 */
typedef enum
{
    AM2320_INTERFACE_IIC  = 0x00,        /**< iic interface */
    AM2320_INTERFACE_GPIO = 0x01,        /**< gpio interface */
} am2320_interface_t;

/**
 * @brief am2320 handle structure definition
 */
typedef struct am2320_handle_s
{
    uint8_t (*iic_init)(void);                                                /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                              /**< point to an iic_deinit function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);       /**< point to an iic_write_cmd function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);        /**< point to an iic_read_cmd function address */
    uint8_t (*bus_init)(void);                                                /**< point to a bus_init function address */
    uint8_t (*bus_read)(uint8_t *value);                                      /**< point to a bus_read function address */
    uint8_t (*bus_write)(uint8_t value);                                      /**< point to a bus_write function address */
    uint8_t (*bus_deinit)(void);                                              /**< point to a bus_deinit function address */
    void (*delay_ms)(uint32_t ms);                                            /**< point to a delay_ms function address */
    void (*delay_us)(uint32_t us);                                            /**< point to a delay_us function address */
    void (*enable_irq)(void);                                                 /**< point to an enable_irq function address */
    void (*disable_irq)(void);                                                /**< point to a disable_irq function address */
    void (*debug_print)(const char *const fmt, ...);                          /**< point to a debug_print function address */
    uint8_t inited;                                                           /**< inited flag */
    uint8_t gpio_iic;                                                         /**< gpio iic interface */
} am2320_handle_t;

/**
 * @brief am2320 info structure definition
 */
typedef struct am2320_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[16];                /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} am2320_info_t;

/**
 * @}
 */

/**
 * @defgroup am2320_link_driver am2320 link driver function
 * @brief    am2320 link driver modules
 * @ingroup  am2320_driver
 * @{
 */

/**
 * @brief     initialize am2320_handle_t structure
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] STRUCTURE is am2320_handle_t
 * @note      none
 */
#define DRIVER_AM2320_LINK_INIT(HANDLE, STRUCTURE)              memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_IIC_INIT(HANDLE, FUC)               (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_IIC_DEINIT(HANDLE, FUC)             (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_IIC_WRITE_COMMAND(HANDLE, FUC)      (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_IIC_READ_COMMAND(HANDLE, FUC)       (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link bus_init function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to a bus_init function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_BUS_INIT(HANDLE, FUC)               (HANDLE)->bus_init = FUC

/**
 * @brief     link bus_deinit function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to a bus_deinit function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_BUS_DEINIT(HANDLE, FUC)             (HANDLE)->bus_deinit = FUC

/**
 * @brief     link bus_read function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to a bus_read function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_BUS_READ(HANDLE, FUC)               (HANDLE)->bus_read = FUC

/**
 * @brief     link bus_write function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to a bus_write function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_BUS_WRITE(HANDLE, FUC)              (HANDLE)->bus_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_DELAY_MS(HANDLE, FUC)               (HANDLE)->delay_ms = FUC

/**
 * @brief     link delay_us function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to a delay_us function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_DELAY_US(HANDLE, FUC)               (HANDLE)->delay_us = FUC

/**
 * @brief     link enable_irq function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to an enable_irq function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_ENABLE_IRQ(HANDLE, FUC)             (HANDLE)->enable_irq = FUC

/**
 * @brief     link disable_irq function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to a disable_irq function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_DISABLE_IRQ(HANDLE, FUC)            (HANDLE)->disable_irq = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an am2320 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_AM2320_LINK_DEBUG_PRINT(HANDLE, FUC)            (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup am2320_base_driver am2320 base driver function
 * @brief    am2320 base driver modules
 * @ingroup  am2320_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an am2320 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t am2320_info(am2320_info_t *info);

/**
 * @brief     set the chip interface
 * @param[in] *handle points to an am2320 handle structure
 * @param[in] interface is the chip interface
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t am2320_set_interface(am2320_handle_t *handle, am2320_interface_t interface);

/**
 * @brief      get the chip interface
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *interface points to a chip interface buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t am2320_get_interface(am2320_handle_t *handle, am2320_interface_t *interface);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an am2320 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 bus initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 * @note      none
 */
uint8_t am2320_init(am2320_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an am2320 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 bus deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t am2320_deinit(am2320_handle_t *handle);

/**
 * @brief      read the temperature and humidity data
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *temperature_raw points to a raw temperature buffer
 * @param[out] *temperature_s points to a converted temperature buffer
 * @param[out] *humidity_raw points to a raw humidity buffer
 * @param[out] *humidity_s points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t am2320_read_temperature_humidity(am2320_handle_t *handle, uint16_t *temperature_raw, float *temperature_s, uint16_t *humidity_raw, float *humidity_s);

/**
 * @brief      read the humidity data
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *raw points to a raw humidity buffer
 * @param[out] *s points to a converted humidity buffer
 * @return     status code
 *             - 0 success
 *             - 1 read humidity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t am2320_read_humidity(am2320_handle_t *handle, uint16_t *raw, float *s);

/**
 * @brief      read the temperature data
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *raw points to a raw temperature buffer
 * @param[out] *s points to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t am2320_read_temperature(am2320_handle_t *handle, uint16_t *raw, float *s);

/**
 * @brief      get device type
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *type points to a type buffer
 * @return     status code
 *             - 0 success
 *             - 1 get device type failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 gpio can't use this function
 * @note       only iic can use this function
 */
uint8_t am2320_get_device_type(am2320_handle_t *handle, uint16_t *type);

/**
 * @brief      get version
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *version points to a version buffer
 * @return     status code
 *             - 0 success
 *             - 1 get version failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 gpio can't use this function
 * @note       only iic can use this function
 */
uint8_t am2320_get_version(am2320_handle_t *handle, uint8_t *version);

/**
 * @brief      get status
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *status points to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 gpio can't use this function
 * @note       only iic can use this function
 */
uint8_t am2320_get_status(am2320_handle_t *handle, uint8_t *status);

/**
 * @brief      get device id
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *id points to an id buffer
 * @return     status code
 *             - 0 success
 *             - 1 get device id failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 gpio can't use this function
 * @note       only iic can use this function
 */
uint8_t am2320_get_device_id(am2320_handle_t *handle, uint32_t *id);

/**
 * @brief     set user reg1
 * @param[in] *handle points to an am2320 handle structure
 * @param[in] reg is the set reg
 * @return    status code
 *            - 0 success
 *            - 1 set user reg1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 gpio can't use this function
 * @note      only iic can use this function
 */
uint8_t am2320_set_user_reg1(am2320_handle_t *handle, uint16_t reg);

/**
 * @brief      get user reg1
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *reg points to a reg buffer
 * @return     status code
 *             - 0 success
 *             - 1 get user reg1 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 gpio can't use this function
 * @note       only iic can use this function
 */
uint8_t am2320_get_user_reg1(am2320_handle_t *handle, uint16_t *reg);

/**
 * @brief     set user reg2
 * @param[in] *handle points to an am2320 handle structure
 * @param[in] reg is the set reg
 * @return    status code
 *            - 0 success
 *            - 1 set user reg2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 gpio can't use this function
 * @note      only iic can use this function
 */
uint8_t am2320_set_user_reg2(am2320_handle_t *handle, uint16_t reg);

/**
 * @brief      get user reg2
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *reg points to a reg buffer
 * @return     status code
 *             - 0 success
 *             - 1 get user reg2 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 gpio can't use this function
 * @note       only iic can use this function
 */
uint8_t am2320_get_user_reg2(am2320_handle_t *handle, uint16_t *reg);

/**
 * @}
 */

/**
 * @defgroup am2320_extern_driver am2320 extern driver function
 * @brief    am2320 extern driver modules
 * @ingroup  am2320_driver
 * @{
 */

/**
 * @brief      set and get the register value
 * @param[in]  *handle points to an am2320 handle structure
 * @param[in]  *input_buf points to an input data buffer
 * @param[in]  input_len is the length of the input data buffer
 * @param[out] *output_buf points to an output data buffer
 * @param[in]  output_len is the length of the output data buffer
 * @return     status code
 *             - 0 success
 *             - 1 set get reg failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 gpio can't use this function
 * @note       only iic can use this function
 */
uint8_t am2320_set_get_reg(am2320_handle_t *handle, uint8_t *input_buf, uint16_t input_len, uint8_t *output_buf, uint16_t output_len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
