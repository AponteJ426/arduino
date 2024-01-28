#include <ESP32Servo.h>




int senUlTrigger = 19;
int senUlEcho = 21;
int pinServo = 14;
int pinMov = 18;
Servo miServo;  


void setup() {

  Serial.begin(921600);
  pinMode(pinMov, INPUT);
  miServo.attach(pinServo);

}

void loop() {
    miServo.write(0);   
 const val = digitalRead(pinMov);
  if (val == HIGH)
     miServo.write(90);  
     delay(9000);
     miServo.write(0);
      Serial.println("Sensor activado");
  } ;
  
}

  
