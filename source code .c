#include <Wire.h>
#include <Adafruit_INA3221.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "time.h"

// INA3221 Setup
Adafruit_INA3221 ina3221;

// WiFi Credentials
#define WIFI_SSID "esp32"
#define WIFI_PASSWORD "12345678"

// Firebase Setup
#define API_KEY "AIzaSyAiegs4qcEIvkJlbwnHJEk9K89jJXMx6eY"
#define DATABASE_URL "https://pizo-data-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define USER_EMAIL "bharathkumaar9883@gmail.com"
#define USER_PASSWORD "piezo123"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// NTP Time Setup
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800; // IST (UTC+5:30)
const int daylightOffset_sec = 0;

bool isValid(float val) {
  return !isnan(val) && isfinite(val);
}

String getTimeStamp() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "unknown_time";
  char buffer[30];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &timeinfo);
  return String(buffer);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  ina3221.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  // Init NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  float voltage_mv[3], current_ma[3], power_mw[3];
  float totalCurrent = 0, totalPower = 0, avgVoltage = 0;
  String timestamp = getTimeStamp();

  for (int i = 0; i < 3; i++) {
    voltage_mv[i] = ina3221.getBusVoltage(i + 1) * 1000.0;
    current_ma[i] = ina3221.getCurrentAmps(i + 1) * 1000.0;
    power_mw[i]   = (voltage_mv[i] * current_ma[i]) / 1000.0;

    if (isValid(voltage_mv[i])) avgVoltage += voltage_mv[i];
    if (isValid(current_ma[i])) totalCurrent += current_ma[i];
    if (isValid(power_mw[i]))   totalPower += power_mw[i];
  }
  avgVoltage /= 3;

  Serial.println("----------- INA3221 Data -----------");
  for (int i = 0; i < 3; i++) {
    Serial.printf("Channel %d: Voltage = %.2f mV, Current = %.2f mA, Power = %.2f mW\n", 
      i + 1, voltage_mv[i], current_ma[i], power_mw[i]);
  }
  Serial.printf("Total Current: %.2f mA\n", totalCurrent);
  Serial.printf("Average Voltage: %.2f mV\n", avgVoltage);
  Serial.printf("Total Power: %.2f mW\n", totalPower);
  Serial.println("------------------------------------");

  // Upload current data to history path with timestamp
  bool success = true;
  for (int i = 0; i < 3; i++) {
    String basePath = "/Channel" + String(i + 1) + "/History/" + timestamp;
    if (isValid(voltage_mv[i])) success &= Firebase.RTDB.setFloat(&fbdo, basePath + "/Voltage", voltage_mv[i]);
    if (isValid(current_ma[i])) success &= Firebase.RTDB.setFloat(&fbdo, basePath + "/Current", current_ma[i]);
    if (isValid(power_mw[i]))   success &= Firebase.RTDB.setFloat(&fbdo, basePath + "/Power", power_mw[i]);
  }

  // Optional: store total summary in timestamped path
  String totalPath = "/Total/History/" + timestamp;
  if (isValid(totalCurrent)) success &= Firebase.RTDB.setFloat(&fbdo, totalPath + "/Current", totalCurrent);
  if (isValid(avgVoltage))   success &= Firebase.RTDB.setFloat(&fbdo, totalPath + "/Voltage", avgVoltage);
  if (isValid(totalPower))   success &= Firebase.RTDB.setFloat(&fbdo, totalPath + "/Power", totalPower);

  if (success) {
    Serial.println("✅ Firebase upload with history successful.");
  } else {
    Serial.print("❌ Firebase error: ");
    Serial.println(fbdo.errorReason());
  }

  delay(5000); // 5 seconds between each log
}
