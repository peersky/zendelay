/*
 * BSP_Debug.c
 *
 *  Created on: 25 Oct 2018
 *      Author: Tim
 */

#include "debug.h"

void _bsp_error(char *file, int line)
{

  printf("Error: file %s on line %d\r\n", file, line);
  while (1)
  {
  }
}
