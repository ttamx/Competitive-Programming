#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int K=1000;
const int M=1e5+3;
const int Q=1e4+5;

int n,q;
int a[N];
tuple<int,int,int,int,int> qr[Q];
int ans[Q];
int inv[M],cnt[M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> q;
	for(int i=0;i<n;i++){
		cin >> a[i];
	}
	inv[1]=1;
	for(int i=2;i<M;i++){
		inv[i]=M-1LL*(M/i)*inv[M%i]%M;
	}
	for(int i=1;i<=q;i++){
		auto &[op,l,r,b,c]=qr[i];
		cin >> op >> l >> r >> b;
		l--;
		if(op==1){
			cin >> c;
			ans[i]=-1;
		}
	}
	for(int e=0;e<K;e++){
		int b_all=1,c_all=0;
		int L=e*K,R=min((e+1)*K,n);
		for(int i=L;i<R;i++){
			cnt[a[i]]++;
		}
		for(int t=1;t<=q;t++){
			auto [op,l,r,b,c]=qr[t];
			l=max(l,L);
			r=min(r,R);
			if(l>=r)continue;
			if(op==1){
				if(l==L&&r==R){
					c_all=(1LL*c_all*b+c)%M;
					b_all=(1LL*b_all*b)%M;
				}else{
					for(int i=l;i<r;i++){
						cnt[a[i]]--;
						int tar=(1LL*(1LL*a[i]*b_all+c_all)%M*b+c)%M;
						a[i]=(1LL*(tar-c_all+M)*inv[b_all])%M;
						cnt[a[i]]++;
					}
				}
			}else{
				if(l==L&&r==R){
					ans[t]+=cnt[(1LL*(b-c_all+M)*inv[b_all])%M];
				}else{
					for(int i=l;i<r;i++){
						if((1LL*a[i]*b_all+c_all)%M==b){
							ans[t]++;
						}
					}
				}
			}
		}
		for(int i=L;i<R;i++){
			cnt[a[i]]--;
		}
	}
	for(int i=1;i<=q;i++){
		if(ans[i]!=-1){
			cout << ans[i] << "\n";
		}
	}
}