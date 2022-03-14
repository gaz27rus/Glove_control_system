#include<ADS1115_WE.h> 
#include<Wire.h>
#include <Adafruit_ADS1X15.h>

const int sensors_count = 6;

Adafruit_ADS1115 ads[sensors_count];

#define AD1115_I2C_ADDRESS 0x48
#define TCA_I2C_ADDRESS    0x70

void setup() {
  Wire.begin();
  Serial.begin(9600);

  for (int i = 0; i < sensors_count; i++)
  {
    if (i == 1) continue;
    setTCAChannel(i);
    ads[i].setGain(GAIN_TWOTHIRDS);
    ads[i].begin();
  }
}

void loop() {
  for (int i = 0; i < sensors_count; i++)
  {
    if (i == 1) continue;
    setTCAChannel(i);
    
    for (int j = 0; j < 4; j++)
    {
      if ((i == 2 || i == 5) && j == 2) continue;
      if (i == 0 && j == 0) continue;
      Serial.print(ads[i].readADC_SingleEnded(j));
      Serial.print(" ");
    }
  }
  Serial.println();

  //Serial.println("****************************");  
  //delay(10);
}

void setTCAChannel(byte i){
  Wire.beginTransmission(TCA_I2C_ADDRESS);
  Wire.write(1 << i);
  Wire.endTransmission();  
}
