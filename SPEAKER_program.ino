#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"
TMRpcm tmrpcm;
void setup()
{
17;
 tmrpcm.speakerPin = 9;
 Serial.begin(9600);
 if(!SD.begin(SD_ChipSelectPin))
 {
 Serial.println("SD fail");
 return;
 }
 tmrpcm.setVolume(5);
 tmrpcm.play("1.wav");
}
void loop() {}
