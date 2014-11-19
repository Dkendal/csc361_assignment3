LDLIBS := -lgtest -lgtest_main -lpthread
CXXFLAGS := -Wall -pedantic -g
TEST_BIN := bin/test
TEST_SRC := `ls test/lib/*`
SRC := `ls lib/*`

#all: $(program)

#$(program): $(srcproj) $(main)
#	$(CXX) $(CXXFLAGS) -o $(program) $(main) $(srcproj)
#

.PHONY: test

test:
	$(CXX) $(CXXFLAGS) -o $(TEST_BIN) $(TEST_SRC) $(SRC) $(LDLIBS)

clean:
	rm -f *.o $(TEST_BIN)
