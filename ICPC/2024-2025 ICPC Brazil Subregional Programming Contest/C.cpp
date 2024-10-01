#include<bits/stdc++.h>

using namespace std;

using ll = long long;

template<class STR>
struct SuffixArray{
    int n;
    vector<int> sa,isa,lcp;
    SuffixArray(){}
    SuffixArray(const STR &s){init(s);};
    void init(const STR &s){
        n=(int)s.size();
        sa=isa=lcp=vector<int>(n+1);
        sa[0]=n;
        iota(sa.begin()+1,sa.end(),0);
        sort(sa.begin()+1,sa.end(),[&](int i,int j){return s[i]<s[j];});
        for(int i=1;i<=n;i++){
            int x=sa[i-1],y=sa[i];
            isa[y]=i>1&&s[x]==s[y]?isa[x]:i;
        }
        for(int len=1;len<=n;len<<=1){
            vector<int> ps(sa),pi(isa),pos(n+1);
            iota(pos.begin(),pos.end(),0);
            for(auto i:ps)if((i-=len)>=0)sa[pos[isa[i]]++]=i;
            for(int i=1;i<=n;i++){
                int x=sa[i-1],y=sa[i];
                isa[y]=pi[x]==pi[y]&&pi[x+len]==pi[y+len]?isa[x]:i;
            }
        }
        for(int i=0,k=0;i<n;i++){
            for(int j=sa[isa[i]-1];j+k<n&&s[j+k]==s[i+k];k++);
            lcp[isa[i]]=k;
            if(k)k--;
        }
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    SuffixArray sa(a);
    auto lcp=sa.lcp;
    ll num=1LL*n*(n+1)/2;
    ll den=1LL*n*n;
    for(int t=0;t<2;t++){
        stack<pair<int,int>> s;
        ll sum=0;
        for(int i=2;i<=n;i++){
            int cnt=1;
            while(!s.empty()&&s.top().first>lcp[i]){
                auto [h,w]=s.top();
                s.pop();
                sum-=1LL*h*w;
                cnt+=w;
            }
            s.emplace(lcp[i],cnt);
            sum+=1LL*lcp[i]*cnt;
            num+=sum;
        }
        reverse(lcp.begin()+2,lcp.end());
    }
    ll g=gcd(num,den);
    cout << num/g << "/" << den/g << "\n";
}