#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD=964493993;
const ll MOD2=990582799;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll my_rand(){
    return rng()%(MOD-1)+1;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    map<string,int> enc,encv;
    vector<int> a;
    int cur=0,curv=n;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        if(s.size()==1&&isalpha(s[0])){
            if(!encv.count(s)){
                encv[s]=curv++;
            }
            a.emplace_back(encv[s]);
        }else{
            if(!enc.count(s)){
                enc[s]=cur++;
            }
            a.emplace_back(enc[s]);
        }
    }
    vector<ll> hsh(curv);
    for(auto &x:hsh){
        x=my_rand();
    }
    vector<ll> hsh2(curv);
    for(auto &x:hsh2){
        x=my_rand();
    }
    ll mul=359707717;
    ll mul2=174539389;
    set<ll> memo;
    set<ll> memo2;
    for(int i=0;i<n;i++){
        vector<int> id(curv,-1);
        for(int i=0;i<n;i++){
            id[i]=i;
        }
        int cur2=n;
        ll res=0,res2=0;
        for(int j=i;j<n;j++){
            if(id[a[j]]==-1){
                id[a[j]]=cur2++;
            }
            res=(res*mul+hsh[id[a[j]]])%MOD;
            res2=(res2*mul2+hsh2[id[a[j]]])%MOD;
            memo.emplace(res);
            memo2.emplace(res2);
        }
    }
    int q;
    cin >> q;
    while(q--){
        int k;
        cin >> k;
        map<string,int> enc2;
        int cur=n;
        ll res=0,res2=0;
        bool flag=true;
        for(int i=0;i<k;i++){
            string s;
            cin >> s;
            if(s.size()==1&&isalpha(s[0])){
                if(!enc2.count(s)){
                    enc2[s]=cur++;
                }
                res=(res*mul+hsh[enc2[s]])%MOD;
                res2=(res2*mul2+hsh2[enc2[s]])%MOD;
            }else{
                if(!enc.count(s)){
                    flag=false;
                }else{
                    res=(res*mul+hsh[enc[s]])%MOD;
                    res2=(res2*mul2+hsh2[enc[s]])%MOD;
                }
            }
        }
        cout << (flag&&memo.count(res)&&memo2.count(res2)?"yes":"no") << "\n";
    }
}