SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
BINS=$(SOURCES:.cpp=)

CXXFLAGS+=-I../include -Wall -Werror -Wextra -g -O2 -std=c++17 -fno-common -pedantic-errors -Wshadow -Wwrite-strings -fshort-enums -Wctor-dtor-privacy -Wzero-as-null-pointer-constant -Wuseless-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Weffc++ -Wold-style-cast

all: $(BINS)

.PHONY: clean all

clean:
	$(RM) $(OBJECTS) $(DEPS) $(BINS)
