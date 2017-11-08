import RPi.GPIO as GPIO
import pigpio
import time

ENABLE = 6
DIR = 5

ON = GPIO.LOW
OFF = GPIO.HIGH

LEFT = GPIO.LOW
RIGHT = GPIO.HIGH

# initialize GPIO
GPIO.cleanup()
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT) # PWM
GPIO.setup(DIR, GPIO.OUT)
GPIO.setup(ENABLE, GPIO.OUT)

try:
    GPIO.output(DIR, RIGHT)
    GPIO.output(ENABLE, ON)

    time.sleep(10.0)

    #GPIO.output(5, GPIO.HIGH)
    GPIO.output(ENABLE, OFF)

    time.sleep(1.0)

    GPIO.output(DIR, LEFT)
    GPIO.output(ENABLE, ON)

    time.sleep(10.0)

    GPIO.output(ENABLE, OFF)
except (KeyboardInterrupt, SystemExit):
    GPIO.output(6, GPIO.HIGH)
