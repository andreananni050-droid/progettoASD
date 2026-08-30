#include<bits/stdc++.h>
using namespace std;
vector<vector<array<long long,2>>> v;
void build_lista_di_adiacenza(){
    for(auto u:M){ // u è un pair<const array<ll,2>,ll>
        int x = u.first[0];
        int y = u.first[1];
        v[x].push_back({y,u.second});
    }
}
