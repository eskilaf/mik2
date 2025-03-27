#include "uart.h"
#include "gpio.h"




void uart_init()
{
    //RTS
    //GPIO->PIN_CNF[5] = (3 << 2) | (1 << 0);

    //TXD
    GPIO->PIN_CNF[6] = (3 << 2) | (1 << 0);

    //CTS
    //GPIO->PIN_CNF[7] = (3 << 2) | (0 << 0);

    //RXD
    GPIO->PIN_CNF[8] = (3 << 2) | (0 << 0);

    UART->PSELTXD = 6;
    UART->PSELRXD = 8;
    
    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;



    UART->BAUDRATE = 0x00275000;

    UART->ENABLE = 4;

    


    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter)
{
    UART->TASKS_STARTTX = 1;
   
   
    UART->TXD = letter;
    while (UART->EVENTS_TXDRDY == 0);
    UART->EVENTS_TXDRDY = 0;

    UART->TASKS_STOPTX = 1;
}

char uart_read()
{
    //UART->EVENTS_RXDRDY = 0;

    char letter = 0;

    while (UART->EVENTS_RXDRDY == 0)

    letter = UART->RXD;

    
    if (UART->EVENTS_RXDRDY) {   
        letter = UART->RXD;
    } else {
        letter = '\0';
    }
    

    UART->EVENTS_RXDRDY = 0;

    


    return letter;
}