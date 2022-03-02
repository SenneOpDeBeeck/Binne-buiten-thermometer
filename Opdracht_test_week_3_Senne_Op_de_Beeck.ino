////////////////////////////////  Library  ////////////////////////////////

#include <Wire.h>                                                   // Library
#include <LiquidCrystal_I2C.h>                                      // Library

LiquidCrystal_I2C lcd(0x27, 16, 2);                                 // Library


#include "DHT.h"                                                    // Library
#define DHTPIN 5                                                    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11                                               // DHT 11

DHT dht(DHTPIN, DHTTYPE);

////////

int sensorPin = A0;
int sensorValue;
int temperature = 0;
int wait = 0; 
unsigned long startTime= 0;

int tempK    = 0;
int tempC    = 0;
long sensor  = 0;

////////

const byte button1 = 3;                                             // Button1 voor waardes van sensor MQ-2
const byte button2 = 2;                                             // Button2 voor waardes van sensor LM335

volatile int state = 0;                                             // Interrupt

////////////////////////////////  Setup  ////////////////////////////////

void setup()
{
  Serial.begin(9600);                                               // Serial print opstarten
  Stippelijn();                                                     // Toont een stippenlijn op de lcd door de fuctie "stippelijn"
  Serial.println("test week 3: Binnen/buiten thermometer");         // Weergeeft op de serial print: "test week 3: Binnen/buiten thermometer"
  Stippelijn();                                                     // Toont een stippenlijn op de lcd door de fuctie "stippelijn"
  delay(100);                                                       // Delay tussen de regels
  Serial.println("*Sensoren zijn aan het opwarmen*");               // Weergeeft op de serial print: "*Sensoren zijn aan het opwarmen*"

  dht.begin();

  lcd.begin();                                                      // Lcd display start scherm
  lcd.backlight();                                                  // Lcd display start scherm
  lcd.setCursor(4, 0);                                              // Lcd display start scherm
  lcd.print("Welcome");                                             // Lcd display start scherm
  lcd.setCursor(0, 1);                                              // Lcd display start scherm
  lcd.print("- Test week 3 -");                                     // Lcd display start scherm
  delay(5000);                                                      // Lcd display start scherm
  lcd.clear();                                                      // Lcd display start scherm
  lcd.setCursor(3, 0);                                              // Lcd display start scherm
  lcd.print("Sensors are");                                         // Lcd display start scherm
  lcd.setCursor(1, 1);                                              // Lcd display start scherm
  lcd.print("Getting ready!!");                                     // Lcd display start scherm
  delay(2000);                                                      // Lcd display start scherm
  lcd.clear();                                                      // Lcd display start scherm

  pinMode(button1, INPUT_PULLUP);                                   // interrupt button 1
  pinMode(button2, INPUT_PULLUP);                                   // interrupt button 2
  attachInterrupt(digitalPinToInterrupt(button1), press1, LOW);     // interrupt button 1
  attachInterrupt(digitalPinToInterrupt(button2), press2, LOW);     // interrupt button 2
}



void loop() 
{
  delay(500);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(" (Binnen sensor)");

  sensorValue = analogRead(sensorPin);
  float temperature = map(sensorValue, 0, 410, -50, 150);
  temperature =(temperature / 10);
  temperature =(temperature - 6);
  Serial.print(F(" Temperature: "));
  Serial.print( temperature);
  Serial.println("°C (Buiten sensor)");

  
  switch (state)                                                    // Menu toont de waarde van sensor DHT11 of LM335.
  {
    case 1:                                                         // Menu van sensor DHT11
      lcd.clear();                                                  // Menu van sensor DHT11
      lcd.setCursor(1, 0);                                          // Menu van sensor DHT11
      lcd.print("Buiten sensor");                                   // Menu van sensor DHT11
      
      lcd.setCursor(0, 1);                                          // Menu van sensor DHT11
      lcd.print("H: ");                                             // Menu van sensor DHT11
      lcd.setCursor(02, 1);                                         // Menu van sensor DHT11
      lcd.print(h);                                                 // Menu van sensor DHT11 
             
      lcd.setCursor(8, 1);                                          // Menu van sensor DHT11
      lcd.print("T: ");                                             // Menu van sensor DHT11
      lcd.setCursor(10, 1);                                         // Menu van sensor DHT11
      lcd.print(t);                                                 // Menu van sensor DHT11
      break;

    case 2:                                                         // Menu van sensor LM335
      lcd.clear();                                                  // Menu van sensor LM335
      lcd.setCursor(1, 0);                                          // Menu van sensor LM335
      lcd.print("Binnen Sensor");                                   // Menu van sensor LM335

      lcd.setCursor(2, 1);                                          // Menu van sensor LM335
      lcd.print("S: ");                                             // Menu van sensor LM335
      lcd.setCursor(5, 1);                                          // Menu van sensor LM335
      lcd.print(temperature);                                       // Menu van sensor LM335
      break;

    default:                                                        // Menu van wachtstand
      lcd.clear();                                                  // Menu van wachtstand
      lcd.setCursor(2, 0);                                          // Menu van wachtstand
      lcd.print("Select Sensor");                                   // Menu van wachtstand
      lcd.setCursor(0, 1);                                          // Menu van wachtstand
      lcd.print("Buiten Of Binnen");                                // Menu van wachtstand
      break;
  }

  



}

////////////////////////////////  Functie  ////////////////////////////////


void Stippelijn()                                                   // Fuctie stippelijn
{                                                                   // Fuctie stippelijn
  Serial.println("<><><><><><><><><><><><><><><><><><><><><><>");   // Fuctie stippelijn
}                                                                   // Fuctie stippelijn

void press1()                                                       // Interrupt voor drukknop 1
{                                                                   // Interrupt voor drukknop 1
  state = 2;                                                        // Interrupt voor drukknop 1
}                                                                   // Interrupt voor drukknop 1

void press2()                                                       // Interrupt voor drukknop 2
{                                                                   // Interrupt voor drukknop 2
  state = 1;                                                        // Interrupt voor drukknop 2
}                                                                   // Interrupt voor drukknop 2
