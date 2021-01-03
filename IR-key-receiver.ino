/* IR key receiver for Digispark - Author: Helmar Wodtke 2021 */
/* Note: The used IR code is something like NEC and tries to avoid clashes. */

#include "DigiKeyboard.h"

#define IR_PIN     2
#define IR_START   4000
#define IR_ZERO    400
#define IR_ONE     1300
#define IR_DEVICE  0x23 // change this if you have a similar device

void setup() {
  pinMode(IR_PIN, INPUT);
  DigiKeyboard.sendKeyStroke(0); // allow OS to register the keyboard
}

int ircode[4];

void loop() {
  while (pulseIn(IR_PIN, HIGH) < IR_START);
  ircode[0] = ir_byte();
  ircode[1] = ir_byte();
  ircode[2] = ir_byte();
  ircode[3] = ir_byte();
  if (ircode[0] == IR_DEVICE && (ircode[1] ^ ircode[2] ^ 0xEC) == ircode[3])
    DigiKeyboard.sendKeyStroke(ircode[1], ircode[2]);
}

int ir_byte() {
  int i, m, r;
  
  for (r = i = 0; i < 8; i++) {
    r <<= 1;
    if ((m = pulseIn(IR_PIN, HIGH)) > IR_START) return -1;
    else if (m > IR_ONE) r |= 1;
    else if (m < IR_ZERO) return -1;
  }
  return r;
}
