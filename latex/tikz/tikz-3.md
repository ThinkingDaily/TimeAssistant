# 图形

这里的图形和tikz-2.tex完全一样，仅代码做了修改。

在tikz-2.tex中，提前计算出了半径（多次尝试而确定）、角度、起始点。在多次尝试的过程中，会修改多个数据，很不灵活。

为此，在tikz-3.tex中，使用了数学计算、变量。

## Code

```
\coordinate (P12) at (1, 2);
\tikzmath{
    \r = 0.3;
    \start = 180 + atan(1);
    \endd = 360 - atan(2);
    \shift{x} = \r * cos(\start);
    \shift{y} = \r * sin(\start);
}
\coordinate (start_1) at ([shift={(\shift{x}, \shift{y})}] P12);
\draw (start_1) arc (\start:\endd:\r);
```

先定义了半径；然后起始角度、结束角度均通过反正切函数求出；再计算出起始点相对于圆心的偏移量。

## Ref

数学计算部分参考 pgfmanual 56 Math Library.
