#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "grouping.cpp"
using namespace std;

int main() {
	int N, D, P;
	cin >> N >> D >> P;
	vector<int> teach(N);
	vector<string> name(N);
	vector<vector<int>> schedule(N, vector<int>(D * P));
	for (int i = 0; i < N; i++) {
		cin >> name[i];
		cin >> teach[i];
		for (int j = 0; j < D * P; j++) {
			cin >> schedule[i][j];
		}
	}

	srand(time(NULL));

	Grouping gp;
	gp.set_variable(N, D, P);
	gp.set_vectors(name, teach, schedule);

	gp.print_explanation();
	gp.print_schedule();
	gp.anneal(100000);
	gp.print_schedule();
	gp.print_pairs();

	return 0;
}