/*
1) Initialize: sparseTable st(n, arr);
2) Preprocess: st.pre();   // builds the table in O(n log n)
3) Queries:
        - st.getAns1(l, r) -> O(log n)
        - st.getAns2(l, r) -> O(1)
*/

struct sparseTable {
    int n , lg;
    vector <vector <long long>> sp; vector <long long> arr;

    sparseTable (int size , vector <ll> &tmp) {
        n = size;
        lg = log2(n) + 1;
        sp.assign(lg , vector <long long> (2 * n));
        arr = tmp;
    }

    //To build SparseTaple
    void pre () {
        for (int i = 0 ; i < n ; i++) sp[0][i] = arr[i];

        for (int i = 1; i < lg ; i++) {
            for (int j = 0 ; j < n ; j++) {
                //You can -> min , max , gcd , AND , OR
                sp[i][j] = min(sp[i - 1][j] , sp[i - 1][j + (1ll << (i - 1))]);
            }
        }
    }

    //To get the minimum in range on O(log n)
    long long getAns1 (int x , int y) {
        int len = (y - x + 1);
        long long ans = oo;

        for (int i = 0 ; i < lg ; i++) {
            if ((len >> i) & 1) {
                //You can change to -> min , max , gcd , AND , OR
                ans = min(ans , sp[i][x]);
                x += (1ll << i);
            }
        }

        return ans;
    }

    //To get the minimum in range on O(1)
    long long getAns2 (int x , int y) {
        int len = (y - x + 1) , Lg = log2(len);

        //You can change to -> min , max , gcd , AND , OR
        return (min(sp[Lg][x] , sp[Lg][y - (1ll << Lg) + 1]));
    }
};
