#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

long long int sol(int A, int B)
{
	return (((A & B) ^ (A | B)) & (A ^ B));
}

long long int inter(long long int arr[], int n)
{
	int i,j;
	long long int min1 = 9999999999, min2 = 9999999999, max = -1;
	for(i=0;i<n-1;i++)
	{
			if(sol(arr[i], arr[i+1]) > max)
				max = sol(arr[i], arr[i+1]);
        if(i+2 <= n-1)
            if(arr[i+1] > arr[i] && arr[i+1] > arr[i+2] && sol(arr[i], arr[i+2]) > max)
                max = sol(arr[i], arr[i+2]);
		
	}
	return max;
	
}

int main()
{
    int n,i;
	scanf("%d", &n);
	long long int arr[n];
	for(i=0;i<n;i++)
	{
		scanf("%lli", &arr[i]);
	}
		printf("%lli", inter(arr, n));
    return 0;
}
