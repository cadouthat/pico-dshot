# pico-dshot
DShot library for the Raspberry Pi Pico using PIO

Supports continuously encoding DShot output on GPIO(s) without ever interrupting the CPU.

Requires 1 PIO state machine per encoder, and some PIO program space shared amongst all instances.
