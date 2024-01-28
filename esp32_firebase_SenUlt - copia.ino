


#include <WiFi.h>
#include <FirebaseESP32.h>
#include <ESP32Servo.h>

#define FIREBASE_HOST "https://calidadaire-5847f-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyCLd5Mjs8VqshO5fTz_8boJP2GUOOgmif8"
#define WIFI_SSID "G54"
#define WIFI_PASSWORD "12345678"

FirebaseData fbdo;


int senUlTrigger = 19;
int senUlEcho = 21;
int pinServo = 18;
Servo miServo;  
void setup() {

  Serial.begin(921600);
  pinMode(senUlTrigger, OUTPUT); //pin como salida
  pinMode(senUlEcho, INPUT);  //pin como entrada
  digitalWrite(senUlTrigger, LOW);
  miServo.attach(pinServo);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("[Wi-Fi]...Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {
  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  
  
  digitalWrite(senUlTrigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(senUlTrigger, LOW);

  t = pulseIn(senUlEcho, HIGH); //obtenemos el ancho del pulso
  d = t / 59;       //escalamos el tiempo a una distancia en cmz
  Firebase.setFloat(fbdo, "/ultrasonido/distanci", d);
     miServo.write(0);  
  if (d<8) {       
     miServo.write(90);  
     delay(7000);
     miServo.write(0);
};
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println(".");
  delay(100);

}
