void get_status() {
  // Get status from firebase

  Serial.printf("Get int pompa_1... %s\n", Firebase.getInt(fbdo, pathPompaK1, &statePompa1) ? String(statePompa1).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int lampu_1... %s\n", Firebase.getInt(fbdo, pathLampuK1, &stateLampu1) ? String(stateLampu1).c_str() : fbdo.errorReason().c_str());

  digitalWrite(POMPA1PIN, statePompa1);
  digitalWrite(LAMPU1PIN, stateLampu1);
 
}
