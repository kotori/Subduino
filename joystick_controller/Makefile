BOARD_TAG    	= atmega644
ALTERNATE_CORE  = Sanguino
ARDUINO_LIBS =
ARDUINO_PORT = /dev/ttyS0
MONITOR_PORT  = /dev/ttyS0
MONITOR_BAUDRATE = 9600
ISP_PROG = usbtiny

include $(ARDMK_DIR)/Arduino.mk

upload:
	avrdude -F -V -D -c $(ISP_PROG) -p $(MCU) -U flash:w:$(TARGET_HEX):i
