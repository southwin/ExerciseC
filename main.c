/*
 * DongHo.c
 *
 * Created: 10/9/2017 9:46:43 PM
 * Author : ASUS
 */ 
// thêm dòng chú thích này
#include <avr/io.h>
#define F_CPU 1200000UL
#include <util/delay.h>
#include <avr/interrupt.h> 
char gio=11,phut=58,giay=0;
char h1=0,h2=0,h3=0,h4=0,h5=0,h6=0;
char so[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};                         
//----------------------------------------------------------------------------------------------
void tachSo(int dem, char *h1, char *h2)
{
	*h1=dem/10;
	*h2=dem%10;
}
//----------------------------------------------------------------------------------------------
void hienThiLed(char h1, char h2, char h3, char h4, char h5, char h6)
{
	PORTA=~0x01;
	PORTC=so[h1];
	_delay_ms(1);
	PORTA=0x01;

	PORTA=~0x02;
	PORTC=so[h2];
	_delay_ms(1);
	PORTA=0x02;

	PORTA=~0x04;
	PORTC=0xbf;
	_delay_ms(1);
	PORTA=0x04;

	PORTA=~0x08;
	PORTC=so[h3];
	_delay_ms(1);
	PORTA=0x08;

	PORTA=~0x10;
	PORTC=so[h4];
	_delay_ms(1);
	PORTA=0x10;

	PORTA=~0x20;
	PORTC=0xbf;
	_delay_ms(1);
	PORTA=0x20;

	PORTA=~0x40;
	PORTC=so[h5];
	_delay_ms(1);
	PORTA=0x40;

	PORTA=~0x80;
	PORTC=so[h6];
	_delay_ms(1);
	PORTA=0x80;
}
//----------------------------------------------------------------------------------------------
int main(void)
{
	int i=0;
	DDRC=0xff;
	DDRA=0xff;
	DDRD=0x00;
	MCUCR|=(1<<ISC11)|(1<<ISC01);
	GICR|=(1<<INT1)|(1<<INT0);
	sei();
    while (1) 
    {
		for(;gio<24;gio++)
		{
			tachSo(gio, &h1, &h2);
			for(;phut<60;phut++)
			{
				tachSo(phut, &h3, &h4);
				for(;giay<60;giay++)
				{
					tachSo(giay, &h5,&h6);
					for(i=0;i<82;i++)
					{
					hienThiLed(h1,h2,h3,h4,h5,h6);	
					}
				}
				giay=0;
			}
			phut=0;
		}
		gio=0;
    }
	return 0;
}
//----------------------------------------------------------------------------------------------
ISR(INT1_vect)
{
	gio++;
	if(gio>23) gio=0;
	tachSo(gio, &h1, &h2);
}
ISR(INT0_vect)
{
	phut++;
	if(phut>59) {phut=0;gio++;}
	tachSo(gio, &h1, &h2);
	tachSo(phut, &h3, &h4);
}

