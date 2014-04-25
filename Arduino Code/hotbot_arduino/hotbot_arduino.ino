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
  0x90,0xA2,0xDA,0x0D,0xD1,0x4F};//mac address of shield
const char* MAC ="90A2DA0DD14F";
IPAddress server(128,164,212,50);//enter server ip
EthernetClient client;//intitilizes client
unsigned long lastConnectTime = 0;//time of last connection in ms
boolean lastConnect = false;//state of connection in last loop
const unsigned long postingInterval = 60*1000;//delay between updates
void setup(){
  Serial.begin(9600);//start serial port
  delay(1000);//give ethernet time to boot
  Ethernet.begin(mac);//start ethernet connection
  Serial.print("My IP:");
  Serial.print(Ethernet.localIP());
}
void loop()
{
  //prints incoming data to serial port
  if(client.available()){
    char c = client.read();
    Serial.print(c);
  }
  //if there's no connection, but there was last time through,
  //stop the client
  if(!client.connected() && lastConnect){
    Serial.println();
    Serial.println("disconnectiong.");
    client.stop();
  }
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
    client.println("Content-Type:application/json");
    client.println("Accept: application/json");
    client.println("Authorization: ApiKey sensor:dcf2cc06582b3d497783bc2348d5ff1fefce0e89");
    client.print("\",\"MAC\": \"");
    client.print(MAC);
    client.print("\",\"temperatureF\": \"");
    client.print(DHT.temperature*9/5+32);
    client.print("\",\"humidity\": \"");
    client.print(DHT.humidity);
    client.print("\"}");

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

