/*
 * display.c
 *
 *  Created on: Nov 12, 2019
 *      Author: Balint
 */
#include "segmentlcd_individual.h"
#include "segmentlcd.h" //beepitett tipusokhoz es fuggvenyekhez
#include "types.h"
#include <stdlib.h> //uint tipusokhoz
#include <time.h>//time_t hasznalata miatt, ez kell a veletlen elrendezesnek
#include <string.h> //string manipulacios fuggvenyekhez



extern buttons control; //iranyitas
extern SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS]; //also digitek tarolasa
extern volatile uint32_t msTicks; // hany millisec telt el
extern time_t timer; //szamlalo a veletlen elrendezes kivalasztasahoz
extern int activeArrangement; //aktualis elrendezes
extern bool startgame; //jatek kezdete



void SysTick_Handler(void) { //it kezeles, a delayhez szukseges, hogy szepen, ugyanolyan hosszu ideig villanjon
    msTicks++;       /* increment counter necessary in Delay()*/
}

void Delay(uint32_t dlyTicks) { //a kesleltetest megvalosito fv, msec-ben van minden
    uint32_t curTicks; //epp mennyi ido telt el inditas ota, kezdeti ido

    curTicks = msTicks;
    while ((msTicks - curTicks) < dlyTicks){}; //addig csinalja, mig az aktualis es a kezdeti ido kulonbsege meg nem haladja
}												//a kivant kesleltetest

void starter() //intro fuggveny, hogy random elrendezest lehessen sorsolni
{
	char introtext[21] = "PRESS SPACE TO START";
	  while(!startgame) //amig a felhasznalo nem kezd el jatszani intro szoveg shiftelese
	  {


		for(int i = 0; i < 17;i++)
		{
			if(control == START) //ha a jatekos elkezdene a jatekot megtorjuk a ciklust
			{
			  startgame = true;
			}
			else //egyebkent noveljuk a timert es shifteljuk eggyel arreb a feliratot
			{
				timer++;

				char subString[8]; //eggyel leptetunk arrebb
				strncpy(subString, introtext + i, 7);
				subString[7] = '\0';

				SegmentLCD_Write (subString); //felkapcsoljuk a szegmenseket, varunk majd lekapcsoljuk
				Delay(350);
				SegmentLCD_AllOff();
			}

		}

		  srand(timer); //a szamlalo aktualis ertekevel seedeljuk a srandot --> mindig mas lesz a pool
		  activeArrangement = rand() % 16; // random szam valasztas a poolbol, modulo 16, hogy csak a 0-15 ig vehessen fel erteket
	  }										//ez adja meg az aktualis elrendezest
}

void blink(position p) //aktualis szegmens villogatatasa
{

	switch(p.segment)
	{
	case 0:
		lowerCharSegments[p.digit].a = 1;
		SegmentLCD_LowerSegments(lowerCharSegments); //az aktualis szegmenst felkapcsoljuk varunk majd lekapcsoljuk
		Delay(250);
		lowerCharSegments[p.digit].a = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 1:
		lowerCharSegments[p.digit].b = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].b = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 2:
		lowerCharSegments[p.digit].c = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].c = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 3:
		lowerCharSegments[p.digit].d = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].d = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 4:
		lowerCharSegments[p.digit].e = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].e = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 5:
		lowerCharSegments[p.digit].f = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].f = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 6: //a 6-os es a 10-es a ket kozepso szegmens, ezeket egyszerre kell villogtatni, hiszen ezek ketten ernek egyet
		lowerCharSegments[p.digit].g = 1;
		lowerCharSegments[p.digit].m = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].g = 0;
		lowerCharSegments[p.digit].m = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 7:
		lowerCharSegments[p.digit].h = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].h = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 8:
		lowerCharSegments[p.digit].j = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].j = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 9:
		lowerCharSegments[p.digit].k = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].k = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 10:
		lowerCharSegments[p.digit].g = 1;
		lowerCharSegments[p.digit].m = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].g = 0;
		lowerCharSegments[p.digit].m = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 11:
		lowerCharSegments[p.digit].n = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].n = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 12:
		lowerCharSegments[p.digit].p= 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].p= 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	case 13:
		lowerCharSegments[p.digit].q = 1;
		SegmentLCD_LowerSegments(lowerCharSegments);
		Delay(250);
		lowerCharSegments[p.digit].q = 0;
		SegmentLCD_LowerSegments(lowerCharSegments);
	break;
	}
	Delay(250); //lekapcsolas utan is legyen kesleltetes
}

void setRing (int hit) //a lovesek meganimalasa
{

	for(uint32_t i = 0; i <= 7; i++) //minden szegmens felkapcsolasa plusz kesleltetes koztuk
	{
		SegmentLCD_ARing(i,1);
		Delay(125);
	}
	if(hit) //talalat eseten haromszor villan is mindegyik
	{
		for(int i = 0; i < 3; i++)
		{

			for(uint32_t i = 0; i <= 7; i++)
			{
				SegmentLCD_ARing(i,0);
			}
			Delay(125);
			for(uint32_t i = 0; i <= 7; i++)
			{
				SegmentLCD_ARing(i,1);
			}
			Delay(125);

		}
	}

	for(uint32_t i = 0; i <= 7; i++) //ha nincs talalat, akkor mindent kikapcsolunk
	{
		SegmentLCD_ARing(i,0);
	}

}

void windisplay()
{
	while(1) // gyozelem eseten felirat kiirasa, villogtatasa
	{
		char text[]= "YOU WON";
		SegmentLCD_Write (text);
		Delay(250);
		SegmentLCD_AllOff();
		Delay(250);
	}

}

//SegmentLCD_Number();
//a fenti kijelzon az eddigi loveseink megjelenitese




