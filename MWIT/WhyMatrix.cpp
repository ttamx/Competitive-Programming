#include<bits/stdc++.h>

using namespace std;

const long long mod=1e9+7;

long long n,q;

struct mat{
	long long a[2][2]={};
	friend mat operator *(mat x,mat y){
		mat z;
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				for(int k=0;k<2;k++){
					z.a[i][j]+=(x.a[i][k]*y.a[k][j])%mod;
                    z.a[i][j]%=mod;
				}
			}
		}
		return z;
	}
};

long long calc(long long n){
	mat ans,tmp;
	tmp.a[0][0]=tmp.a[0][1]=tmp.a[1][0]=1;
	ans.a[0][0]=ans.a[1][1]=1;
	while(n){
		if(n&1){
			ans=ans*tmp;
		}
		tmp=tmp*tmp;
		n>>=1;
	}
	return ans.a[1][0];
}

void runcase(){
	long long c;
	cin >> c;
	cout << calc(c) << '\n';
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> q;
	while(q--)runcase();
}
