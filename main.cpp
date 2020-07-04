#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "grouping.cpp"
using namespace std;

int main() {
	int N, D, P, Q, R;
	cin >> N >> D >> P >> Q >> R;
	vector<string> date(D);
	vector<string> start(P);
	vector<string> end(P);
	for (int i = 0; i < D; i++) {
		cin >> date[i];
	}
	for (int i = 0; i < P; i++) {
		cin >> start[i] >> end[i];
	}

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
	gp.set_variable(N, D, P, Q, R);
	gp.set_vectors(date, start, end, name, teach, schedule);

	gp.print_explanation();
	gp.print_schedule();
	gp.create_timetable();
	gp.print_timetable();
	gp.local_search(10000);
	gp.print_timetable();
	gp.print_pairs();

	return 0;
}