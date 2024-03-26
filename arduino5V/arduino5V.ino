/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
int reley = 2;
int ledpin = 7;
int reley2 = 5;
int ledpin2 = 3;
int MotorPin2 = 13;
int outMotor = 11;
int outMotor2 = 10;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(reley, OUTPUT);
  pinMode(ledpin, INPUT);
  pinMode(reley2, OUTPUT);
  pinMode(ledpin2, INPUT);
  pinMode(MotorPin2, OUTPUT);
  pinMode(outMotor, INPUT);
  pinMode(outMotor2, INPUT);
  
}

// the loop function runs over and over again forever
void loop() {
  if(digitalRead(ledpin) == 0){
    digitalWrite(reley, HIGH);
  }else{
    digitalWrite(reley, LOW);
  }
  if(digitalRead(ledpin2) == 0){
    digitalWrite(reley2, HIGH);
  }else{
    digitalWrite(reley2, LOW);
  }
  Serial.println(digitalRead(outMotor));
  Serial.println(digitalRead(outMotor2));
  if(digitalRead(outMotor) == 1 && digitalRead(outMotor2) == 1){
    Serial.println("LEVEL 2");
    analogWrite(MotorPin2, 255);
  }else if(digitalRead(outMotor) == 0 && digitalRead(outMotor2) == 1){
    Serial.println("LEVEL 1");
    analogWrite(MotorPin2, 127);
  }else{
    Serial.println("LEVEL 0");
    analogWrite(MotorPin2, 0);
  }
}
