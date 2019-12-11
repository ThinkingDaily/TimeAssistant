# 图形说明

一个辅助的 ```3 x 3``` 网格内，有两个角，并绘制两个小圆弧配置数字标记。

## 转换关系

首先是arc的起始点、起始角度、半径之间的计算关系:

```
% starts from (x,y)
% with center (x-r*cos(start), y-r*sin(start)) and
```

或者,

```
% center O, radius = r, start angle = start
% start point/position: O + (r*cos(start), r*sin(start))
```

## 半径

在本例中，是先确定的圆心、起始角度。因为是画一个圆弧表示角度，所以半径可以通过实际效果进行调整。在确定了半径字后，通过相对位置偏移，计算出起始位置。

## 度数

这里通过 ```arctan()```计算出角度。

# Code

```
\begin{tikzpicture}
\draw (0,0)--(3,0)--(3,3)--(0,3)--cycle;
\draw[dashed](1,0)--(1,3) (2,0)--(2,3) (0,1)--(3,1) (0,2)--(3,2);
\draw (0,1)--(1,2) --(2,0)--(3,3);

% arctan(2)=63.43494882
\coordinate (P12) at (1, 2);
% r=0.3; r*cos(225)=-0.212; r*sin(225)=-0.212
\coordinate (start_1) at ([shift={(-0.212, -0.212)}] P12);
\draw(start_1) arc (225:297:0.3);

% arctan(3)=71.56505118
% r = 0.3; r*cos(71.565)=0.095; r*sin(71.565)=0.285
\coordinate (P20) at (2, 0);
\coordinate (start_2) at ([shift={(0.095, 0.285)}] P20);
% 180-63.435=116.565
\draw(start_2) arc (71.565:116.565:0.3);

\node at ([shift={(0.14,-0.3)}] start_1) {1};
\node at ([shift={(-0.1,0.3)}] start_2) {2};

\end{tikzpicture}
```
