#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct SuffixArray{
    vector<int> sa,isa,lcp;
    void init(const string &s){
        int n=s.size();
        sa=isa=lcp=vector<int>(n+1);
        sa[0]=n;
        iota(sa.begin()+1,sa.end(),0);
        sort(sa.begin(),sa.end(),[&](int i,int j){return s[i]<s[j];});
        for(int i=1;i<=n;i++){
            int x=sa[i-1],y=sa[i];
            isa[y]=i>1&&s[x]==s[y]?isa[x]:i;
        }
        for(int len=1;len<=n;len*=2){
            vector<int> ps(sa),pi(isa),pos(n+1);
            iota(pos.begin(),pos.end(),0);
            for(auto i:ps)
        }
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
}