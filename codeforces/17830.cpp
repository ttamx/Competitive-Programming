#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a;
    vector<int> cnt(101);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    int mx=0;
    for(int i=100;i>0;i--){
        if(cnt[i]){
            cnt[i]--;
            mx=i;
            a.push_back(i);
            break;
        }
    }
    bool ok=false;
    for(int i=mx-1;i>0;i--){
        if(cnt[i]){
            cnt[i]--;
            a.push_back(i);
            ok=true;
            break;
        }
    }
    if(!ok){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for(int i=100;i>0;i--){
        while(cnt[i]){
            cnt[i]--;
            a.push_back(i);
        }
    }
    for(auto x:a)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}