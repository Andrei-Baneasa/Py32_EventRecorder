# PY32 EventRecorder Port (Keil-compatible)

This repository provides a **PY32 port of Arm CMSIS Event Recorder** for projects built with **Keil MDK** (and generally usable in other bare-metal toolchains).

It includes:

- the EventRecorder public headers and configuration file,
- the EventRecorder core source,
- a PY32 hardware timer backend for timestamps,
- and a GPIO toggle example project (currently included as a reference, not yet finalized).

## Repository layout

- `EventRecorder/Inc/` – public headers (`EventRecorder.h`, `EventRecorderConf.h`)
- `EventRecorder/Src/` – implementation (`EventRecorder.c`, `EventRecorderHwTimer.c`)
- `Examples/GPIO_Toggle/` – integration example project for PY32/Keil

## What this port changes

Compared with upstream CMSIS Event Recorder, this port adds/adjusts:

1. **PY32 target integration** (`py32f0xx.h` includes and timer peripheral setup).
2. **User timer implementation** for timestamp source using PY32 timers.
3. **Compiler compatibility shim** in `EventRecorder.c` for common attributes/macros used by the CMSIS implementation.

## Quick start (Keil MDK)

1. Copy these files into your application:
   - `EventRecorder/Inc/EventRecorder.h`
   - `EventRecorder/Inc/EventRecorderConf.h`
   - `EventRecorder/Src/EventRecorder.c`
   - `EventRecorder/Src/EventRecorderHwTimer.c`
2. Add include path for `EventRecorder/Inc`.
3. Ensure your project already has PY32 device support (`py32f0xx.h`, startup, system clock init).
4. Configure timer options in `EventRecorderConf.h`:
   - `PY32_EVENT_TIMER_NUM`
   - `PY32_EVENT_TIMER_INPUT_HZ`
   - `PY32_EVENT_TIMER_TICK_HZ`
5. Initialize early in startup (for example, after clock init):

   ```c
   #include "EventRecorder.h"

   void App_Init(void) {
     EventRecorderInitialize(EventRecordAll, 1U);
   }
   ```

6. Record events in code:

   ```c
   EventRecord2(EventID(EventLevelAPI, 0x01U, 0x01U), arg1, arg2);
   ```

## Configuration notes

- `EVENT_RECORD_COUNT` controls buffer size (records are 16 bytes each).
- `EVENT_TIMESTAMP_SOURCE` is set for the user timer path in this port.
- Timestamp frequency must divide input clock exactly in the current timer implementation.

## Example status

`Examples/GPIO_Toggle` is kept in-repo for reference and toolchain setup, but it is not considered fully polished yet.

## License

See [LICENSE](./LICENSE). Core Event Recorder code remains under the original Arm Apache-2.0 licensing terms, with porting changes for PY32 integration in this repository.
