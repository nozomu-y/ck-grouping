# ck-grouping

Aud. や C.&C. 用の組分けアルゴリズムです．  
各パートごとに見る側・見られる側のペアを決定します．

[PDF 版](https://github.com/nozomu-y/ck-grouping/blob/master/README.pdf)

## 入力

入力は以下の形式で標準入力から与えてください．

- $N$ : パート内の団員数
- $D$ : 設定する期間の日数
- $P$ : 1 日あたりのコマ数
- $Q$ : 1 回の練習あたりのコマ数
- $R$ : 練習回数

例えば， 1 コマ 2 時間であった場合，1 人あたりの最終的な練習時間は $2QR$ 時間になる．

> $N$ $D$ $P$ $Q$ $R$

続いて，それぞれの日とコマの情報が与えられる．

- $date_i$ : $i$ 日目の日付
- $start_i$ : $i$ コマ目の開始時刻
- $end_i$ : $i$ コマ目の終了時刻

> $date_1$   
> $\vdots$  
> $date_D$  
> $start_1$ $end_1$  
> $\vdots$  
> $start_P$ $end_P$


この後，団員 $i=\{1,2,\cdots,N\}$ について，以下の情報を与えてください．

- $S_i$ : 団員 $i$ の名前
- $t_i$ : 団員 $i$ が指導可能である場合は $1$ ，指導不能な場合は $0$
- $s_{i,d,p}$ : 団員 $i$ が $d$ 日目の $p$ コマ目に予定が空いている場合は $1$ ，空いていない場合は $0$

なお，$d=\{1,2,\cdots,D\},\ p=\{1,2,\cdots,P\}$ とします．

> $S_i$  
> $t_i$  
> $s_{i,1,1}$ $s_{i,1,2}$ $\cdots$ $s_{i,1,P}$  
> $s_{i,2,1}$ $s_{i,2,2}$ $\cdots$ $s_{i,2,P}$  
> $\vdots$  
> $s_{i,D,1}$ $s_{i,D,2}$ $\cdots$ $s_{i,D,P}$

### 入力例

```
3 7 8 2 2
Alex
0
1 0 0 1 1 1 0 1
1 0 0 1 0 1 1 0
1 0 1 0 0 0 1 0
0 0 0 1 1 1 1 1
0 0 0 0 1 1 1 1
0 0 0 0 0 0 0 1
1 1 1 0 1 1 0 0
Brian
1
1 0 1 1 1 0 0 1
1 0 1 1 1 1 0 1
1 0 1 0 0 0 1 0
1 1 1 0 0 1 1 1
1 1 0 0 0 0 0 1
1 0 1 1 0 1 1 0
0 1 0 0 1 1 1 0
Charles
1
1 0 0 1 0 1 0 0
1 0 1 1 1 1 0 1
0 0 0 1 1 1 0 1
1 1 1 1 0 1 0 0
1 1 0 1 1 0 0 0
0 1 0 1 0 1 0 0
1 1 1 1 0 0 0 0
```

### 出力例

```
Teacher  -> Learner
Brian    -> Alex     at Day 4 Period 6 to 7
Brian    -> Alex     at Day 7 Period 5 to 6
Charles  -> Brian    at Day 2 Period 3 to 4
Charles  -> Brian    at Day 2 Period 5 to 6
Brian    -> Charles  at Day 4 Period 1 to 2
Brian    -> Charles  at Day 5 Period 1 to 2
```

## ファイル

### grouping.cpp

本体．

### generator.py

$N$, $D$, $P$ の値を入力することで，乱数を元にテストケースを作成します．
