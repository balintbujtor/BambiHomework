/*
 * types.h
 *
 *  Created on: Nov 12, 2019
 *      Author: Balint
 */

#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

typedef struct {         //struktura az aktualis pozicionak,
	unsigned digit;		//melyik digiten vagyunk (szamjegy)
	unsigned segment;	//melyik szegmensen vagyunk a digiten belul
} position;

typedef enum {IDLE,LEFT,RIGHT,UP,DOWN,START,FIRE} buttons;
//enum az uart-on erkezo karaktereknek,
//kiegeszitve egy idle allapottal, amibe visszaterunk, ha eppen nem jon semmilyen karakter


#endif /* SRC_TYPES_H_ */
