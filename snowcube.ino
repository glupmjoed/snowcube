#include "snowcube.h"

// x/y axis pins:
// 2, 4, 7, 8, 12, 13
uint8_t IO_PINS_Z[6];

// z axis pins:
// 3, 5, 6, 9, 10, 11
uint8_t xy1[3];
uint8_t xy2[3];

// cube buffer
#define CB_SIZE (6 * 8 * 8)
uint8_t cb[CB_SIZE];

void setup() {

  setPins();

  LEDDiagnosticSetup();

}

void loop() {
  
  LEDDiagnosticLoop();

}

void displayFrameBuffer() {

  int i = 0;
  uint8_t upper;
  uint8_t lower;

  while (i < 256) {
    upper = i >> (3 + 3);
    lower = (i >> 3) & 7;
    writeControl(upper, lower, HIGH);
    writeColumn(i);
    writeControl(upper, lower, LOW);
    delayMicroseconds(STD_DELAY);
    i += 8;
  }

  upper = 4;
  while (upper < 8) {
    writeControl(upper, 0, HIGH);
    writeColumn(i);
    writeControl(upper, 0, LOW);
    delayMicroseconds(STD_DELAY);
    i += 8;
    upper++;

  }

}

void writeLED(uint8_t x, uint8_t y, uint8_t z, uint8_t val) {

  cb[(y << 6) + (x << 3) + z] = val;

}

uint8_t readLED(uint8_t x, uint8_t y, uint8_t z) {

  return cb[(y << 6) + (x << 3) + z];

}

void writeColumn(int col) {

  digitalWrite(IO_PINS_Z[0], cb[col++]);
  digitalWrite(IO_PINS_Z[1], cb[col++]);
  digitalWrite(IO_PINS_Z[2], cb[col++]);
  digitalWrite(IO_PINS_Z[3], cb[col++]);
  digitalWrite(IO_PINS_Z[4], cb[col++]);
  digitalWrite(IO_PINS_Z[5], cb[col]);
  delayMicroseconds(STD_DELAY);
  digitalWrite(IO_PINS_Z[0], LOW);
  digitalWrite(IO_PINS_Z[1], LOW);
  digitalWrite(IO_PINS_Z[2], LOW);
  digitalWrite(IO_PINS_Z[3], LOW);
  digitalWrite(IO_PINS_Z[4], LOW);
  digitalWrite(IO_PINS_Z[5], LOW);

}

void writeColumnAnalog(int col) {

  analogWrite(IO_PINS_Z[0], cb[col++]);
  analogWrite(IO_PINS_Z[1], cb[col++]);
  analogWrite(IO_PINS_Z[2], cb[col++]);
  analogWrite(IO_PINS_Z[3], cb[col++]);
  analogWrite(IO_PINS_Z[4], cb[col++]);
  analogWrite(IO_PINS_Z[5], cb[col]);
  delayMicroseconds(STD_DELAY);
  analogWrite(IO_PINS_Z[0], LOW);
  analogWrite(IO_PINS_Z[1], LOW);
  analogWrite(IO_PINS_Z[2], LOW);
  analogWrite(IO_PINS_Z[3], LOW);
  analogWrite(IO_PINS_Z[4], LOW);
  analogWrite(IO_PINS_Z[5], LOW);

}

void loopColumn() {

   for (uint8_t j = 0; j < 6; j++) {
      digitalWrite(IO_PINS_Z[j], HIGH);
      delayMicroseconds(STD_DELAY);
      digitalWrite(IO_PINS_Z[j], LOW);
    }

}

void writeControl(int upper, int lower, uint8_t signal) {

  for (int i = 0; i < 3; i++) {
    digitalWrite(xy1[i], (lower>>i) & signal);
    digitalWrite(xy2[i], (upper>>i) & signal);
  }

}

void setPins() {

  //column:
  xy1[0] = 2;
  pinMode(2, OUTPUT);
  xy1[1] = 4;
  pinMode(4, OUTPUT);
  xy1[2] = 7;
  pinMode(7, OUTPUT);
  xy2[0] = 8;
  pinMode(8, OUTPUT);
  xy2[1] = 12;
  pinMode(12, OUTPUT);
  xy2[2] = 13;
  pinMode(13, OUTPUT);

  //layer:
  IO_PINS_Z[0] = 3;
  pinMode(3, OUTPUT);
  IO_PINS_Z[1] = 5;
  pinMode(5, OUTPUT);
  IO_PINS_Z[2] = 6;
  pinMode(6, OUTPUT);
  IO_PINS_Z[3] = 9;
  pinMode(9, OUTPUT);
  IO_PINS_Z[4] = 10;
  pinMode(10, OUTPUT);
  IO_PINS_Z[5] = 11;
  pinMode(11, OUTPUT);

}

void LEDDiagnosticSetup() {

  for (int i = 0; i < CB_SIZE; i++) {
    cb[i] = 1;
  }

}

void LEDDiagnosticLoop() {

  for (int i = 0; i < CB_SIZE; i++) {
    displayFrameBuffer();
    cb[i] = 0;
  }

  LEDDiagnosticSetup();

}
