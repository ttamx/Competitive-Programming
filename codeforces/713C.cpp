#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    multiset<int> ms;
    long long ans=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        x-=i;
        if(!ms.empty()&&x<*ms.rbegin())ans+=*ms.rbegin()-x;
        ms.emplace(x);
        ms.emplace(x);
        ms.erase(prev(ms.end()));
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}