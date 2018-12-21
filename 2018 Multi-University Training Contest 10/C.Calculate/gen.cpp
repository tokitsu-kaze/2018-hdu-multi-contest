#include <bits/stdc++.h>

int randint(int x, int y) {
  return x + rand() % (y - x + 1);
}

int T, V;

void exec() {
  int A, B, C;

  printf("%d\n", T);

  while (T --) {
    A = randint(std::max(1.0, V * 0.9), V);
    B = randint(std::max(1.0, V * 0.7), V);
    C = randint(std::max(1.0, V * 0.5), V);

    printf("%d %d %d\n", A, B, C);
  }
}

int main(int argc, char **argv) {
  int cur(1), randval;
#define READ(x) sscanf(argv[cur ++], "%d", &x)
  READ(T), READ(V), READ(randval);
  srand(randval);
  exec();
  return 0;
}
