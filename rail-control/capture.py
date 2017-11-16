import tel_commander as light
import serial as serial
import time
import logging

logging.basicConfig(level = logging.DEBUG)
log = logging.getLogger("CAPTURE")

log.info("Setting up serial")
arduino = serial.Serial('/dev/ttyUSB0', 115200)

if __name__ == "__main__":
    # Send rail for 10s left
    log.info("Sending rail left for 10 s")
    ser.write("L10000")

    # Set light intensity to 1200 mA
    log.info("Set light intensity to 1200 mA")
    light.cmd("IY E 1200")

    # Turn light on
    log.info("Turning light on")
    light.cmd("LC A 1")

    # Here should be runing of the grabbing binary
    log.debug("Should grab image")
    log.info("Waiting for movement finish")
    time.sleep(10.0)

    log.info("Turning off light")
    light.cmd("LC A 0")

    log.info("Sending rail back right for 10 s")
    ser.write("R10000")
