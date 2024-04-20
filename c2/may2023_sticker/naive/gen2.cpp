#include<bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int x){
    return rng()%x;
}

int rnd(int l,int r){
    return l+rnd(r-l+1);
}

double rand_double(){
    double res=1;
    for(int t=0;t<3;t++){
        res=(res*rnd(1024))/1024;
    }
    return res;
}

void gencase(int test_num,bool optimize){
    string name=to_string(test_num);
    if(name.size()<2)name='0'+name;
    ifstream fin("../test/"+name+".in");
    int n,m,k,full_score;
    fin >> n >> m >> k >> full_score;
    vector<int> h(k),w(k),v(k),a(k),b(k);
    vector<vector<int>> id(11);
    vector<vector<vector<int>>> cnt(11,vector<vector<int>>(n,vector<int>(m)));
    int score=0;
    auto gen_pos=[&](int i){
        a[i]=rnd(0,n-h[i]);
        b[i]=rnd(0,m-w[i]);
    };
    auto add=[&](int idx){
        for(int t=v[idx];t>0;t--){
            for(int i=0;i<h[idx];i++)for(int j=0;j<w[idx];j++){
                if(++cnt[t][i+a[idx]][j+b[idx]]==1){
                    score++;
                }
            }
        }
    };
    auto del=[&](int idx){
        for(int t=v[idx];t>0;t--){
            for(int i=0;i<h[idx];i++)for(int j=0;j<w[idx];j++){
                if(--cnt[t][i+a[idx]][j+b[idx]]==0){
                    score--;
                }
            }
        }
    };
    for(int i=0;i<k;i++){
        fin >> h[i] >> w[i] >> v[i];
        id[v[i]].emplace_back(i);
    }
    if(optimize){
        // ifstream ffin("optsol/"+name+".txt");
        ifstream ffin("sol/output_"+name+".txt");
        for(int i=0;i<k;i++){
            int j;
            ffin >> j;
            j--;
            ffin >> a[j] >> b[j];
        }
    }else{
        for(int i=0;i<k;i++)gen_pos(i);
    }
    for(int i=0;i<k;i++)add(i);
    int max_score=score;
    auto ans_a=a,ans_b=b;
    auto ans_cnt=cnt;
    auto backup=[&](){
        ofstream fout("sol/output_"+name+".txt");
        for(int t=1;t<=10;t++){
            for(auto i:id[t]){
                fout << i+1 << " " << ans_a[i] << " " << ans_b[i] << "\n";
            }
        }
    };
    auto reset=[&](){
        cout << "-- RESET --\n";
        score=max_score;
        a=ans_a,b=ans_b;
        cnt=ans_cnt;
    };
    cout << "starting with " << max_score << endl;
    for(int temp=10000000,counter=0;temp>0;temp--){
        int idx=rnd(k);
        int oa=a[idx],ob=b[idx];
        int old_score=score;
        del(idx);
        gen_pos(idx);
        add(idx);
        int new_score=score;
        if(new_score>max_score){
            cout << "(" << temp << ") " << max_score << " -> " << new_score << endl;
            max_score=new_score;
            ans_a=a,ans_b=b;
            ans_cnt=cnt;
            backup();
            counter=0;
            continue;
        }
        if(++counter==10000){
            reset();
            counter=0;
        }
        double dif=new_score-old_score;
        if(rand_double()>=exp(dif/temp)){
            continue;
        }
        del(idx);
        a[idx]=oa,b[idx]=ob;
        add(idx);
    }
    cout << "score : " << max_score << " / " << full_score << endl;
    cout << endl;
}

int main(){
    gencase(1,false);
}