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
//Aproach 2
/*
#include<stdio.h>

// Macro for max of two numbers
#define MAX2(a, b) ((a) > (b) ? (a) : (b))

// Macro for max of three numbers using MAX2
#define MAX3(a, b, c) (MAX2(MAX2(a, b), c))

int main()
{
    int x, y, z;

    printf("Enter three numbers: ");
    scanf("%d %d %d", &x, &y, &z);

    printf("Maximum = %d", MAX3(x, y, z));

    return 0;
}

*/
//Approach 3
/*
#include<stdio.h>

inline int max3(int a, int b, int c)
{
    return (a > b && a > c) ? a : (b > c ? b : c);
}

int main()
{
    int x, y, z;

    printf("Enter three numbers: ");
    scanf("%d %d %d", &x, &y, &z);

    printf("Maximum = %d", max3(x, y, z));

    return 0;
}
*/
//Approach 4
/*
#include<stdio.h>

// Macro to get max of two numbers
#define MAX2(a, b) ((a) > (b) ? (a) : (b))

int main()
{
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d numbers:\n", n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int max = arr[0];

    for(i = 1; i < n; i++)
    {
        max = MAX2(max, arr[i]);
    }

    printf("Maximum = %d", max);

    return 0;
}
*/
//Approach 4
/*
//using verdiac macros
#include<stdio.h>
#include<stdarg.h>

// Function to handle n numbers
int maxN(int count, ...)
{
    va_list args;
    va_start(args, count);

    int max = va_arg(args, int);

    for(int i = 1; i < count; i++)
    {
        int num = va_arg(args, int);
        if(num > max)
            max = num;
    }

    va_end(args);
    return max;
}

// Macro wrapper
#define MAXN(count, ...) maxN(count, __VA_ARGS__)

int main()
{
    printf("Maximum = %d", MAXN(5, 10, 25, 7, 99, 3));
    return 0;
}
*/

//Approach 5 Bitwise
/*
#include<stdio.h>

// Bitwise max and min
//#define MAX(a, b) ((a) ^ (((a) ^ (b)) & -((a) < (b))))
//#define MIN(a, b) ((b) ^ (((a) ^ (b)) & -((a) < (b))))


// Extract sign bit (assuming 32-bit int) with out < 
#define SIGN(x) ((x) >> 31)

// Max and Min using bitwise only
#define MAX(a, b) ((a) - (((a) - (b)) & SIGN((a) - (b))))
#define MIN(a, b) ((b) + (((a) - (b)) & SIGN((a) - (b))))

int main()
{
    int a = 10, b = 25;

    printf("Max = %d\n", MAX(a, b));
    printf("Min = %d\n", MIN(a, b));

    return 0;
}
*/
