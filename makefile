##
# @file
#
# Linux makefile for the Brackets coding puzzle
#
# @author Emil Maskovsky
#


###############
#    Setup    #
###############

# the main executable target
TARGET = brackets

# the object files
OBJS = \
	$(TARGET).o

# optimization and debugging settings
OPTFLAGS = -g -o2

# the compiler flags
CPPFLAGS = $(OPTFLAGS) -Wall -Wextra -Werror

# the linker flags
LDFLAGS = $(OPTFLAGS)

# the source file paths
VPATH = src


#####################
#    Build rules    #
#####################

.PHONY: all test clean cleanall

all: $(TARGET)

test: all
	./$(TARGET)

clean:
	-rm -f $(OBJS)

cleanall: clean
	-rm -f $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LNKFLAGS) -o $@ $^

.cpp.o:
	$(CXX) -c $(CPPFLAGS) -o $@ $<


######################
#    Dependencies    #
######################


# EOF
