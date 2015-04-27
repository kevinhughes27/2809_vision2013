CC = g++
CFLAGS = -g -Wall

TRAIN_SRCS = trainSVM.cpp
TRAIN_PROG = train.exe

RUN_SRCS = main.cpp segmentTargets.cpp
RUN_PROG = vision.exe

OPENCV = -I"C:\opencv\build\include" -L"C:\opencv\build\x86\mingw\lib" -lopencv_core243 -lopencv_imgproc243 -lopencv_ml243 -lopencv_highgui243

all: $(RUN_PROG) $(TRAIN_PROG)

$(TRAIN_PROG) : $(TRAIN_SRCS)
	$(CC) $(CFLAGS) -o $(TRAIN_PROG) $(TRAIN_SRCS) $(OPENCV)

$(RUN_PROG) : $(RUN_SRCS)
	$(CC) $(CFLAGS) -o $(RUN_PROG) $(RUN_SRCS) $(OPENCV)
