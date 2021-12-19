#include <Arduino.h>
#include <HTTPClient.h>
#include <iostream>
#include <string>

#include "sensors/rht03.h"
#include "sensors/ldr.h"
#include "sensors/bmp180.h"
#include "driver_code/cap.h"

#include "controller.h"

#include "wifi/connection.h"

#define SAMPLE_NUMBER 10
#define SERVER_ADDRESS "Server address to connect to"

float temperatureValues[SAMPLE_NUMBER];
float pressureValues[SAMPLE_NUMBER];
float lightValues[SAMPLE_NUMBER];
float humidityValues[SAMPLE_NUMBER];
const char *initialTime = __TIME__;
string server_endpoint = "endpoint";
using namespace std;

void setup() {
  Serial.begin(115200);
  initializeController();
  initializeRHT03();
  initializeBMP180();
  initializeLDR();
}

void loop() {
  if (__TIME__ - initialTime < 15*60){
    return;
  }
  else{
    float tempMean = getMean(temperatureValues);
    float tempSD = getStandardDeviation(temperatureValues, tempMean);
    float humidityMean = getMean(humidityValues);
    float humiditySD = getStandardDeviation(humidityValues, humidityMean);
    float pressureMean = getMean(pressureValues);
    float pressureSD = getStandardDeviation(pressureValues, pressureMean);
    float lightMean = getMean(lightValues);
    float lightSD = getStandardDeviation(lightValues, lightMean);
    String capMessage = generateCAPMessage(tempMean, tempSD, humidityMean, humiditySD, pressureMean, pressureSD, lightMean, lightSD);
    char serverAddress[] = SERVER_ADDRESS;
    if (isWiFiConnected()){
      HTTPClient http;
      http.begin(server_endpoint);
      int response = http.POST(capMessage);
      String response = http.getString();
      http.end();
    }
    else{
      Serial.println("Wi-Fi connection not established.");
    }
  }
}

double getMean(float values[SAMPLE_NUMBER]) { 
  float sum = 0.0;
  for (int i = 0; i < SAMPLE_NUMBER; i++)
  {
    sum += values[i];
  }
  return sum/SAMPLE_NUMBER;
 }

double getStandardDeviation(float values[SAMPLE_NUMBER], float mean) {
  float standardDeviation = 0.0;
  for (int i = 0; i < SAMPLE_NUMBER; ++i)
  {
    standardDeviation += pow(values[i] - mean, 2);
  }

  return sqrt(standardDeviation / SAMPLE_NUMBER);
}
