#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> b(10);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        for(int i=0;i<10;i++){
            if(x&1)b[i]++;
            x>>=1;
        }
    }
    int mn=0,mx=0;
    for(int i=0;i<10;i++){
        if(b[i]>0)mx+=1<<i;
        if(b[i]==n)mn+=1<<i;
    }
    cout << mx-mn << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}