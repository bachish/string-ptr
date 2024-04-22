TARGET=Tests
PTR=StringPtr
BUILDS=build
CXX=g++
CXXFLAGS=-O0 -g 

all: $(TARGET)

#compile library objerct file
$(TARGET): $(PTR).hpp $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -c $(TARGET).cpp -o $(BUILDS)/$(TARGET).o -D DEBUG
	$(CXX) $(CXXFLAGS) $(BUILDS)/$(TARGET).o  -o $(BUILDS)/$(TARGET) 
	./$(BUILDS)/$(TARGET)  