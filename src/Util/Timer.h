#ifndef CIRCUITOS_TIMER_H
#define CIRCUITOS_TIMER_H

#include <Arduino.h>

#define dis(timer) do { CM::timerAlarmDisable(timer); CM::timerStop(timer); CM::timerWrite(timer, 0); } while(0)

struct hw_timer_reg_s;
typedef struct hw_timer_reg_s hw_timer_reg_t;

struct hw_timer_s;
typedef struct hw_timer_s hw_timer_t;

typedef struct hw_timer_s hw_timer_t;

namespace CM {
void IRAM_ATTR timerStop(hw_timer_t* timer);

void IRAM_ATTR timerWrite(hw_timer_t* timer, uint64_t val);

void IRAM_ATTR timerAlarmWrite(hw_timer_t* timer, uint64_t alarm_value, bool autoreload);

void IRAM_ATTR timerAlarmDisable(hw_timer_t* timer);

uint64_t IRAM_ATTR timerRead(hw_timer_t* timer);
}

#endif //CIRCUITOS_TIMER_H
