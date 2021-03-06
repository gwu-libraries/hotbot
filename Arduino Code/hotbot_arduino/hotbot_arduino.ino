/*
  The sketch creates a connection with server, and 
  sends data from a temperature sensor to the server
  Created 4/26/14
  by John Savino
  based on work posted on arduino.cc and dfrobot.com
  Modified 4/30/14
  by Matt Mihalik
*/

#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4
#include <SPI.h>
#include <Ethernet.h>

//MAC address of shield in byte format
byte mac[] = {0xAA,0x00,0xBB,0x11,0xCC,0x22};

//MAC address of shield
const char* MAC ="aa00bb11cc22";

//Server IP address, define below in httpreq 1&2 as 'Host: '
byte server[]={0,0,0,0};

//Intitilizes client
EthernetClient client;

//Time of last connection in milliseconds
unsigned long lastConnectTime = 0;

//State of connection in last loop
boolean lastConnect = false;

//Delay between updates
const unsigned long postingInterval = 30*1000;

void setup(){
  Serial.begin(9600);//start serial port
  Ethernet.begin(mac);
  delay(2000);//give ethernet time to boot
  Serial.print("My IP: ");
  Serial.println(Ethernet.localIP());
  Serial.println();
}

void loop(){

  //Prints incoming data to serial port
  if(client.available()){
    char c = client.read();
    Serial.print(c);
  };
  
  //If there's no connection, but there was last time through, stop the client
  if(!client.connected() && lastConnect){
    Serial.println();
    Serial.println("Disconnecting...");
    Serial.println();
    client.stop();
  };
  
  //If not connected, and ten seconds have passed since last connection, connect again and send
  if(!client.connected() && (millis() - lastConnectTime > postingInterval)){
    httpReq1();
    httpReq2();
  }
  lastConnect=client.connected();//updates last connect variable
}

void httpReq1(){

  //Reads sensor values
  int chk;
  chk = DHT.read(DHT11_PIN);
  
  //Build the PostDataF
  String PostDataF="{\"sensor\":\"/api/v1/sensor/";
  PostDataF=PostDataF+(MAC);
  PostDataF=PostDataF+"/\",\"metric\":\"";
  PostDataF=PostDataF+"temperatureF";
  PostDataF=PostDataF+"\",\"value\":";
  PostDataF=PostDataF+(DHT.temperature*9/5+32);
  PostDataF=PostDataF+"}";
  
  //If client connected:
  if(client.connect(server, 80)){
    Serial.println("Connecting...");
    Serial.println();
    
    //Send POST request temperature data:
    client.println("POST /api/v1/reading/ HTTP/1.1");
    Serial.println("POST /api/v1/reading/ HTTP/1.1");
    client.println("Host: 0.0.0.0");
    Serial.println("Host: 0.0.0.0");
    client.println("Connection: close");
    Serial.println("Connection: close");
    client.println("Content-Type: application/json");
    Serial.println("Content-Type: application/json");
    client.println("Accept: application/json");
    Serial.println("Accept: application/json");
    
    //Insert your API key
    client.println("Authorization: ApiKey sensor:");
    Serial.println("Authorization: ApiKey sensor:");
    client.print("Content-Length: ");
    Serial.print("Content-Length: ");
    client.println(PostDataF.length());
    Serial.println(PostDataF.length());
    client.println();
    Serial.println();
    client.println(PostDataF);
    Serial.println(PostDataF);
    
    //End the first connection
    client.stop();
    Serial.println("Connection: close");
    Serial.println();
  }
    else{
    Serial.println("Connection Failed");
    Serial.println("Disconnecting...");
    Serial.println();
    client.stop();
    }
}
 
void httpReq2(){

  //Reads sensor values
  int chk;
  chk = DHT.read(DHT11_PIN);
      
  //Build the PostDataH
  String PostDataH="{\"sensor\":\"/api/v1/sensor/";
  PostDataH=PostDataH+(MAC);
  PostDataH=PostDataH+"/\",\"metric\":\"";
  PostDataH=PostDataH+"humidity";
  PostDataH=PostDataH+"\",\"value\":";
  PostDataH=PostDataH+(DHT.humidity);
  PostDataH=PostDataH+"}";
  
  //If client connected:
  if(client.connect(server, 80)){
    Serial.println("Connecting...");
    Serial.println();
    
    //Send POST request humidity data:
    client.println("POST /api/v1/reading/ HTTP/1.1");
    Serial.println("POST /api/v1/reading/ HTTP/1.1");
    client.println("Host: 0.0.0.0");
    Serial.println("Host: 0.0.0.0");
    client.println("Connection: close");
    Serial.println("Connection: close");
    client.println("Content-Type: application/json");
    Serial.println("Content-Type: application/json");
    client.println("Accept: application/json");
    Serial.println("Accept: application/json");
    
    //Insert your API key
    client.println("Authorization: ApiKey sensor:");
    Serial.println("Authorization: ApiKey sensor:");
    client.print("Content-Length: ");
    Serial.print("Content-Length: ");
    client.println(PostDataH.length());
    Serial.println(PostDataH.length());
    client.println();
    Serial.println();
    client.println(PostDataH);
    Serial.println(PostDataH);
    
    //End the second connection
    client.println("Connection: close");
    Serial.println("Connection: close");
    client.println();
    Serial.println();
    lastConnectTime=millis();
  }
  else{
    Serial.println("Connection Failed");
    Serial.println("Disconnecting...");
    Serial.println();
    client.stop();
  }
 } 
