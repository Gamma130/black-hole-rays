#include <unistd.h>
#include <stdio.h>

void arrayCalculation(float input[], float output[], int size);

int main(void)
{
    float input[4] = {4, 3, 2, 1};
    float output[4] = {1, 2, 3, 4};
    arrayCalculation(input, output, 4);
    printf("%f\n", output[3]);
    return 0;
}

void arrayCalculation(float input[], float output[], int size)
{
    output[3] = input[3];
}