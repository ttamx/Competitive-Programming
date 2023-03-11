#include<bits/stdc++.h>

using namespace std;

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	string a,b;
	cin >> a >> b;
	long long x=0,y=0;
	for(int i=2;i<a.size();i+=3)x*=10,x+=a[i]-'\x90';
	for(int i=2;i<b.size();i+=3)y*=10,y+=b[i]-'\x90';
	long long z=x+y;
	string s="";
	while(z>0){
		char c=(z%10)+'\x90';
		s=c+s;
		s="\xe0\xb9"+s;
		z/=10;
	}
	cout << s;
}