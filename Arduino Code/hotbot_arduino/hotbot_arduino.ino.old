/*
  
 The sketch creates a connection with server, and 
 sends data from a temperature sensor to the server
 Created 3/26/14
 by John Savino
 based on work posted on arduino.cc and dfrobot.com
 */
#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {  
  0x00,0x00,0x00,0x00,0x00,0x00};//mac address of shield
const char* MAC ="000000000000";
byte server[]={0,0,0,0};//server url
EthernetClient client;//intitilizes client
unsigned long lastConnectTime = 0;//time of last connection in ms
boolean lastConnect = false;//state of connection in last loop
const unsigned long postingInterval = 10*1000;//delay between updates
void setup(){
  Serial.begin(9600);//start serial port
  Ethernet.begin(mac);
  delay(2000);//give ethernet time to boot
  Serial.print("My IP:");
  Serial.print(Ethernet.localIP());
}
void loop()
{
  //prints incoming data to serial port
  if(client.available()){
    char c = client.read();
    Serial.print(c);
  };
  //if there's no connection, but there was last time through,
  //stop the client
  if(!client.connected() && lastConnect){
    Serial.println();
    Serial.println("disconnectiong.");
    client.stop();
  };
  //if not connected, and ten seconds have passed since last connection, 
  //connect again and send
  if(!client.connected() && (millis() - lastConnectTime > postingInterval)){
    httpReq();
  }
  lastConnect=client.connected();//updates last connect variable
}
void httpReq(){

  //reads sensor values
  int chk;
  chk = DHT.read(DHT11_PIN);
  //if client connected:
  if(client.connect(server, 80)){
    Serial.println("connecting...");
    //send PUT request:
    client.println("POST /api/v1/reading/ HTTP/1.1");
    client.println("HOST: 0.0.0.0");
    client.println("Content-Type: application/json");
    client.println("Accept: application/json ");
    client.println("Authorization: ApiKey sensor:");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.print("{\"sensor\": \"/api/v1/sensor/");
    client.print(MAC);
    client.print("/\",\"metric\": \"");
    client.print("temperatureF");
    client.print("\",\"value\": ");
    client.print(DHT.temperature*9/5+32);
    client.println("}");
    /*

    client.print("Content-Type:application/json");
    client.print("Accept: application/json");
    client.print("Authorization: ApiKey sensor:");
    client.print("\",\"MAC\": \"");
    client.print(MAC);
    client.print("\",\"metric\": \"");
    client.print("humidity");
    client.print("\",\"value\": \"");
    client.print(DHT.humidity);
    client.print("\"}");*/

    client.println("Connection: close");
    client.println();
    lastConnectTime=millis();
  }
  else{
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }
}


