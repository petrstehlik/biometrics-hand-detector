import RPi.GPIO as GPIO
import pigpio
import time

GPIO_ENABLE_PIN = 6
GPIO_DIRECTION_PIN = 5

ON = GPIO.LOW
OFF = GPIO.HIGH

LEFT = GPIO.LOW
RIGHT = GPIO.HIGH

MOVEMENT_TIME = 10.0
BREAK_TIME = 1.0

# initialize GPIO
GPIO.cleanup()
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(GPIO_PWM, GPIO.OUT)
GPIO.setup(GPIO_DIRECTION_PIN, GPIO.OUT)
GPIO.setup(GPIO_ENABLE_PIN, GPIO.OUT)

try:
    GPIO.output(GPIO_DIRECTION_PIN, RIGHT)
    GPIO.output(GPIO_ENABLE_PIN, ON)

    time.sleep(MOVEMENT_TIME)

    GPIO.output(GPIO_ENABLE_PIN, OFF)

    time.sleep(BREAK_TIME)

    GPIO.output(GPIO_DIRECTION_PIN, LEFT)
    GPIO.output(GPIO_ENABLE_PIN, ON)

    time.sleep(MOVEMENT_TIME)

    GPIO.output(GPIO_ENABLE_PIN, OFF)
except (KeyboardInterrupt, SystemExit):
    GPIO.output(GPIO_ENABLE_PIN, OFF)
