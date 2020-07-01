CXX = /usr/local/bin/g++-9
OBJS = grouping

%: %.cpp
	$(CXX) -Wall -std=c++14 $< -o $@

test: grouping testcase/sample.in
	./grouping < testcase/sample.in >| testcase/sample.out

testcase/sample.in: generator.py
	python3 generator.py

clean:
	rm -f $(OBJS)
	rm -f testcase/sample.in
	rm -f testcase/sample.out