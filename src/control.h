/*
 * control.h
 *
 *  Created on: Nov 12, 2019
 *      Author: Balint
 */

#ifndef SRC_CONTROL_H_
#define SRC_CONTROL_H_

#include <stdbool.h> // hogy ertelmezni tudja a bool visszateresi erteket

void editActive(position *p);
void storeHits(position p);
bool fire(position p, int active);
bool win(int active);

#endif /* SRC_CONTROL_H_ */
