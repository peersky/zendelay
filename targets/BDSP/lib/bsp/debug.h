/*
 * BSP_Debug.h
 *
 *  Created on: 25 Oct 2018
 *      Author: Tim
 */

#ifndef BSP_BSP_DEBUG_H_
#define BSP_BSP_DEBUG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include "stdio.h"

    void _bsp_error(char *file, int line);

#define bsp_debug(fmt, ...)           \
    do                                \
    {                                 \
        if (BSP_DEBUG)                \
            printf(fmt, __VA_ARGS__); \
    } while (0)

#define BSP_Error_Handler()                 \
    do                                      \
    {                                       \
        if (BSP_DEBUG)                      \
            _bsp_error(__FILE__, __LINE__); \
    } while (0)

#define bsp_dbg_print(str)       \
    do                           \
    {                            \
        if (BSP_DEBUG)           \
            printf("%s\n", str); \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif /* BSP_BSP_DEBUG_H_ */
