#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<int> a(n+1);
    vector<long long> even(n+1),odd(n+1),one(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        if(a[i]==1){
            one[i]+=a[i];
        }else if(a[i]==(a[i]&-a[i])){
            even[i]+=a[i];
        }else if(a[i]%2){
            odd[i]+=a[i];
        }
    }
    for(int i=1;i<=n;i++){
        one[i]+=one[i-1];
        even[i]+=even[i-1];
        odd[i]+=odd[i-1];
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        int cnt=one[r]-one[l-1];
        int s1=even[r]-even[l-1]+(cnt+1)/2;
        int s2=odd[r]-odd[l-1]+cnt/2;
        if(s1>s2)cout << "A\n";
        else if(s2>s1)cout << "B\n";
        else cout << "E\n";
    }
}