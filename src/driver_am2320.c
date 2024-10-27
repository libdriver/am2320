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
 * @file      driver_am2320.c
 * @brief     driver am2320 source file
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

#include "driver_am2320.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                "ASAIR AM2320"        /**< chip name */
#define MANUFACTURER_NAME        "ASAIR"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN       3.1f                  /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX       5.5f                  /**< chip max supply voltage */
#define MAX_CURRENT              0.95f                 /**< chip max current */
#define TEMPERATURE_MIN          -20.0f                /**< chip min operating temperature */
#define TEMPERATURE_MAX          60.0f                 /**< chip max operating temperature */
#define DRIVER_VERSION           1000                  /**< driver version */

/**
 * @brief chip address definition
 */
#define AM2320_ADDRESS             0xB8                /**< chip iic address */

/**
 * @brief modbus address definition
 */
#define AM2320_MODBUS_ADDRESS_HUMI_MSB             0x00        /**< humi msb */
#define AM2320_MODBUS_ADDRESS_HUMI_LSB             0x01        /**< humi lsb */
#define AM2320_MODBUS_ADDRESS_TEMP_MSB             0x02        /**< temp msb */
#define AM2320_MODBUS_ADDRESS_TEMP_LSB             0x03        /**< temp lsb */
#define AM2320_MODBUS_ADDRESS_DEVICE_TYPE_MSB      0x08        /**< device type msb */
#define AM2320_MODBUS_ADDRESS_DEVICE_TYPE_LSB      0x09        /**< device type lsb */
#define AM2320_MODBUS_ADDRESS_VERSION              0x0A        /**< version */
#define AM2320_MODBUS_ADDRESS_DEVICE_3             0x0B        /**< device id 3 */
#define AM2320_MODBUS_ADDRESS_DEVICE_2             0x0C        /**< device id 2 */
#define AM2320_MODBUS_ADDRESS_DEVICE_1             0x0D        /**< device id 1 */
#define AM2320_MODBUS_ADDRESS_DEVICE_0             0x0E        /**< device id 0 */
#define AM2320_MODBUS_ADDRESS_STATUS               0x0F        /**< status */
#define AM2320_MODBUS_ADDRESS_USER_REG1_MSB        0x10        /**< user reg1 msb */
#define AM2320_MODBUS_ADDRESS_USER_REG1_LSB        0x11        /**< user reg1 lsb */
#define AM2320_MODBUS_ADDRESS_USER_REG2_MSB        0x12        /**< user reg2 msb */
#define AM2320_MODBUS_ADDRESS_USER_REG2_LSB        0x13        /**< user reg2 lsb */

/**
 * @brief crc16 table high definition
 */
static const uint8_t gs_crc_table_hi[] =
{
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40
};

/**
 * @brief crc16 table low definition
 */
static const uint8_t gs_crc_table_lo[] =
{
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5,
    0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B,
    0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE,
    0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6,
    0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8,
    0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C,
    0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21,
    0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A,
    0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7,
    0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91, 0x51,
    0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
    0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D,
    0x4C, 0x8C, 0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40
};

/**
 * @brief     generate the crc16
 * @param[in] *data points to a data buffer
 * @param[in] count is the data length
 * @return    crc
 * @note      none
 */
static uint16_t a_am2320_generate_crc16(uint8_t *data, uint16_t count) 
{
    uint8_t crc_hi = 0xFF;
    uint8_t crc_lo = 0xFF;
    uint8_t i;

    while (count--)                                  /* count-- */
    {
        i = crc_lo ^ *data++;                        /* get index */
        crc_lo = crc_hi ^ gs_crc_table_hi[i];        /* get crc lo */
        crc_hi = gs_crc_table_lo[i];                 /* get crc hi */
    }

    return ((uint16_t)crc_hi << 8 | crc_lo);         /* return crc16 */
}

/**
 * @brief     reset the chip
 * @param[in] *handle points to an am2320 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 no response
 * @note      none
 */
