# Arduino Embedded Fundamentals

A collection of arduino/c++ projects that include sensor and I/O programming(February 2024). The final project beautifully integrates these into an embedded security I/0 system,
 in which the output is displayed onto an LCD screen and a lock/unlock state mechanism, utilizing non-blocking timing and hardware asynchrony throughout.

## Contents

- **Ultrasonic Sensor /** - distance sensing progression: interrupt-driven reading -> LCD-display ouput -> complementary-filtering to smooth out native sensor
issues via exponential moving averag.
- **Photoresistor /** - Light-Level Sensing: LED response to room brightness -> averaged luminosity sampling script written in **ComputingAverageLuminosity.ino**
**IRremote_Code /** - Includes IRremote decoding through raw button-print based on input -> basic switch structure command handling -> combined with LCD feedback
**Final Project /** - Includes an 8 step incremental build of an embedded security I/0 project -> ultrasonic-based instrusion detection, LED status indicators, LCD display,
IR remote unlock, and an unlock/lock state mechanism. **Step 8 is the final, fully integrated script** - begin there if you desire to read one file only. Each previous step
is revealed to demonstrate the building process.

## Technical notes

- Ultrasonic sensing uses a hardware interrupt (`attachInterrupt`) on the
  echo pin, rather than blocking `pulseIn()` calls.
- All timing (LED blinking, button debouncing, sensor polling) uses
  non-blocking `millis()`-based scheduling instead of `delay()`.
- Requires the [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote)
  library (Arduino IDE → Library Manager). `LiquidCrystal` ships bundled
  with the Arduino core.
