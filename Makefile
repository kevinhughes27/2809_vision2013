CC = g++
CFLAGS = -g -Wall
SRCS = main.cpp
PROG = vision.exe

OPENCV = -I"C:\opencv\build\include" -L"C:\opencv\build\x86\mingw\lib" -lopencv_core243 -lopencv_highgui243

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(OPENCV)