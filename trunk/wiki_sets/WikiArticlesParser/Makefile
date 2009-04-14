#------------------------------ CONFIGURATION ------------------------------#

AppName = WikiArticlesParser

# C++ compiler options.
CXXFLAGS = -Wall -ansi -pedantic-errors -O3 -DNDEBUG -fno-inline

# C++ Glibmm and Libxml++ references.
CXXFLAGS += $(shell pkg-config --cflags glibmm-2.4)
LDFLAGS += $(shell pkg-config --libs glibmm-2.4)
CXXFLAGS += $(shell pkg-config --cflags libxml++-2.6)
LDFLAGS += $(shell pkg-config --libs libxml++-2.6)
LDFLAGS += -lm -lpthread

ifneq ($(Release), YES)
	CXXFLAGS += -ggdb -DDEBUG
endif

#--------------------------------- COMPILE ---------------------------------#

# Take all the files.
Files ?= $(wildcard *.cpp)
OFiles = $(patsubst %.cpp,%.o,$(Files))

.PHONY: all

all: build clean

build: $(OFiles)
	@if [ -z "$(OFiles)" ]; \
	then \
		echo "No *.cpp files to compile."; \
		false; \
	fi >&2
	g++ $(LDFLAGS) $(OFiles) $(LOADLIBES) $(LDLIBS) -o ./$(AppName)

clean:
	@$(RM) -fv *.o

