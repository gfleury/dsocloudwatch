CC=g++
CFLAGS=-c -g -std=gnu++11 -Wall -Ithird-party/aws-sdk-cpp/aws-cpp-sdk-monitoring/include/ -I./third-party/aws-sdk-cpp/aws-cpp-sdk-core/include/
ifdef DYNAMIC
LDFLAGS=-Lthird-party/aws-sdk-cpp/aws-cpp-sdk-monitoring/ -laws-cpp-sdk-monitoring -Lthird-party/aws-sdk-cpp/aws-cpp-sdk-core -laws-cpp-sdk-core
OBJECTS=$(SOURCES:.cpp=.o)
else
LDFLAGS=-lssl -lcurl -lcrypto -lstdc++
OBJECTS=$(SOURCES:.cpp=.o) third-party/aws-sdk-cpp/aws-cpp-sdk-monitoring/libaws-cpp-sdk-monitoring.a third-party/aws-sdk-cpp/aws-cpp-sdk-core/libaws-cpp-sdk-core.a
endif
SOURCES=put_metric.cpp
EXECUTABLE=put_metric

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


