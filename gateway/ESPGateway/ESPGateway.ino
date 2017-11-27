#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <SoftwareSerial.h>

#define D7 13
#define D8 15

SoftwareSerial mySerial(D7, D8); // RX = D7, TX  = D8

const char* ssid = "XT1069";
const char* password = "*******";
const char* mqtt_server = "m14.cloudmqtt.com"; /// MQTT Broker
int mqtt_port = 17078;


char msg[15];
const char* mqtt_username = "mmxjuyfz";
const char* mqtt_password = "*******"; 
WiFiClient espClient;
//PubSubClient client(espClient, mqtt_username, mqtt_password );
PubSubClient client(espClient);




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(D7,INPUT); //d7 is RX, receiver, so define it as input
  pinMode(D8,OUTPUT); //d8 is TX, transmitter, so define it as output

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  Serial.println("Connected ");
  Serial.print("MQTT Server ");
  Serial.print(mqtt_server);
  Serial.print(":");
  Serial.println(String(mqtt_port)); 
  Serial.print("ESP8266 IP ");
  Serial.println(WiFi.localIP()); 
  Serial.println("GATEWAY Online");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
   
}

void reconnect() {
  // Loop until reconnect
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
  // Attempt to connect
    if (client.connect("ESP8266Client", mqtt_username, mqtt_password)) {
      Serial.println("connected");
    // client.subscribe("event");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
   }
 }
}

void loop() {
   if (!client.connected()) {
      reconnect();
   }
   
  // put your main code here, to run repeatedly:
   while(mySerial.available() > 0){   
    if(mySerial.read() == 35){ 
     mySerial.readStringUntil('\n').toCharArray(msg,15);
    
     Serial.println(msg);
    
     delay(100);
    
     if(client.publish("rbp/ifsc/sensor", msg, true)){
      Serial.println("Publish ok");
     }
     
    }
   }

   client.loop();
   delay(1000);

}
