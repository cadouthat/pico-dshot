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
  // If enable_repeat is true, the PIO will continuously output the last provided value at
  // 8000 frames per second.
  // Warning: enable_repeat should only be used with the watchdog enabled, otherwise it is
  // unsafe as the PIO will carry on sending dshot frames even if the CPU is stuck.
  bool init(bool enable_repeat);

  // Note: enable_repeat applies to the latest value from any send function.
  // When enable_repeat is false, each send function call triggers a single dshot frame

  // Send a raw DShot command
  void sendCommand(uint16_t c);

  // Send throttle command once, for specified throttle in range [0, 1]
  void sendThrottle(double t);

  // Stop generating output (until next send command)
  // It is not necessary to call this when enable_repeat is false
  void stop();

  // Util to compute the command value for a specified throttle in range [0, 1]
  static uint16_t getThrottleCommand(double t);

 private:
  static constexpr uint16_t MIN_THROTTLE_COMMAND = 48;
  static constexpr uint16_t MAX_THROTTLE_COMMAND = 2047;

  uint dshot_gpio;

  PIO pio;
  uint pio_offset;
  int pio_sm = -1;
};

#endif
