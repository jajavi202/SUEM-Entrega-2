/*
 * kbi_pins.h
 *
 *  Created on: 20 may. 2025
 *      Author: jajav
 */

#ifndef KBI_PINS_H_
#define KBI_PINS_H_

#define KBI1_BOARD_KEY1 (1U << 27U)
#define KBI1_BOARD_KEY2 (1U << 28U)

#define KBI1_MASK (KBI1_BOARD_KEY1 | KBI1_BOARD_KEY2)


#define KBI0_KEY_1 (1U << 16U)
#define KBI0_KEY_2 (1U << 17U)
#define KBI0_KEY_3 (1U << 18U)
#define KBI0_KEY_4 (1U << 19U)

#define KBI0_MASK (KBI0_KEY_1 | KBI0_KEY_2 | KBI0_KEY_3 | KBI0_KEY_4)

#endif /* KBI_PINS_H_ */
