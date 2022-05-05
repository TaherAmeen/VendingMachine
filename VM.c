/*******************************************************
This program was created by the CodeWizardAVR V3.31
Automatic Program Generator
© Copyright 1998-2017 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 25/11/2018
Author  :
Company :
Comments:


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <io.h>
#include <alcd.h>
#include <delay.h>

// Declare your global variables here
unsigned char get_key();
void EE_WriteC(char adr, char data);
char EE_ReadC(char adr);
char item = '';
char tempo = 0;
char admBtn = '';
char *names[] = {"Chocolate", "Drink", "Candy", "Potato"};
volatile unsigned char Prices[] = {0, 0, 0, 0};
char address = '';
char pr = '';
char inturr = 0;
volatile unsigned char i = 0;
// External Interrupt 1 service routine


void main(void)
{
	// Declare your local variables here
	//	volatile unsigned char i = 0;  // for FOR loops
	DDRB = 0b11111110;
	DDRC = 0b00000111; // For KeyPad
	PORTD = 0b00001000;
	PORTC = 0b11111000; // Enable internal pull-up for 4 rows.

	EE_WriteC(0, 3);
	EE_WriteC(1, 5);
	EE_WriteC(2, 4);
	EE_WriteC(3, 5);

	TCCR0 = (1 << CS02) | (1 << CS01) | (0 << CS00);

	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: On
	// INT1 Mode: Falling Edge
	// INT2: Off
	GICR |= (1 << INT1) | (0 << INT0) | (0 << INT2);
	MCUCR |= (1 << ISC11) | (0 << ISC10) ;

	lcd_init(16);

	// Globally enable interrupts
#asm("sei")

	while (1)
		{
		for (i = 0 ; i < 4 ; i++)
			Prices[i] = EE_ReadC(i);
		TCNT0 = 0;



		lcd_clear();
		lcd_puts("Choose an item");
		lcd_gotoxy(0, 1);
		lcd_puts("1 -> 4");
		delay_ms(1500);
		lcd_clear();
		lcd_puts("1:Chco 2:Drink");
		lcd_gotoxy(0, 1);
		lcd_puts("3:Candy 4:Potato");

		item = get_key();

		if(inturr == 1)
			{
			inturr = 0;
			continue;
			}

		while (item != 1 && item != 2 && item != 3 && item != 4)item = get_key();
		if(inturr == 1)
			{
			inturr = 0;
			continue;
			}
		inturr = 2;
		lcd_clear();
		lcd_puts(names[item - 1]);
		lcd_gotoxy(0, 1);
		if(Prices[item - 1] == 0)
			lcd_puts("it's free :)");
		else
			{
			lcd_puts("Price = ");
			lcd_putchar(Prices[item - 1] + 48);
			}
		delay_ms(2000);
		lcd_clear();
		lcd_puts("Enter coins");
		TCNT0 = 0;
		lcd_gotoxy(0, 1);
		tempo = 0;
		while(TCNT0 < Prices[item - 1])
			{
			if(tempo < TCNT0)
				{
				lcd_gotoxy(0, 1);
				lcd_putchar(TCNT0 + 48);
				tempo = TCNT0;
				}
			}

		delay_ms(200);
		PORTD.2 = 0;
		lcd_clear();
		lcd_puts("Grab your item");
		if(item == 1)PORTB.2 = 1;
		else if (item == 2)PORTB.3 = 1;
		else if(item == 3)PORTB.4 = 1;
		else if(item == 4)PORTB.5 = 1;
		delay_ms(3000);
		PORTB = 0;
		inturr = 0;
		}


}


char get_key()
{
	while (inturr == 0)
		{

		PORTC.0 = 0;  //Activate C1 by "Low"
		PORTC.1 = 1;  //Deactivate C2 by High
		PORTC.2 = 1;  //Deactivate C3 by High

		switch (PINC)
			{
			case 0b11110110 :
				while (PINC.3 == 0) ; // Hang execution untill switch is released
				return 1;
				break;

			case 0b11101110 :
				while (PINC.4 == 0) ; // Hang execution untill switch is released
				return 4;
				break;

			case 0b11011110 :
				while (PINC.5 == 0) ; // Hang execution untill switch is released
				return 7;
				break;

			case 0b10111110 :
				while (PINC.6 == 0) ; // Hang execution untill switch is released
				return 10;
				break;
			}

		PORTC.0 = 1;  //Deactivate C1 by High
		PORTC.1 = 0;  //Activate C2 by low
		PORTC.2 = 1;  //Deactivate C3 by High

		switch (PINC)
			{
			case 0b11110101 :
				while (PINC.3 == 0) ; // Hang execution untill switch is released
				return 2;
				break;

			case 0b11101101 :
				while (PINC.4 == 0) ; // Hang execution untill switch is released
				return 5;
				break;

			case 0b11011101 :
				while (PINC.5 == 0) ; // Hang execution untill switch is released
				return 8;
				break;

			case 0b10111101 :
				while (PINC.6 == 0) ; // Hang execution untill switch is released
				return 0;
				break;
			}

		PORTC.0 = 1;  //Deactivate C1 by High
		PORTC.1 = 1;  //Deactivate C2 by High
		PORTC.2 = 0;  //Activate C3 by Low

		switch (PINC)
			{
			case 0b11110011 :
				while (PINC.3 == 0) ; // Hang execution untill switch is released
				return 3;
				break;

			case 0b11101011 :
				while (PINC.4 == 0) ; // Hang execution untill switch is released
				return 6;
				break;

			case 0b11011011 :
				while (PINC.5 == 0) ; // Hang execution untill switch is released
				return 9;
				break;

			case 0b10111011 :
				while (PINC.6 == 0) ; // Hang execution untill switch is released
				return 11;
				break;
			}
		}
}

void EE_WriteC(char adr, char data)
{
	while (EECR.1 == 1);
	EEDR = data;
	EEAR = adr;
	EECR.2 = 1;  //Enable Master Write;
	EECR.1 = 1;  // Begin writing;
}

char EE_ReadC(char adr)
{
	while (EECR.1 == 1);
	EEAR = adr;
	EECR.0 = 1; //Begin Reading
	return EEDR;
}

interrupt [EXT_INT1] void ext_int1_isr(void)
{
	// Place your code here

	if(inturr == 2)
		{
		lcd_clear();
		lcd_puts("Wait for the");
		lcd_gotoxy(0, 1);
		lcd_puts("current trans");
		delay_ms(2000);
		lcd_clear();
		lcd_puts("Continue");
		lcd_gotoxy(0, 1);
		if(TCNT0 < Prices[item - 1])
			lcd_putchar(TCNT0 + 48);
		}
	else
		{
		do
			{
			lcd_clear();
			lcd_puts("Enter item");
			lcd_gotoxy(0, 1);
			lcd_puts("number");
			address = get_key();
			while (address != 1 && address != 2 && address != 3 && address != 4)address = get_key();
			lcd_clear();
			lcd_puts("Enter new price");
			pr = get_key();
			while(pr == 10 || pr == 11)pr = get_key();
			EE_WriteC(address - 1, pr);
			lcd_clear();
			lcd_puts("Price changed");
			delay_ms(2000);
			lcd_clear();
			lcd_puts("Exit : *");
			lcd_gotoxy(0, 1);
			lcd_puts("continue :else");
			admBtn = get_key();
			}
		while(admBtn != 10);
		inturr = 1;
		}


}



