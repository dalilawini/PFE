#ifndef FIREBASESERVER_H
#define FIREBASESERVER_H
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

/*
#define API_KEY  "AIzaSyC8t_fg4MZoP9PgNyXmLG2e4Ngd7iYDITw"
#define DATABASE_URL "https://detectionpresence-19a28-default-rtdb.firebaseio.com/"
#define USER_EMAIL "oumaymaamzoughi@gmail.com"
#define USER_PASSWORD "oumaima"*/

#define API_KEY "AIzaSyDlxjQl7iUDNUY8uow-CvpjqWzXmRPKGTs"
#define DATABASE_URL "https://dali-4defd-default-rtdb.firebaseio.com/" 
#define USER_EMAIL "dalilawini742@gmail.com"
#define USER_PASSWORD "TEST123"
#define WIFI_SSID "MedAli"
#define WIFI_PASSWORD "1234567891"

class FireBaseServer {
private:
bool beginFlag=true;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
int Authorized = 0;
String TAG_ID="xx-xx-xx-xx";
public:
  FireBaseServer();
  ~FireBaseServer() {}
  void update();
  void setID(String id){TAG_ID=id;}
  int  begin();
  String toString();
};

#endif