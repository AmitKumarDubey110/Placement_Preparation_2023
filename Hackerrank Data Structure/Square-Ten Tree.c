#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int powtwo(int x)
{
    if (x < 0)
        return 0;
    return 1 << x;
}

void subtract(char *src, char *dst, int start, int end, int borrow)
{
    while (start < end)
    {
        dst[start] += borrow;
        borrow = 0;
        if (src[start] < dst[start])
        {
            src[start] += 10;
            borrow++;
        }
        src[start] -= dst[start];
        dst[start] = 0;
        start++;
    }
}

void add(char *src, char *dst, int start, int end)
{
    int carry = 0;
    while (start < end || carry)
    {
        src[start] += dst[start] + carry;
        dst[start] = 0;
        carry = src[start] / 10;
        src[start] %= 10;
        start++;
    }
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    char a[1048577] = {0}, b[1048577] = {0};
    int A, B, i, j, k, l, m, n;
    short int ansA[25] = {0}, ansB[25] = {0}, countA = 0, countB = 0;
    scanf("%s%s", a, b);
    for (A = -1; a[++A]; a[A] -= '0');
    for (B = -1; b[++B]; b[B] -= '0');
    for (i = -1; ++i < A >> 1; a[i] ^= a[A - i - 1] ^= a[i] ^= a[A - i - 1]);
    for (i = -1; ++i < B >> 1; b[i] ^= b[B - i - 1] ^= b[i] ^= b[B - i - 1]);
    if (A == B)
    {
        while (A && a[A - 1] == b[B - 1])
            a[--A] = b[--B] = 0;
    }
    else
    {
        while (A < B)
            a[A++] = 0;
    }
    if (!A)
    {
        printf("1\n0 1\n");
        return 0;
    }
    n = m = 1;
    while (A > n)
    {
        n <<= 1;
        m++;
    }
    a[0] -= 2;
    l = 0;
    for (i = -1; ++i < m - 1;)
    {
        k = powtwo(i) - powtwo(i - 1);
        for (j = -1; ++j < k; l++)
        {
            a[l] = 9 - a[l];
            a[l + 1] -= a[l] / 10;
            a[l] %= 10;
            ansA[i] = ansA[i] || a[l];
            ansB[i] = ansB[i] || b[l];
        }
        countA += ansA[i];
        countB += ansB[i];
    }
    i = powtwo(m - 2);
    subtract(b, a, i, A, 1);
    for (i--; ++i < A;)
        ansB[m - 1] = ansB[m - 1] || b[i];
    countB += ansB[--m];
    while (!ansA[m] && !ansB[m])
        m--;
    if (ansA[m] == ansB[m])
    {
        ansA[m] = 0;
        countA--;
        add(b, a, powtwo(m - 1), powtwo(m));
    }
    printf("%d", countA + countB);
    for (i = -1; ++i <= m;)
    {
        if (ansA[i])
        {
            printf("\n%d ", i);
            k = powtwo(i);
            j = powtwo(i - 1);
            while (!a[--k]);
            while (k >= j)
                printf("%c", '0' + a[k--]);
        }
    }
    while (m >= 0 && !ansB[m])
        m--;
    if (m >= 0)
    {
        printf("\n%d ", m);
        k = powtwo(m);
        j = powtwo(m - 1);
        while (!b[k])
            k--;
        while (k >= j)
            printf("%c", '0' + b[k--]);
        while (m--)
        {
            if (ansB[m])
            {
                printf("\n%d ", m);
                k = powtwo(m);
                j = powtwo(m - 1);
                while (!b[--k]);
                while (k >= j)
                    printf("%c", '0' + b[k--]);
            }
        }
    }
        
    return 0;
}
