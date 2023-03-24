#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        b[i]=a[i];
    }
    sort(b.begin(),b.end());
    map<int,int> cnt[2];
    for(int i=0;i<n;i++)cnt[i&1][b[i]]++;
    for(int i=0;i<n;i++){
        if(cnt[i&1][a[i]]==0)return void(cout << "NO\n");
        cnt[i&1][a[i]]--;
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}