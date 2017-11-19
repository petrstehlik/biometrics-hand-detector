import RPi.GPIO as GPIO
import pigpio
import time
import sys

# Declarations
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
GPIO.setup(GPIO_DIRECTION_PIN, GPIO.OUT)
GPIO.setup(GPIO_ENABLE_PIN, GPIO.OUT)

def move(direction, delay):

    if direction != LEFT and direction != RIGHT:
        raise ValueError('Direction must be LEFT or RIGHT')

    if float(delay) < 0.0:
        raise ValueError('Delay must be positive float number')

    try:
        GPIO.output(GPIO_DIRECTION_PIN, direction)
        GPIO.output(GPIO_ENABLE_PIN, ON)

        time.sleep(delay)

        GPIO.output(GPIO_ENABLE_PIN, OFF)

    except (KeyboardInterrupt, SystemExit):
        # Stop if anything bad happens
        GPIO.output(GPIO_ENABLE_PIN, OFF)

if __name__ == "__main__":
    if len(sys.argv) == 2:
        # We have args
        direction = None

        if sys.argv[1] == 'LEFT':
            direction = LEFT
        elif sys.argv[1] == 'RIGHT':
            direction = RIGHT
        else:
            raise ValueError('Unknown value')

        move(direction, 10.0)

    else:
        move(RIGHT, MOVEMENT_TIME)
        time.sleep(BREAK_TIME)
        move(LEFT, MOVEMENT_TIME)
