#include<bits/stdc++.h>
using namespace std;
map<array<long long,2>,long long> M;

void lettura(){
    vector<long long> p;
    string filename = "19980101.all-paths";
    ifstream myfile(filename);

    string testa, path, coda;
    string num;

    while(getline(myfile, testa, ' ')) {
        getline(myfile, path, ' ');
        stringstream ss(path);
        p.clear();
        while(getline(ss, num, '|')) {
            p.push_back(stoll(num));
        }
        getline(myfile, coda);
        long long len = p.size();
        for(int i = 1;i < len;i++){
            M[{p[i-1],p[i]}]++;
            M[{p[i],p[i-1]}]++;
        }
    }

}
