#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <MicroGear.h>
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>

SoftwareSerial NodeSerial(D2, D3);// Rx, Tx
int serial_data = 0;

const char* ssid     = "oofin008"; //change this to your SSID TP-LINK_2CB814 inoofnut_2.4
const char* password = "0873493482"; //change this to your PASSWORD 86001038 8378327359

//Heroku part
//host use 'http://' link
const char* host = "http://nodemcu-chatbot.herokuapp.com/bot.php";//change this to your linebot server ex.http://numpapick-linebot.herokuapp.com/bot.php

//NetPIE "Device key" part
#define APPID   "santiCHATBOT"     //change this to your APPID
#define KEY     "HYOLXhtWBbfQngt"     //change this to your KEY
#define SECRET  "AGzgckUUZTp6yyNDLMhEDKw58"     //change this to your SECRET

#define ALIAS   "NodeMCU1" //set name of device
#define TargetWeb "switch" //set target name of web

#define MY_LED 16
WiFiClient client;
String uid = "";
int timer = 0;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {  
    Serial.print("Incoming message -->");
    msg[msglen] = '\0';
Serial.println((char *)msg);
    if(*(char *)msg == '1'){
        digitalWrite(D0, LOW);   // LED on
        serial_data = 10;
        NodeSerial.write(serial_data);
        //microgear.chat(TargetWeb,"1");
        //send_data("ESP_LED_ON");
        send_json("ESP LED ON");
    }else if(*(char *)msg == '2'){
      digitalWrite(D0, HIGH);  // LED off
      serial_data = 5;
      NodeSerial.write(serial_data);
      //microgear.chat(TargetWeb,"0");
      //send_data("ESP_LED_OFF");
      send_json("ESP LED OFF");
    }else if(*(char *)msg == '3'){
      digitalWrite(D0, HIGH);  // LED off
      serial_data = 20;
      NodeSerial.write(serial_data);
      //microgear.chat(TargetWeb,"0");
      //send_data("ESP_LED_OFF");
      send_json("ESP FAN ON");
    }
    else if(*(char *)msg == '4'){
      digitalWrite(D0, HIGH);  // LED off
      serial_data = 15;
      NodeSerial.write(serial_data);
      //microgear.chat(TargetWeb,"0");
      //send_data("ESP_LED_OFF");
      send_json("ESP FAN OFF");
    }
    else if(*(char *)msg == '5'){
      digitalWrite(D0, HIGH);  // LED off
      serial_data = 30;
      NodeSerial.write(serial_data);
      //microgear.chat(TargetWeb,"0");
      //send_data("ESP_LED_OFF");
      send_json("ESP BUZZER ON");
    }
    else if(*(char *)msg == '6'){
      digitalWrite(D0, HIGH);  // LED off
      serial_data = 25;
      NodeSerial.write(serial_data);
      //microgear.chat(TargetWeb,"0");
      //send_data("ESP_LED_OFF");
      send_json("ESP BUZZER OFF");
    }
    /*else if(*(char *)msg == "hello"){
      serial_data = 0;
      NodeSerial.write(serial_data);
      send_json("What's UP?");
    }*/
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    microgear.setName(ALIAS);
}


void setup() {
  microgear.on(MESSAGE,onMsghandler);
  microgear.on(CONNECTED,onConnected);

  pinMode(D2,INPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(115200);
  Serial.println("Starting...");
  NodeSerial.begin(4800);

  pinMode(D0, OUTPUT);

  if (WiFi.begin(ssid, password)) {
      while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          Serial.print(".");
      }
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  microgear.init(KEY,SECRET,ALIAS);
  microgear.connect(APPID);
  digitalWrite(D0, HIGH);   // LED on
}

void send_json(String data){
  StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
  JsonObject& JSONencoder = JSONbuffer.createObject(); 

  JSONencoder["ESP"] = data;

  JsonArray& values = JSONencoder.createNestedArray("values"); //JSON array
  values.add(20); //Add value to array
  values.add(21); //Add value to array
  values.add(23); //Add value to array


  char JSONmessageBuffer[300];
  JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println(JSONmessageBuffer);

  HTTPClient http;    //Declare object of class HTTPClient

  http.begin(host);      //Specify request destination
  http.addHeader("Content-Type", "application/json");  //Specify content-type header

  int httpCode = http.POST(JSONmessageBuffer);   //Send the request
  String payload = http.getString();                                        //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
}
void loop() {
  if (microgear.connected()) {
     // Serial.println("..."); 
      microgear.loop();
      timer = 0;
  }
  else {
      Serial.println("connection lost, reconnect...");
      if (timer >= 5000) {
          microgear.connect(APPID); 
          timer = 0;
      }
      else timer += 100;
  }
  delay(500);
}
