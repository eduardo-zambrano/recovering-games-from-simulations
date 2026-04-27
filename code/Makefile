CXX ?= c++
CXXFLAGS ?= -O2 -std=c++14 -Wno-write-strings -Wno-format -Wno-comment -Wno-unused-result

elfarol: main.cpp define.h extern.h global.h agents.h forecast.h history.h
	$(CXX) $(CXXFLAGS) -o $@ main.cpp

clean:
	rm -f elfarol

.PHONY: clean
