 //Anemometer data logger code,logging the average every 10sec
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"

RTC_DS1307 rtc;
unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
const long interval = 10000; 


const int chipSelect = 4;
float sum = 0;
int v =0; 
float avg = 0;
float sum2 = 0;
int v2 =0; 
float avg2 = 0;
 void setup()
{
   Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

 
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {

float velocity;
int analogin = analogRead(A0);
float voltage = analogin * (5.0 / 1023.0);
velocity=(((voltage-0)/(5-0))*50);

float velocity2;
int analogin2 = analogRead(A1);
float voltage2 = analogin2 * (5.0 / 1023.0);
velocity2=(((voltage2-0)/(5-0))*50);

 Serial.print("   velocity:");
 Serial.println(velocity);
 Serial.print("   voltage:");
 Serial.println(voltage);

 




unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    //j   Serial.print(" (");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
      avg = sum/v;
       avg2 = sum2/v2;
   String dataString = "";
   
   
 
   dataString += String(now.day(), DEC) + "/" +String(now.month(), DEC) +  "/" + String(now.year(), DEC)  + " , " + String(now.hour(), DEC) + ":" +  String(now.minute(), DEC)+ ":" + String(now.second(), DEC);
   dataString += " , ";
   dataString += String(avg);
   dataString += " , ";
   dataString += String(avg2);
   avg=0;
   sum=0;
   v=0;
   avg2=0;
   sum2=0;
   v2=0;
   File dataFile = SD.open("AirLOGvc.txt", FILE_WRITE);
   delay(500);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
    Serial.println("Success");
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
   
  
   
  }

 else {
   sum = velocity+sum;
   v++;
    sum2 = velocity+sum2;
   v2++;
  }
 }
