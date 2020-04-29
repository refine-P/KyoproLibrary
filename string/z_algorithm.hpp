// 各 i について「S と S[i:|S|-1] の最長共通接頭辞の長さ」を記録した配列を O(|S|) で構築
// ex. aaabaaaab
//     921034210
vector<int> z_algorithm(const string& S) {
    vector<int> res(S.size());
    res[0] = S.size();
    int i = 1, j = 0;
    while (i < S.size()) {
        while (i+j < S.size() && S[j] == S[i+j]) ++j;
        res[i] = j;
        if (j == 0) { ++i; continue;}
        int k = 1;
        while (i+k < S.size() && k+res[k] < j) res[i+k] = res[k], ++k;
        i += k; j -= k;
    }
    return res;
}
