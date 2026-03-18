#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    auto ask_xor=[&](int i,int j){
        cout << "XOR " << i+1 << " " << j+1 << endl;
        int res;
        cin >> res;
        return res;
    };
    auto ask_and=[&](int i,int j){
        cout << "AND " << i+1 << " " << j+1 << endl;
        int res;
        cin >> res;
        return res;
    };
    vector<int> a(n);
    for(int i=1;i<n;i++){
        a[i]=ask_xor(0,i);
    }
    vector<int> pos(n,-1);
    pos[0]=0;
    a[0]=-1;
    for(int i=1;i<n;i++){
        if(pos[a[i]]==-1){
            pos[a[i]]=i;
        }else{
            a[0]=a[i]^(ask_and(pos[a[i]],i));
            break;
        }
    }
    if(a[0]==-1){
        int p1=find(a.begin(),a.end(),n-1)-a.begin();
        int p2=p1==1?2:1;
        int s=(a[p1]^a[p2])+2*ask_and(p1,p2);
        a[0]=(a[p1]+a[p2]+s)/2+ask_and(0,p2)-s;
    }
    for(int j=1;j<n;j++){
        a[j]^=a[0];
    }
    cout << "!";
    for(auto x:a){
        cout << " " << x;
    }
    cout << endl;
}