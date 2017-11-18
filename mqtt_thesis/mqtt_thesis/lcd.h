#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define CMD_RS	PORTF1 //PORTF pin 1
#define CMD_RW	PORTF2 //PORTF pin 2
#define CMD_EN	PORTF3 //PORTF pin 3

#define LCD_EN	2	//enable
#define LCD_CUR	1	//cursor
#define LCD_BL	0	//blink

void LCD_init();
void LCD_clock();
void LCD_command(unsigned char val);
void LCD_data(unsigned char val);
void LCD_goto(unsigned char row, unsigned char col);
void LCD_creatctg();
void LCD_Puts (char*s);
void LCD_Put_int(int val);
#endif /* LCD_H_ */