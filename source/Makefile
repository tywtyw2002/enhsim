# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all clean

CC = g++                        # compiler to use

LINKERFLAG = -pthread 

SRC_DIRS := .
SRCS := $(shell find $(SRC_DIRS) -name \*.cpp )
OBJS := $(SRCS:%.cpp=%.o)
DEPS := $(OBJS:.o=.d)
TARGET_EXEC := enhsim

all: ${TARGET_EXEC}

$(TARGET_EXEC): $(OBJS)
		@echo "Checking.."
		${CC} -O2 ${LINKERFLAG} $^  -framework CoreServices ../zthread/src/.libs/libZThread.a -o $@

%.o: %.cpp
		@echo "Creating object.."
		${CC} -I/usr/local/include -I../zthread/include -O2 -c $< -o $@

%.o: %.c
		@echo "Creating object.."
		gcc -I/usr/local/include -I../zthread/include -O2 -c $< -o $@

clean:
		@echo "Cleaning up..."
		rm -rvf *.o ${BINS}
