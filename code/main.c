#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "srf04.h"
#include "srf04_params.h"
#include "xtimer.h"
#include "periph/gpio.h"
#include "periph/i2c.h"


#define D_THRESHOLD 150

// ultrasonic 1
gpio_t trigger_pin = GPIO_PIN(0,1);
gpio_t echo_pin = GPIO_PIN(0,2);

// rgb led pins
gpio_t led_pin = GPIO_PIN(0,3);



uint32_t echo_time;
uint32_t echo_time_start;

void echo_cb(void *arg){
    int val = gpio_read(echo_pin);
    uint32_t echo_time_stop;

    (void) arg;
    if(val){
        echo_time_start = xtimer_now_usec();
    }else{
        echo_time_stop = xtimer_now_usec();
        echo_time = echo_time_stop - echo_time_start;
    }
}

int read_distance(gpio_t triggerPin){
    echo_time = 0;
    gpio_clear(triggerPin);
    xtimer_usleep(20);
    gpio_set(triggerPin);
    xtimer_msleep(100);
    return echo_time / 58;
}




int main(void){
    
    // initialize rgb led pins
    gpio_init(led_pin, GPIO_OUT);

    // sensor pin initialization
    gpio_init(trigger_pin, GPIO_OUT);
    gpio_init_int(echo_pin, GPIO_IN, GPIO_BOTH, &echo_cb, NULL);

    read_distance(trigger_pin);
    int distance = 0;
    distance = read_distance(trigger_pin);
    int timer = 0;
   
    while(1){
        distance = read_distance(trigger_pin);
        printf("Distance : %d cm\n", distance);

        if(distance < 150){
            printf("User in range.. \n");
            timer += 1;
        }else{
            printf("User not in range..\n");
            timer = 0;
        }

        if(timer > 1){
            printf("User on the station..\n");
            gpio_set(led_pin);
        } else if(timer == 0){
            gpio_clear(led_pin);
        }
        printf("Timer : %d sec \n", timer);
        xtimer_sleep(1);

    }
    return 0;
}