#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int da,db;
    string sa,sb;
    cin >> da >> db;
    cin >> sa >> sb;
    ll a=stoll(sa);
    ll b=stoll(sb);
    ll den=1;
    for(int i=0;i<db;i++)den*=10;
    den--;
    ll num=a*den+b;
    for(int i=0;i<da;i++)den*=10;
    ll g=gcd(num,den);
    cout << num/g << " " << den/g << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}