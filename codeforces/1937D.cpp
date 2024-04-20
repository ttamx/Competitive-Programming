#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<ll> ans(n);
    for(int t=0;t<2;t++){
    deque<int> dq,dqr,dql;
    ll suml=0,sumr=0;
    for(int i=0;i<n;i++)if(s[i]=='<')dq.emplace_back(i);
        for(int i=0,p=-1;i<n;i++){
            if(s[i]=='<'){
                p=i;
                while(!dqr.empty()&&dqr.front()<=p){
                    sumr-=dqr.front();
                    dqr.pop_front();
                }
                s[i]='>';
            }else{
                dql.emplace_back(i);
                suml+=i;
                while(!dq.empty()&&dql.size()>dqr.size()){
                    int j=dq.front();
                    dq.pop_front();
                    if(j<=p)continue;
                    dqr.emplace_back(j);
                    sumr+=j;
                }
                while(dql.size()-dqr.size()>1){
                    suml-=dql.front();
                    dql.pop_front();
                }
                ans[i]=sumr*2-suml*2+i+(dql.size()==dqr.size()?1:n);
                s[i]='<';
            }
        }
        reverse(s.begin(),s.end());
        reverse(ans.begin(),ans.end());
    }
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}