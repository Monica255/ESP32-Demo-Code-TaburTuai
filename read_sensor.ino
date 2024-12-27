void read_sensor() {
  // ini coding khusus untuk membaca data sensor, agar mudah maintenance coding tiap sensornya

  // get value temperature from sensor
  valHum = dht.readHumidity();
  valTemp = dht.readTemperature();
  if (isnan(valHum) || isnan(valTemp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  // membaca sensor kelembaban
   const int soilTreshold = 100;
  // read soil sensor 1
  int readSoil = analogRead(SOILPIN);
  if (readSoil >= soilTreshold && readSoil <= 4095) {
    valSoil = (100 - ((readSoil / 4095.0) * 100));
  } else {
    Serial.println(F("Failed to read soil sensor 1!"));
    // Set valSoil to 0 if the soil sensor 1 reading is out of range
    valSoil = 0;
  }

  // read soil sensor 2
  int readSoil2 = analogRead(SOILPIN2);
  if (readSoil2 >= soilTreshold && readSoil2 <= 4095) {
    valSoil2 = (100 - ((readSoil2 / 4095.0) * 100));
  } else {
    Serial.println(F("Failed to read soil sensor 2!"));
    // Set valSoil to 0 if the soil sensor 1 reading is out of range
    valSoil2 = 0;
  }

  // read soil sensor 3
  int readSoil3 = analogRead(SOILPIN3);
  if (readSoil3 >= soilTreshold && readSoil3 <= 4095) {
    valSoil3 = (100 - ((readSoil3 / 4095.0) * 100));
  } else {
    Serial.println(F("Failed to read soil sensor 3!"));
    // Set valSoil to 0 if the soil sensor 1 reading is out of range
    valSoil3 = 0;
  }

  // read soil sensor 4
  int readSoil4 = analogRead(SOILPIN4);
  if (readSoil4 >= soilTreshold && readSoil4 <= 4095) {
    valSoil4 = (100 - ((readSoil4 / 4095.0) * 100));
  } else {
    Serial.println(F("Failed to read soil sensor 4!"));
    // Set valSoil to 0 if the soil sensor 1 reading is out of range
    valSoil4 = 0;
  }
  

  // membaca sensor water level
  int pulse, inches, cm;
  digitalWrite(TRIG_WL,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_WL, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_WL, LOW);
  pulse = pulseIn(ECHO_WL, HIGH);
  valCm = pulse * 0.034 / 2;
  inches = valCm * 2.54;
  
  readWaterFlow();
  Serial.println("Temp : " + String(valTemp));
  Serial.println("Hum : " + String(valHum));
  Serial.println("Soil Moisture1: " + String(valSoil) + "%");
  Serial.println("Soil Moisture2: " + String(valSoil2) + "%");
  Serial.println("Soil Moisture3: " + String(valSoil3) + "%");
  Serial.println("Soil Moisture4: " + String(valSoil4) + "%");
  Serial.print("Jarak (cm) : " + String(valCm));

  delay(500);
}

void readWaterFlow()
{
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    
    pulse1Sec = pulseCount;
    pulseCount = 0;

    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();

    flowMilliLitres = (flowRate / 60) * 1000;

    //Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;
    
    //Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));
    Serial.println("L/min");

    Serial.print("\t");       // Print tab space

    //Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL / ");
    Serial.print(totalMilliLitres / 1000);
    Serial.println("L");
  }
}
