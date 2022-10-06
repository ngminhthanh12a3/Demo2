#include <Arduino.h>

//////////////////////////////////////////////
//   Easy Module Shield Weather Station     //
//                                          //
//           http://www.educ8s.tv           //
/////////////////////////////////////////////

#include "DHT.h"
// #include <LiquidCrystal_I2C.h>

// cam bien hong ngoai
#include <IRremote.h>
#include <EasyBuzzer.h>

#define DHTPIN 4
#define DHTTYPE DHT11

//
#define LM35PIN A2
#define IR_RECV_PIN DDD6

float humidity = 0;
float temperature = 0;
float light = 0;

//
float LM35_value = 0;

DHT dht(DHTPIN, DHTTYPE);

// CB hong ngoai
IRrecv irrecv(IR_RECV_PIN);
decode_results results;

// LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address
void readHumidityDHT();
void readTemperatureDHT();
void readLight();
void printText();
void ReadLM35();

void setup()
{
  dht.begin();
  // lcd.begin(20, 4);
  // printText();

  //
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  EasyBuzzer.setPin(pin);
}

void loop()
{
  readHumidityDHT();
  readTemperatureDHT();
  readLight();

  //
  ReadLM35();

  // printData();
  printText();
  delay(1000);
}

void printText()
{
  Serial.print("\nWeather Station: ");
  Serial.print("\n\tTemperature DTH: ");
  Serial.print(temperature);
  Serial.print("\n\tHumidity DTH: ");
  Serial.print(humidity);
  Serial.print("\n\tLight: ");
  Serial.print(light);

  Serial.print("\n\tTemperature LM35: ");
  Serial.print(LM35_value);

  if (irrecv.decode(&results))
  {
    Serial.print("\n\tIR1838: ");
    Serial.print(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}

void readHumidityDHT()
{
  humidity = dht.readHumidity();
}

void readTemperatureDHT()
{
  temperature = dht.readTemperature(); // Celsius
}

void readLight()
{
  light = analogRead(A1);
  light = map(light, 200, 1023, 0, 100);
}

// void printData()
// {
//   lcd.setCursor(13, 1);
//   lcd.print(temperature);
//   lcd.setCursor(13, 2);
//   lcd.print(humidity);
//   lcd.setCursor(13, 3);
//   lcd.print(light);
// }

//
void ReadLM35()
{
  int reading = analogRead(LM35PIN);
  float voltage = reading * 5.0 / 1024.0;
  LM35_value = voltage * 100.0;
}