/*
 * SoftI2CMaster.h -- Multi-instance software I2C Master library
 * 
 * 2010-2012 Tod E. Kurt, http://todbot.com/blog/
 * 2014, by Testato: update library and examples for follow Wire’s API of Arduino IDE 1.x
 *
 */

/*
   Modify support ESP-IDF by IOXhop : www.ioxhop.com
   
   .:: SimArduino-framework ::.
 */
 
#ifndef SoftI2CMaster_h
#define SoftI2CMaster_h

#define _SOFTI2CMASTER_VERSION 13  // software version of this library


class SoftI2CMaster
{

private:
  // per object data
  int _sclPin;
  int _sdaPin;
  int _sclBitMask;
  int _sdaBitMask;
  volatile int *_sclPortReg;
  volatile int *_sdaPortReg;
  volatile int *_sclDirReg;
  volatile int *_sdaDirReg;

  int usePullups;
  
  // private methods

  void i2c_writebit(char c );
  int i2c_readbit(void);
  void i2c_init(void);
  void i2c_start(void);
  void i2c_repstart(void);
  void i2c_stop(void);
  int i2c_write(char c );
  int i2c_read(char ack );
  
public:
  // public methods
  SoftI2CMaster();

  void setPins(int, int, bool);

  int beginTransmission(char);
  int endTransmission(void);
  void write(char);
  void write(char*, int);
  void write(char*);
  void begin(int, int) ;
  int requestFrom(char);
  int read(char);
  int read();
  int readLast();

};


extern SoftI2CMaster Wire;

#endif
