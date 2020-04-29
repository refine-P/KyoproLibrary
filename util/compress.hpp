//引数unzipには圧縮前のvectorを入れる
int compress(vector<ll>& unzip, map<ll, int>& zip) {
    sort(unzip.begin(), unzip.end());
    unzip.erase(unique(unzip.begin(), unzip.end()), unzip.end());
    for (int i = 0; i < unzip.size(); i++) {
        zip[unzip[i]] = i;
    }
    return unzip.size();
}
