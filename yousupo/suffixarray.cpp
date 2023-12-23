#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define sz(x) (x).size()

using namespace std;

using vi = vector<int>;

struct suffixarray{
    vi sa,lcp,rank;
    suffixarray(){}
    suffixarray(const string &s){init(s);}
    void init(const string &s){
        int n=sz(s)+1;
        sa=lcp=rank=vi(n);
        iota(1+all(sa),0);sa[0]=n-1;
        sort(1+all(sa),[&](int i,int j){return s[i]<s[j];});
        for(int i=1;i<n;i++){
            int a=sa[i],b=sa[i-1];
            rank[a]=i>1&&s[a]==s[b]?rank[b]:i;
        }
        for(int k=1;k<n;k*=2){
            vi ps(sa),pr(rank),pos(n);
            iota(all(pos),0);
            for(int i:ps)if((i-=k)>=0)sa[pos[rank[i]]++]=i;
            for(int i=1;i<n;i++){
                int a=sa[i],b=sa[i-1];
                rank[a]=pr[a]==pr[b]&&pr[a+k]==pr[b+k]?rank[b]:i;
            }
        }
        for(int i=0,j,k=0;i<n-1;lcp[rank[i++]]=k)
            for(k&&k--,j=sa[rank[i]-1];s[i+k]==s[j+k];k++);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    suffixarray sa(s);
    for(int i=1;i<sz(sa.sa);i++)cout << sa.sa[i] << " ";
}