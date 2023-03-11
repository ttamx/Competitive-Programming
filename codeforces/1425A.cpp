#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n;
    cin >> n;
    long long ans=0;
    while(n>0){
        if(n%2==0 && (n<=4 || (n/2)%2)){
            ans+=n/2;
            n/=2;
        }else{
            n--;
            ans++;
        }
        if(n%2==0 && (n<=4 || (n/2)%2)){
            n/=2;
        }else{
            n--;
        }
    }
    std::cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}