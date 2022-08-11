#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
	int n, q;
	int lastans = 0;
	cin >> n >> q;
	vector<vector<int>>sqces(n);
	while (q--)
	{
		int a;
		long long x, y;
		cin >> a >> x >> y;
		long long t = (x^lastans) % n;
		if (a == 1)
		{
			sqces[t].push_back(y);
		}
		else
		{
			long long size = sqces[t].size();
			long long b;
			if (size != 0)
				b = y%size;
			else
				continue;
			cout << sqces[t][b] << endl;
			lastans =sqces[t][b];
		}
	}
	return 0;
}