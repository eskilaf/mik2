#include "uart.h"
#include "gpio.h"

#include <stdio.h>
#include <sys/types.h> // For ssize_t

void uart_send_str(char ** str){
    UART->TASKS_STARTTX = 1;
    char * letter_ptr = *str;
    while(*letter_ptr != '\0'){
        UART->TXD = *letter_ptr;
        while(!UART->EVENTS_TXDRDY);
        UART->EVENTS_TXDRDY = 0;
        letter_ptr++;

    }
}

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
        uart_send(*letter);
        letter++;
    }
    return count;
}

int main() {

    	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
	
    GPIO->PIN_CNF[13] = (3 << 2);
	
	GPIO->PIN_CNF[14] = (3 << 2);

    uart_init();


    int variabel = 0;
    
    
    int sleep = 0;
	while(1){
        uart_send_str((char **)iprintf("The average grade in TTK%d was in %d was: %c\n\r",4235, 2022, 'B'));

        //Recieve
        if(0) {

            char letter = uart_read();

            if (letter != '\0') {
                if (variabel) {
                    GPIO->OUT = 0x0;
                } else {
                    GPIO->OUT = (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20);
                }
                variabel = (variabel + 1) % 2;
                letter = 0;
            
            }
        }
		
        if (0) {
            uart_send('a');
        }

        //Send
        if (0) {
            /* Check if button 1 is pressed;
            * turn on LED matrix if it is. */
            if (!(GPIO->IN & (1 << 13))) {
                GPIO->OUT = 0x0;
                uart_send('A');
            }
            
            /* Check if button 2 is pressed;	// Configure LED Matrix
            for(int i = 17; i <= 20; i++){
            GPIO->DIRSET = (1 << i);
            GPIO->OUTCLR = (1 << i);
            }
        
            * turn off LED matrix if it is. */
        
            if (!(GPIO->IN & (1 << 14))) {
                GPIO->OUT = (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20);
                uart_send('B');
            }

        }   

        sleep = 10000000;
        while (--sleep);
        }
	return 0;
}