#include "pico_dshot/dshot_encoder.h"

#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"

#include "pico_pio_loader/pico_pio_loader.h"

#include "dshot_encoder.pio.h"

bool DShotEncoder::init() {
  pio_sm = pio_claim_unused_sm(pio, /*required=*/false);
  if (pio_sm < 0) {
    return false;
  }

  if (!pio_loader_add_or_get_offset(pio, &dshot_encoder_program, &pio_offset)) {
    pio_sm_unclaim(pio, pio_sm);
    pio_sm = -1;
    return false;
  }

  dshot_encoder_program_init(pio, pio_sm, pio_offset, dshot_gpio);

  // The PIO will begin waiting for command values
  pio_sm_set_enabled(pio, pio_sm, true);
  return true;
}

void DShotEncoder::sendCommand(uint16_t c) {
  // Shift for telemetry bit (0)
  c = c << 1;

  // Shift and include checksum
  uint16_t checksum = (c ^ (c >> 4) ^ (c >> 8)) & 0x0F;
  c = (c << 4) | checksum;

  pio_sm_put_blocking(pio, pio_sm, c);
}

void DShotEncoder::sendThrottle(double t) {
  if (t < 0) t = 0;
  if (t > 1) t = 1;

  uint16_t c = MIN_THROTTLE_COMMAND + t * (MAX_THROTTLE_COMMAND - MIN_THROTTLE_COMMAND);
  if (c < MIN_THROTTLE_COMMAND) c = MIN_THROTTLE_COMMAND;
  if (c > MAX_THROTTLE_COMMAND) c = MAX_THROTTLE_COMMAND;
  sendCommand(c);
}
