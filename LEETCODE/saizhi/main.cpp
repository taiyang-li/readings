#include <iostream>
#include <cmath>

double get_win_probility(double p, int n) {
    double q = 1.0 - p;
    double sum = 0.0;
    double tmp = 1.0;
    for (size_t i=0; i<=n; ++i) {
        sum += tmp;
        tmp *= q * (1.0 + n/(1.0+i));
    }
    return sum * std::pow(p, n+1);
}

int main() {
    double p = 0.51;
    for (int n=1; n<=2000; ++n) {
        std::cout << n << " " << get_win_probility(p, n) << std::endl;
    }
    return 0;
}


