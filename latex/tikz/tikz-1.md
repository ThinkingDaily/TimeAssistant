# 图形说明

共 6 层的正三角形+小正三角形。

绘图时从上往下，依次取 ```y={0,...,5}```.

而每一层的点数 ```x=y+1```, 且最左边的点定义为 ```Base(240:y)```, 即往左下方向240°，距离原点 ```(0,0)``` 的距离为 ```y```. 

对于每一层，基于 ```Base``` 确定每个点的坐标位置，即 ```Top = Base + (x, 0)```. 这里假定每个小三角形的上面的定点为 Top, 下面两点左右分别为 Left 和 Right. 确定了 TLR 三个点之后，连线成为一个三角形.

# Code

```
\begin{tikzpicture}
\foreach \y in {0,...,5} {
    \coordinate (Base) at (240:\y);

    \foreach \x in {0,...,\y} {
        \coordinate (T) at ([shift={(\x, 0)}] Base); % Top
        \coordinate (L) at ([shift={(240:1)}] T); % Left
        \coordinate (R) at ([shift={(1, 0)}] L); % Right
        \draw (T)--(L)--(R)--cycle;
    }
}
\end{tikzpicture}
```
