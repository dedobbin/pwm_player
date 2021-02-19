#include <SPI.h>
#include "sram.h"

void ram_init()
{
  SPI.begin();
  pinMode(SS_PIN, OUTPUT);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
}

void ram_read(char* output, long addr, long len)
{
  digitalWrite(SS_PIN, LOW); 
  SPI.transfer(WRSR);
  SPI.transfer(0x40 | 1); // Stream mode, hold line disabled
  digitalWrite(SS_PIN, HIGH);  
      
  digitalWrite(SS_PIN, LOW); 
  SPI.transfer(RDSR);
  int mode=SPI.transfer(0xFF);
  digitalWrite(SS_PIN, HIGH);  

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(READ);
  SPI.transfer((char)(addr >> 16)); // Should be skipped for some other chips, not 23LCV1024
  SPI.transfer((char)(addr >> 8));
  SPI.transfer((char)addr);
      
  long i = 0;
  for (i = 0; i < len; i++) {
    output[i] = SPI.transfer(0xFF);
  }
  digitalWrite(SS_PIN, HIGH); // disable
}

void ram_write(char* input, long addr, long len)
{
  digitalWrite(SS_PIN, LOW);  
  SPI.transfer(WRSR);
  SPI.transfer(0x40 | 1); // Stream mode, hold line disabled
  digitalWrite(SS_PIN, HIGH);  
  
  digitalWrite(SS_PIN, LOW); 
  SPI.transfer(RDSR);
  int mode = SPI.transfer(0xFF); 
  digitalWrite(SS_PIN, HIGH);  

  digitalWrite(SS_PIN, LOW); 
  SPI.transfer(WRITE);
  SPI.transfer((char)(addr >> 16)); // Should be skipped for some other chips, not 23LCV1024
  SPI.transfer((char)(addr >> 8));
  SPI.transfer((char)addr);
  long i;
  for (i = 0; i < len; i++) {
      SPI.transfer(input[i]);
  }
  digitalWrite(SS_PIN, HIGH); 
}
