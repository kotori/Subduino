BOARD_TAG    = atmega328
ARDUINO_LIBS =
ARDUINO_PORT = /dev/ttyACM*
ISP_PROG = usbtiny

include ../Arduino.mk

upload:
	avrdude -F -V -D -c $(ISP_PROG) -p $(MCU) -U flash:w:$(TARGET_HEX):i
