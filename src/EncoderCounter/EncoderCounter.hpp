#include "Arduino.h"
#include "../Utilities.h"

#ifndef ENCODER_H
#define ENCODER_H

class EncoderCounter {
  uint8 slaveSelectEnc1, slaveSelectEnc2;

  signed long encoder1count, encoder2count;

public:
  EncoderCounter(uint8 ss1, uint8 ss2);
  void init();
  long readEncoder(int encoder);
  void clearCount();
};

#endif
