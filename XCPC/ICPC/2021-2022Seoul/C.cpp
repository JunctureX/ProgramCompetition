#include <bits/stdc++.h>

using namespace std;
map<int,int> mp;
int n;

int main()
{
	cin>>n;
	char c;
	int x,k,i;
	for (int i=0;i<n;i++)
	{
	scanf("%d %c %d",&x,&c,&k);
		if (c=='L')
			mp[x]=x-k;
		else
			mp[x]=x+k;

	}
	cin>>i;
	while (mp.find(i)!=mp.end())
	{
		int to=mp[i];
		mp.erase(i);
		i=to;
	}
	cout<<i<<endl;
}