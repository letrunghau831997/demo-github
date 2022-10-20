#include <BH1750.h>
#include "DHT.h"
#include "RTClib.h"

#define DHTTYPE DHT11
#define DHTPIN 2 
DHT dht(DHTPIN, DHTTYPE);
RTC_DS1307 rtc;
BH1750 lightMeter;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void setup() {
  Serial.begin(9600); 
  dht.begin();
  
  Serial.begin(115200);
    Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  lightMeter.begin();
  Serial.println(F("BH1750 Test begin"));

   while (!Serial); // for Leonardo/Micro/Zero
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float lux = lightMeter.readLightLevel();
    DateTime now = rtc.now();
    if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.print(" *C");
    Serial.print("   Light Intensity: ");
    Serial.print(t);
    Serial.println(" Lux");
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);
    Serial.println();
    char humidityChar[8]; // Buffer big enough for 7-character float
    dtostrf(lux, 6, 2, humidityChar);
    Serial.write(humidityChar, 8); //Write the serial data
    char temperatureChar[8]; // Buffer big enough for 7-character float
    dtostrf(lux, 6, 2, temperatureChar);
    Serial.write(temperatureChar, 8); //Write the serial data
    char lightChar[8]; // Buffer big enough for 7-character float
    dtostrf(lux, 6, 2, lightChar);
    Serial.write(lightChar, 8); //Write the serial data
    delay(3000);
  }
}
