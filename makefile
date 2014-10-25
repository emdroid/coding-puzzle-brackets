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

TEST_TARGET = $(TARGET)_test

# the object files
OBJS =

# the main executable object files
OBJS_TARGET = \
	$(TARGET).o

# the test executable object files
OBJS_TEST = $(OBJS) \
	$(TEST_TARGET).o

# optimization and debugging settings
OPTFLAGS = -g -O0 -fno-inline
#OPTFLAGS = -O2 -DNDEBUG

# the compiler flags
CPPFLAGS = $(OPTFLAGS) -Wall -Wextra -Werror

# the linker flags
LDFLAGS = $(OPTFLAGS)

# the source file paths
VPATH = src:test


#####################
#    Build rules    #
#####################

.PHONY: all test clean cleanall

all: $(TARGET)

test: all $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	-rm -f $(OBJS) $(OBJS_TARGET) $(OBJS_TEST) $(TEST_TARGET)

cleanall: clean
	-rm -f $(TARGET)

$(TARGET): $(OBJS) $(OBJS_TARGET)
	$(CXX) $(LDFLAGS) -o $@ $^

$(TEST_TARGET): $(OBJS) $(OBJS_TEST)
	$(CXX) $(LDFLAGS) -o $@ $^

.cpp.o:
	$(CXX) -c $(CPPFLAGS) -o $@ $<


######################
#    Dependencies    #
######################


# EOF
