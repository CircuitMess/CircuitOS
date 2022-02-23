#include "Timer.h"

struct hw_timer_reg_s {
	union {
		struct {
			uint32_t reserved0: 10;
			uint32_t alarm_en: 1;             /*When set  alarm is enabled*/
			uint32_t level_int_en: 1;             /*When set  level type interrupt will be generated during alarm*/
			uint32_t edge_int_en: 1;             /*When set  edge type interrupt will be generated during alarm*/
			uint32_t divider: 16;             /*Timer clock (T0/1_clk) pre-scale value.*/
			uint32_t autoreload: 1;             /*When set  timer 0/1 auto-reload at alarming is enabled*/
			uint32_t increase: 1;             /*When set  timer 0/1 time-base counter increment. When cleared timer 0 time-base counter decrement.*/
			uint32_t enable: 1;             /*When set  timer 0/1 time-base counter is enabled*/
		};
		uint32_t val;
	} config;
	uint32_t cnt_low;                             /*Register to store timer 0/1 time-base counter current value lower 32 bits.*/
	uint32_t cnt_high;                            /*Register to store timer 0 time-base counter current value higher 32 bits.*/
	uint32_t update;                              /*Write any value will trigger a timer 0 time-base counter value update (timer 0 current value will be stored in registers above)*/
	uint32_t alarm_low;                           /*Timer 0 time-base counter value lower 32 bits that will trigger the alarm*/
	uint32_t alarm_high;                          /*Timer 0 time-base counter value higher 32 bits that will trigger the alarm*/
	uint32_t load_low;                            /*Lower 32 bits of the value that will load into timer 0 time-base counter*/
	uint32_t load_high;                           /*higher 32 bits of the value that will load into timer 0 time-base counter*/
	uint32_t reload;                              /*Write any value will trigger timer 0 time-base counter reload*/
};

struct hw_timer_s {
	hw_timer_reg_t* dev;
	uint8_t num;
	uint8_t group;
	uint8_t timer;
	portMUX_TYPE lock;
};

void IRAM_ATTR CM::timerStop(hw_timer_t* timer){
	timer->dev->config.enable = 0;
}

void IRAM_ATTR CM::timerWrite(hw_timer_t* timer, uint64_t val){
	timer->dev->load_high = (uint32_t)(val >> 32);
	timer->dev->load_low = (uint32_t)(val);
	timer->dev->reload = 1;
}

void IRAM_ATTR CM::timerAlarmWrite(hw_timer_t* timer, uint64_t alarm_value, bool autoreload){
	timer->dev->alarm_high = (uint32_t)(alarm_value >> 32);
	timer->dev->alarm_low = (uint32_t)alarm_value;
	timer->dev->config.autoreload = autoreload;
}

void IRAM_ATTR CM::timerAlarmDisable(hw_timer_t* timer){
	timer->dev->config.alarm_en = 0;
}

uint64_t IRAM_ATTR CM::timerRead(hw_timer_t* timer){
	timer->dev->update = 1;
	while(timer->dev->update) delayMicroseconds(1);
	uint64_t h = timer->dev->cnt_high;
	uint64_t l = timer->dev->cnt_low;
	return (h << 32) | l;
}
