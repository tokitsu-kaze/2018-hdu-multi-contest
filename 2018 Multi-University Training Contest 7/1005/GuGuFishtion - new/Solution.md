题意:给定$n$,$m$,$p$,求
$$(\sum\limits_{a=1}^m\sum\limits_{b=1}^n\frac{\phi(ab)}{\phi(a)\phi(b)})\pmod p$$
其中:
$1\le m,n\le 1,000,000$
$\max⁡(m,n)<p\le  1,000,000,007$
并保证$p$为质数

解法:通过观察,容易得到
$$\frac{\phi(ab)}{\phi(a)\phi(b)}=\frac{\gcd(a,b)}{\phi(\gcd(a,b))}$$
故原式等价于
$$\sum\limits_{a=1}^{n}\sum\limits_{b=1}^{m}\sum\limits_{k=1}^{\min(n,m)}[k==\gcd(a,b)]\frac{k}{\phi(k)}=\sum\limits_{k=1}^{\min(n,m)}\frac{k}{\phi(k)}\sum\limits_{a=1}^{n}\sum\limits_{b=1}^{m}[k==\gcd(a,b)]$$

右式等价于统计$a=1-n$与$b=1-m$中最大公因数为$k$的个数,解法很多(如Mobius).

题目保证质数比$n$与$m$大,故直接求逆元最后乘起来即可.

标程复杂度:$O(n\log n + T n\log n )$
