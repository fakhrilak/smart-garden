#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#define DHTPIN 16
#define DHTTYPE DHT11
#include <EEPROM.h>
DHT dht(DHTPIN, DHTTYPE);


String receivedwords;
String words;

void writestringwords(char addr,String words);
String readstringwords(char addr);

#define BLYNK_PRINT Serial
int WLC =A0;
int POMPA =15;
int aa;
int dd;
int celcius_1;
int menu=0;
int xxx;
String UserName,Password;
BlynkTimer timer;
char auth[] = "txxJxPvZfquxQ7JvkzaZVoOBpUQWlrTq";
char ssid[] = "vivo 1719";
char pass[] = "ZILOG-80";
WidgetLCD lcd(V3);
int a;
int b;
int c;
void setup() {                                                     
  pinMode(POMPA,OUTPUT);
  pinMode(WLC,INPUT);
  Blynk.begin(auth, ssid, pass);
  digitalWrite(15,0);
  Serial.begin(9600); 
  Serial.println("Pengujian DHT11!");
  dht.begin();
}
BLYNK_WRITE(V0)
{
  if (param.asInt()==1)
  {
    a=1;
  }
  else
  {
    a=0;
  }
}
BLYNK_WRITE(V1)
{
  if (param.asInt()==1)
  {
    b=1;
  }
  else
  {
    b=0;
  }
}
BLYNK_WRITE(V2)
{
  if (param.asInt()==1)
  {
    c=1;
  }
  else
  {
    c=0;
  }
}
BLYNK_WRITE(V5)
{
  
  if (param.asInt()==1)
  {
    dd = 1;
  }
  else 
  {
    dd= 0;
  }
}

void sensorsuhu()
{
  delay(1000);
  
  float humidity_1 = dht.readHumidity();
  
 celcius_1 = dht.readTemperature();
  
  float fahrenheit_1 = dht.readTemperature(true);
 
 
  if (isnan(humidity_1) || isnan(celcius_1) || isnan(fahrenheit_1)) {
    Serial.println("Pembacaan data dari module sensor gagal!");
    return;
  }
 
  float htof = dht.computeHeatIndex(fahrenheit_1, humidity_1); 
  
  float htoc = dht.computeHeatIndex(celcius_1, humidity_1, false);
 
  Serial.print("Kelembaban: ");
  Serial.print(humidity_1);
  Serial.print(" %\t");
  
  Serial.print("Suhu : ");
  Serial.print(celcius_1); 
  Serial.print(" 'C ");
  Serial.print(fahrenheit_1); 
  Serial.print(" 'F\t");
 
  Serial.print("Indeks Panas: ");
  Serial.print(htof); 
  Serial.println(" *F");
 
  Serial.print(htoc);
  Serial.println(" *C ");
}
BLYNK_WRITE(V8){
   xxx = param.asInt();
   
}
void loop()
{ 
  lcd.setCursor(0,0);
  Serial.println(aa);
  Blynk.run();
  timer.run();
  if (a==1 && b==0)
  {
    Serial.println("MODE SUHU");
    lcd.print(0,0,"MODE KELEMBABAN");
    int zz = aa/4;
    Blynk.virtualWrite(V6,zz);
    aa = analogRead(WLC);
    Serial.println(aa);
    sensorsuhu();
    lcd.print(0,1,celcius_1);
    lcd.print(2,1,"°C");
    Serial.println(xxx);
    if (zz>= xxx)
    {
      digitalWrite(POMPA,HIGH);
    }
    else
    {
      digitalWrite(POMPA,LOW);
    }
  }
  else if(a==0 && b==1)
  { 
    Serial.println("MODE JADWAL");
    lcd.print(0,0,"MODE JADWAL     ");
    sensorsuhu();
    lcd.print(0,1,celcius_1);
    lcd.print(2,1,"°C");
        if (dd==1)
    {
      digitalWrite(POMPA,HIGH);
    }
    else
    {
      digitalWrite(POMPA,LOW);
    }
     
  }
  else
  {
    Serial.println("MODE MANUAL");
    lcd.print(0,0,"MODE MANUAL     ");
    sensorsuhu();
    lcd.print(0,1,celcius_1);
    lcd.print(2,1,"°C");
    if (c == 1)
    {
      digitalWrite(POMPA,HIGH);
    }
    else
    {
      digitalWrite(POMPA,LOW);
    }
   }
  }
  
