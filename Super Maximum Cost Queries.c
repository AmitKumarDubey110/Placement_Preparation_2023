#include <stdio.h>

static long long int a[100000][3], parent[100001], n;
void mer(int p, int q, int r)
{
	static int le[100001][3], ri[100001][3], i, j, k;
	int n1 = q - p + 1, n2 = r - q;
	for (i = 0; i<n1; i++)
	{
		le[i][0] = a[p + i][0];
		le[i][1] = a[p + i][1];
		le[i][2] = a[p + i][2];
	}
	for (j = 0; j<n2; j++)
	{
		ri[j][0] = a[q + j + 1][0];
		ri[j][1] = a[q + j + 1][1];
		ri[j][2] = a[q + j + 1][2];
	}
	le[n1][2] = ri[n2][2] = 1000000001;
	i = j = 0;
	for (k = p; k <= r; k++)
	{
		if (le[i][2] <= ri[j][2])
		{
			a[k][0] = le[i][0];
			a[k][1] = le[i][1];
			a[k][2] = le[i][2];
			i++;
		}
		else
		{
			a[k][0] = ri[j][0];
			a[k][1] = ri[j][1];
			a[k][2] = ri[j][2];
			j++;
		}
	}
}
void merge_sort(int p, int r)
{
	int q;
	if (p<r)
	{
		q = (p + r) / 2;
		merge_sort(p, q);
		merge_sort(q + 1, r);
		mer(p, q, r);
	}
}

int getParent(int x)
{
	if (x == parent[x])
		return x;
	parent[x] = getParent(parent[x]);
	return parent[x];
}

int bin_search(int x)
{
	int low, mid, upp;
	low = 0;
	upp = n;
	mid = (low + upp) / 2;
	while (low<upp)
	{
		if (x<a[mid][2])
		{
			upp = mid - 1;
		}
		else if (x>a[mid][2])
		{
			if (x >= a[mid + 1][2])
				low = mid + 1;
			if (x<a[mid + 1][2])
				break;
		}
		else
		{
			break;
		}
		mid = (low + upp) / 2;
	}
	return mid;
}

int main() {
	static long long int q, count[100001], i, j, k, x, y, z, px, py;
	scanf("%lld%lld", &n, &q);
	for (i = 1; i<n; i++)
	{
		parent[i] = i;
		count[i] = 1;
		scanf("%lld%lld%lld", &a[i][0], &a[i][1], &a[i][2]);
	}
	parent[i] = i;
	count[i] = 1;
	merge_sort(1, n - 1);
	for (i = 1; i<n; i++)
	{
		x = a[i][0];
		y = a[i][1];
		px = getParent(x);
		py = getParent(y);
		a[i][0] = count[px] * count[py];
		if (count[px] >= count[py])
		{
			count[px] += count[py];
			parent[py] = px;
		}
		else
		{
			count[py] += count[px];
			parent[px] = py;
		}
	}
	for (i = 2, j = 1; i<n; i++)
	{
		if (a[j][2] == a[i][2])
		{
			a[j][0] += a[i][0];
		}
		else
		{
			j++;
			a[j][0] = a[i][0] + a[j - 1][0];
			a[j][2] = a[i][2];
		}
	}
	n = j;
	while (q--)
	{
		scanf("%lld%lld", &x, &y);
		px = bin_search(x - 1);
		py = bin_search(y);
		printf("%lld\n", a[py][0] - a[px][0]);
	}
	return 0;
}
