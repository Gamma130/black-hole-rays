#include <unistd.h>
#include <stdio.h>
#include <math.h>

void ODEfunction(double input[], double output[]);

int main(void)
{
    double X[8] = {0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double output[8];
    ODEfunction(X, output);
    printf("Elements of the array are: ");

    int length = sizeof(output) / sizeof(output[0]);
    for (int i = 0; i < length; i++) {
        printf("%f ", output[i]); 
    }
    return 0;
}


/* ---- Helper: cot(x) ---- */
static inline double cot(double x)
{
    return cos(x) / sin(x);
}

/* ---- dX4 ---- */
double compute_dX_4(double X1, double X4, double X5)
{
    return (X4 * X5) / (X1 * (1.0 - X1));
}

/* ---- dX5 ---- */
double compute_dX_5(double X1, double X2,
                    double X4, double X5,
                    double X6, double X7)
{
    double X1_cubed = X1 * X1 * X1;
    double sinX2 = sin(X2);

    double term1 = ((1.0 - X1) / (2.0 * X1_cubed)) * (X4 * X4);
    double term2 = (1.0 / (2.0 * X1 * (X1 - 1.0))) * (X5 * X5);
    double term3 = (X1 - 1.0) *
                   (X6 * X6 + (sinX2 * sinX2) * (X7 * X7));

    return term1 + term2 + term3;
}

/* ---- dX6 ---- */
double compute_dX_6(double X1, double X2,
                    double X5, double X6, double X7)
{
    return (-2.0 / X1) * X5 * X6
           + sin(X2) * cos(X2) * (X7 * X7);
}

/* ---- dX7 ---- */
double compute_dX_7(double X1, double X2,
                    double X5, double X6, double X7)
{
    return (-2.0 / X1) * X5 * X7
           - 2.0 * cot(X2) * X6 * X7;
}

void ODEfunction(double X[], double dX[])
{

    dX[0] = X[4];
    dX[1] = X[5];
    dX[2] = X[6];
    dX[3] = X[7];

    dX[4] = compute_dX_4(X[1], X[4], X[5]);

    dX[5] = compute_dX_5(X[1], X[2],
                         X[4], X[5],
                         X[6], X[7]);

    dX[6] = compute_dX_6(X[1], X[2],
                         X[5], X[6], X[7]);

    dX[7] = compute_dX_7(X[1], X[2],
                         X[5], X[6], X[7]);
}