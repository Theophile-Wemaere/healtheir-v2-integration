#!/usr/bin/python3

import serial
import uploader

ser = None
baudrate = 115200
try:
    ser = serial.Serial('/dev/ttyUSB0', baudrate)
except serial.serialutil.SerialException:
    ser = serial.Serial('/dev/ttyUSB1', baudrate)

def calculatechecksum(frame, checksum):
    new_checksum = 0
    for value in frame:
        new_checksum ^= int(value,16)
    if new_checksum == int(checksum,16):
        return True
    else:
        print("Bad checksum : " ,frame)
        return False

def process_data(data,ser):
    print(data)
    if data.startswith("FE"):
        command = data[2:4]
        sensor = data[4]
        payload_size = data[5:6]
        size=  int(payload_size,16)
        payload = data[6:6+size]
        checksum = data[6+size:]
        frame = [
            "FE",
            command,
            sensor,
            payload_size,
        ]
        for i in payload:
            frame.append(i)
        if calculatechecksum(frame,checksum):
            payload = int(payload,16)
            if int(sensor) in [2,4,5,6,7] : # temp, dust, humidity
                 payload /= 100
            ser.write("read_ok\n".encode())
            print("Value : " , payload)
            uploader.upload_data(sensor,payload)
        else:
            ser.write("read_bad\n".encode())


def main():
    if ser.is_open:
        # Clear input buffer
        ser.flushInput()

        # Clear output buffer
        ser.flushOutput()
        while True:
            if ser.in_waiting > 0:
                data = ser.readline().decode().rstrip()
                #print(data)
                process_data(data,ser)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        exit(1)
