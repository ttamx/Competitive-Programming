#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
int a[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        int s,e;
        cin >> s >> e;
        a[s]++,a[e]--;
    }
    for(int i=1;i<N;i++)a[i]+=a[i-1];
    int ans=0;
    for(int i=0;i<N;i++)if(a[i]>a[ans])ans=i;
    cout << (a[ans]==n?"yes":"no") << " " << ans << "\n";
}