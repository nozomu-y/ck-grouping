#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int evaluate(vector<vector<int>> pair, vector<int> teach, int N, int D, int P);
vector<vector<int>> anneal(vector<vector<int>> pair, vector<int> teach, vector<vector<int>> schedule, int N, int D, int P);

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

	vector<vector<int>> pair(N, vector<int>(P * D, -1));

	std::srand(time(NULL));
	vector<vector<int>> pair_new = pair;
	int score, score_new;

	// for (int l = 0; l < 10000; l++) {
	// 	pair_new = anneal(pair_new, teach, schedule, N, D, P);
	// 	pair = pair_new;
	// }

	score = evaluate(pair, teach, N, D, P);
	printf("Each Day is divided into %d periods.\n", P);
	printf("There are %d days in this testcase. \n", D);

	printf("\nThe following data is given for each member. \n");
	printf("* name\n");
	printf("* whether the member can teach or not\n");
	printf("* schedule for each period\n");

	printf("\nThe horizontal axis in the chart below expresses each period. (%d x %d)\n\n", D, P);

	printf(" - : occupied\n");
	printf(" * : vacant\n\n");

	printf("Initial State    score: %d/%d\n", score, (500 + 100) * N);
	for (int i = 0; i < N; i++) {
		// printf("%s\n", name[i]);
		cout << name[i] << endl;
		for (int j = 0; j < D * P; j++) {
			if (pair[i][j] != -1) {
				printf("%d ", pair[i][j]);
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
	printf("\n");

	int refresh = 0;
	while (refresh < 1000000) {
		refresh++;
		pair_new = pair;
		pair_new = anneal(pair_new, teach, schedule, N, D, P);
		score_new = evaluate(pair_new, teach, N, D, P);
		if (score_new > score) {
			refresh = 0;
			score = score_new;
			pair = pair_new;
		}
	}

	/****/
	printf("Convergence State    score: %d/%d\n", score, (500 + 100) * N);

	for (int i = 0; i < N; i++) {
		cout << name[i] << endl;
		// printf("%d\n", i);
		for (int j = 0; j < D * P; j++) {
			if (pair[i][j] != -1) {
				printf("%d ", pair[i][j]);
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

	printf("\n\n");
	printf("Teacher -> Learner\n");
	vector<int> teach_cnt(N, 0);
	vector<int> learn_cnt(N, 0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < D * P; j++) {
			if (pair[i][j] != -1) {
				// printf("%d -> %d at %d\n", pair[i][j], i, j);
				cout << left << setw(7) << name[pair[i][j]] << " -> " << left << setw(7) << name[i] << "    at    Day " << right << setw(2) << j / P << " Period " << j % P << endl;
				teach_cnt[pair[i][j]]++;
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

	return 0;
}

int evaluate(vector<vector<int>> pair, vector<int> teach, int N, int D, int P) {
	int score;
	vector<int> teach_cnt(N, 0);
	for (int i = 0; i < N; i++) {
		vector<int> count(N, 0);
		int learn_cnt = 0;
		for (int j = 0; j < P * D; j++) {
			if (pair[i][j] != -1) {
				learn_cnt++;
				count[pair[i][j]]++;
				teach_cnt[pair[i][j]]++;
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
			if (pair[i][j] != -1) {
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

vector<vector<int>> anneal(vector<vector<int>> pair, vector<int> teach, vector<vector<int>> schedule, int N, int D, int P) {
	int i = rand() % N;  // teach
	int j = rand() % N;  // learn
	int k = rand() % (P * D);
	if (i != j) {
		if (teach[i] == 1 && schedule[i][k] == 1 && schedule[j][k] == 1 && pair[i][k] == -1) {
			for (int l = 0; l < N; l++) {
				if (pair[l][k] == i || pair[l][k] == j) {
					return pair;
				}
			}

			if (pair[j][k] != -1) {
				pair[j][k] = -1;
			} else {
				pair[j][k] = i;
			}
		}
	}
	return pair;
}