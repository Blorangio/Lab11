#include "LIS3DH.h"
#include "oled-wing-adafruit.h"

#define accelerometerChipSelect D3

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

OledWingAdafruit display;

LIS3DHConfig config;
LIS3DHSample sample;
LIS3DHSPI accel(SPI, accelerometerChipSelect, WKP);

double xMovement;
double yMovement;
double zMovement;

void setup()
{
  display.setup();
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  config.setAccelMode(LIS3DH::RATE_100_HZ);
  accel.setup(config);
  Serial.begin(9600);
}
void loop()
{
  display.clearDisplay();
  display.setCursor(0, 0);

  if (accel.getSample(sample))
  {
    xMovement = round(sample.x / (32768.0 / 2.0) * 100.0) / 100.0;
    yMovement = round(sample.y / (32768.0 / 2.0) * 100.0) / 100.0;
    zMovement = round(sample.z / (32768.0 / 2.0) * 100.0) / 100.0;

    display.printf("movement x %f \nmovement y %f \nmovement z %f", xMovement, yMovement, zMovement);

    Serial.println();
    Serial.println(xMovement);
    Serial.println(yMovement);
    Serial.println(zMovement);
  }

  display.display();
}