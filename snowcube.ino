#include "snowcube.h"

// x/y axis pins:
// 2, 4, 7, 8, 12, 13
uint8_t IO_PINS_Z[6];

// z axis pins:
// 3, 5, 6, 9, 10, 11
uint8_t xy1[3];
uint8_t xy2[3];

// cube buffer
#define CB_SIZE (6 * 6 * 8)
uint8_t cb[CB_SIZE];

// discrete snow buffer
vertpt_t sbd[SBD_GENS];

void setup() {

  setPins();

  zeroCubeBuffer();

  snowDiscSetup();

}

void loop() {

  snowDisc();

}

// snowDisc simulates snowfall by moving snowflakes discretely down through the
// cube (i.e. one LED per snowflake).
void snowDisc() {

  int i = 0;
  while (i < SBD_GENS - SBD_MIN - 1) {

    int j = i;
    // turn off old snowflakes
    for (int z = 0; z < 6; z++) {
      writeLED(sbd[j].x, sbd[j].y, z, 0);
      j++;
    }
    // move snow buffer window forward
    i++;
    j = i;
    // turn on new snowflakes
    for (int z = 0; z < 6; z++) {
      writeLED(sbd[j].x, sbd[j].y, z, 1);
      j++;
    }

    // display cube buffer for approximately SBD_DELAY * STD_DELAY microseconds
    for (int k = 0; k < SBD_DELAY; k++) {
      displayCubeBuffer();
    }

  }
  zeroCubeBuffer();

}

// snowDiscSetup randomly places SBD_GENS layers of snowflakes in the discrete
// snow buffer array (sbd).
void snowDiscSetup() {

  uint8_t rand;
  for (int i = 0; i < SBD_GENS; i++) {
    rand = random(36);
    sbd[i] = {rand%(NUM_X*NUM_Y), rand/(NUM_X*NUM_Y)};
  }

}

void displayCubeBuffer() {

  int i = 0;
  uint8_t upper;
  uint8_t lower;

  while (i < 256) {
    upper = i >> (3 + 3);
    lower = (i >> 3) & 0x7;
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

  cb[(y * 8 * 6) + (x * 8) + z] = val;

}

uint8_t readLED(uint8_t x, uint8_t y, uint8_t z) {

  return cb[(y * 8 * 6) + (x * 8) + z];

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
    displayCubeBuffer();
    cb[i] = 0;
  }

  LEDDiagnosticSetup();

}

void zeroCubeBuffer() {
  for (int i = 0; i < CB_SIZE; i++) {
    cb[i] = 0;
  }
}
