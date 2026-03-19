#include "py32f0xx.h"
#include "EventRecorder.h"
#include "EventRecorderConf.h"

#if defined(PY32F002A) || defined(PY32F002B) || defined(PY32F002C)
  #if (PY32_EVENT_TIMER_NUM != 1) && (PY32_EVENT_TIMER_NUM != 16)
    #error "PY32F002 supports only TIM1 and TIM16"
  #endif
#endif
#if   (PY32_EVENT_TIMER_NUM == 1)
  #define EVENT_TIMER              TIM1
  #define EVENT_TIMER_ENABLE()     (RCC->APBENR2 |= RCC_APBENR2_TIM1EN)
  #define EVENT_TIMER_IS_16BIT     1

#elif (PY32_EVENT_TIMER_NUM == 3)
  #define EVENT_TIMER              TIM3
  #define EVENT_TIMER_ENABLE()     (RCC->APBENR1 |= RCC_APBENR1_TIM3EN)
  #define EVENT_TIMER_IS_16BIT     1

#elif (PY32_EVENT_TIMER_NUM == 14)
  #define EVENT_TIMER              TIM14
  #define EVENT_TIMER_ENABLE()     (RCC->APBENR2 |= RCC_APBENR2_TIM14EN)
  #define EVENT_TIMER_IS_16BIT     1

#elif (PY32_EVENT_TIMER_NUM == 16)
  #define EVENT_TIMER              TIM16
  #define EVENT_TIMER_ENABLE()     (RCC->APBENR2 |= RCC_APBENR2_TIM16EN)
  #define EVENT_TIMER_IS_16BIT     1

#elif (PY32_EVENT_TIMER_NUM == 17)
  #define EVENT_TIMER              TIM17
  #define EVENT_TIMER_ENABLE()     (RCC->APBENR2 |= RCC_APBENR2_TIM17EN)
  #define EVENT_TIMER_IS_16BIT     1

#else
  #error "Unsupported PY32_EVENT_TIMER_NUM"
#endif

#define EVENTREC_TIMER_HZ 1000000UL

uint32_t EventRecorderTimerSetup(void)
{
    uint32_t psc;

    if ((PY32_EVENT_TIMER_INPUT_HZ == 0U) || (PY32_EVENT_TIMER_TICK_HZ == 0U)) {
        return 0U;
    }
    
    if ((PY32_EVENT_TIMER_INPUT_HZ % PY32_EVENT_TIMER_TICK_HZ) != 0U) {
    // optional: reject non-integer divider
        return 0U;
    }
    psc = (PY32_EVENT_TIMER_INPUT_HZ / PY32_EVENT_TIMER_TICK_HZ) - 1U;

    EVENT_TIMER_ENABLE();

    EVENT_TIMER->CR1 = 0;
    EVENT_TIMER->PSC = psc;
    EVENT_TIMER->ARR = 0xFFFFU;
    EVENT_TIMER->CNT = 0U;
    EVENT_TIMER->EGR = TIM_EGR_UG;   // load prescaler immediately
    EVENT_TIMER->CR1 = TIM_CR1_CEN;

    return 1U;
}

uint32_t EventRecorderTimerGetFreq(void)
{
    return PY32_EVENT_TIMER_TICK_HZ;
}

uint32_t EventRecorderTimerGetCount(void)
{
    return EVENT_TIMER->CNT;
}