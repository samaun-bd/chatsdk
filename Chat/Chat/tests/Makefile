ALL = simpletest.out

all: $(ALL)

C++ := g++

CPPFLAGS := -std=c++11

LIBS := \
	-lpthread \
	-lcurl

SDK_PATH := ../src
PARSER_PATH := ../../ChatParser/src
IPVCORE_PATH := ../../../../ipvcore/core
TEST_PATH := ./

INCLUDE := \
	-I$(PARSER_PATH) \
	-I$(SDK_PATH) \
	-I$(IPVCORE_PATH)

SDK_SRCS := $(shell find $(SDK_PATH) -name '*.cpp')
PARSER_SRCS := $(shell find $(PARSER_PATH) -name '*.cpp')
IPVCORE_SRCS := $(shell find $(IPVCORE_PATH) -name '*.cpp')
TEST_SRCS := $(shell find $(TEST_PATH) -name '*.cpp')

SDK_OBJS := $(SDK_SRCS:%.cpp=%.o)
PARSER_OBJS := $(PARSER_SRCS:%.cpp=%.o)
IPVCORE_OBJS := $(IPVCORE_SRCS:%.cpp=%.o)
TEST_OBJS := $(TEST_SRCS:%.cpp=%.o)

OBJS := \
	$(SDK_OBJS) \
	$(PARSER_OBJS) \
	$(TEST_OBJS) \
	$(IPVCORE_OBJS)

.cpp.o:
	$(C++) $(CPPFLAGS) $(INCLUDE) -o $@ -c -MP -MMD $<

simpletest.out: $(OBJS)
	$(C++) $(CPPFLAGS) $(OBJS) -o simpletest.out $(LIBS)

clean:
	$(RM) $(OBJS:%.o=%.d)
	$(RM) $(OBJS)
	$(RM) $(ALL)

-include $(OBJS:%.o=%.d)
