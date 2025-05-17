#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include "display.h"
#include "paymentgateway.h"
#include "QR.h"

#define PRODUCT_1 27
#define PRODUCT_2 26
#define PRODUCT_3 25
#define PRODUCT_4 33
#define INCREMENT 32
#define DECREMENT 35
#define PROCEED 34
#define CANCEL 39
#define BUZZER 13

#define RELAY_1 17
#define RELAY_2 16
#define RELAY_3 12
#define RELAY_4 14


const int buttonPins[] = {PRODUCT_1, PRODUCT_2, PRODUCT_3, PRODUCT_4, INCREMENT, DECREMENT, PROCEED, CANCEL};

const char* buttonNames[] = {"Product 1", "Product 2", "Product 3", "Product 4", "Increase", "Decrease", "Proceed", "Cancel"};

int lastPressedActionButton = -1;


unsigned long lastActivityTime = 0;
const unsigned long inactivityThreshold = 5000;

int motorRunTime[] = {500, 750, 750, 750}; // Define run times for different products based on quantity

#define MAX_STOCK 3 // Maximum stock per product initially

int availableStock[] = {MAX_STOCK, MAX_STOCK, MAX_STOCK, MAX_STOCK}; // Available stock for each product

void setup() {
  tft.init();
  tft.setRotation(0);
  drawHeader();
  drawTable();
  drawButtons();

  Serial.begin(115200);
  digitalWrite( 5, HIGH);

  // Initialize Relay Pins
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  // Turn off all relays initially
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);

  // Wi-Fi and Firebase setup
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.print("\nConnected to Wi-Fi\n");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Sign up OK");
    signupOK = true;
  } else {
    Serial.printf("Sign up failed: %s\n", config.signer.signupError.message.c_str());
    tft.fillScreen(TFT_RED);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(15, 140);
    tft.print("SignUP ERROR");
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  if (!SD.begin(5, tft.getSPIinstance())) {
    Serial.println("Card Mount Failed");
    return;
  }

  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++) {
    pinMode(buttonPins[i], INPUT_PULLDOWN);
  }

  // Initialize available stock (example: initially, all products have max stock)
  for (int i = 0; i < 4; i++) {
    availableStock[i] = MAX_STOCK;
  }

  pinMode(BUZZER, OUTPUT);

  if (!Firebase.RTDB.beginStream(&stream, "/payment")) {
    Serial.printf("Stream begin error, %s\n", stream.errorReason().c_str());
  }
  Firebase.RTDB.setStreamCallback(&stream, streamCallback, streamTimeoutCallback);
}

