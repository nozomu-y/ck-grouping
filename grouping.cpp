#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Grouping {
   private:
	int N;
	int D;
	int P;
	int score;
	int loop_cnt = 0;
	vector<string> name;
	vector<int> teach;
	vector<vector<int>> schedule;
	vector<vector<int>> pairs;
	int evaluate(vector<vector<int>>);
	vector<vector<int>> change_random(vector<vector<int>>);

   public:
	void set_variable(int, int, int);
	void set_vectors(vector<string>, vector<int>, vector<vector<int>>);
	void print_schedule();
	void print_pairs();
	void print_explanation();
	void anneal(int);
};

void Grouping::anneal(int repeat = 10000) {
	vector<vector<int>> pairs_new;
	int score_new;
	int refresh = 0;
	while (refresh < repeat) {
		loop_cnt++;
		refresh++;
		pairs_new = change_random(pairs);
		score_new = evaluate(pairs_new);
		if (score_new > score) {
			refresh = 0;
			score = score_new;
			pairs = pairs_new;
		}
	}
};

vector<vector<int>> Grouping::change_random(vector<vector<int>> pairs) {
	int i = rand() % N;  // teach
	int j = rand() % N;  // learn
	int k = rand() % (P * D);
	if (i != j) {
		if (teach[i] == 1 && schedule[i][k] == 1 && schedule[j][k] == 1 && pairs[i][k] == -1) {
			for (int l = 0; l < N; l++) {
				if (pairs[l][k] == i || pairs[l][k] == j) {
					return pairs;
				}
			}

			if (pairs[j][k] != -1) {
				pairs[j][k] = -1;
			} else {
				pairs[j][k] = i;
			}
		}
	}
	return pairs;
}

int Grouping::evaluate(vector<vector<int>> pairs) {
	int score;
	vector<int> teach_cnt(N, 0);
	for (int i = 0; i < N; i++) {
		vector<int> count(N, 0);
		int learn_cnt = 0;
		for (int j = 0; j < P * D; j++) {
			if (pairs[i][j] != -1) {
				learn_cnt++;
				count[pairs[i][j]]++;
				teach_cnt[pairs[i][j]]++;
			}
		}
		if (learn_cnt == 2) {
			score += 100;
		} else if (learn_cnt == 0) {
			score -= 1000;
		} else {
			score -= abs(2 - learn_cnt) * 100;
		}
		for (int j = 0; j < N; j++) {
			if (count[j] == 2 && learn_cnt == 2) {
				score += 500;
			} else if (count[j] != 0) {
				score -= 500;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		if (teach_cnt[i] >= 4) {
			score -= (teach_cnt[i] - 4) * 100;
		}
		//  else if (teach_cnt[i] < 2 && teach[i] == 1) {
		// score -= 100;
		// }
	}
	for (int i = 0; i < N; i++) {
		vector<int> day(D, 0);
		for (int j = 0; j < D * P; j++) {
			if (pairs[i][j] != -1) {
				day[j / P]++;
			}
		}
		for (int j = 0; j < D; j++) {
			if (day[j] > 1) {
				score -= (day[j] - 1) * 500;
			}
		}
	}

	return score;
}

void Grouping::set_variable(int N, int D, int P) {
	this->N = N;
	this->D = D;
	this->P = P;
	// initialize vector
	pairs.resize(N);
	for (int i = 0; i < N; i++) {
		pairs[i].resize(D * P);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < D * P; j++) {
			pairs[i][j] = -1;
		}
	}
}

void Grouping::set_vectors(vector<string> name, vector<int> teach, vector<vector<int>> schedule) {
	this->name = name;
	this->teach = teach;
	this->schedule = schedule;
	score = evaluate(pairs);
}

void Grouping::print_schedule() {
	printf("Loop count: %d, score: %d/%d\n", loop_cnt, score, (500 + 100) * N);
	for (int i = 0; i < N; i++) {
		cout << name[i] << endl;
		for (int j = 0; j < D * P; j++) {
			if (pairs[i][j] != -1) {
				printf("%d ", pairs[i][j]);
			} else {
				if (schedule[i][j] == 1) {
					printf("* ");
				} else {
					printf("- ");
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}

void Grouping::print_pairs() {
	printf("Teacher -> Learner\n");
	vector<int> teach_cnt(N, 0);
	vector<int> learn_cnt(N, 0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < D * P; j++) {
			if (pairs[i][j] != -1) {
				cout << left << setw(7) << name[pairs[i][j]] << " -> " << left << setw(7) << name[i] << "    at    Day " << right << setw(2) << j / P + 1 << " Period " << right << setw(2) << j % P + 1 << endl;
				teach_cnt[pairs[i][j]]++;
				learn_cnt[i]++;
			}
		}
	}
	cout << endl;
	printf("Teach count\n");
	for (int i = 0; i < N; i++) {
		if (teach[i] == 1) {
			cout << name[i] << ": " << teach_cnt[i] << endl;
		} else {
			cout << name[i] << ": -  (cannot teach) " << endl;
		}
	}
	cout << endl;
	printf("Learn count\n");
	for (int i = 0; i < N; i++) {
		cout << name[i] << ": " << learn_cnt[i] << endl;
	}
	cout << endl;
	printf("score: %d/%d\n", score, (500 + 100) * N);
}

void Grouping::print_explanation() {
	printf("Each day is divided into %d periods.\n", P);
	printf("There are %d days in this testcase. \n", D);

	printf("\nThe following data is given for each member. \n");
	printf("* name\n");
	printf("* whether the member can teach or not\n");
	printf("* schedule for each period\n");

	printf("\nThe horizontal axis in the chart below expresses each period. (%d x %d)\n\n", D, P);

	printf(" - : occupied\n");
	printf(" * : vacant\n\n");
}
