#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "grouping.cpp"
using namespace std;

int main() {
    Grouping gp("./testcase/form.in");
    // Grouping gp("./testcase/sample.in");
    gp.global_search(100, 10000);
    gp.print_pairs();

    return 0;
}
