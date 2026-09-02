#include<bits/stdc++.h>
using namespace std;
vector<array<long long,3>> edges; //
vector<long long> lin;
vector<long long> siz;
vector<vector<array<long long,2>>> mst;
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
    lin.resize(ccount+1);
    siz.resize(ccount+1);
    mst.resize(ccount+1);
    for(int i = 1;i <= ccount;i++){
        lin[i] = i;
        siz[i] = 1;
    }
    sort(edges.begin(),edges.end());
    for(auto u:edges){
        if(!same(u[1],u[2])){
            mst[u[1]].push_back({u[2],u[0]});
            mst[u[2]].push_back({u[1],u[0]});
            uni(u[1],u[2]);
        }
    }
}
long long query(long long u,long long v){
    long long x = C[u];
    long long y = C[v];
    queue<long long> bfs;
    vector<long long> dis(ccount+1,0);
    vector<bool> vis(ccount+1,false);
    bfs.push(x);
    while(!bfs.empty()){
        long long cur = bfs.front();
        if(cur == y)break;
        vis[cur] = true;
        bfs.pop();
        for(auto q:mst[cur]){
            if(vis[q[0]])continue;
            dis[q[0]] = max(dis[cur],q[1]);
            bfs.push(q[0]);
        }
    }
    return dis[y];
}
int main(){
    lettura();
    kruskal();
    long long num_query;
    cin >> num_query;
    while(num_query--){
        long long a,b;
        cin >> a >> b;
        cout << query(a,b) << endl;
    }
}
