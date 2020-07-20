#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "grouping.cpp"
using namespace std;

int main() {
	Grouping gp("./testcase/form.in");
	gp.global_search(10, 10000);
	gp.print_pairs();

	return 0;
}
