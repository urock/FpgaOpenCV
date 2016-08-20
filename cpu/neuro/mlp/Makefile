TARGET = neuro
PREFIX = /usr/local/bin
SRCS = main.cpp neuro.cpp descriptor.cpp teacher.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.hpp)
LIBS = -lopencv_highgui -lopencv_imgproc -lopencv_core -lopencv_imgcodecs -lopencv_videoio
CC = g++
CPPFLAGS = -std=c++11

.PHONY: all clean install uninstall

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
install:
	install $(TARGET) $(PREFIX)
uninstall:
	rm -rf $(PREFIX)/$(TARGET)
