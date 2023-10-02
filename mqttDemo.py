from paho.mqtt import client as mqtt

clientId = 'broker'
port = 1883
broker = "localhost"

client = mqtt.Client(clientId)
client.connect(broker, port)
client.publish("desklight", "{\"status\":\"OFF\"}")

client.loop_forever()