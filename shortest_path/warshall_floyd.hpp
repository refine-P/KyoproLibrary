typedef vector<vector<int> > Matrix; //隣接行列

const int INF = 1000000000;

Matrix dist;

//trueなら負の閉路を検出
bool warshall_floyd(int n) { //nは頂点数
    for (int k = 0; k < n; k++) { //経由点
        for (int i = 0; i < n; i++) { //始点
            for (int j = 0; j < n; j++) { //終点
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    //負の閉路を検出
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) return true;
    }
    return false;
}
