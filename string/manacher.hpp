// 各 i について「文字 i を中心とする最長の回文の半径」を記録した配列を O(|S|) で構築
// 半径: (全長+1)/2
// ex. abaaababa
//     121412321
// ※普通にやると奇数長の回文しか検出できないが、
//   "a$b$a$a$b"のようにダミー文字を挟むと偶数長の回文も検出可能
vector<int> manacher(const string& S) {
    vector<int> res(S.size());
    int i = 0, j = 0;
    while (i < S.size()) {
        while (i-j >= 0 && i+j < S.size() && S[i-j] == S[i+j]) ++j;
        res[i] = j;
        int k = 1;
        while (i-k >= 0 && i+k < S.size() && k+res[i-k] < j) res[i+k] = res[i-k], ++k;
        i += k; j -= k;
    }
    return res;
}
