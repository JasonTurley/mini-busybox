EXE = mini_busybox
OBJS = mini_busybox.o

CXX = g++
CXX_FLAGS = -pedantic -Wall -Wextra -Werror -Wfatal-errors -Wno-unused-parameter -Wno-unused-variable
CXX_FLAGS_DEBUG = $(CXX_FLAGS) -g -O0

LD = g++
LDFLAGS = -std=c++11

.PHONY: all
.PHONY: clean

all: $(EXE)

$(EXE): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(EXE)
