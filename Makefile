CXX = /usr/local/bin/g++-9
OBJS = main

%: %.cpp
	$(CXX) -Wall -std=c++14 $< -o $@

test: main testcase/sample.in
	./main < testcase/sample.in >| testcase/sample.out

testcase/sample.in: generator.py
	python3 generator.py

clean:
	rm -f $(OBJS)