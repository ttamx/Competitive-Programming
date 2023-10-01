#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        a[x]=i;
    }
    if(a[1]<a[n]&&a[2]<a[n]){
        cout << a[n] << " " << max(a[1],a[2]) << "\n";
    }else if(a[1]>a[n]&&a[2]>a[n]){
        cout << a[n] << " " << min(a[1],a[2]) << "\n";
    }else{
        cout << 1 << " " << 1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}