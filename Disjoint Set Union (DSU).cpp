/*
1) Initialize:  DSU dsu(n);     --->   O(n)

2) Operations:
        - dsu.Merge(x, y)      -> unite two sets (returns true if merged)   --->  ≈ O(1)
        - dsu.sameGroup(x, y)  -> check if x and y are in same set          --->  ≈ O(1)
        - dsu.getSize(x)       -> get size of the set containing x          --->  ≈ O(1)
*/


struct DSU {
    vector <int> parent , group; int sz;

    DSU (int n) {
        parent = vector <int> (n + 1); sz = n;
        group = vector <int> (n + 1 , 1);
        iota(all(parent) , 0);    //initially each node is its own parent
    }

    // Find leader of the set with path compression
    int getLeader (int x) {
        if (parent[x] == x) return x;
        return parent[x] = getLeader(parent[x]);
    }


    // Union by size (merge two sets)
    bool Merge (int x, int y) {
        int Leader1 = getLeader(x), Leader2 = getLeader(y);
        if (Leader1 == Leader2) return 0;

        if (group[Leader1] > group[Leader2]) swap(Leader1, Leader2);

        parent[Leader1] = Leader2;
        group[Leader2] += group[Leader1];

        return 1;  //merged successfully
    }


    // Check if two nodes are in the same set
    bool sameGroup (int x, int y) {
        return getLeader(x) == getLeader(y);
    }


    // Get size of the set containing x
    int getSize (int x) {
        return group[getLeader(x)];
    }
};

