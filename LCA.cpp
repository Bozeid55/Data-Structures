const int lg = 30;
vector <int> adj[N];
long long anc[N][lg] , lvl[N];

struct LCA {

    void BuildAncestors (int node , int par) {
        lvl[node] = lvl[par] + 1;
        anc[node][0] = par;

        for (int i = 1 ; i < lg ; i++) {
            anc[node][i] = anc[anc[node][i - 1]][i - 1];
        }

        for (auto i : adj[node]) {
            if (i != par) {
                BuildAncestors(i , node);
            }
        }
    }

    int KthAncestor (int node , int k) {
        for (int i = lg - 1 ; i >= 0 ; i--) {
            if ((k >> i) & 1) {
                node = anc[node][i];
            }
        }

        return node;
    }

    int lca (int x , int y) {
        if (lvl[x] < lvl[y]) swap(x , y);
        x = KthAncestor(x , lvl[x] - lvl[y]);

        if (x == y) return x;

        for (int i = lg - 1 ; i >= 0 ; i--) {
            if (anc[x][i] != anc[y][i]) {
                x = anc[x][i]; y = anc[y][i];
            }
        }

        return anc[x][0];
    }

    int distance2nodes (int x , int y) {
        int curLca = lca(x , y);
        return lvl[x] + lvl[y] - (2 * lvl[curLca]);
    }

};
