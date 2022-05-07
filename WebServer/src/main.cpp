// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>
// #include <ESP8266HTTPClient.h>
// #include <DNSServer.h>
// const char *ssid = "root";
// const char *password = "1234567890";

// ESP8266WebServer server(80);

// //Check if header is present and correct
// bool is_authentified() {
//   Serial.println("Enter is_authentified");
//   if (server.hasHeader("Cookie")) {
//     Serial.print("Found cookie: ");
//     String cookie = server.header("Cookie");
//     Serial.println(cookie);
//     if (cookie.indexOf("ESPSESSIONID=1") != -1) {
//       Serial.println("Authentification Successful");
//       return true;
//     }
//   }
//   Serial.println("Authentification Failed");
//   return false;
// }

// // //login page, also called for disconnect
// // void handleLogin() {
// //   String msg;
// //   if (server.hasHeader("Cookie")) {
// //     Serial.print("Found cookie: ");
// //     String cookie = server.header("Cookie");
// //     Serial.println(cookie);
// //   }
// //   if (server.hasArg("DISCONNECT")) {
// //     Serial.println("Disconnection");
// //     server.sendHeader("Location", "/login");
// //     server.sendHeader("Cache-Control", "no-cache");
// //     server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
// //     server.send(301);
// //     return;
// //   }
// //   if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")) {
// //     if (server.arg("USERNAME") == "admin" &&  server.arg("PASSWORD") == "admin") {
// //       server.sendHeader("Location", "/");
// //       server.sendHeader("Cache-Control", "no-cache");
// //       server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
// //       server.send(301);
// //       Serial.println("Log in Successful");
// //       return;
// //     }
// //     msg = "Wrong username/password! try again.";
// //     Serial.println("Log in Failed");
// //   }
// //   String content = "<html><body><form action='/login' method='POST'>To log in, please use : admin/admin<br>";
// //   content += "User:<input type='text' name='USERNAME' placeholder='user name'><br>";
// //   content += "Password:<input type='password' name='PASSWORD' placeholder='password'><br>";
// //   content += "<input type='submit' name='SUBMIT' value='Submit'></form>" + msg + "<br>";
// //   content += "You also can go <a href='/inline'>here</a></body></html>";
// //   server.send(200, "text/html", content);
// // }

// //root page can be accessed only if authentification is ok
// void handleRoot() {
//   Serial.println("Enter handleRoot");
//   String header;
//   if (!is_authentified()) {
//     server.sendHeader("Location", "/login");
//     server.sendHeader("Cache-Control", "no-cache");
//     server.send(301);
//     return;
//   }
//   String content = "<html><body><H2>hello, you successfully connected to esp8266!</H2><br>";
//   if (server.hasHeader("User-Agent")) {
//     content += "the user agent used is : " + server.header("User-Agent") + "<br><br>";
//   }
//   content += "You can access this page until you <a href=\"/login?DISCONNECT=YES\">disconnect</a></body></html>";
//   server.send(200, "text/html", content);
// }

// // //no need authentification
// // void handleNotFound() {
// //   String message = "File Not Found\n\n";
// //   message += "URI: ";
// //   message += server.uri();
// //   message += "\nMethod: ";
// //   message += (server.method() == HTTP_GET) ? "GET" : "POST";
// //   message += "\nArguments: ";
// //   message += server.args();
// //   message += "\n";
// //   for (uint8_t i = 0; i < server.args(); i++) {
// //     message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
// //   }
// //   server.send(404, "text/plain", message);
// // }

// void setup(void) {
//   Serial.begin(115200);
//  WiFi.softAP(ssid, password);
//   IPAddress myIP = WiFi.softAPIP();
//   Serial.print("AP IP address: ");
//   Serial.println(myIP);


//   server.on("/", handleRoot);
//   //server.on("/login", handleLogin);
//   server.on("/inline", []() {
//     server.send(200, "text/plain", "this works without need of authentification");
//   });

//   // server.onNotFound(handleNotFound);
//   //here the list of headers to be recorded
//   const char * headerkeys[] = {"User-Agent", "Cookie"} ;
//   size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
//   //ask server to track these headers
//   server.collectHeaders(headerkeys, headerkeyssize);
//   server.begin();
//   Serial.println("HTTP server started");
// }

// void loop(void) {
//   server.handleClient();
// }

// /*********
//   Rui Santos
//   Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-input-data-html-form/
  
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files.
  
//   The above copyright notice and this permission notice shall be included in all
//   copies or substantial portions of the Software.
// *********/

// #include <Arduino.h>
// #ifdef ESP32
//   #include <WiFi.h>
//   #include <AsyncTCP.h>
// #else
//   #include <ESP8266WiFi.h>
//   #include <ESPAsyncTCP.h>
// #endif
// #include <ESPAsyncWebServer.h>
// //#include <ESP8266WebServer.h>
// #include <DNSServer.h>
// AsyncWebServer server(80);

// // REPLACE WITH YOUR NETWORK CREDENTIALS
// const char *ssid = "root";
// const char *password = "1234567890";

// const char* PARAM_INPUT_1 = "input1";
// const char* PARAM_INPUT_2 = "input2";
// const char* PARAM_INPUT_3 = "input3";

