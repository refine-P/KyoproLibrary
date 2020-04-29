struct SqrtDecomposition {
    const int sqrtN = 512;
    int N, K;
    vector<int> data;
    vector<int> bucket;

    SqrtDecomposition(int n) : N(n) {
        K = (N + sqrtN - 1) / sqrtN;
        data.assign(K * sqrtN, 0);
        bucket.assign(K, 0);
    }

    void point_query(int x, int y) {
        int k = x / sqrtN;
        data[x] += y;
        int sum = 0;
        for (int i = k * sqrtN; i < (k + 1) * sqrtN; ++i) {
            sum += data[i];
        }
        bucket[k] = sum;
    }

    // [x, y)
    int range_query(int x, int y) {
        int sum = 0;
        for (int k = 0; k < K; ++k) {
            int l = k * sqrtN, r = (k + 1) * sqrtN;
            if (r <= x || y <= l) continue;
            if (x <= l && r <= y) {
                sum += bucket[k];
            } else {
                for (int i = max(x, l); i < min(y, r); ++i) {
                    sum += data[i];
                }
            }
        }
        return sum;
    }
};
