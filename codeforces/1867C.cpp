#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int mex=n;
    for(int i=n-1;i>=0;i--)if(a[i]!=i)mex=i;
    cout << mex << endl;
    while(true){
        int x;
        cin >> x;
        if(x==-1)break;
        cout << x << endl; 
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}