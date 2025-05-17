#include <WiFi.h>
#include <Firebase_ESP_Client.h>
// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Tushar"
#define WIFI_PASSWORD "12345678910"
// Insert Firebase project API Key
#define API_KEY "AIzaSyDSrR8_a-bp90gg6kf2fKxt6giblVq766o"

// Insert RTDB URL
#define DATABASE_URL "https://razorpay-iot-gateway-default-rtdb.asia-southeast1.firebasedatabase.app/"

// Define Firebase Data object
FirebaseData fbdo;
FirebaseData stream;
FirebaseAuth auth;
FirebaseConfig config;

int totalAmount=0; 

bool signupOK = false;
bool ledState = false;
bool paymentDone = false;

void streamCallback(FirebaseStream data) {
  Serial.println("Stream Data...");
  Serial.println(data.streamPath());
  Serial.println(data.dataPath());
  Serial.println(data.dataType());
  Serial.println(data.eventType());

  if (data.dataType() == "json") {
    FirebaseJson& json = data.jsonObject();
    FirebaseJsonData jsonData;
    String path = "";
    if (json.get(jsonData, "/payload/payment/entity/captured", false)) {
      if (jsonData.type == "boolean") {
         paymentDone= jsonData.boolValue;

        if (paymentDone) {
          tft.fillScreen(TFT_GREEN);
          tft.setTextColor(TFT_BLACK);
          tft.setTextSize(3);
          tft.setCursor(25, 140);
          tft.print("Dispensing");
          delay(2000);
    
          // Move data to old_payments
          String oldPaymentPath = "/old_payments" + data.dataPath();
          if (Firebase.RTDB.setJSON(&fbdo, oldPaymentPath.c_str(), &json)) {
            Serial.println("Data moved to old_payments successfully");

            // Delete the payment node
            if (Firebase.RTDB.deleteNode(&fbdo, "/payment")) {
              Serial.println("/payment node deleted successfully");
            } else {
              Serial.printf("Failed to delete /payment node, %s\n", fbdo.errorReason().c_str());
            }

          } else {
            Serial.printf("Failed to move data to old_payments, %s\n", fbdo.errorReason().c_str());
          }
        } 
      }
    }
  }
}

void streamTimeoutCallback(bool timeout) {
  if (timeout) {
    tft.fillScreen(TFT_RED);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(15, 140);
    tft.print("Stream ERROR");
    Serial.println("Stream timeout, resuming...");
  }
}

// Function to handle awaiting payment logic
bool awaitingPayment() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi Disconnected. Reconnecting...");
    tft.fillScreen(TFT_RED);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(20, 140);
    tft.print("Wi-Fi ERROR");
    Serial.println("Stream timeout, resuming...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(300);
    }
    Serial.println("Reconnected to Wi-Fi.");
  }

  if (!Firebase.RTDB.readStream(&stream)) {
    // Retry logic for connection refused
    if (stream.errorReason().indexOf("connection refused") != -1) {
      Serial.println("Reconnecting to Firebase...");
      Firebase.begin(&config, &auth);
    }
  }

  return paymentDone; // Return the status of payment
}
