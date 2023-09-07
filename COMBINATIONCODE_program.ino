#include <SPI.h>
#include <MFRC522.h>
#include <SD.h>
#include <TMRpcm.h>

#define SS_PIN 10  // Slave Select pin for SD card
#define RST_PIN 9  // Reset pin for RFID-RC522 module

MFRC522 rfid(RST_PIN, SS_PIN);
TMRpcm audio;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  SD.begin(SS_PIN);
  audio.speakerPin = 3;  // Pin connected to the speaker
  audio.setVolume(5);    // Adjust the volume (0 to 7)
}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String cardID = getCardID();
    playSound(cardID);
    rfid.PICC_HaltA();
  }
}

String getCardID() {
  String cardID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    cardID += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    cardID += String(rfid.uid.uidByte[i], HEX);
  }
  cardID.toUpperCase();
  return cardID;
}

void playSound(String cardID) {
  audio.disable();
  
  if (cardID == "833D58AD") {
    String fileName = "coco.wav";  // Name of the audio file
    if (SD.exists(fileName)) {
      Serial.print("Playing: ");
      Serial.println(fileName);

      // Convert String to char array
      char charArray[fileName.length() + 1];
      fileName.toCharArray(charArray, sizeof(charArray));

      audio.play(charArray);  // Pass the char array to the play() function

      while (audio.isPlaying()) {
        // Wait for audio to finish playing
      }
    } else {
      Serial.println("File not found.");
    }
  }
  
  delay(1000);  // Delay to prevent rapid scanning
}
