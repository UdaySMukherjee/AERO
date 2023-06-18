#include "ArduiKalman.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <SPI.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include <Wire.h>
#include "BMP085.h"

#include <DHT.h>
#define DHTPIN 04
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
float pressure;
float mbar;
BMP085 myBarometer; // initialise pressure sensor

#define MQ135_analog 36
#define MQ9_analog 39
#define MQ8_analog 34
#define MQ7_analog 35
#define MQ5_analog 32
#define MQ4_analog 33
#define MQ3_analog 25
#define MQ2_analog 26
#define UPDATE_TIME  100
long current; 

int stateNum = 1;
int measureNum = 1;

//init matrix for Kalman
float xc1[1];
float xc2[1];// correct state vector 
float xc3[1];
float xc4[1];// correct state vector 
float xc5[1];
float xc6[1];// correct state vector 
float xc7[1];
float xc8[1];// correct state vector 
float xp[1];        // predict state vector 
float A[1][1];      // prediction error covariance 
float Q[1][1];      // process noise covariance 
float R[1][1];      // measurement error covariance
float H[1][1];      // Measurement model
float P[1][1];      // Post-prediction, pre-update
  
KalmanFilter m_kf1;
KalmanFilter m_kf2;
KalmanFilter m_kf3;
KalmanFilter m_kf4;
KalmanFilter m_kf5;
KalmanFilter m_kf6;
KalmanFilter m_kf7;
KalmanFilter m_kf8;

