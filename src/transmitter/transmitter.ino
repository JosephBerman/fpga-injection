
#include <SPI.h>

#define CLK_SPEED 100
#define DATA_LENGTH 5

#define ss 10


SPISettings spiConfig(CLK_SPEED, MSBFIRST, SPI_MODE0);

byte data[DATA_LENGTH] = {0xA1, 0xB2, 0xC3, 0xD4, 0};

void setup() {
  Serial.begin(115200);


  pinMode(ss, OUTPUT);
  SPI.begin();
  
}

void loop() {

  //tell receiver to listen
  digitalWrite(ss, LOW);

  
  SPI.beginTransaction(spiConfig);

  data[4] = checkSum(data);

  printData();
  for (int i = 0; i < DATA_LENGTH; i++){
    SPI.transfer(data[i]);
  }
  
    
  SPI.endTransaction();

  //tell receiver to stop
  digitalWrite(SS, HIGH);

}



byte checkSum(byte data[5]){

  return data[0] ^ data[1] ^ data[2] ^ data[3];

}

void printData(){
 
  Serial.print("{");
  for (int i = 0; i < DATA_LENGTH-1; i++){
    Serial.print(data[i], HEX);
    Serial.print(",");
  }

  Serial.print(data[4], HEX);
  Serial.print("}");
  Serial.println();
}
