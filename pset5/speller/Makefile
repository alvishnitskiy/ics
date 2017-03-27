# compiler to use
CXX = clang++

# flags to pass compiler
CXXFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c++11 -Wall -Werror

# name for executable
EXE = speller

# space-separated list of header files
HDRS = speller.h stopwatch.h wordsaudit.h dictionary.h trie.h table.h list.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# space-separated list of source files
SRCS = speller.cpp stopwatch.cpp wordsaudit.cpp trie.cpp table.cpp list.cpp

# automatically generated list of object files
OBJS = $(SRCS:.cpp=.o)


# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o