void setup() {
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  dht.begin(); 
  myBarometer.init();
  pinMode(MQ7_analog, INPUT); 
  pinMode(MQ135_analog, INPUT);
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);
  
  m_kf1.init(stateNum, measureNum, &A[0][0], &P[0][0], &Q[0][0], &H[0][0], &R[0][0], &xp[0], &xc1[0]);
  m_kf1.zeros();
  m_kf2.init(stateNum, measureNum, &A[0][0], &P[0][0], &Q[0][0], &H[0][0], &R[0][0], &xp[0], &xc2[0]);
  m_kf2.zeros();
  m_kf3.init(stateNum, measureNum, &A[0][0], &P[0][0], &Q[0][0], &H[0][0], &R[0][0], &xp[0], &xc3[0]);
  m_kf3.zeros();
  m_kf4.init(stateNum, measureNum, &A[0][0], &P[0][0], &Q[0][0], &H[0][0], &R[0][0], &xp[0], &xc4[0]);
  m_kf4.zeros();
  m_kf5.init(stateNum, measureNum, &A[0][0], &P[0][0], &Q[0][0], &H[0][0], &R[0][0], &xp[0], &xc5[0]);
  m_kf5.zeros();
  m_kf6.init(stateNum, measureNum, &A[0][0], &P[0][0], &Q[0][0], &H[0][0], &R[0][0], &xp[0], &xc6[0]);
  m_kf6.zeros();
  m_kf7.init(stateNum, measureNum, &A[0][0], &P[0][0], &Q[0][0], &H[0][0], &R[0][0], &xp[0], &xc7[0]);
  m_kf7.zeros();
  m_kf8.init(stateNum, measureNum, &A[0][0], &P[0][0], &Q[0][0], &H[0][0], &R[0][0], &xp[0], &xc8[0]);
  m_kf8.zeros();
  A[0][0] = 1.0f;
  H[0][0] = 1.0f;
  Q[0][0] = 0.01f;
  R[0][0] = 100.0f;
  P[0][0] = 1.0f;
  xc1[0] = analogRead(MQ2_analog);
  xc2[0] = analogRead(MQ3_analog);
  xc3[0] = analogRead(MQ4_analog);
  xc4[0] = analogRead(MQ5_analog);
  xc5[0] = analogRead(MQ7_analog);
  xc6[0] = analogRead(MQ8_analog);
  xc7[0] = analogRead(MQ9_analog);
  xc8[0] = analogRead(MQ135_analog);
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  // predict
  float *predict1 = m_kf1.predict();
  // correct
  float measured_value1 = analogRead(MQ2_analog);
  float measurement1[measureNum];
  measurement1[0] = measured_value1;
  float *correct1 = m_kf1.correct(measurement1);
  float estimated_value_MQ2 = correct1[0];
  //Serial.println();

  float *predict2 = m_kf2.predict();
  // correct
  float measured_value2 = analogRead(MQ3_analog);
  float measurement2[measureNum];
  measurement2[0] = measured_value2;
  float *correct2 = m_kf2.correct(measurement2);
  float estimated_value_MQ3 = correct2[0];

  float *predict3 = m_kf3.predict();
  // correct
  float measured_value3 = analogRead(MQ4_analog);
  float measurement3[measureNum];
  measurement3[0] = measured_value3;
  float *correct3 = m_kf3.correct(measurement3);
  float estimated_value_MQ4 = correct3[0];

  float *predict4 = m_kf4.predict();
  // correct
  float measured_value4 = analogRead(MQ5_analog);
  float measurement4[measureNum];
  measurement4[0] = measured_value4;
  float *correct4 = m_kf4.correct(measurement4);
  float estimated_value_MQ5 = correct4[0];

  // predict
  float *predict5 = m_kf5.predict();
  // correct
  float measured_value5 = analogRead(MQ7_analog);
  float measurement5[measureNum];
  measurement5[0] = measured_value5;
  float *correct5 = m_kf5.correct(measurement5);
  float estimated_value_MQ7 = correct5[0];
  //Serial.println();

  float *predict6 = m_kf6.predict();
  // correct
  float measured_value6 = analogRead(MQ8_analog);
  float measurement6[measureNum];
  measurement6[0] = measured_value6;
  float *correct6 = m_kf6.correct(measurement6);
  float estimated_value_MQ8 = correct6[0];

  float *predict7 = m_kf7.predict();
  // correct
  float measured_value7 = analogRead(MQ9_analog);
  float measurement7[measureNum];
  measurement7[0] = measured_value7;
  float *correct7 = m_kf7.correct(measurement7);
  float estimated_value_MQ9 = correct7[0];

  float *predict8 = m_kf8.predict();
  // correct
  float measured_value8 = analogRead(MQ135_analog);
  float measurement8[measureNum];
  measurement8[0] = measured_value8;
  float *correct8 = m_kf8.correct(measurement8);
  float estimated_value_MQ135 = correct8[0];

  float h=dht.readHumidity();
  float t=dht.readTemperature();
  Serial.print(h);
  Serial.println(" %");
  Serial.print(t);
  Serial.println(" °C");

  pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP()); // read pressure value in pascals
  mbar = pressure / 100; // convert millibar to pascals
  Serial.print(mbar);
  Serial.println(" Pa");

  Serial.print("MQ2 ");
  Serial.println(estimated_value_MQ2);
  Serial.print("MQ3 ");
  Serial.println(estimated_value_MQ3);
  Serial.print("MQ4 ");
  Serial.println(estimated_value_MQ4);
  Serial.print("MQ5 ");
  Serial.println(estimated_value_MQ5);
  Serial.print("MQ7 ");
  Serial.println(estimated_value_MQ7);
  Serial.print("MQ8 ");
  Serial.println(estimated_value_MQ8);
  Serial.print("MQ9 ");
  Serial.println(estimated_value_MQ9);
  Serial.print("MQ135 ");
  Serial.println(estimated_value_MQ135);

  // set the fields with the values
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, mbar);
  ThingSpeak.setField(3, estimated_value_MQ4);
  ThingSpeak.setField(4, estimated_value_MQ5);
  ThingSpeak.setField(5, estimated_value_MQ7);
  ThingSpeak.setField(6, estimated_value_MQ8);
  ThingSpeak.setField(7, estimated_value_MQ9);
  ThingSpeak.setField(8, estimated_value_MQ135);
 
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(20000); // Wait 20 seconds to update the channel again
}
