#include "AdafruitIO_WiFi.h"
#define AIO_SERVER      "io.adafruit.com" //Adafruit Server
#define AIO_SERVERPORT  1883       


#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 //กำหนดขาที่จะเชื่อมต่อ Sensor 2 = d4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ตั้งค่า key ของ Adafruit IO
#define IO_USERNAME  "uuii"
#define IO_KEY       "aio_paiU24xGhITAyEshzSjPvslCOJNQ"

// ตั้งค่าชื่อ wifi
#define WIFI_SSID "who"
#define WIFI_PASS "Lamng5641"
int ledPin = 4;
int ledPin2 = 0;
int motorpin2 = 16;
int motorpin = 15;
// #define DHTPIN 2 // DHT ต่อกับขา 2
// #define DHTTYPE 11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS); // สร้างออปเจกชื่อ io สำหรับติดต่อ Adafruit IO
AdafruitIO_Feed *temp = io.feed("temp"); // สร้างออปเจกสำหรับติดต่อ feed ชื่อ temp
AdafruitIO_Feed *Turbidity = io.feed("Turbidity"); 
AdafruitIO_Feed *pump = io.feed("pump");
AdafruitIO_Feed *light = io.feed("light");
AdafruitIO_Feed *motor = io.feed("motor");
AdafruitIO_Feed *Auto = io.feed("auto");

bool checkauto = false;

//DHT dht(ONE_WIRE_BUS, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(motorpin,OUTPUT);
  pinMode(motorpin2,OUTPUT);
  digitalWrite(ledPin,1);
  analogWrite(motorpin,0);
  while (! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect(); // เริ่มเชื่อมต่อ Adafruit IO

  while (io.status() < AIO_CONNECTED) { //เช็คว่าเชื่อมต่อสำเร็จ
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText()); //แสดงข้อความสถานะการเชื่อมต่อกับ Adafruit IO
  pump->onMessage(handleMessage);
  light->onMessage(handleMessage2);
  Auto->onMessage(handleMessage3);
  motor->onMessage(handleMessage4);
  sensors.begin();
  pump->get();   
  light->get();    
  Auto->get();
  motor->get();
}

void loop() {
  // หน่วงเวลา 4 วินาทีเพื่อให้เซนเซอร์ทำงาน
  delay(4000);
  Serial.println("Requesting temperatures...");
  sensors.requestTemperatures(); //อ่านข้อมูลจาก library
  Serial.print("Temperature is: ");
  Serial.print(sensors.getTempCByIndex(0)); // แสดงค่า อูณหภูมิ 
  Serial.println(" *C");
  io.run();
  float t = sensors.getTempCByIndex(0); // อ่านค่าอุณหภูมิ
  int sensorValue = analogRead(A0);
  temp->save(t);// ส่งค่าไปที่ feed ชื่อ temp
  Turbidity->save(sensorValue);
  Autos(t,sensorValue);
  Serial.println(sensorValue);
  Serial.println("Temp : ");
  Serial.println(t);
}
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  if(!checkauto){
    if(data->toPinLevel() == 1){
      Serial.println("HIGH");
      digitalWrite(ledPin,1);
    }
    else{
      digitalWrite(ledPin,0);
      Serial.println("LOW");
    }
  }
  Serial.println(data->value());
}
void handleMessage2(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  if(!checkauto){
    if(data->toPinLevel() == 1){
      Serial.println("HIGH");
      digitalWrite(ledPin2,1);
    }
    else{
      digitalWrite(ledPin2,0);
      Serial.println("LOW");
    }
  }
  Serial.println(data->value());
}
void handleMessage3(AdafruitIO_Data *data) {

  Serial.print("sdafd");
  if(data->toPinLevel() == 1){
    checkauto = true;
  }
  else{
    checkauto = false;
  }
}
void handleMessage4(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  if(!checkauto){
    if(data->toPinLevel() == 2){
      Serial.println("level 2");
      digitalWrite(motorpin,1);
      digitalWrite(motorpin2,1);
    }else if(data->toPinLevel() == 1){
      Serial.println("level 1");
      digitalWrite(motorpin,0);
      digitalWrite(motorpin2,1);
    }else{
      digitalWrite(motorpin2,0);
      digitalWrite(motorpin,0);
    }
  }
  Serial.println(data->value());
}
void Autos(float t,int sensorValue){
  if(checkauto){
    if(sensorValue < 650){
      digitalWrite(ledPin,1);
    }else{
      digitalWrite(ledPin,0);
    }
    if(t < 27){
      digitalWrite(ledPin2,1);
    }else{
      digitalWrite(ledPin2,0);
    }
  }
}
