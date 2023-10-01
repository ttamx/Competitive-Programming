#include<bits/stdc++.h>

using namespace std;

string s="KBHY";

int mx[50];
string ans[46]={
"",
"K",
"KK",
"KKB",
"KKBK",
"KKBKK",
"KKBKKB",
"KKBKKBB",
"KKBKKBBH",
"KKBKKBBHH",
"KKBKKBBHHK",
"KKBKKBBHHKK",
"KKBKKBBHHKKB",
"KKBKKBBHHKKBK",
"KKBKKBBHHKKBKK",
"KKBKKBBHHKKBKKB",
"KKBKKBBHHKKBKKBB",
"KKBKKBBHHKKBKKBBH",
"KKBKKBBHHBHBKKBBKK",
"KKBKKBBHHBHBKKBBKKB",
"KKBKKBBHHBHBKKBBKKBH",
"KKBKKBBHHBHKYKKBKBBHK",
"KKBKKBBHHKHHBKBBKBHHKK",
"KKBKKBBHHKHHBKBBKBHHKKH",
"KKBKKBBHHBHKYKKBKBBHKHBB",
"KKBKKBBHHBKBYHKKHHBBHKKBB",
"KKBKKBBHHKKHBBYBBHHYHKKBKK",
"KKBKKBBHHKHHBYBBKBHHKBKHHKK",
"KKBKKBBHHKKBKHYHHYBBHHKBBKBK",
"KKBKKBBHHKYBYBHHKHHBKKBBHKBKB",
"KKBKKBBHHKKHHBBYYBBHHKKHHBKBKK",
"KKBKKBBHHKKBKBBHYHBBHHKYHKYKBBK",
"KKBKKBBHHKKBKBBHYHBBHHKYHKYKBBKK",
"KKBKKBBHHKKHBBYBHHYHHKKBKYBBKKBKB",
"KKBKKBBHHKKBKBBHYHBYHHKYHKKBBKHKBB",
"KKBKKBBHHKKBBHYBHHYYHKKBKKBBHHKKBBH",
"KKBKKBBHHKKBKBHHYYHBYYBBHKKHKBBHKKBK",
"KKBKKBBHHKKBKKBHHYYHHBYYBBHKKHKKBBHBK",
"KKBKKBBHHKKBKKBHHYYHHBYYBBHKKHKKBBHBKK",
"KKBKKBBHHKKHKKYBBHBHHYBBHHYKKYKKBBHBBKK",
"KKBKKBBHHKKBKKBHHYYHHBYYBBHKKHKKBBHHKKBK",
"KKBKKBBHHKKBKKBHHYYHHBYYBBHKKHKKBBHHKKBKK",
"KKBKKBBHHKKBKKBBYYHHYBYHHYHKKBKKHBBHKKBKKB",
"KKBKKBBHHKKBKKBHYYBHHBYYHYHKKBKKBBHHKKBKKBB",
"KKBKKBBHHKKBKKBHYYBHHBYYHYHKKBKKBBHHKKBKKBBH",
"KKBKKBBHHKKBKKBHYYBHHBYYHYHKKBKKBBHHKKBKKBBHY"
};

void runcase(){
    int n;
    cin >> n;
    cout << '"' << ans[n] << '"' << ",\n";
}

long long cnt=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    stack<pair<int,vector<int>>> pq;
    pq.push({0,{}});
    while(!pq.empty()){
        if(++cnt>1e10)break;
        if(cnt%10000000==0)cout << cnt << endl;
        auto [u,v]=pq.top();
        pq.pop();
        int sz=v.size();
        if(u>mx[sz]){
            mx[sz]=u;
            ans[sz]="";
            for(auto x:v)ans[sz].push_back(s[x]);
            cout << sz << " : ";
            cout << ans[sz] << endl;
        }
        if(sz==45)continue;
        bool used[4]={};
        for(int i=1;2*i<=sz;i++)if(v[sz-i]==v[sz-2*i])used[v[sz-i]]=true;
        for(int i=3;i>=0;i--){
            if(used[i])continue;
            v.emplace_back(i);
            pq.push({u+4-i,v});
            v.pop_back();
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}