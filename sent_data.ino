void sent_data() {
  // ini void khusus update monitoring

  json.set("temperatur", valTemp);
  json.set("humidity", valHum);
  json.set("kelembaban_tanah_1", valSoil);
  //json.set("water_level", valCm);
  //json.set("water_flow",flowRate);

  Firebase.setJSON(fbdo, pathMonitoring, json);

}
