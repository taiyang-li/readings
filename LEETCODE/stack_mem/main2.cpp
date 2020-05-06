#include <stdio.h>

int main() {
    int c = 1;
    int a[8];
    int b = 10;

    a[8] = 11;
    printf("%d\n", c);

    printf("%lu\n", a);
    printf("%lu\n", &c);
    printf("%lu\n", &a[8]);
    return 0;
}
