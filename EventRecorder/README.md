# EventRecorder module

This directory contains the reusable EventRecorder module for PY32 targets.

## Files

- `Inc/EventRecorder.h`  
  Public API and event helper macros.
- `Inc/EventRecorderConf.h`  
  Build-time configuration (record count, timestamp source, PY32 timer settings).
- `Src/EventRecorder.c`  
  Event Recorder core implementation, adapted for PY32/CMSIS environment.
- `Src/EventRecorderHwTimer.c`  
  PY32 timer backend used by Event Recorder timestamping.

## Integration checklist

1. Add both `Src` source files to your project.
2. Add `Inc` to your include paths.
3. Ensure `py32f0xx.h` is available in include paths.
4. Verify timer configuration in `EventRecorderConf.h` matches your system clock.
5. Call `EventRecorderInitialize(...)` during system/application initialization.

## Timer backend behavior

- Uses a selected general-purpose/advanced timer (`TIM1/TIM3/TIM14/TIM16/TIM17`, depending on config and part support).
- Prescaler is computed from:
  - `PY32_EVENT_TIMER_INPUT_HZ`
  - `PY32_EVENT_TIMER_TICK_HZ`
- Returns failure from setup when parameters are invalid or not integer-divisible.

## Compatibility

This implementation targets PY32F0-family style CMSIS device headers and is designed to work smoothly with Keil MDK projects.
