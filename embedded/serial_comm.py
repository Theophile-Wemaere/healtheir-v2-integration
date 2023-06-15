#!/usr/bin/python3

import serial

ser = serial.Serial('/dev/ttyUSB0', 9600)

def calculatechecksum(frame, checksum):
    new_checksum = 0
    for value in frame:
        new_checksum ^= int(value,16)
    if new_checksum == checksum:
        return True
    else:
        print("Bad checksum : " + frame)
        return False

def process_data(data):
    if data.startswith("FE"):
        print(data)
        command = data[2:4]
        sensors = data[4]
        payload_size = data[5:6]
        size=  int(payload_size,16)
        payload = data[6:6+size]
        checksum = data[6+size:]
        frame = [
            "FE",
            command,
            sensors,
            payload_size,
        ]
        for i in payload:
            frame.append(i)
        if calculatechecksum(frame,checksum):


    

def main():

    if ser.is_open:
        while True:
            if ser.in_waiting > 0:
                
                data = ser.readline().decode().rstrip()
                process_data(data)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        exit(1)