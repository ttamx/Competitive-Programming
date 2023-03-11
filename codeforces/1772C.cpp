#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> k >> n;
    int num=1;
    for(int i=0;i<k;i++){
        if(num+k-1<=n)num+=i;
        else if(i)num++;
        cout << num << ' ';
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}