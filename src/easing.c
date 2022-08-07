#include <math.h>
#include "easing.h"
double easeOutElastic(double x) {
    const double c4 = (2 * M_PI) / 3;

    return x == 0
      ? 0
      : x == 1
      ? 1
      : pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
}

double easeOutBack(double x){
    const double c1 = 1.70158;
    const double c3 = c1 + 1;

    return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
}

double easeInOutCirc(double x){
return x < 0.5
  ? (1 - sqrt(1 - pow(2 * x, 2))) / 2
  : (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
}
