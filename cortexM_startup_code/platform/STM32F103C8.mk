C_SOURCES += 
CPP_SOURCES += platform/$(MCU).cpp
S_SOURCES += 
DEFINES += 
COMPILE_CXX_FLAGS += -mcpu=cortex-m3 -mthumb
COMPILE_CPP_FLAGS += -mcpu=cortex-m3 -mthumb
COMPILE_ASM_FLAGS +=
LINK_FLAGS += -mcpu=cortex-m3 -mthumb