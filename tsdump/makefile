CC = g++
CCFLAGS = -Wall -I ~/LinuxSDK/DTAPI/Include
LIBS = -lstdc++ -lpthread

DEPS = Application.h common.h conversion.h DektecReader.h errorcodes.h Event.h \
EventInformationSection.h EventStreamParser.h Exception.h FileReader.h \
IOBase.h Reader.h Service.h StreamParser.h TimeDateSection.h TransportPacket.h

OBJ = Application.o conversion.o DektecReader.o Event.o EventInformationSection.o \
EventStreamParser.o FileReader.o main.o Service.o StreamParser.o TimeDateSection.o \
TransportPacket.o ~/LinuxSDK/DTAPI/Lib/GCC4.3.2/DTAPI64.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

tsdump: $(OBJ)
	gcc -o $@ $^ $(CCFLAGS) $(LIBS)

install: tsdump
	cp tsdump ~/bin

clean:
	rm -rf *.o tsdump
