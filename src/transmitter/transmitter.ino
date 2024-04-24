
#include <SPI.h>

#define CLK_SPEED 10000
#define DATA_LENGTH 4

#define ss 10


SPISettings spiConfig(CLK_SPEED, MSBFIRST, SPI_MODE0);

byte data[DATA_LENGTH] = {0xA1, 0xB2, 0xC3, 0xD4};

void setup() {
  pinMode(ss, OUTPUT);
  SPI.begin();
  
}

void loop() {

  //tell receiver to listen
  digitalWrite(ss, LOW);

  
  SPI.beginTransaction(spiConfig);

  for (int i = 0; i < DATA_LENGTH; i++){
    SPI.transfer(data[i]);
  }
  
  SPI.transfer(checkSum(data));
    
  SPI.endTransaction();

  //tell receiver to stop
  digitalWrite(SS, HIGH);

}



byte checkSum(byte data[4]){

  return data[0] ^ data[1] ^ data[2] ^ data[3];

}
