# AraBellaC
把‘A'字符的出现位置集合记录为$a_i$,类似的记录'B', 'C'字符的出现位置$b_i$, $c_i$。如果假定循环节长度为 $len$， 那么 $a, b, c$ 有解当且仅当任意 $i, j, k$ 对如下公式成立 
$$ \begin{cases} 
		max\{(a_i-1)\ mod\ len\} < min\{(b_j-1)\ mod\ len\} \\
        max\{(b_j-1)\ mod\ len\} < min\{(c_k-1)\ mod\ len\} \\
\end{cases} $$
如果此方程满足了，则可以更新$a, b, c$ 的最优解为 $max\{(a_i-1)\ mod\ len\}, max\{(b_j-1)\ mod\ len\}-max\{(a_i-1)\ mod\ len\}, len-max\{(b_j-1)\ mod\ len\}$。

但是如果直接暴力，复杂度将会达到 $T*N*M$,其中$N, M$分别表示已知的点的个数与最大循环节长度。

考虑进行优化：
枚举循环节长度，并在当前循环节长度下枚举每个循环节，二分查找这个循环节内的 $max\{(a_i-1)\ mod\ len\} , max\{(b_j-1)\ mod\ len\} , max\{(c_k-1)\ mod\ len\}$，复杂度为$T*M*log(M)*log(N)$

可以通过$ST$表优化到 $T*m*log(m)$。