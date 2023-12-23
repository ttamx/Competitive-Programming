#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int s1,s2;
    cin >> s1 >> s2;
    int s=(s1^s2)&1;
    set<int> pos[2];
    vector<int> p(n+2);
    for(int i=1;i<=n;i++){
        int a,b;
        cin >> a >> b;
        p[i]=(a^b)&1;
        pos[p[i]].emplace(i);
    }
    auto del=[&](int i){
        pos[p[i]].erase(i);
    };
    int t;
    if(pos[s^1].size()<=n/2){
        cout << "First" << endl;
        t=1;
    }else{
        cout << "Second" << endl;
        t=0;
    }
    s^=t;
    for(int i=1;i<=n;i++){
        if((i&1)==t){
            int p;
            if(!pos[s].empty())p=*pos[s].begin();
            else p=*pos[s^1].begin();
            cout << p << endl << "\n";
            del(p);
        }else{
            int p;
            cin >> p;
            del(p);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}