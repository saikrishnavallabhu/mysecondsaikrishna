SOURCES = src/main.c src/memory.c

ifeq ($(PLATFORM),MSP432)
    SOURCES += src/interrupts_msp432p401r_gcc.c \
               src/startup_msp432p401r_gcc.c \
               src/system_msp432p401r.c
endif
