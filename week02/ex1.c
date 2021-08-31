#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    int _integerVariable = INT_MAX;
    float _floatVariable = FLT_MAX;
    double _doubleVariable = DBL_MAX;

    printf("The size of integer variable is %d bytes, and its value is %d\n", sizeof(_integerVariable), _integerVariable);
    printf("The size of float variable is %d bytes, and its value is %f\n", sizeof(_floatVariable), _floatVariable);
    printf("The size of double variable is %d bytes, and its value is %f\n", sizeof(_doubleVariable), _doubleVariable);

    return 0;
}