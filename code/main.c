#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "paho_mqtt.h"
#include "MQTTClient.h"

#include "srf04.h"
#include "srf04_params.h"
#include "xtimer.h"
#include "ztimer.h"
#include "periph/gpio.h"
#include "periph/i2c.h"


//MQTT settings
#define BUF_SIZE 1024

#define MQTT_VERSION_v311               4       /* MQTT v3.1.1 version is 4 */
#define COMMAND_TIMEOUT_MS              5000

#define BROKER_ADDRESS "172.16.47.128"
#define DEFAULT_MQTT_PORT               1883
#define DEFAULT_KEEPALIVE_SEC           15
#define TOPIC "desklight"

#define IS_CLEAN_SESSION                1
#define IS_RETAINED_MSG                 0

#define D_THRESHOLD 150


static MQTTClient client;
static Network network;
static unsigned char buf[BUF_SIZE];
static unsigned char readbuf[BUF_SIZE];

// ultrasonic 1
gpio_t trigger_pin = GPIO_PIN(0,1);
gpio_t echo_pin = GPIO_PIN(0,2);

// rgb led pins
gpio_t led_pin = GPIO_PIN(0,3);



uint32_t echo_time;
uint32_t echo_time_start;

int mqtt_init(void){

    xtimer_sleep(5);

    NetworkInit(&network);
    MQTTClientInit(&client, &network, COMMAND_TIMEOUT_MS, buf, BUF_SIZE, readbuf, BUF_SIZE);
    MQTTStartTask(&client);

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = MQTT_VERSION_v311;
    data.clientID.cstring = "";
    data.username.cstring = "";
    data.password.cstring = "";
    data.keepAliveInterval = 60;
    data.cleansession = 1;

    printf("MQTT: Connecting to MQTT Broker from %s %d\n",
            BROKER_ADDRESS, DEFAULT_MQTT_PORT);
    printf("MQTT: Trying to connect to %s, port: %d\n",
            BROKER_ADDRESS, DEFAULT_MQTT_PORT);
    
    int res = NetworkConnect(&network, BROKER_ADDRESS, DEFAULT_MQTT_PORT);

    if(res){
        printf("MQTT unable to connect: Error %d\n", res);
        return res;
    }
    printf("user:%s clientId:%s password:%s\n", data.username.cstring,
             data.clientID.cstring, data.password.cstring);
    res = MQTTConnect(&client, &data);

    if (res < 0) {
        printf("MQTT: Unable to connect client %d\n", res);
        int res = MQTTDisconnect(&client);
        if (res < 0) {
            printf("MQTT: Unable to disconnect\n");
        }
        else {
            printf("MQTT: Disconnect successful\n");
        }
        NetworkDisconnect(&network);
        return res;
    }
    else{
        printf("MQTT: Connection success!\n");
    }

    printf("MQTT client succesfully connected to the broker\n");
    return 0;
}

int publish(char* msg){
    //MQTT publish
    MQTTMessage message;
    message.qos = QOS1;
    message.retained = IS_RETAINED_MSG;
    message.payload = msg;
    message.payloadlen = strlen(message.payload);

    int rp = MQTTPublish(&client, TOPIC, &message);
    if (rp){
        printf("MQTT error %d: unable to publish!\n", rp);
        return 1;
    }else{
        printf("MQTT message published succesfully to topic %s\n", TOPIC);
    }
    return 0;
}


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

    int conn_res = mqtt_init();
    if (conn_res){
        printf("MQTT initialization error!\n");
        printf("\n##### Offline only mode #####\n");
    } else 
        printf("MQTT initialization success \n\n#### Online mode enabled ####\n");
    
    int i = 0;
    char *status = "OFF";

   
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
            status = "ON";
            char json [200];
            sprintf(json, "{\"id\": \"%d\", \"lastDistance\": \"%d\", \"status\": \"%s\"}",i, distance, status);
             char* msg = json;
            
            if(publish(msg)){
                printf("Error publishing on topic: %s", TOPIC);
            }
        } else if(timer == 0){
            status = "OFF"
            gpio_clear(led_pin);
             char json[200];

                sprintf(json, "{\"id\": \"%d\", \"lastDistance\": \"%d\", \"status\": \"%s\"}",
                                    i, distance, status);

                char* msg = json;

                if(publish(msg)){
                    printf("Error publishing on topic: %s", TOPIC);
                }
        }
        printf("Timer : %d sec \n", timer);
        xtimer_sleep(1);

    }
    return 0;
}