#include<stdio.h>
#define mem(a,v) memset(a,v,sizeof(a))
long int parent[100005],rank[100005],val[100005];
long int find(long int x)
{
	if(parent[x]==x)
	return x;
	return find(parent[x]);
}
void _union(long int x,long int y)
{
	long int vv,dd=find(x);
	long int hh=find(y);
	if(dd!=hh)
	{
	if(rank[hh]>rank[dd])
	{
		parent[dd]=hh;
	val[hh]+=val[dd];
	}
	else if(rank[hh]<rank[dd])
	{
		parent[hh]=dd;
	val[dd]+=val[hh];
	}
	else
	{
	parent[hh]=dd;
	val[dd]+=val[hh];
	rank[dd]++;	
	}
	}
}
int main()
{
	long int c,d,t,i,e;
	char ff[3];

for(i=0;i<=100005;i++)
	{
		parent[i]=i;
		val[i]=1;
		rank[i]=1;
	}
	scanf("%ld%ld",&c,&d);
	for(i=0;i<=c;i++)
	parent[i]=i;
	while(d--)
	{
		scanf("%s",ff);
		if(ff[0]=='M')
		{
		scanf("%ld%ld",&e,&t);
		_union(e,t);
		}
		else
		{
			scanf("%ld",&e);
		printf("%ld\n",val[find(e)]);
		}
	}
	return 0;
}
