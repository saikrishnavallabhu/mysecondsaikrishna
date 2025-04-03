# Define PLATFORM from command line
PLATFORM ?= HOST

# Compiler selection
ifeq ($(PLATFORM),HOST)
    CC = gcc
    TARGET = c1m2.out
    SOURCES = main.c memory.c
    INCLUDES = -I./include/common
    CFLAGS = -Wall -Werror -g -O0 -std=c99 -DHOST
    LDFLAGS =
else ifeq ($(PLATFORM),MSP432)
    CC = arm-none-eabi-gcc
    TARGET = c1m2.out
    SOURCES = main.c memory.c interrupts_msp432p401r_gcc.c startup_msp432p401r_gcc.c system_msp432p401r.c
    INCLUDES = -I./include/common -I./include/msp432 -I./include/CMSIS
    CFLAGS = -Wall -Werror -g -O0 -std=c99 -DMSP432 \
             -mcpu=cortex-m4 -mthumb -march=armv7e-m \
             -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs
    LDFLAGS = -T msp432p401r.lds
endif

# Generate object files from sources
OBJECTS = $(SOURCES:.c=.o)

# Targets
.PHONY: all compile-all build clean

all: build

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

compile-all: $(OBJECTS)

build: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET)
	size $(TARGET)

clean:
	rm -f *.o *.i *.asm *.map $(TARGET)
