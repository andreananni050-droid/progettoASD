#include<bits/stdc++.h>
using namespace std;
vector<array<long long,3>> edges; //
vector<long long> lin;
vector<long long> siz;
vector<long long> weight;
vector<long long> depth;
vector<long long> roots;
vector<array<long long,20>> parent;
map<long long,long long> C;
map<array<long long,2>,long long> M;
long long ccount = 1;
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
        for(int i = 0;i < len;i++){
            if(!C[p[i]])C[p[i]] = ccount++;
            p[i] = C[p[i]];
        }
        for(int i = 1;i < len;i++){
            if(p[i-1] > p[i])M[{p[i-1],p[i]}]++;
            else M[{p[i],p[i-1]}]++;
        }
    }
    for(auto u:M){
        edges.push_back({u.second,u.first[0],u.first[1]});
    }
}
long long fin(long long x){
    while(x != lin[x])x = lin[x];
    return x;
}
bool same(long long x, long long y){
    return fin(x) == fin(y);
}
void uni(long long x,long long y){
    x = fin(x);
    y = fin(y);
    if(siz[x] < siz[y])swap(x,y);
    lin[y] = x;
    siz[x]+=siz[y];
}
void kruskal(){
    lin.resize(2*ccount+1);
    siz.resize(2*ccount+1);
    depth.resize(2*ccount+1);
    weight.resize(2*ccount+1);
    parent.resize(2*ccount+1);
    roots.resize(2*ccount+1);
    for(int i = 1;i <= 2*ccount-1;i++){
        lin[i] = i;
        siz[i] = 1;
        roots[i] = i;
    }
    sort(edges.begin(),edges.end());
    for(auto u:edges){
        if(!same(u[1],u[2])){
            long long x = fin(u[1]);
            long long y = fin(u[2]);
            parent[roots[x]][0] = ccount;
            parent[roots[y]][0] = ccount;
            uni(x,ccount);
            uni(y,ccount);
            roots[fin(ccount)] = ccount; //ccount è la radice nell'albero costruito contenente x,y per ora
            weight[ccount] = u[0];
            ccount++;
        }
    }
    long long root = ccount-1;
    depth[root] = 0;
    for(int i = root-1;i > 0;i--){
        depth[i] = depth[parent[i][0]]+1;
    }
}
void lca_preprocessing();
long long lca(long long u,long long v);
long long query(long long u, long long v);
int main(){
    lettura();
    kruskal();
    lca_preprocessing();
    long long num_query;
    cin >> num_query;
    while(num_query--){
        long long a,b;
        cin >> a >> b;
        cout << query(a,b) << endl;
    }
}
