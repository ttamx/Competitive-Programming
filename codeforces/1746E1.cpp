#include<bits/stdc++.h>

using namespace std;

int n;

bool ask(set<int> q){
    cout << "? " << q.size();
    for(auto i:q){
        cout << ' ' << i;
    }
    cout << endl;
    string s;
    cin >> s;
    return s=="YES";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    int l=1,r=n;
    set<int> all,v;
    for(int i=1;i<=n;++i)all.insert(i);
    while(ask(all));
    while(l<r){
        int m=(l+r)/2;
        set<int> tmp;
        for(auto it:v)tmp.insert(it);
        for(int i=l;l<=m;++l)tmp.insert(i);
        if(ask(tmp)){
            
            r=m;
        }else{
            l=m+1;
        }
    }
    cout << "! " << l;
    cout << endl;
    cout << "! " << l;
    cout << endl;
}
