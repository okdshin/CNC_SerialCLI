CXX = g++ -std=gnu++11
CXXFLAGS = -Wall -g -D SERIAL_UNIT_TEST
INCLUDES = 
LIBS = -lboost_system
OBJS = serial.o
PROGRAM = serial.out

all:$(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDES) $(LIBS) -o $(PROGRAM)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -c $<

.PHONY: clean
clean:
	rm -f *o $(PROGRAM)
