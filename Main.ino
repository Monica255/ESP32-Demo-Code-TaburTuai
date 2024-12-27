// branch mamasa

// Library Firebase ESP32
#include <WiFi.h>
#include <FirebaseESP32.h>

// Library Sensor DHT
#include <DHT.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Pin Sensor
#define SOILPIN 32 // ADC0
#define SOILPIN2 35
#define SOILPIN3 34
#define SOILPIN4 36
#define DHTPIN 15 //RX 3
//#define POMPA2PIN 2 //D2 4
#define POMPA1PIN 4 //D2 4
// #define LAMPU1PIN 5 //D4 2

// pin water level
#define TRIG_WL 5
#define ECHO_WL 18

// Pin sensor water flow
#define WATER_FLOW 17

//#define DHTTYPE Sensor;
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//wifi dan password
#define WIFI_SSID "Wifi"
#define WIFI_PASSWORD "Wifi12345"

#define API_KEY "AIzaSyAU9mj87Pq1ixTQm7lkzMHtaz1Eqm0Iht0"
#define USER_EMAIL "test@test.com"
#define USER_PASSWORD "123456"
#define UID "Za1HWAsqusRwQIIi3hqFeXOYFDs2"

FirebaseData fbdo;
FirebaseJson json;
FirebaseAuth auth;
FirebaseConfig config;

String uid, path, pathPompaK1 , pathLampuK1, pathMonitoring;

// init variabel value sensor
//int bacaSensorPH = 0;   //membaca hasil dari sensor pH
int valTemp, valHum;
int valCm;
int valSoil;
int valSoil2, valSoil3, valSoil4;

// init variabel status 0/1
int statePompa1;
// int stateLampu1;

// init variable water level
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

void IRAM_ATTR pulseCounter()
{
 pulseCount++;
}

void initPin() {
  pinMode(POMPA1PIN, OUTPUT);
  pinMode(LAMPU1PIN, OUTPUT);
  pinMode(SOILPIN, INPUT);
  pinMode(SOILPIN2, INPUT);
  pinMode(SOILPIN3, INPUT);
  pinMode(SOILPIN4, INPUT);
  pinMode(TRIG_WL, OUTPUT);
  pinMode(ECHO_WL, INPUT);
  pinMode(WATER_FLOW, INPUT_PULLUP);
}

void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

void initFirebase() {
  config.api_key = API_KEY;
    auth.user.email = "test@test.com";
    auth.user.password = "123456";
    uid = UID; 

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  config.database_url = "smart-farming-andro-default-rtdb.asia-southeast1.firebasedatabase.app"; 
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
}


void setup() {
  Serial.begin(115200);

  dht.begin();
  
   initPin();
   initWiFi();
   Serial.println("Connection to Firebase");
   
   initFirebase();
   readFirebase();
   
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
 totalMilliLitres = 0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(WATER_FLOW), pulseCounter, FALLING);
}

void readFirebase(){
  Serial.println("Getting User UID");

  path = "/smart_farming/" + String(uid) + "/realtime_kebun";
  pathPompaK1 =  String(path) + "/kebun_1/controlling/pompa_1/state";
  pathLampuK1 =  String(path) + "/kebun_1/controlling/lampu_1/state";
  pathMonitoring = String (path) + "/kebun_1/monitoring";
}

void loop() {
  Serial.print("looping");
  if(!Firebase.ready()){
    initFirebase();
    readFirebase();
    Serial.print("Firebase now ready");
  }
  
  // GET CONNECTION STATE
  get_connection();
  
  // GET STATUS KONTROL
  get_status();

  // READ DATA SENSOR
  read_sensor();

  // KIRIM DATA SENSOR KE FIREBASE
  sent_data();

  delay(1000); 
}
