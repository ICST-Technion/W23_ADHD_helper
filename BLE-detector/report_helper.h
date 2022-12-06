#include <Firebase.h>

#include <Arduino.h>
//#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

//Define Firebase Data object
FirebaseData fbdo;

unsigned long sendDataPrevMillis = 0;

void report(bool signupOK){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    // Read the current progress
    if (Firebase.RTDB.getInt(&fbdo, "progress/")) {
      if (fbdo.dataType() == "int") {
        int currProgress = fbdo.intData();
        Serial.println(currProgress);

        // Write an Float number on the database path test/count/float
        if (Firebase.RTDB.setFloat(&fbdo, "taskId1/progress/", currProgress +1)){
          Serial.println("PASSED");
          Serial.println("PATH: " + fbdo.dataPath());
          Serial.println("TYPE: " + fbdo.dataType());
        }
        else {
          Serial.println("FAILED");
          Serial.println("REASON: " + fbdo.errorReason());
        }
      }
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}
