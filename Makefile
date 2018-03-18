# CC = g++ # This is the main compiler
# # CC := clang --analyze # and comment out the linker last line for sanity
# SRCDIR = src
# BUILDDIR = build
# TARGET = bin/runner
#
# SRCEXT = cpp
# SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
# OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
#
# $(TARGET): $(OBJECTS)
# 	@echo " Linking..."
# 	@echo " $(CC) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET)
#
# $(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
# 	@mkdir -p $(BUILDDIR)
#   @echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<
#

#
# bin/volimage: volimage.o
# 	g++ -o bin/volimage
#
#
# test: test/000-CatchMain
# 	./bin/000-CatchMain
#
# test/000-CatchMain: test/000-CatchMain.o
# 	g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -o ./bin/000-CatchMain ./test/tests-volimage.o ./build/volimage.o
#
# test/000-CatchMain.o: test/000-CatchMain.cpp test/tests-volimage.cpp src/volimage.cpp


CXX = g++ # This is the main compiler
CXXFLAGS = -std=c++11 -Wall
VPATH = test src include bin build

runner: volimage.o driver.o
	$(CXX) $(CXXFLAGS) -o bin/runner build/volimage.o build/driver.o && bin/runner "test" --success

driver.o: driver.cpp driver.h
	$(CXX) $(CXXFLAGS) -c src/driver.cpp -o build/driver.o

volimage.o: volimage.cpp volimage.h
	$(CXX) $(CXXFLAGS) -c src/volimage.cpp -o build/volimage.o


test: 000-CatchMain.o volimage.o driver.o tests-volimage.o
	./bin/tests-volimage --success


tests-volimage.o: tests-volimage.cpp
	$(CXX) $(CXXFLAGS) -I ./include -o bin/tests-volimage build/000-CatchMain.o build/volimage.o build/driver.o test/tests-volimage.cpp


000-CatchMain.o: 000-CatchMain.cpp catch.hpp
	$(CXX) $(CXXFLAGS) -I ./include -c test/000-CatchMain.cpp -o build/000-CatchMain.o

.PHONY: clean

clean:
	find . -type f \( -name "*.o" ! -name "000-CatchMain.o" -or -name "volimage-test" \) -delete
