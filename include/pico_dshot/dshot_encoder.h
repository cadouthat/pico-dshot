#ifndef __PICO_DSHOT_DSHOT_ENCODER_H__
#define __PICO_DSHOT_DSHOT_ENCODER_H__

#include <stdint.h>

#include "hardware/pio.h"

class DShotEncoder {
 public:
  DShotEncoder(uint dshot_gpio, PIO pio = pio0)
    : dshot_gpio(dshot_gpio), pio(pio) {}
  // TODO: cleanup in destructor

  // Init PIO, but do not output data yet
  bool init();

  // Set methods begin continuously generating output, repeating the last value
  void setCommand(uint16_t c); // Set the DShot command value
  void setThrottle(double t);  // Set the throttle in range [0, 1]

  // Stop generating output (until next set command)
  void stop();

 private:
  static constexpr uint16_t MIN_THROTTLE_COMMAND = 48;
  static constexpr uint16_t MAX_THROTTLE_COMMAND = 2047;

  uint dshot_gpio;

  PIO pio;
  uint pio_offset = 0;
  uint pio_sm = 0;
};

#endif
