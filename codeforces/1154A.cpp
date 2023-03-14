#include<bits/stdc++.h>

using namespace std;

void runcase(){
    vector<int> a(4);
    for(auto &x:a)cin >> x;
    for(int i=0;i<4;i++){
        int sum=0;
        for(int j=0;j<4;j++)if(i!=j)sum+=a[j];
        if(sum==2*a[i]){
            for(int j=0;j<4;j++)if(i!=j)cout << a[i]-a[j] << ' ';
            cout << '\n';
            return;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}