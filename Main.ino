#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "TP-Link_1910";
const char* password = "25913401";

// Your website URL
const char* serverURL = "http://clintpump.mypressonline.com/get_status.php";

// LED pin
const int ledPin = 12;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Start with LED off
  
  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Make HTTP GET request
    http.begin(serverURL);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      response.trim(); // Remove any whitespace
      
      Serial.print("Status from server: ");
      Serial.println(response);
      
      // Control LED based on response
      if (response == "1") {
        digitalWrite(ledPin, HIGH); // Turn LED ON
        Serial.println("LED turned ON");
      } else if (response == "0") {
        digitalWrite(ledPin, LOW); // Turn LED OFF
        Serial.println("LED turned OFF");
      }
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    
    http.end();
  } else {
    Serial.println("WiFi disconnected");
  }
  
  delay(2000); // Check every 2 seconds
}
