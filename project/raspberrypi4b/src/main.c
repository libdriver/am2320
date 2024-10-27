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
 * @file      main.c
 * @brief     main source file
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
#include "driver_am2320_read_test.h"
#include <getopt.h>
#include <stdlib.h>
#include <math.h>

/**
 * @brief     am2320 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t am2320(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"interface", required_argument, NULL, 1},
        {"times", required_argument, NULL, 2},
        {"value", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint16_t value = 0x0000;
    uint32_t times = 3;
    am2320_interface_t interface = AM2320_INTERFACE_IIC;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* interface */
            case 1 :
            {
                if (strcmp("iic", optarg) == 0)
                {
                    interface = AM2320_INTERFACE_IIC;
                }
                else if (strcmp("gpio", optarg) == 0)
                {
                    interface = AM2320_INTERFACE_GPIO; 
                }
                else
                {
                    return 5;
                }
                
                break;
            } 
            
            /* running times */
            case 2 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* value */
            case 3 :
            {
                char *p;
                uint16_t l;
                uint16_t i;
                uint64_t hex_data;

                /* set the data */
                l = strlen(optarg);

                /* check the header */
                if (l >= 2)
                {
                    if (strncmp(optarg, "0x", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else if (strncmp(optarg, "0X", 2) == 0)
                    {
                        p = optarg + 2;
                        l -= 2;
                    }
                    else
                    {
                        p = optarg;
                    }
                }
                else
                {
                    p = optarg;
                }
                
                /* init 0 */
                hex_data = 0;

                /* loop */
                for (i = 0; i < l; i++)
                {
                    if ((p[i] <= '9') && (p[i] >= '0'))
                    {
                        hex_data += (p[i] - '0') * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'F') && (p[i] >= 'A'))
                    {
                        hex_data += ((p[i] - 'A') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else if ((p[i] <= 'f') && (p[i] >= 'a'))
                    {
                        hex_data += ((p[i] - 'a') + 10) * (uint32_t)pow(16, l - i - 1);
                    }
                    else
                    {
                        return 5;
                    }
                }
                
                /* set the data */
                value = hex_data & 0xFFFF;
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (am2320_read_test(interface, times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float temperature;
        float humidity;
        
        /* init */
        res = am2320_basic_init(interface);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 2000ms */
            am2320_interface_delay_ms(2000);
            
            /* read data */
            res = am2320_basic_read((float *)&temperature, (float *)&humidity);
            if (res != 0)
            {
                (void)am2320_basic_deinit();
                
                return 1;
            }
            
            /* output */
            am2320_interface_debug_print("am2320: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            am2320_interface_debug_print("am2320: temperature is %0.2fC.\n", temperature);
            am2320_interface_debug_print("am2320: humidity is %0.2f%%.\n", humidity); 
        }
        
        /* deinit */
        (void)am2320_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_reg1", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = am2320_basic_init(interface);
        if (res != 0)
        {
            return 1;
        }
        
        if (argc == 4)
        {
            /* get user reg1 */
            res = am2320_basic_get_user_reg1(&value);
            if (res != 0)
            {
                (void)am2320_basic_deinit();
                
                return 1;
            }
            
            /* output */
            am2320_interface_debug_print("am2320: get user reg1 0x%04X.\n", value);
        }
        else
        {
            /* set user reg1 */
            res = am2320_basic_set_user_reg1(value);
            if (res != 0)
            {
                (void)am2320_basic_deinit();
                
                return 1;
            }
            
            /* output */
            am2320_interface_debug_print("am2320: set user reg1 0x%04X.\n", value);
        }
        
        /* deinit */
        (void)am2320_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_reg2", type) == 0)
    {
        uint8_t res;
        
        /* init */
        res = am2320_basic_init(interface);
        if (res != 0)
        {
            return 1;
        }
        
        if (argc == 4)
        {
            /* get user reg2 */
            res = am2320_basic_get_user_reg2(&value);
            if (res != 0)
            {
                (void)am2320_basic_deinit();
                
                return 1;
            }
            
            /* output */
            am2320_interface_debug_print("am2320: get user reg2 0x%04X.\n", value);
        }
        else
        {
            /* set user reg2 */
            res = am2320_basic_set_user_reg2(value);
            if (res != 0)
            {
                (void)am2320_basic_deinit();
                
                return 1;
            }
            
            /* output */
            am2320_interface_debug_print("am2320: set user reg2 0x%04X.\n", value);
        }
        
        /* deinit */
        (void)am2320_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        am2320_interface_debug_print("Usage:\n");
        am2320_interface_debug_print("  am2320 (-i | --information)\n");
        am2320_interface_debug_print("  am2320 (-h | --help)\n");
        am2320_interface_debug_print("  am2320 (-p | --port)\n");
        am2320_interface_debug_print("  am2320 (-t read | --test=read) [--interface=<gpio | iic>] [--times=<num>]\n");
        am2320_interface_debug_print("  am2320 (-e read | --example=read) [--interface=<gpio | iic>] [--times=<num>]\n");
        am2320_interface_debug_print("  am2320 (-e reg1 | --example=reg1) [--interface=<iic>]\n");
        am2320_interface_debug_print("  am2320 (-e reg1 | --example=reg1) [--interface=<iic>] [--value=<hex>]\n");
        am2320_interface_debug_print("  am2320 (-e reg2 | --example=reg2) [--interface=<iic>]\n");
        am2320_interface_debug_print("  am2320 (-e reg2 | --example=reg2) [--interface=<iic>] [--value=<hex>]\n");
        am2320_interface_debug_print("\n");
        am2320_interface_debug_print("Options:\n");
        am2320_interface_debug_print("  -e <read | reg1 | reg2>, --example=<read | reg1 | reg2>\n");
        am2320_interface_debug_print("                                  Run the driver example.\n");
        am2320_interface_debug_print("  -h, --help                      Show the help.\n");
        am2320_interface_debug_print("  -i, --information               Show the chip information.\n");
        am2320_interface_debug_print("      --interface=<gpio | iic>    Set the chip interface.([default: iic])\n");
        am2320_interface_debug_print("  -p, --port                      Display the pin connections of the current board.\n");
        am2320_interface_debug_print("  -t <read>, --test=<read>        Run the driver test.\n");
        am2320_interface_debug_print("      --times=<num>               Set the running times.([default: 3])\n");
        am2320_interface_debug_print("      --value=<hex>               Set the value[hex].([default: 0x0000])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        am2320_info_t info;
        
        /* print am2320 information */
        am2320_info(&info);
        am2320_interface_debug_print("am2320: chip is %s.\n", info.chip_name);
        am2320_interface_debug_print("am2320: manufacturer is %s.\n", info.manufacturer_name);
        am2320_interface_debug_print("am2320: interface is %s.\n", info.interface);
        am2320_interface_debug_print("am2320: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        am2320_interface_debug_print("am2320: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        am2320_interface_debug_print("am2320: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        am2320_interface_debug_print("am2320: max current is %0.2fmA.\n", info.max_current_ma);
        am2320_interface_debug_print("am2320: max temperature is %0.1fC.\n", info.temperature_max);
        am2320_interface_debug_print("am2320: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        am2320_interface_debug_print("am2320: DATA pin connected to GPIO17(BCM).\n");
        am2320_interface_debug_print("am2320: SCL connected to GPIO3(BCM).\n");
        am2320_interface_debug_print("am2320: SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = am2320(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        am2320_interface_debug_print("am2320: run failed.\n");
    }
    else if (res == 5)
    {
        am2320_interface_debug_print("am2320: param is invalid.\n");
    }
    else
    {
        am2320_interface_debug_print("am2320: unknown status code.\n");
    }

    return 0;
}
