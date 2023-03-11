#include<bits/stdc++.h>

using namespace std;

long long n,m;
long long ans=0;
set<pair<long long,long long>> s;

long long calc(long long i){
	if(s.empty())return 0ll;
	auto it=s.lower_bound({i,0ll});
	long long mx;
	if(it==s.begin()){
		mx=it->second-abs(it->first-i);
	}else if(it==s.end()){
		mx=prev(it)->second-abs(prev(it)->first-i);
	}else{
		mx=max(it->second-abs(it->first-i),prev(it)->second-abs(prev(it)->first-i));
	}
	return max(0ll,mx);
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for(int i=0;i<m;i++){
		long long a,b,c;
		cin >> a >> b >> c;
		if(s.empty()){
			s.insert({a,c});
			s.insert({b,c});
			ans=c;
		}else{
			long long mxa=calc(a);
			long long mxb=calc(b);
			if(!s.empty()){
				auto it=s.lower_bound({b,0ll});
					while(it!=s.end()&&mxa+c-abs(b-it->first)>=it->second){
						it=s.erase(it);
					}
					it=s.lower_bound({b,0ll});
					if(it!=s.begin()){
						it=prev(it);
						while(mxa+c-abs(b-it->first)>=it->second){
							it=s.erase(it);
							if(it==s.begin())break;
							it=prev(it);
						}
					}
			}
			if(!s.empty()){
				auto it=s.lower_bound({a,0ll});
					while(it!=s.end()&&mxb+c-abs(a-it->first)>=it->second){
						it=s.erase(it);
					}
					it=s.lower_bound({a,0ll});
					if(it!=s.begin()){
						it=prev(it);
						while(mxb+c-abs(a-it->first)>=it->second){
							it=s.erase(it);
							if(it==s.begin())break;
							it=prev(it);
						}
					}
			}
			if(mxa+c>mxb){
				s.insert({b,mxa+c});
				ans=max(ans,mxa+c);
			}
			if(mxb+c>mxa){
				s.insert({a,mxb+c});
				ans=max(ans,mxb+c);
			}
		}
		cout << ans << '\n';
	}
}