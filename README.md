# ck-grouping

Aud. や C.&C. 用の組分けアルゴリズムです．  
各パートごとに見る側・見られる側のペアを決定します．

[PDF 版](https://github.com/nozomu-y/ck-grouping/blob/master/README.pdf)

## 入力

入力は以下の形式で標準入力から与えてください．

- <img src="https://render.githubusercontent.com/render/math?math=N"/> : パート内の団員数
- <img src="https://render.githubusercontent.com/render/math?math=D"/> : 設定する期間の日数
- <img src="https://render.githubusercontent.com/render/math?math=P"/> : 1 日あたりのコマ数
- <img src="https://render.githubusercontent.com/render/math?math=Q"/> : 1 回の練習あたりのコマ数
- <img src="https://render.githubusercontent.com/render/math?math=R"/> : 練習回数

例えば， 1 コマ 2 時間であった場合，1 人あたりの最終的な練習時間は <img src="https://render.githubusercontent.com/render/math?math=2QR"/> 時間になる．

> <img src="https://render.githubusercontent.com/render/math?math=N%20D%20P%20Q%20R"/>

続いて，それぞれの日とコマの情報が与えられる．

- <img src="https://render.githubusercontent.com/render/math?math=\rm{date}_i"/> : <img src="https://render.githubusercontent.com/render/math?math=i"/> 日目の日付
- <img src="https://render.githubusercontent.com/render/math?math=\rm{start}_i"/> : <img src="https://render.githubusercontent.com/render/math?math=i"/> コマ目の開始時刻
- <img src="https://render.githubusercontent.com/render/math?math=\rm{end}_i"/> : <img src="https://render.githubusercontent.com/render/math?math=i"/> コマ目の終了時刻

> <img src="https://render.githubusercontent.com/render/math?math=\rm{date}_1"/><span/>  
> <img src="https://render.githubusercontent.com/render/math?math=\vdots"/>   
> <img src="https://render.githubusercontent.com/render/math?math=\rm{date}_D"/>  
> <img src="https://render.githubusercontent.com/render/math?math=\rm{start}_1\:\rm{end}_1"/>   
> <img src="https://render.githubusercontent.com/render/math?math=\vdots"/>   
> <img src="https://render.githubusercontent.com/render/math?math=\rm{start}_P\:\rm{end}_P"/> 


この後，団員 <img src="https://render.githubusercontent.com/render/math?math=i=\{1,2,\cdots,N\}"/> について，以下の情報を与えてください．

- <img src="https://render.githubusercontent.com/render/math?math=S_i"/> : 団員 <img src="https://render.githubusercontent.com/render/math?math=i"/> の名前
- <img src="https://render.githubusercontent.com/render/math?math=t_i"/> : 団員 <img src="https://render.githubusercontent.com/render/math?math=i"/> が指導可能である場合は <img src="https://render.githubusercontent.com/render/math?math=1"/> ，指導不能な場合は <img src="https://render.githubusercontent.com/render/math?math=0"/>
- <img src="https://render.githubusercontent.com/render/math?math=s_{i,d,p}"/> : 団員 <img src="https://render.githubusercontent.com/render/math?math=i"/> が <img src="https://render.githubusercontent.com/render/math?math=d"/> 日目の <img src="https://render.githubusercontent.com/render/math?math=p"/> コマ目に予定が空いている場合は <img src="https://render.githubusercontent.com/render/math?math=1"/> ，空いていない場合は <img src="https://render.githubusercontent.com/render/math?math=0"/>

なお，<img src="https://render.githubusercontent.com/render/math?math=d=\{1,2,\cdots,D\}"/>, <img src="https://render.githubusercontent.com/render/math?math=p=\{1,2,\cdots,P\}"/> とします．

> <img src="https://render.githubusercontent.com/render/math?math=S_i"/><span/>  
> <img src="https://render.githubusercontent.com/render/math?math=t_i"/>  
> <img src="https://render.githubusercontent.com/render/math?math=s_{i,1,1}\:s_{i,1,2}\:\cdots\:s_{i,1,P}"/>  
> <img src="https://render.githubusercontent.com/render/math?math=s_{i,2,1}\:s_{i,2,2}\:\cdots\:s_{i,2,P}"/>  
> <img src="https://render.githubusercontent.com/render/math?math=\vdots"/>  
> <img src="https://render.githubusercontent.com/render/math?math=s_{i,D,1}\:s_{i,D,2}\:\cdots\:s_{i,D,P}"/>

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

<img src="https://render.githubusercontent.com/render/math?math=N,D,P"/> の値を入力することで，乱数を元にテストケースを作成します．
