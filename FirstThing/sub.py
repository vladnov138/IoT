import serial
import time, random
import paho.mqtt.client as paho

responses = {"g_ard_d": 12,
             "g_ard_u": 10}

corresponds = {"g_ard_d": "d",
               "g_ard_u": "u"}

port = "COM6"
broker = "broker.emqx.io"
connection = serial.Serial(timeout=5000, port=port)
topic_name = 'house/bulb1'


def on_message(client, userdata, message):
    message_decoded = message.payload.decode('utf-8')
    if message_decoded in responses.keys():
        m_len = responses[message_decoded]
        cmd = corresponds[message_decoded]
        print(f'Send command to arduino: {cmd} and got result: {send_cmd(cmd, m_len)}')


def send_cmd(cmd: str, response_len) -> str:
    connection.write(cmd.encode())
    if response_len != 0:
        return connection.read(response_len).decode()
    return ""


def main():
    client_name = "client-isu-1337"
    client = paho.Client(client_name)
    client.on_message = on_message
    print(f"Connection to broker: {broker}")
    client.connect(broker)
    client.loop_start()
    print("Subscribing")
    print(f"Listening to topic: {topic_name}")
    print(f"Using port: {port}")
    client.subscribe(topic_name)
    time.sleep(2000)


if __name__ == '__main__':
    main()