/*
 * reaction.h
 *
 *  Created on: 20 may. 2025
 *      Author: jajav
 */

#ifndef STATES_REACTION_H_
#define STATES_REACTION_H_

#include "pin_mux.h"

#define SALEAE_INIT BOARD_INITPINS_SALAE_INIT_GPIO_PORT
#define SALEAE_INIT_MASK BOARD_INITPINS_SALAE_INIT_PIN_MASK

#define SALEAE_END BOARD_INITPINS_SALAE_END_GPIO_PORT
#define SALEAE_END_MASK BOARD_INITPINS_SALAE_END_PIN_MASK

void Reaction();

#endif /* STATES_REACTION_H_ */
