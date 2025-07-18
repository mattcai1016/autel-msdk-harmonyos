// header file for KM algorithm
// ref: https://blog.csdn.net/accelerator_/article/details/39050519

#ifndef KM_H
#define KM_H

namespace DroneFormation {

#define MAX_POINTS 20

class KM {
    const double INF = 1e9;

    double w[MAX_POINTS][MAX_POINTS];
    double l[MAX_POINTS], r[MAX_POINTS], slack[MAX_POINTS];

    int left[MAX_POINTS];
    bool s[MAX_POINTS], t[MAX_POINTS];

    int num;

   public:
    void init(int n) { num = n; }

   public:
    void add_edge(int i, int j, double weight) { w[i][j] = weight; }

    bool dfs(int i);
    void update();
    void solve();

    void get_ans(int index[]);
};

}

#endif
