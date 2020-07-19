#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "grouping.cpp"
using namespace std;

int main() {
	Grouping gp("./testcase/form.in");
	gp.print_explanation();
	gp.print_schedule();
	gp.create_timetable();
	gp.print_timetable();
	gp.global_search(100, 10000);
	gp.print_timetable();
	gp.print_pairs();

	return 0;
}