#include<bits/stdc++.h>
using namespace std;
map<array<long long,2>,long long> M;
map<long long,long long> C;
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
            M[{p[i-1],p[i]}]++;
            M[{p[i],p[i-1]}]++;
        }

    }

}
vector<vector<array<long long,2>>> adj;
void build_lista_di_adiacenza(){
    adj.resize(ccount+1);
    for(auto u:M){ // u è un pair<const array<ll,2>,ll>
        int x = u.first[0];
        int y = u.first[1];
        adj[x].push_back({y,u.second});
    }
}
long long inf = 1e12;
long long query(long long u, long long v){
    long long x = C[u];
    long long y = C[v];
    priority_queue<array<long long,2>> djk;
    vector<long long> dis(ccount+1,inf);
    dis[x] = 0;
    djk.push({0,x});
    while(!djk.empty()){
        array<long long,2> q = djk.top();
        djk.pop();
        if(q[1] == y)return dis[y]; //la prima volta che estraggo y per monotonia dis[y] avrà valore minimo
        if(-q[0] > dis[q[1]])continue;
        for(auto node:adj[q[1]]){
            long long w = max(node[1],-q[0]);
            if(dis[node[0]] > w){
                dis[node[0]] = w;
                djk.push({-w,node[0]});
            }
        }
    }
    return dis[y];
}
int main(){
    lettura();
    build_lista_di_adiacenza();
    long long numero_query;
    cin >> numero_query;
    while(numero_query--){
        long long u,v;
        cin >> u >> v;
        cout << query(u,v) << endl;
    }
}