static uint8_t a_am2320_reset(am2320_handle_t *handle)
{
    uint8_t retry = 0;
    uint8_t res;
    uint8_t value;
    
    res = handle->bus_write(0);                                      /* set low */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("am2320: bus write 0 failed.\n");        /* write failed */
        
        return 1;                                                    /* return error */
    }
    handle->delay_ms(1);                                             /* wait 1ms */
    handle->disable_irq();                                           /* disable interrupt */
    res = handle->bus_write(1);                                      /* set high */
    if (res != 0)                                                    /* check result */
    {
        handle->enable_irq();                                        /* enable interrupt */
        handle->debug_print("am2320: bus write 1 failed.\n");        /* write failed */
        
        return 1;                                                    /* return error */
    }
    handle->delay_us(30);                                            /* wait 20-40us */
    res = handle->bus_read((uint8_t *)&value);                       /* read 1 bit */
    if (res != 0)                                                    /* check result */
    {
        handle->enable_irq();                                        /* enable interrupt */
        handle->debug_print("am2320: bus read failed.\n");           /* read failed */
        
        return 1;                                                    /* return error */
    }
    while ((value != 0) && (retry < 100))                            /* wait 40-80us */
    {
        res = handle->bus_read((uint8_t *)&value);                   /* read 1 bit */
        if (res != 0)                                                /* check result */
        {
            handle->enable_irq();                                    /* enable interrupt */
            handle->debug_print("am2320: bus read failed.\n");       /* read failed */
            
            return 1;                                                /* return error */
        }
        retry++;                                                     /* retry times++ */
        handle->delay_us(1);                                         /* delay 1us */
    }
    if (retry >= 100)                                                /* if retry times is over 100 times */
    {
        handle->enable_irq();                                        /* enable interrupt */
        handle->debug_print("am2320: bus no response.\n");           /* no response */
        
        return 1;                                                    /* return error */
    }
    else
    {
        retry = 0;                                                   /* reset retry times */
    }
    res = handle->bus_read((uint8_t *)&value);                       /* read 1 bit */
    if (res != 0)                                                    /* check result */
    {
        handle->enable_irq();                                        /* enable interrupt */
        handle->debug_print("am2320: bus read failed.\n");           /* read failed */
        
        return 1;                                                    /* return error */
    }
    while ((!value) && (retry < 100))                                /* wait for 40-80us */
    {
        res = handle->bus_read((uint8_t *)&value);                   /* read 1 bit */
        if (res != 0)                                                /* check result */
        {
            handle->enable_irq();                                    /* enable interrupt */
            handle->debug_print("am2320: bus read failed.\n");       /* read failed */
            
            return 1;                                                /* return error */
        }
        retry++;                                                     /* retry times++ */
        handle->delay_us(1);                                         /* delay 1 us */
    }
    if (retry >= 100)                                                /* if retry times is over 100 times */
    { 
        handle->enable_irq();                                        /* enable interrupt */
        handle->debug_print("am2320: bus no response.\n");           /* no response */
        
        return 1;                                                    /* return error */
    }
    handle->enable_irq();                                            /* enable interrupt */
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      read one bit
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *value points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_am2320_read_bit(am2320_handle_t *handle, uint8_t *value)
{
    uint8_t retry = 0;
    uint8_t res;
    
    res = handle->bus_read((uint8_t *)value);                        /* read 1 bit */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("am2320: bus read failed.\n");           /* read failed */
        
        return 1;                                                    /* return error */
    }
    while (((*value) != 0) && (retry < 100))                         /* wait 100us */
    {
        res = handle->bus_read((uint8_t *)value);                    /* read 1 bit */
        if (res != 0)                                                /* check result */
        {
            handle->debug_print("am2320: bus read failed.\n");       /* read failed */
            
            return 1;                                                /* return error */
        }
        retry++;                                                     /* retry times++ */
        handle->delay_us(1);                                         /* delay 1 us */
    }
    retry = 0;                                                       /* reset retry times */
    res = handle->bus_read((uint8_t *)value);                        /* read 1 bit */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("am2320: bus read failed.\n");           /* read failed */
        
        return 1;                                                    /* return error */
    }
    while ((!(*value)) && (retry < 100))                             /* wait 100us */
    {
        res = handle->bus_read((uint8_t *)value);                    /* read 1 bit */
        if (res != 0)                                                /* check result */
        {
            handle->debug_print("am2320: bus read failed.\n");       /* read failed */
            
            return 1;                                                /* return error */
        }
        retry++;                                                     /* retry times++ */
        handle->delay_us(1);                                         /* wait 1 us */
    }
    handle->delay_us(40);                                            /* wait 40us */
    res = handle->bus_read((uint8_t *)value);                        /* read 1 bit */
    if (res != 0)                                                    /* check result */
    {
        handle->debug_print("am2320: bus read failed.\n");           /* read failed */
        
        return 1;                                                    /* return error */
    }
    else
    {
        return 0;                                                    /* success return 0 */
    }
}