// // HTML web page to handle 3 input fields (input1, input2, input3)
// const char index_html[] PROGMEM = R"rawliteral(
// <!DOCTYPE HTML><html><head>
//   <title>ESP Input Form</title>
//   <meta name="viewport" content="width=device-width, initial-scale=1">
//   </head><body>
//   <form action="/get">
//     input1: <input type="text" name="input1">
//     <input type="submit" value="Submit">
//   </form><br>
//   <form action="/get">
//     input2: <input type="text" name="input2">
//     <input type="submit" value="Submit">
//   </form><br>
//   <form action="/get">
//     input3: <input type="text" name="input3">
//     <input type="submit" value="Submit">
//   </form>
// </body></html>)rawliteral";

// void notFound(AsyncWebServerRequest *request) {
//   request->send(404, "text/plain", "Not found");
// }

// void setup() {
//   Serial.begin(115200);
//    WiFi.softAP(ssid, password);
//   IPAddress myIP = WiFi.softAPIP();
//   Serial.print("AP IP address: ");
//   Serial.println(myIP);

//   // Send web page with input fields to client
//   // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//   //   request->send_P(200, "text/html", index_html);
//   // });

//   // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
//   server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
//     String inputMessage;
//     String inputParam;
//     // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
//     if (request->hasParam(PARAM_INPUT_1)) {
//       inputMessage = request->getParam(PARAM_INPUT_1)->value();
//       inputParam = PARAM_INPUT_1;
//     }
//     // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
//     else if (request->hasParam(PARAM_INPUT_2)) {
//       inputMessage = request->getParam(PARAM_INPUT_2)->value();
//       inputParam = PARAM_INPUT_2;
//     }
//     // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
//     else if (request->hasParam(PARAM_INPUT_3)) {
//       inputMessage = request->getParam(PARAM_INPUT_3)->value();
//       inputParam = PARAM_INPUT_3;
//     }
//     else {
//       inputMessage = "No message sent";
//       inputParam = "none";
//     }
//     Serial.println(inputMessage);
//     request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
//                                      + inputParam + ") with value: " + inputMessage +
//                                      "<br><a href=\"/\">Return to Home Page</a>");
//   });
//   server.onNotFound(notFound);
//   server.begin();
// }

// void loop() {
  
// }



/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-input-data-html-form/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <SPIFFS.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <Hash.h>
  #ifdef USE_LittleFS
	#include <FS.h>
	#define SPIFFS LittleFS
	#include <LittleFS.h> 
 #endif
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char *ssid = "root";
const char *password = "1234567890";

const char* PARAM_STRING = "inputString";
const char* PARAM_INT = "inputInt";
const char* PARAM_FLOAT = "inputFloat";

// HTML web page to handle 3 input fields (inputString, inputInt, inputFloat)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script>
    function submitMessage() {
      alert("Saved value to ESP SPIFFS");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }
  </script></head><body>
  <form action="/get" target="hidden-form">
    inputString (current value %inputString%): <input type="text" name="inputString">
    <input type="submit" value="Submit" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    inputInt (current value %inputInt%): <input type="number " name="inputInt">
    <input type="submit" value="Submit" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    inputFloat (current value %inputFloat%): <input type="number " name="inputFloat">
    <input type="submit" value="Submit" onclick="submitMessage()">
  </form>
  <iframe style="display:none" name="hidden-form"></iframe>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  file.close();
  Serial.println(fileContent);
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}

// Replaces placeholder with stored values
String processor(const String& var){
  //Serial.println(var);
  if(var == "inputString"){
    return readFile(SPIFFS, "/inputString.txt");
  }
  else if(var == "inputInt"){
    return readFile(SPIFFS, "/inputInt.txt");
  }
  else if(var == "inputFloat"){
    return readFile(SPIFFS, "/inputFloat.txt");
  }
  return String();
}

void setup() {
  Serial.begin(115200);
  // Initialize SPIFFS
  #ifdef ESP32
    if(!SPIFFS.begin(true)){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #else
    if(!SPIFFS.begin()){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #endif

  //   Serial.begin(115200);
   WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/get?inputString=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET inputString value on <ESP_IP>/get?inputString=<inputMessage>
    if (request->hasParam(PARAM_STRING)) {
      inputMessage = request->getParam(PARAM_STRING)->value();
      writeFile(SPIFFS, "/inputString.txt", inputMessage.c_str());
    }
    // GET inputInt value on <ESP_IP>/get?inputInt=<inputMessage>
    else if (request->hasParam(PARAM_INT)) {
      inputMessage = request->getParam(PARAM_INT)->value();
      writeFile(SPIFFS, "/inputInt.txt", inputMessage.c_str());
    }
    // GET inputFloat value on <ESP_IP>/get?inputFloat=<inputMessage>
    else if (request->hasParam(PARAM_FLOAT)) {
      inputMessage = request->getParam(PARAM_FLOAT)->value();
      writeFile(SPIFFS, "/inputFloat.txt", inputMessage.c_str());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/text", inputMessage);
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  // To access your stored values on inputString, inputInt, inputFloat
  String yourInputString = readFile(SPIFFS, "/inputString.txt");
  Serial.print("*** Your inputString: ");
  Serial.println(yourInputString);
  
  int yourInputInt = readFile(SPIFFS, "/inputInt.txt").toInt();
  Serial.print("*** Your inputInt: ");
  Serial.println(yourInputInt);
  
  float yourInputFloat = readFile(SPIFFS, "/inputFloat.txt").toFloat();
  Serial.print("*** Your inputFloat: ");
  Serial.println(yourInputFloat);
  delay(5000);
}