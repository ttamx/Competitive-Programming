#include<bits/stdc++.h>
using namespace std;
long long C(long long n, long long r){
	long long m=n;
	for(int i=1;i<r;i++){
		m*=n-i;
		m/=i+1;
	}
	return m;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
	long long t,n,p,a,b,c;
	cin >> t;
	while(t--){
		cin >> n >> p;
		long long ans=0;
		if(n<p){
			for(long long k=1;k<n+1;k++){
				a=C(n,k);
				a%=p;
				b=pow(k,k);
				b%=p;
				c=pow(n-k+1,n-k-1);
				c%=p;
				ans+=a*b*c;
				ans%=p;
			}
			if(ans>=0) cout << ans << endl;
			else cout << ans+p << endl;
		}
		else{
			for(long long k=p+1;k<n+1;k++){
				ans+=C(n,k)*pow(k,k)*pow(n-k+1,n-k-1);
				ans%=p;
			}
			if(ans>=0) cout << ans << endl;
			else cout << ans+p << endl;
		}
	}
}
