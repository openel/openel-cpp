ROOT := $(dir $(lastword $(MAKEFILE_LIST)))../..

LIB_DIR = ../../lib

COMPONENT = simLinux

CPP_LIB_SOURCES = \
	$(LIB_DIR)/surface/Actuator.cpp \
	$(LIB_DIR)/surface/EventTimer.cpp \
	$(LIB_DIR)/surface/HALComponent.cpp \
	$(LIB_DIR)/surface/HALId.cpp \
	$(LIB_DIR)/surface/HALObserver.cpp \
	$(LIB_DIR)/surface/openEL_linkedList.cpp \
	$(LIB_DIR)/surface/openEL_registryConfig.cpp \
	$(LIB_DIR)/surface/openEL.cpp \
	$(LIB_DIR)/surface/Property.cpp \
	$(LIB_DIR)/surface/Sensor.cpp \
	$(LIB_DIR)/surface/TimerObserver.cpp \
	$(LIB_DIR)/device/$(COMPONENT)/openEL_ActuatorSim.cpp \
	$(LIB_DIR)/device/$(COMPONENT)/openEL_SensorSim.cpp

C_OPTIMISATION_FLAGS = -Os

INC_PATH := \
	-I../../include \
	-I../../include/device \
	-I../../include/device/$(COMPONENT) \
	-I../../include/surface

O_FILES = $(CPP_LIB_SOURCES:cpp=o)

LIB_TARGET = libopenel.a

TARGET = sample

TARGET_SOURCES = projSimLinux.cpp

LDFLAGS += -lopenel -lrt -lm -lpthread -lstdc++

CC = gcc

.PHONY: release
release: CFLAGS+=
release: all
release:
	rm $(O_FILES)

.PHONY: debug
debug: CFLAGS+=-DDEBUG_BUILD
debug: all
debug:
	rm $(O_FILES)

.PHONY : all
all : openel sample

.PHONY : sample
sample : $(TARGET)
	@echo "Linking $@"
	$(CC) $(CFLAGS) $(INC_PATH) -L. -o $@ $(TARGET_SOURCES) $(LDFLAGS)

.PHONY : openel
openel : $(LIB_TARGET)
  $(LIB_TARGET): $(O_FILES)
	@echo "Creating $@"
	$(AR) rv $(LIB_TARGET) $(O_FILES)

%.o: %.cpp
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) $(INC_PATH) -c -o $@ $<

.PHONY: clean
clean:
	rm $(LIB_TARGET)
	rm $(TARGET)
