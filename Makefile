BOARD_TAG = uno
MONITOR_PORT = $(ls /dev/ttyACM* | head -1)
ARDUINO_DIR = /usr/share/arduino
include $(ARDUINO_DIR)/Arduino.mk
