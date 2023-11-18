import time

import paho.mqtt.client as paho

broker = 'broker.emqx.io'


def on_message(client, userdata, message):
    time.sleep(1)
    data = str(message.payload.decode("utf-8"))
    print("Received message = ", data)


client = paho.Client("client-isu-82")
client.on_message = on_message

print("Connecting to broker ", broker)
client.connect(broker)
client.loop_start()

print("Subscribing")
client.subscribe("house/bulb1")
time.sleep(1880)
client.disconnect()
client.loop_stop()