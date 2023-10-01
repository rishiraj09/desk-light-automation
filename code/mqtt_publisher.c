#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>

#define ADDRESS     "172.16.47.128:1883" // Replace with your broker's IP address
#define CLIENTID    "Publisher"
#define TOPIC       "test"
#define PAYLOAD     "Hello, MQTT!"
#define QOS         1
#define TIMEOUT     10000L

int main(int argc, char* argv[]) {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTMessage message = MQTTMessage_initializer;

    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    message.payload = PAYLOAD;
    message.payloadlen = strlen(PAYLOAD);
    message.qos = QOS;
    message.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &message, NULL);

    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    
    return EXIT_SUCCESS;
}
