#include <SoftwareSerial.h>

#define SER_FIFO_SIZE 64

SoftwareSerial ser_midi31(10, 11); // RX, TX  これも、Serialも64Bのバッファを持ってるそうです
SoftwareSerial ser_dbg(8, 9); // RX, TX


void setup() {
  Serial.begin(38400);
  ser_dbg.begin(19200);   // 同時に二つの”受信は”できない(.listen() で切り替えて
  ser_midi31.begin(31250);

//  Serial.println("38400 start");  // やるなら sysEx とかじゃないと不正
//  ser_midi31.println("31250 start");
  ser_dbg.println("dbg print start");
}



void loop() {
  int s;
  uint8_t d;
  static uint16_t skip = 0;

  // 38400 -> midi
  if (s = Serial.available())
  {
    ser_midi31.write( Serial.read() );
    if( s > 2 )
    {
      ser_dbg.println( s );
    }
  }

  // midi -> 38400
  if (s = ser_midi31.available())
  {
    Serial.write( ser_midi31.read() );
  }
}

