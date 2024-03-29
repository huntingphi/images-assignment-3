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


run: utils.o volimage.o driver.o
	$(CXX) $(CXXFLAGS) -o bin/runner build/utils.o build/volimage.o build/driver.o

run-build: volimage.o driver.o
	$(CXX) $(CXXFLAGS) -o bin/runner build/volimage.o build/driver.o build/utils.o

run-diffmap: volimage.o driver.o
	$(CXX) $(CXXFLAGS) -o bin/runner build/volimage.o build/driver.o && bin/runner -d 0 1 test
run-extract: volimage.o driver.o
	$(CXX) $(CXXFLAGS) -o bin/runner build/volimage.o build/driver.o && bin/runner -x 0 test


driver.o: driver.cpp driver.h
	$(CXX) $(CXXFLAGS) -c src/driver.cpp -o build/driver.o


test: 000-CatchMain.o volimage.o tests-volimage.cpp Metadata.o utils.o tests-volimage.o
	$(CXX) $(CXXFLAGS) -I ./include -o bin/test build/000-CatchMain.o build/volimage.o build/Metadata.o build/utils.o build/tests-volimage.o && ./bin/test --success

volimage.o: volimage.cpp volimage.h
	$(CXX) $(CXXFLAGS) -c src/volimage.cpp -o build/volimage.o

tests-utils: 000-CatchMain.o tests-utils.cpp Metadata.o utils.o tests-utils.o
	$(CXX) $(CXXFLAGS) -I ./include -o bin/tests-utils build/000-CatchMain.o build/Metadata.o build/utils.o build/tests-utils.o && ./bin/tests-utils

Metadata.o: Metadata.cpp
	$(CXX) $(CXXFLAGS) -c src/Metadata.cpp -o build/Metadata.o

utils.o: utils.cpp
	$(CXX) $(CXXFLAGS) -c src/utils.cpp -o build/utils.o

tests-utils.o: tests-utils.cpp
	$(CXX) $(CXXFLAGS) -c test/tests-utils.cpp -o build/tests-utils.o


tests-volimage.o: tests-volimage.cpp
	# $(CXX) $(CXXFLAGS) -I ./include -c build/volimage.o test/tests-volimage.cpp
	echo "Testing VolImage..."
	$(CXX) $(CXXFLAGS) -c test/tests-volimage.cpp -o build/tests-volimage.o


000-CatchMain.o: 000-CatchMain.cpp catch.hpp
	$(CXX) $(CXXFLAGS) -I ./include -c test/000-CatchMain.cpp -o build/000-CatchMain.o

.PHONY: clean

clean:
	find . -type f \( -name "*.o" ! -name "000-CatchMain.o" -or -name "volimage-test" \) -delete
	find . -type f \( -name "*.gch" -or -name "tests-utils" -or -name "runner" \) -delete
	find output_raws -type f -name "*.raw" -delete
