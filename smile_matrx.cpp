#include "Arduino_LED_Matrix.h"

#include "smile_matrx.h"

ArduinoLEDMatrix matrix;


  void smile () {
    matrix.begin();
    byte frame[8][12] = {
      { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 },
      { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
      { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
      { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
      { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    const uint32_t happy[] = {

      0x19819,

      0x80000001,

      0x81f8000

      };
  
  
    matrix.loadFrame(happy);
  }