import time

import paho.mqtt.client as paho

broker = 'broker.emqx.io'

client = paho.Client("client-isu-81")

print("Connecting to broker ", broker)
client.connect(broker)
client.loop_start()
print("Publishing")

# cmd = input()
start_time = 40
cur_time_limit = start_time
min_time = 20
while True:
    client.publish("house/bulb1", "1")
    print(1)
    time.sleep(cur_time_limit)
    client.publish("house/bulb1", "0")
    print(0)
    time.sleep(60 - cur_time_limit)
    if cur_time_limit > 20:
        cur_time_limit -= 1
    else:
        cur_time_limit = start_time

client.disconnect()
client.loop_stop()