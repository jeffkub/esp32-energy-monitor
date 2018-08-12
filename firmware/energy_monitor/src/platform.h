#ifndef _PROJECT_H_
#define _PROJECT_H_

#include <driver/gpio.h>

#define LED1_PIN        GPIO_NUM_18
#define LED2_PIN        GPIO_NUM_19
#define LED3_PIN        GPIO_NUM_21

#define CS_PIN          GPIO_NUM_15
#define SCK_PIN         GPIO_NUM_14
#define MOSI_PIN        GPIO_NUM_13
#define MISO_PIN        GPIO_NUM_12

#define ADC_RESET_PIN   GPIO_NUM_25
#define ADC_PWDN_PIN    GPIO_NUM_33
#define ADC_START_PIN   GPIO_NUM_26
#define ADC_DRDY_PIN    GPIO_NUM_27

#define DEBUG1_PIN      GPIO_NUM_22
#define DEBUG2_PIN      GPIO_NUM_23

/* Debug macros */
#define SET_DEBUG1()    GPIO.out_w1ts = (1 << DEBUG1_PIN)
#define CLR_DEBUG1()    GPIO.out_w1tc = (1 << DEBUG1_PIN)

#define SET_DEBUG2()    GPIO.out_w1ts = (1 << DEBUG2_PIN)
#define CLR_DEBUG2()    GPIO.out_w1tc = (1 << DEBUG2_PIN)

#endif /* #ifndef _PROJECT_H_ */
