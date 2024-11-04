#include<bits/stdc++.h>

using namespace std;

const int X=1e7+5;

bool notprime[X];
bool seen[X];
int ans[X];

void runcase(){
    int n;
    cin >> n;
    cout << (ans[n]+(n>=5?1:0)) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int last=-10;
    for(int i=2;i<X;i++){
        ans[i]+=ans[i-1];
        if(notprime[i])continue;
        if(i-last==2)ans[i]++;
        last=i;
        for(int j=i*2;j<X;j+=i){
            notprime[j]=true;
        }
    }
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}