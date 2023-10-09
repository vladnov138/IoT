import time

import paho.mqtt.client as paho

broker = 'broker.emqx.io'
OFF_CMD = "Pub down"

client = paho.Client("client-isu-81")

print("Connecting to broker ", broker)
client.connect(broker)
client.loop_start()
print("Publishing")

cmd = input()
while cmd:
    print("Command: ", cmd)
    print(len(cmd))
    client.publish("house/bulb1", cmd)
    time.sleep(1)
    cmd = input()

# client.publish("house/bulb1", OFF_CMD)
time.sleep(1)
client.disconnect()
client.loop_stop()
