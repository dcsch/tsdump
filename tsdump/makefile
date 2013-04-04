CC = g++
CCFLAGS = -Wall -I ~/LinuxSDK/DTAPI/Include
LIBS = -lstdc++ -lpthread

DEPS = Application.h common.h conversion.h DektecReader.h errorcodes.h Event.h \
EventInformationSection.h EventStreamParser.h Exception.h FileReader.h \
IOBase.h Reader.h Service.h stdafx.h StreamParser.h TransportPacket.h

OBJ = Application.o conversion.o DektecReader.o drift.o Event.o EventInformationSection.o \
EventStreamParser.o FileReader.o Service.o StreamParser.o \
TransportPacket.o ~/LinuxSDK/DTAPI/Lib/GCC4.3.2/DTAPI64.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

drift: $(OBJ)
	gcc -o $@ $^ $(CCFLAGS) $(LIBS)

install: drift
	cp drift ~/bin

clean:
	rm -rf *.o drift
