import random

N = int(input("N:"))
D = int(input("D:"))
P = int(input("P:"))
Q = int(input("Q:"))
R = int(input("R:"))
filename = './testcase/sample.in'

f = open(filename, mode='w')

f.write(str(N) + ' ' + str(D) + ' ' + str(P) + ' ' + str(Q) + ' ' + str(R) + '\n')
for i in range(D):
    f.write("Day" + str(i + 1) + "\n")
for i in range(P):
    f.write("Period" + str(i + 1) + " " + "Period" + str(i + 1) + "\n")

teach_cnt = 0

for i in range(N):
    f.write("Name" + str(i) + "\n")
    teach = random.randrange(5)
    if teach != 0:
        teach = 1
        teach_cnt += 1
    f.write(str(teach) + "\n")
    for _ in range(D):
        # a = random.randrange(2, 3)
        a = 2
        for _ in range(P):
            s = random.randrange(a)
            if s == 0:
                s = 1
            else:
                s = 0
            f.write(str(s) + " ")
        f.write("\n")

print(teach_cnt)
