CXX = /usr/local/bin/g++-9
OBJS = main grouping

main: main.cpp grouping.cpp
	$(CXX) -Wall -std=c++14 main.cpp -o main

grouping: grouping.cpp
	$(CXX) -Wall -std=c++14 grouping.cpp -o grouping

test: main testcase/sample.in
	./main >| testcase/sample.out

testcase/sample.in: generator.py
	python3 generator.py

clean:
	rm -f $(OBJS)
	rm -f testcase/sample.in
	rm -f testcase/sample.out