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

  // Send a raw DShot command
  void sendCommand(uint16_t c);

  // Send throttle command once, for specified throttle in range [0, 1]
  // Note: this should be called often, most ESCs will disarm after a time period without throttle commands
  void sendThrottle(double t);

 private:
  static constexpr uint16_t MIN_THROTTLE_COMMAND = 48;
  static constexpr uint16_t MAX_THROTTLE_COMMAND = 2047;

  uint dshot_gpio;

  PIO pio;
  uint pio_offset;
  int pio_sm = -1;
};

#endif
