// Jack Berkowitz
// Lab 2, Mechatronics
// 1/23/24 


#include <avr/io.h>

void change_state(char);
void wait(volatile int);

int main(void)
{
	int states = 22;
	char pattern[] = {'A','C','B','C','A','C','A','D','A','D','B','C','B','C','A','D','B','C','B','C','B','E'};
	int flag=0;
	
	DDRD = 0b00000000; //all pins set as inputs (includes PD2, attached to switch)
	DDRC = 0b00000011; //pins PCO & PC1 set as output for LEDs
	PORTC = 0b00000011; //turn off the LEDS (assumes they are wired as active low)
	
	// ==================
	// PROGRAM LOOP
	// ==================
	
	if(flag==0)
	{
	while(PIND & 0b00000100) {} //will run forever when PD2 is high (switch not pressed)
	flag++;
	}
	
	while(1)
	{
		for (int i=0; i<states; i++)
		{
				change_state(pattern[i]);
		}
			
	}
}	
		
	
void change_state(char new_state)
{
	switch(new_state)
	{
		case 'A': //short "on"
			PORTC = 0b00000000; //turn on LEDs
			wait(200);
		break;
		case 'B': //long "on"
			PORTC = 0b00000000; //turn on LEDs
			wait(600);
		break;
		case 'C': //short "off"
			PORTC = 0b00000011; //turn off LEDs
			wait(200);
		break;
		case 'D': //long "off"
			PORTC = 0b00000011; //turn off LEDs
			wait(600);
		break;
		case 'E':
			PORTC = 0b00000011; //turn off LEDs
			wait(2000);
		break;
	}
	while(!(PIND & 0b00000100)) //will run when switch is pressed, pause the pattern		
	{
		wait(50); //switch debounce
	}
	
}

void wait(volatile int multiple)
{
	while(multiple > 0)
	{
		TCCR0A = 0x00; //clears WGM00 and WGM01 (bits 0 and 1) to ensure timer/counter is in normal mode
		TCNT0 = 0; //preload value for testing on count = 250
		TCCR0B = 0b00000011;
		while(TCNT0 < 0xFA); //exits when count = 250 (req. preload of 0 to make count 250)
		TCCR0B = 0x00;//stop timeR0
		multiple--;
	}
}
		
	

		
