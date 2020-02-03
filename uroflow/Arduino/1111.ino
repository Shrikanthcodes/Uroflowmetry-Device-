#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "HX711.h"
#include <FirebaseArduino.h>

// Replace with your network credentials
const char* ssid = "HTIC_INCUBATION";

const char* password = "router@mti";
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
HX711 scale(5,4); 
String page = "";
String text = "";
double data;
#define FIREBASE_HOST "https://uro-256ed.firebaseio.com "
#define FIREBASE_AUTH "RVbHpnVFTxqBrRqNVIRELjF9LZunaz84kVYPJTdZ"
 
void setup(void){
 scale.set_scale(-647);  //Calibration Factor obtained from first sketch
 scale.tare();   
 Serial.begin(115200);
 WiFi.begin(ssid, password); //begin WiFi connection
 Serial.println("");
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 // Wait for connection
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
}
 
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 /*
 server.on("/data.txt", [](){
   text = (String)data;
   server.send(200, "text/html", text);
 });
 server.on("/", [](){
   page = "<h1 id=\"data\">";
   page += "<script>\r\n";
   page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
   page += "function loadData(url, callback){\r\n";
   page += "var xhttp = new XMLHttpRequest();\r\n";
   page += "xhttp.onreadystatechange = function(){\r\n";
   page += " if(this.readyState == 4 && this.status == 200){\r\n";
   page += " callback.apply(xhttp);\r\n";
   page += " }\r\n";
   page += "};\r\n";
   page += "xhttp.open(\"GET\", url, true);\r\n";
   page += "xhttp.send();\r\n";
   page += "}\r\n";
   page += "function updateData(){\r\n";
   page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
   page += "}\r\n";
   page += "</script>\r\n";
   server.send(200, "text/html", page);
});
*/ 
 server.begin();
 Serial.println("Web server started!");
}
 
void loop(void){
 data = scale.get_units();
 Serial.println(data);
 Firebase.push("/data", data);
 if (Firebase.failed()) {
  Serial.print("setting /number failed:");
  Serial.println(Firebase.error());  
  return;
}
 delay(1000); 
 server.handleClient();
}
