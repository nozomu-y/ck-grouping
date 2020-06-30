import random

N = int(input("N:"))
D = int(input("D:"))
P = int(input("P:"))
filename = './testcase/sample.in'

f = open(filename, mode='w')

f.write(str(N) + ' ' + str(D) + ' ' + str(P) + '\n')

teach_cnt = 0

for i in range(N):
    f.write("Name" + str(i) + "\n")
    teach = random.randrange(5)
    if teach != 0:
        teach = 1
        teach_cnt += 1
    f.write(str(teach) + "\n")
    a = random.randrange(2, 4)
    print(str(i) + ":" + str(a))
    for _ in range(D):
        for _ in range(P):
            s = random.randrange(a)
            if s == 0:
                s = 1
            else:
                s = 0
            f.write(str(s) + " ")
        f.write("\n")

print(teach_cnt)