/**
 * @brief      read one byte
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *byte points to a byte buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_am2320_read_byte(am2320_handle_t *handle, uint8_t *byte)
{
    uint8_t i;
    uint8_t res;
    uint8_t value;
    
    *byte = 0;                                                       /* set byte 0 */
    for (i = 0; i < 8; i++)                                          /* read 8 bits */
    {
        *byte <<= 1;                                                 /* left shift 1 bit */
        res = a_am2320_read_bit(handle, (uint8_t *)&value);          /* read 1 bit */
        if (res != 0)                                                /* check result */
        {
            handle->debug_print("am2320: bus read failed.\n");       /* read failed */
            
            return 1;                                                /* return error */
        }
        *byte |= value;                                              /* set LSB */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     set the chip interface
 * @param[in] *handle points to an am2320 handle structure
 * @param[in] interface is the chip interface
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t am2320_set_interface(am2320_handle_t *handle, am2320_interface_t interface)
{
    if (handle == NULL)                          /* check handle */
    {
        return 2;                                /* return error */
    }
    
    handle->gpio_iic = (uint8_t)interface;       /* set interface */
    
    return 0;                                    /* success return 0 */
}

/**
 * @brief      get the chip interface
 * @param[in]  *handle points to an am2320 handle structure
 * @param[out] *interface points to a chip interface buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t am2320_get_interface(am2320_handle_t *handle, am2320_interface_t *interface)
{
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    
    *interface = (am2320_interface_t)(handle->gpio_iic);        /* get interface */
    
    return 0;                                                   /* success return 0 */
}

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
uint8_t am2320_read_humidity(am2320_handle_t *handle, uint16_t *raw, float *s)
{
    uint8_t buf[5];
    uint8_t i;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                      /* gpio */
    {
        if (a_am2320_reset(handle) == 0)                                            /* reset the chip */
        {
            handle->disable_irq();                                                  /* disable interrupt */
            for (i = 0; i < 5; i++)                                                 /* read 5 bytes */
            {
                if (a_am2320_read_byte(handle, (uint8_t *)&buf[i]) != 0)            /* read each byte */
                {
                    handle->enable_irq();                                           /* enable interrupt */
                    handle->debug_print("am2320: read byte failed.\n");             /* read failed */
                    
                    return 1;                                                       /* return error */
                }
            }
            handle->enable_irq();                                                   /* enable interrupt */
            if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])                      /* calculate checksum */
            {
                *raw = (uint16_t)buf[0] << 8 | buf[1];                              /* get raw data */
                *s = (float)(*raw) / 10.0f;                                         /* convert raw data to real data */
                
                return 0;                                                           /* success return 0 */
            }
            else
            {
                handle->debug_print("am2320: data check failed.\n");                /* checksum error */
                
                return 1;                                                           /* return error */
            }
        }
        else
        {
            handle->debug_print("am2320: reset failed.\n");                         /* reset failed */
            
            return 1;                                                               /* return error */
        }
    }
    else                                                                            /* iic */
    {
        uint8_t res;
        uint8_t input_buf[3];
        uint8_t out_buf[6];
        uint16_t crc16;
        
        (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
        input_buf[0] = 0x03;                                                        /* set function code */
        input_buf[1] = AM2320_MODBUS_ADDRESS_HUMI_MSB;                              /* set addr */
        input_buf[2] = 0x02;                                                        /* set number */
        res = handle->iic_write_cmd(AM2320_ADDRESS, (uint8_t *)input_buf, 3);       /* write command */
        if (res != 0)                                                               /* check result */
        {
            handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
           
            return 1;                                                               /* return error */
        }
        handle->delay_ms(2);                                                        /* delay 2ms */
        res = handle->iic_read_cmd(AM2320_ADDRESS, (uint8_t *)out_buf, 6);          /* read command */
        if (res != 0)                                                               /* check result */
        {
            handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
           
            return 1;                                                               /* return error */
        }
        crc16 = ((uint16_t)out_buf[5] << 8 | (uint16_t)out_buf[4]);                 /* get crc16 */
        if (crc16 != a_am2320_generate_crc16(out_buf, 4))                           /* check crc16 */
        {
            handle->debug_print("am2320: crc check error.\n");                      /* crc check error */
           
            return 1;                                                               /* return error */
        }
        if (out_buf[0] != 0x03)                                                     /* check code */
        {
            handle->debug_print("am2320: code is invalid.\n");                      /* code is invalid */
           
            return 1;                                                               /* return error */
        }
        if (out_buf[1] != 0x02)                                                     /* check number */
        {
            handle->debug_print("am2320: number is invalid.\n");                    /* number is invalid */
           
            return 1;                                                               /* return error */
        }
        *raw = (uint16_t)out_buf[2] << 8 | out_buf[3];                              /* get humidity raw */
        *s = (float)(*raw) / 10.0f;                                                 /* convert humidity raw data to real data */
        
        return 0;                                                                   /* success return 0 */
    }
}

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
uint8_t am2320_read_temperature_humidity(am2320_handle_t *handle, uint16_t *temperature_raw, float *temperature_s, uint16_t *humidity_raw, float *humidity_s)
{
    uint8_t buf[5];
    uint8_t i;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                      /* gpio */
    {
        if (a_am2320_reset(handle) == 0)                                            /* reset the chip */
        {
            handle->disable_irq();                                                  /* disable interrupt */
            for (i = 0; i < 5; i++)                                                 /* read 5 bytes */
            {
                if (a_am2320_read_byte(handle, (uint8_t *)&buf[i]) != 0)            /* read each byte */
                {
                    handle->enable_irq();                                           /* enable interrupt */
                    handle->debug_print("am2320: read byte failed.\n");             /* read failed */
                    
                    return 1;                                                       /* return error */
                }
            }
            handle->enable_irq();                                                   /* enable interrupt */
            if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])                      /* calculate checksum */
            {
                if ((buf[2] & (1 << 7)) != 0)                                       /* if temperature is below zero */
                {
                    *temperature_raw = (uint16_t)buf[2] << 8 | buf[3];              /* get temperature raw data */
                    *temperature_s= (float)((buf[2] & ~(1 << 7)) * 256 + 
                                             buf[3]) / 10.0f * (-1.0f);             /* convert temperature raw data to temperature real data */
                }
                else
                {
                    *temperature_raw = (uint16_t)buf[2] << 8 | buf[3];              /* get temperature raw data */
                    *temperature_s= (float)(buf[2] * 256 + buf[3]) / 10.0f;         /* convert temperature raw data to temperature real data */
                }
                *humidity_raw = (uint16_t)buf[0] << 8 | buf[1];                     /* get humidity raw */
                *humidity_s = (float)(*humidity_raw) / 10.0f;                       /* convert humidity raw data to real data */
                
                return 0;                                                           /* success return 0 */
            }
            else
            {
                handle->debug_print("am2320: data check failed.\n");                /* checksum error */
                
                return 1;                                                           /* return error */
            }
        }
        else
        {
            handle->debug_print("am2320: reset failed.\n");                         /* reset failed */
            
            return 1;                                                               /* return error */
        }
    }
    else                                                                            /* iic */
    {
        uint8_t res;
        uint8_t input_buf[3];
        uint8_t out_buf[8];
        uint16_t crc16;
        
        (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
        input_buf[0] = 0x03;                                                        /* set function code */
        input_buf[1] = AM2320_MODBUS_ADDRESS_HUMI_MSB;                              /* set addr */
        input_buf[2] = 0x04;                                                        /* set number */
        res = handle->iic_write_cmd(AM2320_ADDRESS, (uint8_t *)input_buf, 3);       /* write command */
        if (res != 0)                                                               /* check result */
        {
            handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
           
            return 1;                                                               /* return error */
        }
        handle->delay_ms(2);                                                        /* delay 2ms */
        res = handle->iic_read_cmd(AM2320_ADDRESS, (uint8_t *)out_buf, 8);          /* read command */
        if (res != 0)                                                               /* check result */
        {
            handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
           
            return 1;                                                               /* return error */
        }
        crc16 = ((uint16_t)out_buf[7] << 8 | (uint16_t)out_buf[6]);                 /* get crc16 */
        if (crc16 != a_am2320_generate_crc16(out_buf, 6))                           /* check crc16 */
        {
            handle->debug_print("am2320: crc check error.\n");                      /* crc check error */
           
            return 1;                                                               /* return error */
        }
        if (out_buf[0] != 0x03)                                                     /* check code */
        {
            handle->debug_print("am2320: code is invalid.\n");                      /* code is invalid */
           
            return 1;                                                               /* return error */
        }
        if (out_buf[1] != 0x04)                                                     /* check number */
        {
            handle->debug_print("am2320: number is invalid.\n");                    /* number is invalid */
           
            return 1;                                                               /* return error */
        }
        if ((out_buf[4] & (1 << 7)) != 0)                                           /* if temperature is below zero */
        {
            *temperature_raw = (uint16_t)out_buf[4] << 8 | out_buf[5];              /* get temperature raw data */
            *temperature_s= (float)((out_buf[4] & ~(1 << 7)) * 256 + 
                                     out_buf[5]) / 10.0f * (-1.0f);                 /* convert temperature raw data to temperature real data */
        }
        else
        {
            *temperature_raw = (uint16_t)out_buf[4] << 8 | out_buf[5];              /* get temperature raw data */
            *temperature_s= (float)(out_buf[4] * 256 + out_buf[5]) / 10.0f;         /* convert temperature raw data to temperature real data */
        }
        *humidity_raw = (uint16_t)out_buf[2] << 8 | out_buf[3];                     /* get humidity raw */
        *humidity_s = (float)(*humidity_raw) / 10.0f;                               /* convert humidity raw data to real data */
        
        return 0;                                                                   /* success return 0 */
    }
}

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
uint8_t am2320_read_temperature(am2320_handle_t *handle, uint16_t *raw, float *s)
{
    uint8_t buf[5];
    uint8_t i;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                      /* gpio */
    {
        if (a_am2320_reset(handle) == 0)                                            /* reset the chip */
        {
            handle->disable_irq();                                                  /* disable interrupt */
            for (i = 0; i < 5; i++)                                                 /* read 5 bytes */
            {
                if (a_am2320_read_byte(handle, (uint8_t *)&buf[i]) != 0)            /* read each byte */
                {
                    handle->enable_irq();                                           /* enable interrupt */
                    handle->debug_print("am2320: read byte failed.\n");             /* read failed */
                    
                    return 1;                                                       /* return error */
                }
            }
            handle->enable_irq();                                                   /* enable interrupt */
            if ((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4])                      /* calculate checksum */
            {
                if ((buf[2] & (1 << 7)) != 0)                                       /* if temperature is below zero */
                {
                    *raw = (uint16_t)buf[2] << 8 | buf[3];                          /* get temperature raw data */
                    *s= (float)((buf[2] & ~(1 << 7)) * 256 + 
                                 buf[3]) / 10.0f * (-1.0f);                         /* convert temperature raw data to temperature real data */
                }
                else
                {
                    *raw = (uint16_t)buf[2] << 8 | buf[3];                          /* get temperature raw data */
                    *s= (float)(buf[2] * 256 + buf[3]) / 10.0f;                     /* convert temperature raw data to temperature real data */
                }
                
                return 0;                                                           /* success return 0 */
            }
            else
            {
                handle->debug_print("am2320: data check failed.\n");                /* checksum error */
                
                return 1;                                                           /* return error */
            }
        }
        else
        {
            handle->debug_print("am2320: reset failed.\n");                         /* reset failed */
            
            return 1;                                                               /* return error */
        }
    }
    else                                                                            /* iic */
    {
        uint8_t res;
        uint8_t input_buf[3];
        uint8_t out_buf[6];
        uint16_t crc16;
        
        (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
        input_buf[0] = 0x03;                                                        /* set function code */
        input_buf[1] = AM2320_MODBUS_ADDRESS_TEMP_MSB;                              /* set addr */
        input_buf[2] = 0x02;                                                        /* set number */
        res = handle->iic_write_cmd(AM2320_ADDRESS, (uint8_t *)input_buf, 3);       /* write command */
        if (res != 0)                                                               /* check result */
        {
            handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
           
            return 1;                                                               /* return error */
        }
        handle->delay_ms(2);                                                        /* delay 2ms */
        res = handle->iic_read_cmd(AM2320_ADDRESS, (uint8_t *)out_buf, 6);          /* read command */
        if (res != 0)                                                               /* check result */
        {
            handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
           
            return 1;                                                               /* return error */
        }
        crc16 = ((uint16_t)out_buf[5] << 8 | (uint16_t)out_buf[4]);                 /* get crc16 */
        if (crc16 != a_am2320_generate_crc16(out_buf, 4))                           /* check crc16 */
        {
            handle->debug_print("am2320: crc check error.\n");                      /* crc check error */
           
            return 1;                                                               /* return error */
        }
        if (out_buf[0] != 0x03)                                                     /* check code */
        {
            handle->debug_print("am2320: code is invalid.\n");                      /* code is invalid */
           
            return 1;                                                               /* return error */
        }
        if (out_buf[1] != 0x02)                                                     /* check number */
        {
            handle->debug_print("am2320: number is invalid.\n");                    /* number is invalid */
           
            return 1;                                                               /* return error */
        }
        if ((out_buf[2] & (1 << 7)) != 0)                                           /* if temperature is below zero */
        {
            *raw = (uint16_t)out_buf[2] << 8 | out_buf[3];                          /* get temperature raw data */
            *s= (float)((out_buf[2] & ~(1 << 7)) * 256 + 
                         out_buf[3]) / 10.0f * (-1.0f);                             /* convert temperature raw data to temperature real data */
        }
        else
        {
            *raw = (uint16_t)out_buf[2] << 8 | out_buf[3];                          /* get temperature raw data */
            *s= (float)(out_buf[2] * 256 + out_buf[3]) / 10.0f;                     /* convert temperature raw data to temperature real data */
        }
        
        return 0;                                                                   /* success return 0 */
    }
}

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
uint8_t am2320_get_device_type(am2320_handle_t *handle, uint16_t *type)
{
    uint8_t res;
    uint8_t input_buf[3];
    uint8_t out_buf[6];
    uint16_t crc16;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                  /* gpio */
    {
        handle->debug_print("am2320: gpio can't use this function.\n");         /* gpio can't use this function */
       
        return 4;                                                               /* return error */
    }
    
    (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
    input_buf[0] = 0x03;                                                        /* set function code */
    input_buf[1] = AM2320_MODBUS_ADDRESS_DEVICE_TYPE_MSB;                       /* set addr */
    input_buf[2] = 0x02;                                                        /* set number */
    res = handle->iic_write_cmd(AM2320_ADDRESS, (uint8_t *)input_buf, 3);       /* write command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
       
        return 1;                                                               /* return error */
    }
    handle->delay_ms(2);                                                        /* delay 2ms */
    res = handle->iic_read_cmd(AM2320_ADDRESS, (uint8_t *)out_buf, 6);          /* read command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
       
        return 1;                                                               /* return error */
    }
    crc16 = ((uint16_t)out_buf[5] << 8 | (uint16_t)out_buf[4]);                 /* get crc16 */
    if (crc16 != a_am2320_generate_crc16(out_buf, 4))                           /* check crc16 */
    {
        handle->debug_print("am2320: crc check error.\n");                      /* crc check error */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[0] != 0x03)                                                     /* check code */
    {
        handle->debug_print("am2320: code is invalid.\n");                      /* code is invalid */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[1] != 0x02)                                                     /* check number */
    {
        handle->debug_print("am2320: number is invalid.\n");                    /* number is invalid */
       
        return 1;                                                               /* return error */
    }
    *type = (uint16_t)out_buf[2] << 8 | out_buf[3];                             /* get type */ 
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t am2320_get_version(am2320_handle_t *handle, uint8_t *version)
{
    uint8_t res;
    uint8_t input_buf[3];
    uint8_t out_buf[5];
    uint16_t crc16;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                  /* gpio */
    {
        handle->debug_print("am2320: gpio can't use this function.\n");         /* gpio can't use this function */
       
        return 4;                                                               /* return error */
    }
    
    (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
    input_buf[0] = 0x03;                                                        /* set function code */
    input_buf[1] = AM2320_MODBUS_ADDRESS_VERSION;                               /* set addr */
    input_buf[2] = 0x01;                                                        /* set number */
    res = handle->iic_write_cmd(AM2320_ADDRESS, (uint8_t *)input_buf, 3);       /* write command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
       
        return 1;                                                               /* return error */
    }
    handle->delay_ms(2);                                                        /* delay 2ms */
    res = handle->iic_read_cmd(AM2320_ADDRESS, (uint8_t *)out_buf, 5);          /* read command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
       
        return 1;                                                               /* return error */
    }
    crc16 = ((uint16_t)out_buf[4] << 8 | (uint16_t)out_buf[3]);                 /* get crc16 */
    if (crc16 != a_am2320_generate_crc16(out_buf, 3))                           /* check crc16 */
    {
        handle->debug_print("am2320: crc check error.\n");                      /* crc check error */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[0] != 0x03)                                                     /* check code */
    {
        handle->debug_print("am2320: code is invalid.\n");                      /* code is invalid */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[1] != 0x01)                                                     /* check number */
    {
        handle->debug_print("am2320: number is invalid.\n");                    /* number is invalid */
       
        return 1;                                                               /* return error */
    }
    *version = out_buf[2];                                                      /* get type */ 
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t am2320_get_status(am2320_handle_t *handle, uint8_t *status)
{
    uint8_t res;
    uint8_t input_buf[3];
    uint8_t out_buf[5];
    uint16_t crc16;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                  /* gpio */
    {
        handle->debug_print("am2320: gpio can't use this function.\n");         /* gpio can't use this function */
       
        return 4;                                                               /* return error */
    }
    
    (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
    input_buf[0] = 0x03;                                                        /* set function code */
    input_buf[1] = AM2320_MODBUS_ADDRESS_STATUS;                                /* set addr */
    input_buf[2] = 0x01;                                                        /* set number */
    res = handle->iic_write_cmd(AM2320_ADDRESS, (uint8_t *)input_buf, 3);       /* write command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
       
        return 1;                                                               /* return error */
    }
    handle->delay_ms(2);                                                        /* delay 2ms */
    res = handle->iic_read_cmd(AM2320_ADDRESS, (uint8_t *)out_buf, 5);          /* read command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
       
        return 1;                                                               /* return error */
    }
    crc16 = ((uint16_t)out_buf[4] << 8 | (uint16_t)out_buf[3]);                 /* get crc16 */
    if (crc16 != a_am2320_generate_crc16(out_buf, 3))                           /* check crc16 */
    {
        handle->debug_print("am2320: crc check error.\n");                      /* crc check error */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[0] != 0x03)                                                     /* check code */
    {
        handle->debug_print("am2320: code is invalid.\n");                      /* code is invalid */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[1] != 0x01)                                                     /* check number */
    {
        handle->debug_print("am2320: number is invalid.\n");                    /* number is invalid */
       
        return 1;                                                               /* return error */
    }
    *status = out_buf[2];                                                       /* get status */ 
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t am2320_get_device_id(am2320_handle_t *handle, uint32_t *id)
{
    uint8_t res;
    uint8_t input_buf[3];
    uint8_t out_buf[8];
    uint16_t crc16;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                  /* gpio */
    {
        handle->debug_print("am2320: gpio can't use this function.\n");         /* gpio can't use this function */
       
        return 4;                                                               /* return error */
    }
    
    (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
    input_buf[0] = 0x03;                                                        /* set function code */
    input_buf[1] = AM2320_MODBUS_ADDRESS_DEVICE_3;                              /* set addr */
    input_buf[2] = 0x04;                                                        /* set number */
    res = handle->iic_write_cmd(AM2320_ADDRESS, (uint8_t *)input_buf, 3);       /* write command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
       
        return 1;                                                               /* return error */
    }
    handle->delay_ms(2);                                                        /* delay 2ms */
    res = handle->iic_read_cmd(AM2320_ADDRESS, (uint8_t *)out_buf, 8);          /* read command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
       
        return 1;                                                               /* return error */
    }
    crc16 = ((uint16_t)out_buf[7] << 8 | (uint16_t)out_buf[6]);                 /* get crc16 */
    if (crc16 != a_am2320_generate_crc16(out_buf, 6))                           /* check crc16 */
    {
        handle->debug_print("am2320: crc check error.\n");                      /* crc check error */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[0] != 0x03)                                                     /* check code */
    {
        handle->debug_print("am2320: code is invalid.\n");                      /* code is invalid */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[1] != 0x04)                                                     /* check number */
    {
        handle->debug_print("am2320: number is invalid.\n");                    /* number is invalid */
       
        return 1;                                                               /* return error */
    }
    *id = (uint32_t)out_buf[2] << 24 | (uint32_t)out_buf[3] << 16 |
          (uint32_t)out_buf[4] << 8 | (uint32_t)out_buf[5] << 0;                /* get device id */ 
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t am2320_set_user_reg1(am2320_handle_t *handle, uint16_t reg)
{
    uint8_t res;
    uint8_t input_buf[7];
    uint8_t out_buf[5];
    uint16_t crc16;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                  /* gpio */
    {
        handle->debug_print("am2320: gpio can't use this function.\n");         /* gpio can't use this function */
       
        return 4;                                                               /* return error */
    }
    
    (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
    input_buf[0] = 0x10;                                                        /* set function code */
    input_buf[1] = AM2320_MODBUS_ADDRESS_USER_REG1_MSB;                         /* set addr */
    input_buf[2] = 0x02;                                                        /* set number */
    input_buf[3] = (reg >> 8) & 0xFF;                                           /* set reg msb */
    input_buf[4] = (reg >> 0) & 0xFF;                                           /* set reg lsb */
    crc16 = a_am2320_generate_crc16(input_buf, 5);                              /* get crc16*/
    input_buf[5] = (crc16 >> 0) & 0xFF;                                         /* set reg msb */
    input_buf[6] = (crc16 >> 8) & 0xFF;                                         /* set reg lsb */
    res = handle->iic_write_cmd(AM2320_ADDRESS, (uint8_t *)input_buf, 7);       /* write command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
       
        return 1;                                                               /* return error */
    }
    handle->delay_ms(2);                                                        /* delay 2ms */
    res = handle->iic_read_cmd(AM2320_ADDRESS, (uint8_t *)out_buf, 5);          /* read command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
       
        return 1;                                                               /* return error */
    }
    crc16 = ((uint16_t)out_buf[4] << 8 | (uint16_t)out_buf[3]);                 /* get crc16 */
    if (crc16 != a_am2320_generate_crc16(out_buf, 3))                           /* check crc16 */
    {
        handle->debug_print("am2320: crc check error.\n");                      /* crc check error */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[0] != 0x10)                                                     /* check code */
    {
        handle->debug_print("am2320: code is invalid.\n");                      /* code is invalid */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[1] != AM2320_MODBUS_ADDRESS_USER_REG1_MSB)                      /* check number */
    {
        handle->debug_print("am2320: addr is invalid.\n");                      /* addr is invalid */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[2] != 0x02)                                                     /* check number */
    {
        handle->debug_print("am2320: number is invalid.\n");                    /* number is invalid */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t am2320_get_user_reg1(am2320_handle_t *handle, uint16_t *reg)
{
    uint8_t res;
    uint8_t input_buf[3];
    uint8_t out_buf[6];
    uint16_t crc16;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                  /* gpio */
    {
        handle->debug_print("am2320: gpio can't use this function.\n");         /* gpio can't use this function */
       
        return 4;                                                               /* return error */
    }
    
    (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
    input_buf[0] = 0x03;                                                        /* set function code */
    input_buf[1] = AM2320_MODBUS_ADDRESS_USER_REG1_MSB;                         /* set addr */
    input_buf[2] = 0x02;                                                        /* set number */
    res = handle->iic_write_cmd(AM2320_ADDRESS, (uint8_t *)input_buf, 3);       /* write command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
       
        return 1;                                                               /* return error */
    }
    handle->delay_ms(2);                                                        /* delay 2ms */
    res = handle->iic_read_cmd(AM2320_ADDRESS, (uint8_t *)out_buf, 6);          /* read command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
       
        return 1;                                                               /* return error */
    }
    crc16 = ((uint16_t)out_buf[5] << 8 | (uint16_t)out_buf[4]);                 /* get crc16 */
    if (crc16 != a_am2320_generate_crc16(out_buf, 4))                           /* check crc16 */
    {
        handle->debug_print("am2320: crc check error.\n");                      /* crc check error */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[0] != 0x03)                                                     /* check code */
    {
        handle->debug_print("am2320: code is invalid.\n");                      /* code is invalid */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[1] != 0x02)                                                     /* check number */
    {
        handle->debug_print("am2320: number is invalid.\n");                    /* number is invalid */
       
        return 1;                                                               /* return error */
    }
    *reg = (uint16_t)out_buf[2] << 8 | out_buf[3];                              /* get reg */ 
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t am2320_set_user_reg2(am2320_handle_t *handle, uint16_t reg)
{
    uint8_t res;
    uint8_t input_buf[7];
    uint8_t out_buf[5];
    uint16_t crc16;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                  /* gpio */
    {
        handle->debug_print("am2320: gpio can't use this function.\n");         /* gpio can't use this function */
       
        return 4;                                                               /* return error */
    }
    
    (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
    input_buf[0] = 0x10;                                                        /* set function code */
    input_buf[1] = AM2320_MODBUS_ADDRESS_USER_REG2_MSB;                         /* set addr */
    input_buf[2] = 0x02;                                                        /* set number */
    input_buf[3] = (reg >> 8) & 0xFF;                                           /* set reg msb */
    input_buf[4] = (reg >> 0) & 0xFF;                                           /* set reg lsb */
    crc16 = a_am2320_generate_crc16(input_buf, 5);                              /* get crc16*/
    input_buf[5] = (crc16 >> 0) & 0xFF;                                         /* set reg msb */
    input_buf[6] = (crc16 >> 8) & 0xFF;                                         /* set reg lsb */
    res = handle->iic_write_cmd(AM2320_ADDRESS, (uint8_t *)input_buf, 7);       /* write command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
       
        return 1;                                                               /* return error */
    }
    handle->delay_ms(2);                                                        /* delay 2ms */
    res = handle->iic_read_cmd(AM2320_ADDRESS, (uint8_t *)out_buf, 5);          /* read command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
       
        return 1;                                                               /* return error */
    }
    crc16 = ((uint16_t)out_buf[4] << 8 | (uint16_t)out_buf[3]);                 /* get crc16 */
    if (crc16 != a_am2320_generate_crc16(out_buf, 3))                           /* check crc16 */
    {
        handle->debug_print("am2320: crc check error.\n");                      /* crc check error */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[0] != 0x10)                                                     /* check code */
    {
        handle->debug_print("am2320: code is invalid.\n");                      /* code is invalid */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[1] != AM2320_MODBUS_ADDRESS_USER_REG2_MSB)                      /* check number */
    {
        handle->debug_print("am2320: addr is invalid.\n");                      /* addr is invalid */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[2] != 0x02)                                                     /* check number */
    {
        handle->debug_print("am2320: number is invalid.\n");                    /* number is invalid */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t am2320_get_user_reg2(am2320_handle_t *handle, uint16_t *reg)
{
    uint8_t res;
    uint8_t input_buf[3];
    uint8_t out_buf[6];
    uint16_t crc16;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                  /* gpio */
    {
        handle->debug_print("am2320: gpio can't use this function.\n");         /* gpio can't use this function */
       
        return 4;                                                               /* return error */
    }
    
    (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
    input_buf[0] = 0x03;                                                        /* set function code */
    input_buf[1] = AM2320_MODBUS_ADDRESS_USER_REG2_MSB;                         /* set addr */
    input_buf[2] = 0x02;                                                        /* set number */
    res = handle->iic_write_cmd(AM2320_ADDRESS, (uint8_t *)input_buf, 3);       /* write command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
       
        return 1;                                                               /* return error */
    }
    handle->delay_ms(2);                                                        /* delay 2ms */
    res = handle->iic_read_cmd(AM2320_ADDRESS, (uint8_t *)out_buf, 6);          /* read command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
       
        return 1;                                                               /* return error */
    }
    crc16 = ((uint16_t)out_buf[5] << 8 | (uint16_t)out_buf[4]);                 /* get crc16 */
    if (crc16 != a_am2320_generate_crc16(out_buf, 4))                           /* check crc16 */
    {
        handle->debug_print("am2320: crc check error.\n");                      /* crc check error */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[0] != 0x03)                                                     /* check code */
    {
        handle->debug_print("am2320: code is invalid.\n");                      /* code is invalid */
       
        return 1;                                                               /* return error */
    }
    if (out_buf[1] != 0x02)                                                     /* check number */
    {
        handle->debug_print("am2320: number is invalid.\n");                    /* number is invalid */
       
        return 1;                                                               /* return error */
    }
    *reg = (uint16_t)out_buf[2] << 8 | out_buf[3];                              /* get reg */ 
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t am2320_init(am2320_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                 /* check debug_print */
    {
        return 3;                                                    /* return error */
    }
    if (handle->iic_init == NULL)                                    /* check iic_init */
    {
        handle->debug_print("am2320: iic_init is null.\n");          /* iic_init is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_deinit == NULL)                                  /* check iic_deinit */
    {
        handle->debug_print("am2320: iic_deinit is null.\n");        /* iic_deinit is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                /* check iic_read_cmd */
    {
        handle->debug_print("am2320: iic_read_cmd is null.\n");      /* iic_read_cmd is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_write_cmd == NULL)                               /* check iic_write_cmd */
    {
        handle->debug_print("am2320: iic_write_cmd is null.\n");     /* iic_write_cmd is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->bus_init == NULL)                                    /* check bus_init */
    {
        handle->debug_print("am2320: bus_init is null.\n");          /* bus_init is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->bus_deinit == NULL)                                  /* check bus_deinit */
    {
        handle->debug_print("am2320: bus_deinit is null.\n");        /* bus_deinit is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->bus_read == NULL)                                    /* check bus_read */
    {
        handle->debug_print("am2320: bus_read is null.\n");          /* bus_read is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->bus_write == NULL)                                   /* check bus_write */
    {
        handle->debug_print("am2320: bus_write is null.\n");         /* bus_write is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->delay_ms == NULL)                                    /* check delay_ms */
    {
        handle->debug_print("am2320: delay_ms is null.\n");          /* delay_ms is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->delay_us == NULL)                                    /* check delay_us */
    {
        handle->debug_print("am2320: delay_us is null.\n");          /* delay_us is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->enable_irq == NULL)                                  /* check enable_irq */
    {
        handle->debug_print("am2320: enable_irq is null.\n");        /* enable_irq is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->disable_irq == NULL)                                 /* check disable_irq */
    {
        handle->debug_print("am2320: disable_irq is null.\n");       /* disable_irq is null */
        
        return 3;                                                    /* return error */
    }
    
    if (handle->gpio_iic != 0)                                       /* gpio */
    {
        if (handle->bus_init() != 0)                                 /* initialize bus */
        {
            handle->debug_print("am2320: bus init failed.\n");       /* bus init failed */
            
            return 1;                                                /* return error */
        }
        if (a_am2320_reset(handle) != 0)                             /* reset the chip */
        {
            handle->debug_print("am2320: reset failed.\n");          /* reset failed */
            (void)handle->bus_deinit();                              /* close bus */
            
            return 4;                                                /* return error */
        }
    }
    else                                                             /* iic */
    {
        if (handle->iic_init() != 0)                                 /* iic init */
        {
            handle->debug_print("am2320: iic init failed.\n");       /* iic init failed */
            
            return 1;                                                /* return error */
        }
    }
    handle->inited = 1;                                              /* flag finish initialization */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t am2320_deinit(am2320_handle_t *handle)
{
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    
    if (handle->gpio_iic != 0)                                     /* gpio */
    {
        if (handle->bus_deinit() != 0)                             /* close bus */
        {
            handle->debug_print("am2320: deinit failed.\n");       /* deinit failed */
            
            return 1;                                              /* return error */
        }
    }
    else                                                           /* iic */
    {
        if (handle->iic_deinit() != 0)                             /* iic deinit */
        {
            handle->debug_print("am2320: iic deinit failed.\n");   /* iic deinit failed */
            
            return 1;                                              /* return error */
        }
    }
    handle->inited = 0;                                            /* flag close */
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t am2320_set_get_reg(am2320_handle_t *handle, uint8_t *input_buf, uint16_t input_len, uint8_t *output_buf, uint16_t output_len)
{
    uint8_t res;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    if (handle->gpio_iic != 0)                                                  /* gpio */
    {
        handle->debug_print("am2320: gpio can't use this function.\n");         /* gpio can't use this function */
       
        return 4;                                                               /* return error */
    }
    
    (void)handle->iic_write_cmd(AM2320_ADDRESS, NULL, 0);                       /* wake up */
    res = handle->iic_write_cmd(AM2320_ADDRESS, input_buf, input_len);          /* write command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: write command failed.\n");                 /* write command failed */
       
        return 1;                                                               /* return error */
    }
    handle->delay_ms(2);                                                        /* delay 2ms */
    res = handle->iic_read_cmd(AM2320_ADDRESS, output_buf, output_len);         /* read command */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("am2320: read command failed.\n");                  /* read command failed */
       
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an am2320 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t am2320_info(am2320_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(am2320_info_t));                         /* initialize am2320 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "GPIO IIC", 16);                       /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
