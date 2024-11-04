import serial

s = serial.Serial('/dev/tty.usbmodem3C8427CB55C81', 9600)

while True:
  if s.in_waiting > 0:
    line = s.readline().decode('utf-8').rstrip()
    print(f"Received message: {line}")
