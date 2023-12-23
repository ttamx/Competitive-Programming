#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long a,b,c;
    cin >> a >> b >> c;
    long long sum=a+b+c;
    for(int i=3;i<=6;i++){
        if(sum%i)continue;
        long long tar=sum/i;
        if(a%tar)continue;
        if(b%tar)continue;
        if(c%tar)continue;
        return void(cout << "YES\n");
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}