void loop() {
  bool activity = false;

  for (int i = 0; i < sizeof(buttonPins) / sizeof(buttonPins[0]); i++) {
    if (digitalRead(buttonPins[i]) == HIGH) {
      delay(100);
      activity = true;
      lastActivityTime = millis();
      Serial.println(buttonNames[i]);

      switch (i) {
        case 0:
        case 1:
        case 2:
        case 3:
          beep();
          selectedProductIndex = i;
          drawTable();
          drawButtons();
          break;
        case 4: // Increment product quantity
          if (selectedProductIndex != -1 && productQuantities[selectedProductIndex] < availableStock[selectedProductIndex]) {
            beep();
            productQuantities[selectedProductIndex]++;
            drawTable();
            drawButtons(4);
            lastPressedActionButton = 4;
          }
          break;
        case 5: // Decrement product quantity
          if (selectedProductIndex != -1 && productQuantities[selectedProductIndex] > 0) {
            beep();
            productQuantities[selectedProductIndex]--;
            drawTable();
            drawButtons(5);
            lastPressedActionButton = 5;
          }
          break;
        case 6: // Proceed with purchase
          if (totalSelectedProducts() > 0) {
            beep();
            int totalAmount = 0;
            for (int j = 0; j < 4; j++) {
              totalAmount += productQuantities[j] * productPrices[j];
            }
            tft.fillScreen(TFT_GREEN);
            tft.setTextColor(TFT_BLACK);
            tft.setTextSize(2);
            tft.setCursor(10, 140);
            tft.print("Total Amount: Rs ");
            tft.print(totalAmount);
            tft.setTextSize(2);
            tft.setCursor(20, 170);
            tft.print("Displaying QR....");
            delay(2000);

            int displayTimeout = 300000; // 5 minutes in milliseconds

            // Display QR code
            String filename = "/" + String(totalAmount) + ".jpg";
            tft.setRotation(0);
            tft.fillScreen(random(0xFFFF));
            drawSdJpeg(filename.c_str(), 0, 0);

            unsigned long qrStartTime = millis(); // Record the start time for QR code display

            while (!awaitingPayment()) {
              if (millis() - qrStartTime >= displayTimeout) { // Check if 5 minutes have passed
                // Reset everything
                tft.fillScreen(TFT_RED); // Optional visual indication of timeout
                tft.setTextColor(TFT_WHITE);
                tft.setTextSize(3);
                tft.setCursor(30, 140);
                tft.print("Payment Timeout");

                delay(2000); // Brief delay for the timeout message

                // Reset selected product and quantities
                selectedProductIndex = -1;
                for (int j = 0; j < 4; j++) {
                  productQuantities[j] = 0;
                }
                drawHeader();
                drawTable();
                drawButtons();

                return; // Exit the function
              }
            }

            // Payment is completed within the timeout; proceed with order processing
            runMotorForProduct();
            updateStock();
            tft.fillScreen(TFT_GREEN);
            tft.setTextColor(TFT_BLACK);
            tft.setTextSize(3);
            tft.setCursor(30, 140);
            tft.print("Thank You");
            delay(3000);

            // Reset selected product and quantities
            selectedProductIndex = -1;
            for (int j = 0; j < 4; j++) {
              productQuantities[j] = 0;
            }
            drawHeader();
            drawTable();
            drawButtons();
            lastPressedActionButton = 6;
            paymentDone = false;


            // After payment, run the motors and update stock
            runMotorForProduct();
            updateStock();
            tft.fillScreen(TFT_GREEN);
            tft.setTextColor(TFT_BLACK);
            tft.setTextSize(3);
            tft.setCursor(30, 140);
            tft.print("Thank You");
            delay(3000);

            selectedProductIndex = -1;
            for (int j = 0; j < 4; j++) {
              productQuantities[j] = 0;
            }
            drawHeader();
            drawTable();
            drawButtons();
            lastPressedActionButton = 6;
            paymentDone = false;
          }
          break;

        case 7: // Cancel and reset
          beep();
          for (int j = 0; j < 4; j++) {
            productQuantities[j] = 0;
          }
          selectedProductIndex = -1;
          drawTable();
          drawButtons(7);
          lastPressedActionButton = 7;
          delay(1000);
          drawButtons();
          break;
      }
      delay(200);
    }
  }

  if (!activity && selectedProductIndex != -1 && (millis() - lastActivityTime >= inactivityThreshold)) {
    selectedProductIndex = -1;
    drawTable();
    drawButtons();
  }
}

void runMotorForProduct() {
  for (int i = 0; i < 4; i++) {
    if (productQuantities[i] > 0) {
      switch (i) {
        case 0:
          digitalWrite(RELAY_1, HIGH);
          delay(motorRunTime[i] * productQuantities[i]);
          digitalWrite(RELAY_1, LOW);
          break;
        case 1:
          digitalWrite(RELAY_2, HIGH);
          delay(motorRunTime[i] * productQuantities[i]);
          digitalWrite(RELAY_2, LOW);
          break;
        case 2:
          digitalWrite(RELAY_3, HIGH);
          delay(motorRunTime[i] * productQuantities[i]);
          digitalWrite(RELAY_3, LOW);
          break;
        case 3:
          digitalWrite(RELAY_4, HIGH);
          delay(motorRunTime[i] * productQuantities[i]);
          digitalWrite(RELAY_4, LOW);
          break;
      }
    }
  }
}

// Function to update available stock after payment is completed
void updateStock() {
  for (int i = 0; i < 4; i++) {
    if (productQuantities[i] > 0) {
      availableStock[i] -= productQuantities[i]; // Reduce available stock
      if (availableStock[i] < 0) availableStock[i] = 0; // Ensure stock doesn't go negative
    }
  }
}

// Utility function to calculate total selected products
int totalSelectedProducts() {
  int total = 0;
  for (int i = 0; i < 4; i++) {
    total += productQuantities[i];
  }
  return total;
}

void beep() {
  digitalWrite(BUZZER, HIGH);
  delay(25);
  digitalWrite(BUZZER, LOW);
}
