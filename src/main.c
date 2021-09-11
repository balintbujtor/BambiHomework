#include "em_device.h"
#include "em_chip.h"
#include "em_core.h"
#include "em_cmu.h"
#include "segmentlcd.h" // szegmens vezérléshez
#include "segmentlcd_individual.h"
#include "stdlib.h"
#include "em_usart.h" //usart kommunikaciohoz
#include "em_gpio.h"
#include "em_lcd.h"
#include "types.h"
#include "uart.h"
#include "display.h"
#include "control.h"
#include <stdbool.h>
#include <time.h>


//SegmentLCD_UpperCharSegments_TypeDef shotDisplay[SEGMENT_LCD_NUM_OF_UPPER_CHARS];

SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];
//elore megirt adatszerkezet az also kijelzo megjelenitesehez

const uint16_t ships[16][7] = {
						  {0x0030,0x0000,0x0880,0x0008,0x0008,0x0000,0x0006},
						  {0x0880,0x0440,0x0440,0x1100,0x0008,0x0008,0x0000},
						  {0x0000,0x0001,0x0001,0x0880,0x1100,0x0000,0x2200},
						  {0x0006,0x2200,0x0008,0x0008,0x0000,0x0440,0x0440},
						  {0x0000,0x1100,0x2200,0x0008,0x0008,0x0000,0x0880},
						  {0x2200,0x0000,0x1100,0x0001,0x0001,0x0880,0x0000},
						  {0x0000,0x0880,0x0000,0x0006,0x0001,0x0001,0x2200},
						  {0x0030,0x2200,0x0440,0x0440,0x0000,0x0880,0x0000},
						  {0x2200,0x0440,0x0440,0x1100,0x0000,0x0000,0x0880},
						  {0x0001,0x0001,0x0880,0x0000,0x0000,0x0006,0x2200},
						  {0x1100,0x0000,0x0880,0x0440,0x0440,0x0000,0x2200},
						  {0x0440,0x0440,0x2200,0x0006,0x0000,0x0001,0x0001},
						  {0x0880,0x0008,0x0008,0x0000,0x0006,0x0000,0x2200},
						  {0x0000,0x0440,0x0440,0x1100,0x0880,0x0000,0x1100},
						  {0x0008,0x0008,0x0880,0x0000,0x0030,0x2200,0x0000},
						  {0x0000,0x0006,0x0001,0x0001,0x0880,0x0000,0x2200}};
//2 dimenzios tomb az elrendezesek tarolasahoz. 16 darab egyenkent 7 digitet ad meg

uint16_t shiphits[7] = {0,0,0,0,0,0,0};
// az eltalt hajodarabokat taroljuk ebben a tombben

buttons control = RIGHT; //gombnyomasok tarolasa
position pos; //aktualis pozicio
bool startgame = false; //logikai valtozo a jatek kezdesenek erzekelesehez
bool youwon = false; //logikai valtozo a gyozelemhez
int numberOfShots = 0; //lovesek szama
int activeArrangement = 0; //aktualis elrendezes
time_t timer = 0; //eltelt ido rnd szamhoz
volatile uint32_t msTicks = 0; //eltelt millisecundomok



int main(void)
{
  /* Chip errata */
  CHIP_Init();
  SegmentLCD_Init(false);
  uartInit();
  //chip, lcd kijelzo, uart kommunikacio inicializalasa

  if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000))
  {
	  while (1);
  }
  //orajel bellitasa

  starter();
  //jatek kezdese

  pos.digit = 3;
  pos.segment = 3;
  //alapertelmezett beallitas az aktualis poziciohoz

  /* Infinite loop */
  while (1)
  {

	  while(!youwon) //amig nem nyerunk, addig folyamatosan ez a resz fut
	  {
		  editActive(&pos); //aktualis pozicio szerkesztese es villogtatasa, lovesek szamanak megjelenitese
		  blink(pos);
		  SegmentLCD_Number(numberOfShots);

		  if(control == FIRE) //ha tuzelunk
		  {
			  bool shotHit = fire(pos,activeArrangement); //talaltunk e
			  if(shotHit) //ha talaltunk akkor eltaroljuk az eltalalt hajodarabot, es megnezzuk, mindent eltalaltunk e
			  {
				  storeHits(pos);
				  youwon = win(activeArrangement);

			  }
			  setRing(shotHit); //a talalattol fuggoen animaljuk ARing szegmenseit
		  }

		  for(int i = 0; i < 7; i++) //megjelenitjuk az eltalalt hajodarabokat
		  {
			lowerCharSegments[i].raw = shiphits[i];
			SegmentLCD_LowerSegments(lowerCharSegments);
		  }
	  }

	  windisplay(); //ha nyertunk akkor folyamatosan villogtatjuk a you won feliratot
  }
}
