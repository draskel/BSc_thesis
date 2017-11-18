/*
 * i2c.c
 *
 * Created: 2017. 11. 18. 21:10:12
 *  Author: Kaulics Dániel
 */ 

 #include <avr/io.h>
 #include <util/twi.h>

 #include "i2c_master.h"

 #define F_SCL 100000UL
 #define Prescaler 1
 #define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

 void i2c_init(void)
 {
	 TWBR = (unsigned char)TWBR_val;
 }

 unsigned char i2c_start(unsigned char address)
 {
	 TWCR = 0;
	 TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	 while( !(TWCR & (1<<TWINT)) );
	 if((TWSR & 0xF8) != TW_START){ return 1; }
	 TWDR = address;
	 TWCR = (1<<TWINT) | (1<<TWEN);
	 while( !(TWCR & (1<<TWINT)) );
	 unsigned char twst = TW_STATUS & 0xF8;
	 if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;
	 return 0;
 }

 unsigned char i2c_write(unsigned char data)
 {
	 TWDR = data;
	 TWCR = (1<<TWINT) | (1<<TWEN);
	 while( !(TWCR & (1<<TWINT)) );
	 if( (TWSR & 0xF8) != TW_MT_DATA_ACK ){ return 1; }
	 return 0;
 }

 unsigned char i2c_read_ack(void)
 {
	 TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	 while( !(TWCR & (1<<TWINT)) );
	 return TWDR;
 }

 unsigned char i2c_read_nack(void)
 {
	 TWCR = (1<<TWINT) | (1<<TWEN);
	 while( !(TWCR & (1<<TWINT)) );
	 return TWDR;
 }

 unsigned char i2c_transmit(unsigned char address, unsigned char* data, unsigned short length)
 {
	 if (i2c_start(address | I2C_WRITE)) return 1;

	 for (unsigned short i = 0; i < length; i++)
	 {
		 if (i2c_write(data[i])) return 1;
	 }
	 i2c_stop();
	 return 0;
 }

 unsigned char i2c_write_8(unsigned char address, unsigned char data)
 {
	 if (i2c_start(address | I2C_WRITE)) return 1;
	 if (i2c_write(data)) return 1;
	 i2c_stop();
	 
	 return 0;
 }

 unsigned char i2c_receive(unsigned char address, unsigned char* data, unsigned short length)
 {
	 if (i2c_start(address | I2C_READ)) return 1;
	 
	 for (unsigned short i = 0; i < (length-1); i++)
	 {
		 data[i] = i2c_read_ack();
	 }
	 data[(length-1)] = i2c_read_nack();
	 i2c_stop();
	 return 0;
 }

 unsigned char i2c_writeReg(unsigned char devaddr, unsigned char regaddr, unsigned char* data, unsigned short length)
 {
	 if (i2c_start(devaddr | 0x00)) return 1;
	 i2c_write(regaddr);
	 for (unsigned short i = 0; i < length; i++)
	 {
		 if (i2c_write(data[i])) return 1;
	 }
	 i2c_stop();
	 return 0;
 }

 unsigned char i2c_readReg(unsigned char devaddr, unsigned char regaddr, unsigned char* data, unsigned short length)
 {
	 if (i2c_start(devaddr)) return 1;
	 i2c_write(regaddr);
	 if (i2c_start(devaddr | 0x01)) return 1;
	 for (unsigned short i = 0; i < (length-1); i++)
	 {
		 data[i] = i2c_read_ack();
	 }
	 data[(length-1)] = i2c_read_nack();
	 i2c_stop();
	 return 0;
 }

 void i2c_stop(void)
 {
	 TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
 }
