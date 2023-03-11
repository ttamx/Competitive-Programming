#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int a,b,c,d,ans,ans1,ans2;
int fac[N];

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> a >> b >> c >> d;
	for(int i=2;i<=d;++i){
		if(fac[i]==0)for(int j=i;j<=d;j+=i)fac[j]=i;
		int val=i,cnt=0;
		while(val>1)val/=fac[val],++cnt;
		int x=b/i*i,y=d/i*i;
		if((x>=a&&y>=c)&&(cnt>ans||(cnt==ans&&(x+y>ans1+ans2||(x+y==ans1+ans2&&x>ans1)))))ans=cnt,ans1=x,ans2=y;
	}
	cout << ans1 << ' ' << ans2;
}