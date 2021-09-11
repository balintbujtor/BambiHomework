/*
 * uart.c
 *
 *  Created on: Nov 12, 2019
 *      Author: Balint
 */
#include "em_usart.h" //az usarthoz tartozo beepitett fv-ek miatt
#include "em_cmu.h" //orajel hasznalat miatt
#include "types.h" // a buttons enum miatt

extern buttons control;

void uartInit() //uart kommunikacio inicializalasa
{
    CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
 // Set PF7 to high
    GPIO_PinModeSet(gpioPortF, 7, gpioModePushPull, 1);
 // Configure UART0
 // (Now use the "emlib" functions whenever possible.)
 // Enable clock for UART0
    CMU_ClockEnable(cmuClock_UART0, true);

    USART_InitAsync_TypeDef UART0_init = USART_INITASYNC_DEFAULT;
    USART_InitAsync(UART0, &UART0_init);
    // USART0: see in efm32ggf1024.h
    // Set TX (PE0) and RX (PE1) pins as push-pull output and input resp.
    // DOUT for TX is 1, as it is the idle state for UART communication
    GPIO_PinModeSet(gpioPortE, 0, gpioModePushPull, 1);
    // DOUT for RX is 0, as DOUT can enable a glitch filter for inputs,
    // and we are fine without such a filter
    GPIO_PinModeSet(gpioPortE, 1, gpioModeInput, 0);
    // Use PE0 as TX and PE1 as RX (Location 1, see datasheet (not refman))
    // Enable both RX and TX for routing
    UART0->ROUTE |= UART_ROUTE_LOCATION_LOC1;
    // Select "Location 1" as the routing configuration
    UART0->ROUTE |= UART_ROUTE_TXPEN | UART_ROUTE_RXPEN;

    USART_IntClear(UART0, USART_IEN_RXDATAV);
    USART_IntEnable(UART0, USART_IEN_RXDATAV);

    NVIC_ClearPendingIRQ(UART0_RX_IRQn);
    NVIC_EnableIRQ(UART0_RX_IRQn);
}

void UART0_RX_IRQHandler(void){
   char UART_data = USART_RxDataGet(UART0); // fogadjuk az uarton erkezo karaktert

   switch(UART_data) //az erkezett karakter alapjan allitjuk be a controlt, hogy mit fogunk csinalni
   {
   case 'w': control = UP; break;
   case 's': control = DOWN; break;
   case 'a': control = LEFT; break;
   case 'd': control = RIGHT; break;
   case 'x': control = FIRE; break;
   case ' ': control = START; break;
   default: control = IDLE; break;
   }
   USART_IntClear(UART0, USART_IEN_RXDATAV); //toroljuk az interruptot
}
