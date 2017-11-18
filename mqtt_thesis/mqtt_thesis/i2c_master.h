/*
 * i2c.h
 *
 * Created: 2017. 11. 18. 21:10:48
 *  Author: Kaulics Dániel
 */ 


#ifndef __I2C_MASTER_H__
#define __I2C_MASTER_H__

#define I2C_READ 0x01
#define I2C_WRITE 0x00

void i2c_init(void);
unsigned char  i2c_start(unsigned char  address);
unsigned char  i2c_write(unsigned char  data);
unsigned char  i2c_read_ack(void);
unsigned char  i2c_read_nack(void);
unsigned char  i2c_transmit(unsigned char  address, unsigned char* data, unsigned short length);
unsigned char  i2c_receive(unsigned char  address, unsigned char * data, unsigned short length);
unsigned char  i2c_writeReg(unsigned char  devaddr, unsigned char  regaddr, unsigned char * data, unsigned short length);
unsigned char  i2c_readReg(unsigned char  devaddr, unsigned char  regaddr, unsigned char * data, unsigned short length);
unsigned char i2c_write_8(unsigned char address, unsigned char data);
void i2c_stop(void);

#endif // I2C_MASTER_H