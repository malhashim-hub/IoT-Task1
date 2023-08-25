#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String url = "https://galilean-connection.000webhostapp.com/view.php";
String payload = "";
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(25, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(19, OUTPUT);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + url + "... ");


}

void loop() {
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  Serial.print(httpResponseCode);
  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println();
    Serial.println(payload);
    if( payload == "f" ){
      digitalWrite(25, HIGH);
    }
    else if( payload == "l"){
       digitalWrite(34, HIGH);  
    }
    else if (payload == "r"){
        digitalWrite(21, HIGH); 
    }
    else if (payload == "b")  {     
        digitalWrite(19, HIGH);
    }
  }

  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }
  
}