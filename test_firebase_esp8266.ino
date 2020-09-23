#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
//#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

#define WIFI_SSID     "08112"
#define WIFI_PASSWORD "89898989"
#define FIREBASE_HOST "neon-rex-258413.firebaseio.com"
#define FIREBASE_AUTH "kf2FQi4mccHxvvJgtb9QoO6bGKZLEXtm0sQwbsJK"
FirebaseData firebaseData;
const int led0 = D0;
const int led1 = D1;
const int led2 = D2;
const int led3 = D4;
int load_1,load_2,load_3,load_0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(WiFi.localIP());
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
}

void loop() {
  
  Serial.println("----------------------");
// pack data to JSON
 /* FirebaseJson data;
  
  data.set("led_control", 1);
  data.set("led_control_1", 1);
  data.set("led_control_2", 1);*/


//push data
  /*if(Firebase.pushJSON(firebaseData, "device", data)) {
    Serial.println("Added"); 
} else {
    Serial.println("Error : " + firebaseData.errorReason());
}*/



if(Firebase.getJSON(firebaseData, "device")) {
    FirebaseJson &json = firebaseData.jsonObject();
    FirebaseJsonData data;
    json.get(data, "/led_control");
    load_0 = data.doubleValue;
    json.get(data, "/led_control_1");
    load_1 = data.doubleValue;
    json.get(data, "/led_control_2");
    load_2 = data.doubleValue;
    json.get(data, "/led_control_3");
    load_3 = data.doubleValue;
    digitalWrite(led0,load_0);
    digitalWrite(led1,load_1);
    digitalWrite(led2,load_2);
    digitalWrite(led3,load_3);
    
} else {
    Serial.println("Error : " + firebaseData.errorReason());
}

  delay(1000);
}
