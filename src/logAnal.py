import RPi.GPIO as GPIO
import time

CLK = 25

GPIO.setmode(GPIO.BCM)

GPIO.setup(CLK, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

counter = 0

def button_callback(channel):
    global counter
    counter += 1
    print(f"Button was pressed! times: {counter}")

GPIO.add_event_detect( CLK, GPIO.RISING, callback=button_callback )

try:
    print("Waiting for button press...")
    while True:
        time.sleep(1)

except KeyboardInterrupt:
    GPIO.cleanup()

