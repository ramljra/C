#include<stdio.h>

// Macro to find maximum of three numbers
#define MAX(a, b, c) ((a > b && a > c) ? a : (b > c ? b : c))

int main()
{
    int x, y, z;

    printf("Enter three numbers: ");
    scanf("%d %d %d", &x, &y, &z);

    printf("Maximum = %d", MAX(x, y, z));

    return 0;
}
