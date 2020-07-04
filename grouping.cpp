/**
 * @file    grouping.cpp
 * @brief   Grouping Algorithm for one-on-one practice. 
 * @author  18T Nozomu Yamazaki
 * @date    2020-06-30 
 * 
 * Copyright (c) 2020 Nozomu Yamazaki
 * Released under the MIT license
 * https://opensource.org/licenses/mit-license.php
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * @class   Grouping
 * @brief   Grouping Algorithm
 */
class Grouping {
   private:
	int N;                          //! Number of members
	int D;                          //! Number of days
	int P;                          //! Number of periods per day
	int Q;                          //! Number of periods per each practice
	int R;                          //! Number of practices (begin taught) per each member
	int score;                      //! Highest score at the time
	int loop_cnt = 0;               //! Number of times change_random was executed
	vector<string> name;            //! Name for each member
	vector<int> teach;              //! Whether the member can teach of not
	vector<vector<int>> schedule;   //! Schedule for each member
	vector<vector<int>> timetable;  //! Timetable for each member
	vector<vector<int>> pairs;      //! Pairs of members. This will be the final output
	vector<string> date;
	vector<string> start;
	vector<string> end;

	/*! Evaluates the score of the current state */
	int evaluate(vector<vector<int>>);
	/*! Changes the state randomly */
	vector<vector<int>> change_random(vector<vector<int>>);

   public:
	void set_variable(int, int, int, int, int);
	void set_vectors(vector<string>, vector<string>, vector<string>, vector<string>, vector<int>, vector<vector<int>>);
	void create_timetable();
	void print_timetable();
	void print_schedule();
	void print_pairs();
	void print_explanation();
	void anneal(int);
};

void Grouping::create_timetable() {
	timetable.resize(N);
	for (int i = 0; i < N; i++) {
		timetable[i].resize(D * (P - Q + 1));
	}
	for (int i = 0; i < N; i++) {
		for (int d = 0; d < D; d++) {
			for (int p = 0; p < P - Q + 1; p++) {
				bool vacant = true;
				for (int q = 0; q < Q; q++) {
					if (schedule[i][P * d + p + q] == 0) {
						vacant = false;
					}
				}
				if (vacant) {
					timetable[i][(P - Q + 1) * d + p] = 1;
				} else {
					timetable[i][(P - Q + 1) * d + p] = 0;
				}
			}
		}
	}
}

void Grouping::print_timetable() {
	for (int i = 0; i < N; i++) {
		cout << name[i] << endl;
		for (int j = 0; j < D; j++) {
			for (int p = 0; p < P - Q + 1; p++) {
				if (pairs[i][j * (P - Q + 1) + p] != -1) {
					printf("%d ", pairs[i][j * (P - Q + 1) + p]);
				} else {
					if (timetable[i][(P - Q + 1) * j + p] == 1) {
						printf("* ");
					} else {
						printf("- ");
					}
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}

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
}

vector<vector<int>> Grouping::change_random(vector<vector<int>> pairs) {
	int i = rand() % N;                  // index of teacher
	int j = rand() % N;                  // index of learner
	int k = rand() % ((P - Q + 1) * D);  // index of period
	if (i != j) {
		if (teach[i] == 1 && timetable[i][k] == 1 && timetable[j][k] == 1 && pairs[i][k] == -1) {
			for (int q = -Q + 1; q < Q; q++) {
				if (pairs[i][k + q] != -1 && (k + q) / D == k / D) {
					return pairs;
				}
			}

			for (int l = 0; l < N; l++) {
				for (int q = -Q + 1; q < Q; q++) {
					if ((pairs[l][k + q] == i || pairs[l][k + q] == j) && (k + q) / D == k / D) {
						return pairs;
					}
				}
			}

			bool vacant = true;
			for (int q = -Q + 1; q < Q; q++) {
				if (pairs[j][k + q] != -1) {
					vacant = false;
				}
			}

			if (vacant) {
				pairs[j][k] = i;
			} else {
				pairs[j][k] = -1;
			}
		}
	}
	return pairs;
}

int Grouping::evaluate(vector<vector<int>> pairs) {
	int score = 0;
	vector<int> teach_cnt(N, 0);
	for (int i = 0; i < N; i++) {
		vector<int> count(N, 0);
		int learn_cnt = 0;
		for (int j = 0; j < (P - Q + 1) * D; j++) {
			if (pairs[i][j] != -1) {
				learn_cnt++;
				count[pairs[i][j]]++;
				teach_cnt[pairs[i][j]]++;
			}
		}
		if (learn_cnt == R) {
			score += 500;
		} else if (learn_cnt == 0) {
			score -= 1000;
		} else {
			score += (learn_cnt / R) * 100;
		}
		for (int j = 0; j < N; j++) {
			if (count[j] == R && learn_cnt == R) {
				score += 1000;
			} else if (count[j] != 0) {
				score -= abs(R - count[j]) * 500;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		if (teach_cnt[i] >= 2 * R) {
			score -= (teach_cnt[i] - 2 * R) * 100;
		}
	}
	for (int i = 0; i < N; i++) {
		vector<int> day(D, 0);
		for (int j = 0; j < D * (P - Q + 1); j++) {
			if (pairs[i][j] != -1) {
				day[j / (P - Q + 1)]++;
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

void Grouping::set_variable(int N, int D, int P, int Q, int R) {
	this->N = N;
	this->D = D;
	this->P = P;
	this->Q = Q;
	this->R = R;
	// initialize vector
	pairs.resize(N);
	for (int i = 0; i < N; i++) {
		pairs[i].resize(D * (P - Q + 1));
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < D * (P - Q + 1); j++) {
			pairs[i][j] = -1;
		}
	}
}

void Grouping::set_vectors(vector<string> date, vector<string> start, vector<string> end, vector<string> name, vector<int> teach, vector<vector<int>> schedule) {
	this->date = date;
	this->start = start;
	this->end = end;
	this->name = name;
	this->teach = teach;
	this->schedule = schedule;
	score = evaluate(pairs);
}

void Grouping::print_schedule() {
	printf("Loop count: %d, score: %d/%d\n", loop_cnt, score, (1500) * N);
	for (int i = 0; i < N; i++) {
		cout << name[i] << endl;
		for (int j = 0; j < D; j++) {
			for (int p = 0; p < P; p++) {
				if (schedule[i][j * P + p] == 1) {
					printf("* ");
				} else {
					printf("- ");
				}
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("\n");
}

void Grouping::print_pairs() {
	printf("Teacher    -> Learner\n");
	vector<int> teach_cnt(N, 0);
	vector<int> learn_cnt(N, 0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < D * (P - Q + 1); j++) {
			if (pairs[i][j] != -1) {
				cout << left << setw(3 * sizeof(2)) << name[pairs[i][j]] << " -> " << left << setw(3 * sizeof(2)) << name[i] << " at  " << left << setw(sizeof(date[P].length())) << date[j / (P - Q + 1)] << "  " << left << setw(sizeof(start[P].length())) << start[j % (P - Q + 1)] << " – " << left << setw(sizeof(end[P].length())) << end[j % (P - Q + 1) + Q - 1] << endl;
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
	printf("score: %d/%d\n", score, (1500) * N);
	printf("loops: %d\n", loop_cnt);
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
