/*
 * control.c
 *
 *  Created on: Nov 12, 2019
 *      Author: Balint
 */
//#include <stdlib.h>
#include <time.h> //time_t hasznalata miatt, ez kell a veletlen elrendezesnek
#include <stdbool.h> //bool tipus hasznalasa miatt
#include "types.h" //buttons es position miatt



extern const uint16_t ships[16][7]; //a hajoelrendezesek
extern buttons control; //aktualis allapot
extern int numberOfShots; //lovesek szama
extern uint16_t shiphits[]; //eltalalt hajodarabkak



void editActive(position *p) //ebben allitjuk be, hogy merre mozogjon az aktualis pozicio, az uarton erkezo karakterek alapjan
{
	if(control == RIGHT) // digit jobbra
	{
		if(6 == p->digit) //ha kimennenk a kepernyorol jobb oldalt
		{
			p->digit = 0;
		}
		else
		{
			p->digit += 1;
		}
	}
	else if(control == LEFT) // digit balra
	{
		if(0 == p->digit) //ha kimennenk balra
		{
			p->digit = 6;
		}
		else
		{
			p->digit -= 1;
		}
	}
	else if(control == DOWN) // szegmens elozo
	{
		if(0 == p->segment)
		{
			p->segment = 13; // ha tulmennenk az osszes szegmensen, ne lehessen negativ
		}
		else
		{
			p->segment -= 1;
		}
	}
	else if(control == UP) //szegmens kovetkezo
	{
		if(13 == p->segment)
		{
			p->segment = 0; // ha tulmennenk az osszes szegmensen
		}
		else
		{
			p->segment += 1;
		}

	}
	control = IDLE; //ha lekezeltuk a mozgast visszaterunk az idle-allapotba,
					//hogy tobbszor ne kezeljuk le ugyanazt az utasitast
}



void storeHits(position p) // a talalt lovesek eltarolasa
{
	if((p.segment == 6) || (p.segment == 10)) //ha a kozepso ket szegmenst talaljuk el, azok egyutt szamitanak egynek
	{
		shiphits[p.digit]|= 1 << 6; //shiphits hetelemu tomb, ebben taroljuk a darabokat, kezdetben minden eleme nulla
		shiphits[p.digit]|= 1 << 10; //ebbe vagyoljuk bele bitenkent az eltalalt darabokat
	}
	else
	{
		shiphits[p.digit]|= 1 << p.segment;
	}
}

bool fire(position p, int active) //a lovesek logikaja
{
	bool hit = false; //visszateresi ertek, hogy talalt e a loves

		numberOfShots += 1; //lovesek szamanak novelese

		uint16_t  taroltdigit = ships[active][p.digit]; //a tarolt elrendezes azon digitje, amire a loves erkezett
		uint16_t celzottszegmens = 1 << p.segment; //azon szegmens amire lottunk, ebbol kepzunk egy szamot

		if((taroltdigit & celzottszegmens) != 0) //ha a ket szam bitenkenti es kapcsolata nem nulla, akkor talalatunk van,
		{										//hiszen egy olyan szegmensre lottunk, ami a tarolt elrendezesben nem nulla,
			hit = true;							//tehat ott hajo van ezert hit-unk van
		}
		else
		{
			hit = false; //nincs hit
		}

	return hit;
}

bool win(int active) //nyertunk e, vegigmegy az osszes digiten es megnezi hogy egyeznek e a szamok, a talalt darabokkal
{
	for(int i = 0; i < 7; i++)
	{
		if(ships[active][i] != shiphits[i]) //ha nem egyezik, akkor van meg olyan szegmens amit meg nem talaltunk el
		{
			return false;
		}
	}
	return true; //ha mindegyik digitnel egyeznek a szamok, akkor minden darabot eltalaltunk, tehat nyertunk
}











