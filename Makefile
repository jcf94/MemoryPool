# ***********************************************
# MYID : Chen Fan
# LANG : Makefile
# PROG : 
# ***********************************************

CC = g++
CFLAGS +=

LD = g++
LDFLAGS +=

NAME = $(wildcard *.cpp)
NAME-OBJS = $(patsubst %.cpp, %.o, $(NAME))
TARGET = $(patsubst %.cpp, %, $(NAME))

SRCS = $(wildcard src/*.cpp)
SRCS-OBJS = $(patsubst %.cpp, %.o, $(SRCS))

CLEAN-O = rm -f $(SRCS-OBJS) $(NAME-OBJS)

release: CFLAGS += -O3
release: LDFLAGS += -O3
release: all

debug: CFLAGS += -g3
debug: LDFLAGS += -g3
debug: all

all: $(TARGET)
	$(CLEAN-O)
	@echo "=------------------------------="
	@echo "|     Target Make Success      |"
	@echo "=------------------------------="

$(TARGET): $(SRCS-OBJS) $(NAME)
	$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)
	$(CLEAN-O)
	@echo "=-----------------------------="
	@echo "|     Target Clean Success    |"
	@echo "=-----------------------------="

show:
	@echo NAME: $(NAME)
	@echo NAME-OBJS: $(NAME-OBJS)
	@echo TARGET: $(TARGET)
	@echo SRCS: $(SRCS)
	@echo SRCS-OBJS: $(SRCS-OBJS)
