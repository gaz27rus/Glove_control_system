#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads; 

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70); // TCA9548A адрес 0x70
  Wire.write(1 << bus); // отправляем байт на выбранную шину
  Wire.endTransmission();
}
void setup()
{
  Wire.begin();
  ads.setGain(GAIN_TWOTHIRDS);
  ads.begin(); // Инициализация модуля ADS1115
}

void loop()
{
  uint16_t adc[4];
  
  for (int i = 0; i < 4; i++)
  {
    TCA9548A(i);
    for (int i = 0; i < 4; i++)
    {
      adc[i] = ads.readADC_SingleEnded(i);
    }
  }
}
