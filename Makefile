# Makefile for ATmega328

# Target file name (without extension)
TARGET = main

# MCU name
MCU = atmega328p

# Programmer type
PROGRAMMER = usbasp

# Clock frequency
F_CPU = 16000000

# AVRDUDE options
AVRDUDE = avrdude
AVRDUDE_FLAGS = -p $(MCU) -c $(PROGRAMMER)

# Compiler options
CFLAGS = -Wall -Os -DF_CPU=$(F_CPU)UL -mmcu=$(MCU) -D_FORTIFY_SOURCE=1 \
       -DBAUDRATE=$(BAUDRATE) \
       -DWORD_LENGHT=$(WORD_LENGHT) \
       -DBIT_STOP=$(BIT_STOP) \
       -DBIT_PARITY=$(BIT_PARITY) \
       -Ilib/adc \
       -Ilib/gpio \
       -Ilib/modbus \
       -Ilib/timer \
       -Ilib/uart

LDFLAGS = -mmcu=$(MCU)

# List of source files
SRCS = main.c \
       lib/adc/adc.c \
       lib/gpio/gpio.c \
       lib/modbus/modbus.c \
       lib/timer/timer0.c \
       lib/timer/timer1.c \
       lib/timer/timer2.c \
       lib/uart/uart.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET).hex

# Compile: create object files from C source files
%.o: %.c
	avr-gcc $(CFLAGS) -c $< -o $@

# Link: create ELF output file from object files
$(TARGET).elf: $(OBJS)
	avr-gcc $(LDFLAGS) $(OBJS) -o $@

# Create HEX file from ELF output file
%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom $< $@

# Program the device
flash: $(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -U flash:w:$<

# Clean target
clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).hex
