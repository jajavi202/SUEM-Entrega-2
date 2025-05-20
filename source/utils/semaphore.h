/*
 * semaphore.h
 *
 *  Created on: 14 may. 2025
 *      Author: jajav
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "board.h"
#include "time.h"

void SemaphoreTest(uint32_t waitTime, gpio_port_num_t *rgbPorts, uint8_t *rgbMasks);
void SemaphoreToogle(uint32_t wait, gpio_port_num_t port, uint8_t mask);

#endif /* SEMAPHORE_H_ */
