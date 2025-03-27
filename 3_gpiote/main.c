#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main() {
    // Configure LED Matrix
    for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
    //Skru av lys
    GPIO->OUT = (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20);

    
}