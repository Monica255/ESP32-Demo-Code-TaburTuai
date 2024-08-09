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
  

  // membaca sensor water level
  //int pulse, inches, cm;
  //digitalWrite(TRIG_WL,LOW);
  //delayMicroseconds(2);
  //digitalWrite(TRIG_WL, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(TRIG_WL, LOW);
  //pulse = pulseIn(ECHO_WL, HIGH);
  //valCm = pulse * 0.034 / 2;
  //inches = valCm * 2.54;
  
  //readWaterFlow();
  Serial.println("Temp : " + String(valTemp));
  Serial.println("Hum : " + String(valHum));
  Serial.println("Moisture: " + String(valSoil) + "%");
  Serial.println("read soil: "+String(readSoil));
  //Serial.print("Jarak (cm) : " + String(valCm));

  delay(500);
}

//void readWaterFlow()
//{
  //currentMillis = millis();
  //if (currentMillis - previousMillis > interval) {
    
    //pulse1Sec = pulseCount;
    //pulseCount = 0;

    //flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    //previousMillis = millis();


    //flowMilliLitres = (flowRate / 60) * 1000;

    // Add the millilitres passed in this second to the cumulative total
    //totalMilliLitres += flowMilliLitres;
    
    // Print the flow rate for this second in litres / minute
    //Serial.print("Flow rate: ");
    //Serial.print(int(flowRate));
    //Serial.println("L/min");

    //Serial.print("\t");       // Print tab space

    // Print the cumulative total of litres flowed since starting
    //Serial.print("Output Liquid Quantity: ");
    //Serial.print(totalMilliLitres);
    //Serial.print("mL / ");
    //Serial.print(totalMilliLitres / 1000);
    //Serial.println("L");
  //}
//}
