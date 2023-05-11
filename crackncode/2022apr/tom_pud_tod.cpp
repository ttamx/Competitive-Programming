#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int cnt=0;
    deque<int> s;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(!s.empty()&&s.front()==x){
            s.pop_front();
            cnt++;
        }else if(s.size()>1&&s[0]!=s[1]&&s[0]!=x&&s[1]!=x){
            s.pop_front();
            s.pop_front();
            cnt++;
        }else{
            s.emplace_front(x);
        }
    }
    if(s.empty()){
        cout << "Yes\n";
        cout << cnt << "\n";
    }else{
        cout << "No\n";
        cout << cnt << "\n";
        cout << s.size() << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}