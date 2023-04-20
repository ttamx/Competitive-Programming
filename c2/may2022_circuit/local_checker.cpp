#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char ** argv) {
    // vector< pair< string, int> > input_terms;

    int N;
    int M;
    if (argc < 3) {
        printf("%s input solution", argv[0]);
        exit(1);
    }
    
    FILE *finput = fopen(argv[1], "rb");
    
    fscanf(finput, "%d %d", &N, &M);
    std::vector < int> sets( 1<<N);
    for(int i=0;i<(1<<N);i++)
        sets[i] = 2;
    for(int i=0;i<M;i++) {
        int Z; 
        string term;
        term.resize(N);
        int inp;
        int val = 0;
        for(int j=0;j<N;j++) {
            fscanf(finput, "%d", &inp);
            if (inp){
                term[j] = '1';
                //val = (val << 1) | 1;
                val |= 1 << j;
            } else {
                term[j] = '0';
                //val = (val << 1);
            }
        }
        
        fscanf(finput,"%d", &Z);
        sets[val]= Z;
    }
    fclose(finput);
    vector< vector< int >> solvec;
    FILE *fsol = fopen(argv[2], "rb");
    int Nsol;
    fscanf( fsol, "%d", & Nsol);

    //while(fgets(buf, 1024, fsol)!=NULL) 
    // correct format only
    int count = 0;
    for(int i=0;i<Nsol;i++)
    {
        int vecsize;
        fscanf(fsol, "%d ", &vecsize);
        vector<int> vec;
        for(int k=0;k<vecsize;k++) {
            int val;
            fscanf(fsol, "%d ", &val);
            vec.push_back(val);
        }
        solvec.push_back(vec);
    }
    fclose(fsol);

    // Alright, let's check, this will be a bit of bruteforce, eh
    int invalid = 0;
    for(int i=0;i<(1<<N);i++)
    {
        // It's not don't care
        if (sets[i] != 2) {
            int sum = 0;
            
            for(int j=0;j<Nsol;j++) {
                int local_prod = 1; 
                // Eval expression
                for(auto & k : solvec[j]) {
                    
                    int bitw = !!(i & (1<<((abs(k)-1) )));
                    // printf("j, K  %d %d %d\n", j, i, k);
                    if (k>0)
                        local_prod &= bitw;
                    else
                        local_prod &= !bitw;
                }
                sum |= local_prod;
                
                if (sets[i] == 1 && sum)
                    break;
            }
            // printf("A %d %d %d\n", i, sets[i], sum);
            if ((sets[i] == 0 && sum) || (sets[i] == 1 && (sum == 0) )) {
                printf("val:%d need:%d found:%d\n",i,sets[i],sum);
                invalid = 1;
                break;
            }            
        }
    }
    if (invalid) {
        printf("Fail!!\n");
        return 0;
    }
    for(int j=0;j<Nsol;j++) {
        count += solvec[j].size()-1;
    }
    printf("Total %d\n", count + Nsol - 1);

    return 0;
}
/*
g++ -std=c++11 -O2 local_checker.cpp -o local_checker
./local_checker aaa.bbb ccc.ddd
*/