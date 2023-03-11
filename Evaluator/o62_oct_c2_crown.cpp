#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
long long a[N];
long long sum,ans=-1;
vector<long long> range,peak,dif;

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	range.emplace_back(0);
	for(int i=1;i<=n;++i){
		cin >> a[i];
		if(a[i]==0)range.emplace_back(i);
	}
	range.emplace_back(n+1);
	for(int idx=1;idx<range.size();++idx){
	long long st=range[idx-1]+1,ed=range[idx]-1;
	if(ed-st+1<3)continue;
	sum=0;
	for(int i=st;i<=ed;++i)sum+=a[i];
	for(int i=st;i<=ed;++i){
		if(a[i]>a[i-1]){
			int l=i-1;
			while(a[i]==a[i+1]){
				++i;
			}
			if(a[i]>a[i+1]){
			peak.emplace_back(i);
			dif.emplace_back(1ll*(i-l)*min(a[i]-a[l],a[i]-a[i+1]));
		}
		}
	}
	sort(dif.begin(),dif.end());
	if(peak.size()==2)sum=sum;
	else if(peak.size()>2){
		for(int i=0;i<peak.size()-2;++i){
			sum-=dif[i];
		}
	}else{
		long long mn=1e18;
		for(int i=st;i<=ed;++i){
			if(a[i-1]<=1||a[i]<=1||a[i+1]<=1)continue;
			mn=min(mn,a[i]-min(a[i-1],a[i+1])+1);
		}
		sum-=mn;
	}
	ans=max(ans,sum);
	}
	cout << ans;
}