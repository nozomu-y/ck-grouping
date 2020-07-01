# ck-grouping

Aud. や C.&C. 用の組分けアルゴリズムです．  
各パートごとに見る側・見られる側のペアを決定します．

[PDF 版](https://github.com/nozomu-y/ck-grouping/blob/master/README.pdf)

## 入力

入力は以下の形式で標準入力から与えてください．

- $N$ : パート内の団員数
- $D$ : 設定する期間の日数
- $P$ : 1 日あたりの時限数

> $N$ $D$ $P$

この後，団員 $i=\{1,2,\cdots,N\}$ について，以下の情報を与えてください．

- $S_i$ : 団員 $i$ の名前
- $t_i$ : 団員 $i$ が指導可能である場合は $1$ ，指導不能な場合は $0$
- $s_{i,d,p}$ : 団員 $i$ が $d$ 日目の $p$ 時限目に予定が空いている場合は $1$ ，空いていない場合は $0$

なお，$d=\{1,2,\cdots,D\},\ p=\{1,2,\cdots,P\}$ とします．

> $S_i$  
> $t_i$  
> $s_{i,1,1}$ $s_{i,1,2}$ $\cdots$ $s_{i,1,P}$  
> $s_{i,2,1}$ $s_{i,2,2}$ $\cdots$ $s_{i,2,P}$  
> $\vdots$  
> $s_{i,D,1}$ $s_{i,D,2}$ $\cdots$ $s_{i,D,P}$

### 入力例

```
3 7 6
Alex
1
1 1 1 0 1 0
0 1 0 0 0 0
0 0 1 1 0 0
1 1 1 0 0 0
0 0 0 1 1 0
1 1 0 1 0 1
1 0 0 1 1 1
Brian
0
1 0 1 1 0 0
0 0 0 0 0 0
1 1 1 1 1 1
1 0 0 1 0 1
0 0 1 0 0 1
0 0 0 0 1 0
1 0 1 0 0 0
Charles
1
0 1 0 0 1 0
1 1 0 1 1 0
1 0 0 0 0 0
0 0 1 1 1 1
1 0 1 0 0 0
0 1 1 1 1 0
1 0 1 0 0 0
```

### 出力例

```
Teacher  -> Learner
Charles  -> Alex     at Day 2 Period 2
Charles  -> Alex     at Day 6 Period 4
Alex     -> Brian    at Day 1 Period 1
Alex     -> Brian    at Day 4 Period 1
Alex     -> Charles  at Day 6 Period 2
Alex     -> Charles  at Day 7 Period 1
```

## ファイル

### grouping.cpp

本体．

### generator.py

使い方: python3 generator.py  
$N$, $D$, $P$ の値を入力することで，乱数を元にテストケースを作成します．
