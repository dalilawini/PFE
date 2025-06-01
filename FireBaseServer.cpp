#include "FireBaseServer.h"

FireBaseServer::FireBaseServer() {
}

int FireBaseServer::begin() {
  if (!beginFlag) {
    fbdo.clear();
    Firebase.reset(&config);
  }
  Serial.println("\nFireBaseServer: begin starting.");
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
  Firebase.reconnectNetwork(true);

  // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
  // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;
  Serial.println("\nFireBaseServer: begin completed .");
  beginFlag = false;
  return 1;
}

void FireBaseServer::update() {
  if (Firebase.ready()) {
    if (Firebase.RTDB.setString(&fbdo, "/TAG_ID", TAG_ID)) {
      Serial.println("Data sent successfully");
    } else {
      Serial.print("Failed to send data: ");
      Serial.println(fbdo.errorReason());
    }

    delay(500);

    if (Firebase.RTDB.getInt(&fbdo, "/Authorized", &Authorized)) {
      Serial.println("Read successful");
      Serial.print("Access : ");
      Serial.println(Authorized ? "Authorized" : "Denied");
    } else {
      Serial.print("Failed to read data: ");
      Serial.println(fbdo.errorReason());
    }
  }
}

String FireBaseServer::toString() {
  return ("TAG_ID: " + TAG_ID + ",Access: " + (Authorized ? "Authorized" : "Denied"));
}
