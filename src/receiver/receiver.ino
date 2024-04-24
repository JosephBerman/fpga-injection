#include<SPI.h>
#define DATA_LENGTH 5

volatile byte data[DATA_LENGTH];
volatile byte dataCounter = 0;
volatile bool flag = false;

void setup() {

  Serial.begin(115200);

  pinMode(SS, INPUT_PULLUP);
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT); 
  pinMode(SCK, INPUT); 

  SPCR |= _BV(SPE); // SPI in peripheral  mode
  SPI.attachInterrupt();  //allows SPI interrupt

}

void loop() {
  
  if (flag){
    byte checkSum = data[4];
    
    if (checkSum != getCheckSum(data)){
      printData();
      Serial.print("Incorrect checksum");
      Serial.println();

    }
    else{
      printData();
    }


    //delay(5);
    flag = false;
    dataCounter = 0;
  }

}

//spi interupt
ISR (SPI_STC_vect) {

  byte rxData = SPDR;
  data[dataCounter++] = rxData;

  // Serial.print("Data rx: ");
  // Serial.print(data[dataCounter], HEX);
  // Serial.println();

  if (dataCounter == 5){
    flag = true;
  }
}

byte getCheckSum(byte data[4]){

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