using namespace std;
#include <algorithm>
#include <cctype>
#include <cmath>
#include <deque>
#include <iomanip>
#include <list>
#include <map>
#include <numeric>
#include <stack>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

#define rep(i, n) for(int i = 0; i < n; i++)
#define rep1(i, begin, end) for(int i = begin; i < end; i++)
#define per(i, n) for(int i = n - 1; i >= 0; i--)
#define all(c) c.begin(), c.end()
#define cout(n) cout << fixed << setprecision(n)
#define si(x) int(x.size())
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vvl vector<vector<ll>>
#define vl vector<ll>
#define vb vector<bool>
#define vvb vector<vector<bool>>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second

constexpr int INF = 1e9 + 7;
constexpr long long LINF = 1e18 + 1;

template <typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template <typename T> bool chmax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template <typename T> bool chmin(T& a, const T& b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

//デバッグ-------------------------------------------------------------------------------
template <typename T> void dv(vector<T>& a) {
    int siz = a.size();
    for (int i = 0; i < siz; i++) cout << a[i] << " ";
    cout << endl;
}

template <typename T> void dvv(vector<vector<T>>& a) {
    int h = a.size();
    int w = a[0].size();
    rep(i, h) {
        rep(j, w) {
            cout << a[i][j];
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

template <class H> void debug(H&& h) {
    cout << h << endl;
    ;
}
template <class H, class... Ts> void debug(H&& h, Ts &&...ts) {
    cout << h << " ";
    debug(forward<Ts>(ts)...);
}
//------------------------------------------------------------------------------

// ライブラリなど
// bound-------------------------------------------------------------------------
// lower_bound:配列に含まれるX以上の"インデックス"を返す、なければ配列外を返す(size)
template <typename T> T LINDEX(T x, vector<T>& A) {
    auto itr = lower_bound(all(A), x);
    T idx = itr - A.begin();
    return idx;
}
// lower_bound:配列に含まれるX以上の"値"を返す。なければ-1を返す
template <typename T> T LVALUE(T x, vector<T>& A) {
    auto itr = lower_bound(all(A), x);
    T value;
    if (itr == A.end())
        value = -1;
    else
        value = *itr;
    return value;
}
// upper_bound:配列に含まれるXより大きい"インデックス"を返す、なければ配列外を返す(size)
template <typename T> T UINDEX(T x, vector<T>& A) {
    auto itr = upper_bound(all(A), x);
    T idx = itr - A.begin();
    return idx;
}
// upper_bound:配列に含まれるXより大きい"値"を返す、なければ-1を返す
template <typename T> T UVALUE(T x, vector<T>& A) {
    auto itr = upper_bound(all(A), x);
    T value;
    if (itr == A.end())
        value = -1;
    else
        value = *itr;
    return value;
}
//------------------------------------------------------------------------------
//二分探索
bool isOK(ll mid) {
    //条件を満たすかどうか
    if (true) {
        return true;
    }
    else {
        return false;
    }
}

//条件を満たす最少の数を返す
//範囲内に条件を満たす場所が存在しない場合-1を返す
// ng、okはどちらも範囲外に設定
//条件を満たす中で最大を求めるときはMAXをNGにMINをOKにする
ll binary_search(ll ng, ll ok) {
    int over1 = ng, over2 = ok;
    while (abs(ok - ng) > 1) {
        ll left = min(ok, ng);
        ll right = max(ok, ng);
        ll mid = left + (right - left) / 2;
        // midが条件を見満たしている間right = mid
        if (isOK(mid)) {
            ok = mid;
        }
        //そうでなければleft = mid
        else {
            ng = mid;
        }
    }
    //条件を満たさない<=left < right<=条件を満たす
    // leftは条件を満たさない最大の数、rightは条件を満たす最少の数
    ll ans = ok;
    //範囲外にある場合の判定
    if (ans == over1 || ans == over2) {
        ans = -1;
    }
    return ans;
}
//------------------------------------------------------------------------------

//最短経路問題---------------------------------------------------------------------------
// ベルマンフォード法
// 負の距離を持つグラフの最短経路を求める
// 負閉路判定
class BellmanFord {
private:
    struct edge {
        int from;
        int to;
        long long cost;
    };
    int v;
    vector<edge> edges;
    vector<long long> dist;
    const long long inf = 1LL << 60;

public:
    // コンストラクタ
    BellmanFord(int n) : v(n), dist(n) { rep(i, n) dist[i] = inf; }
    // 辺の追加
    void add_edge(int v, int u, long long cost) {
        edges.push_back({ v, u, cost });
    }
    // sからの最短経路を求める
    // trueであれば負閉路がある
    bool shortest_path(int s) {
        dist.resize(v, inf);
        dist[s] = 0;
        int cnt = 0;
        while (cnt < v) {
            bool update = false;
            for (auto e : edges) {
                if (dist[e.from] != inf && dist[e.from] + e.cost < dist[e.to]) {
                    dist[e.to] = dist[e.from] + e.cost;
                    update = true;
                }
            }
            if (!update) break;
            cnt++;
        }
        return (cnt == v);
    }

    vector<long long> get_shortest_path() { return dist; }
};

// ダイクストラ法
// 単一始点の最短経路の距離を求める
// 単一始点の最短経路のパスを求める
// 最短路木を作る際に採用した辺を求める
class Dijkstra {
private:
    // 辺の構造体
    struct edge {
        // to->iから隣接している頂点,index->辺のindex, cost->辺の重み
        int to;
        // 辺の頂点のコスト
        long long cost;
        // 辺のindex
        int index;
        edge(int to, long long cost, int index)
            : to(to), cost(cost), index(index) {}
    };
    // 始点
    int s;
    //グラフの定義
    vector<vector<edge>> graph;
    // dist[i] -> sからiまでの距離
    vector<long long> dist;
    // from[i] -> sからiの最短経路に採用した辺のindex
    vector<int> from;
    //　辺の集合
    vector<pair<int, int>> edges;
    // 最短路木を作るための辺のindexの集合
    vector<int> shortest_path_edges;
    // [dist,now,edge_index]
    using dnp = tuple<long long, int, int>;
    long long inf = 1e18 + 1;

public:
    Dijkstra(long long n) : graph(n), dist(n), from(n) {
        rep(i, n) dist[i] = inf;
        rep(i, n) from[i] = -1;
    }
    //辺の追加
    void add_edge(int v, int u, long long cost, int index) {
        edge e(u, cost, index);
        // グラフに辺を追加
        graph[v].push_back(e);
        // 辺の情報を配列でもっておく
        // 無向グラフの場合は一度のみ追加
        if (index == (int)edges.size()) edges.emplace_back(v, u);
    }

    // sを始点に最短経路を求める
    void shortest_path(int s) {
        //小さい順のpriority_queue
        //[dist,now, edge_index]
        priority_queue<dnp, vector<dnp>, greater<dnp>> mpq;
        int n = (int)graph.size();
        // sからのdist,fromを初期化
        dist.resize(n, inf);
        from.resize(n, -1);
        // その頂点が始点なのか到達不可能なのか区別するためにindexを-2で更新
        mpq.push({ 0, s, -2 });

        // 距離が近い順に探索
        while ((int)mpq.size()) {
            // [dist,v,edge_index]
            auto [d, v, ei] = mpq.top();
            mpq.pop();
            if (dist[v] <= d) continue;
            dist[v] = d;
            from[v] = ei;
            if (ei >= 0) shortest_path_edges.push_back(ei);
            // 隣隣接している頂点を見る
            // [to,cost,index]
            for (auto [u, c, i] : graph[v]) {
                // 探索済みならスルー
                if (dist[u] <= d + c) continue;
                // vまでの距離と辺のコストが距離となる
                mpq.emplace(d + c, u, i);
            }
        }
    }

    // 頂点xまでの最短経路の距離を取得
    long long get_dist(int x) { return dist[x]; }

    // 最短路木を作る際に採用する辺を求める
    vector<int> get_shortest_path_edges() { return shortest_path_edges; }

    // 頂点xまでの最短経路が存在するか
    bool is_shortest_path(int x) {
        if (dist[x] != inf)
            return true;
        else
            return false;
    }
    // 頂点sから頂点xにおける最短経路
    // [index,v,u]
    vector<tuple<int, int, int>> get_shortest_path(int x) {
        vector<tuple<int, int, int>> res;
        // その頂点には到達不可能
        if (from[x] == -1) {
            res.push_back({ -1, -1, -1 });
            return res;
        }
        // その頂点はスタート
        if (from[x] == -2) {
            res.push_back({ -1, -1, -1 });
            return res;
        }

        //根に戻るまで探索
        while (from[x] >= 0) {
            auto [v, u] = edges[from[x]];
            res.push_back({ x, v, u });
            x = v;
        }
        return res;
    }
};
//------------------------------------------------------------------------------

//エラトステネスの篩-----------------------------------------------------------------------------
//エラトステネスの篩を利用した
//素数判定
//素因数分解、列挙
//約数列挙
struct Eratosthenes {
    // IsPrime[i]が素数かどうか
    vector<bool> is_prime;
    // minfactor[i]の約数の最小の素数
    vector<int> minfactor;
    // primefactor[i]の<素因数,指数>の列挙
    vector<vector<pair<int, int>>> primefactor;

    Eratosthenes(int n)
        : is_prime(n + 1, true), minfactor(n + 1, -1), primefactor(n + 1) {
        // 0,1に関する初期化
        is_prime[0] = is_prime[1] = false;
        minfactor[1] = 1;

        //篩
        for (int i = 2; i <= n; i++) {

            //古いに落とされたものはスキップ
            if (!is_prime[i]) continue;

            //素数の場合は必ずiが最小の約数での素数となる
            minfactor[i] = i;

            for (int j = 2; i * j <= n; j++) {
                is_prime[i * j] = false;

                //合成数でまだ素数が約数となっていない場合にはiが約数となる
                if (minfactor[i * j] == -1) minfactor[i * j] = i;
            }
        }

        // 1からNまでの素因数分解
        for (int i = 2; i <= n; i++) {
            auto x = factorize(i);
            for (auto y : x) {
                primefactor[i].push_back(y);
            }
        }
    }

    // 素因数分解(Xの素因数を得る)
    // O(LogN)
    // xの<約数,指数>を列挙して返す
    vector<pair<int, int>> factorize(int x) {
        vector<pair<int, int>> res;
        while (x > 1) {
            int p = minfactor[x];
            int exp = 0;

            // Nで割り切れる限り割る
            while (minfactor[x] == p) {
                x /= p;
                ++exp;
            }
            res.emplace_back(p, exp);
        }
        return res;
    }

    //約数列挙(Xの約数を得る)
    //計算量は約数の個数をnとしてO(n)
    //約数の個数は10^9までの数で n <= 1344となる
    vector<int> divisors(int x) {
        vector<int> res({ 1 });

        // xが0以下のときは-1として返す
        if (x <= 0) {
            res[0] *= -1;
            return res;
        }

        //素素因を取得
        auto pf = factorize(x);

        //約数列挙
        for (auto p : pf) {
            int siz = (int)res.size();
            for (int i = 0; i < siz; i++) {
                int v = 1;
                for (int j = 0; j < p.second; j++) {
                    v *= p.first;
                    res.push_back(res[i] * v);
                }
            }
        }
        return res;
    }
    //-------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    // debug
    //--------------------------------------------------------------------------

    // nまでの最小の素因数の約数を表示する
    void show_minfactor(int n) {
        rep(i, n) cout << i << ":" << minfactor[i] << " ";
        cout << endl;
    }

    // xの最小の素因数の約数を表示する
    void show_primefactor(int x) {
        cout << x << " の[素因数,指数]" << endl;
        auto pf = primefactor[x];
        for (auto [f, i] : pf) cout << f << " " << i << endl;
        cout << "---------------------------------" << endl;
    }

    // xの約数を列挙する
    void show_divisors(int x) {
        auto d = divisors(x);
        for (auto x : d) cout << x << " ";
        cout << endl;
    }
};
//--------------------------------------------------------------------------------
// DAG(有向非巡回グラフ)-----------------------------------------------------------------------------
// DAG
// トポロジカルソート
// 最長経路の長さ、経路、パス
// おまけでDAGかどうか(有向グラフに閉路があるか)判定
struct DAG {
    // グラフ
    vector<vector<int>> g;
    // グラフがDAGかどうか
    bool dag;
    // トポロジカルソートを行ったかどうか
    bool sorted;
    // indegree[i]における入次数の数
    vector<int> indegree;
    // outdegree[i]における出次数の数
    vector<int> outdegree;
    // トポロジカルソート済みリスト
    vector<int> topo_sorted_list;
    // 頂点iまでの最長経路の長さ
    vector<int> maxdist;
    // DAG上の最長パス
    vector<int> longestpath;
    // 最長パスを求める際のパス上の親
    vector<int> from;

    DAG(int n) : g(n), indegree(n), outdegree(n), maxdist(n), from(n) {
        rep(i, n) from[i] = i;
        dag = true;
        sorted = false;
    }

    // グラフの作成
    void make_edge(int v, int u) {
        // vからuを辺で結ぶ
        g[v].push_back(u);

        // 入次数と出次数を記録
        indegree[u]++;
        outdegree[v]++;
    }

    // グラフに閉路があるかどうかを調べる
    bool is_dag() {
        // トポロジカルソートができればDAG,できなければ非DAGといえる
        // トポロジカルソートをしていなかったらする
        if (!sorted) topological_sort();
        if (dag)
            return true;
        else
            return false;
    }

    // トポロジカルソート
    void topological_sort() {
        sorted = true;
        // indegreeをコピーする
        vector<int> cp_indegree = indegree;
        // 入次数がない頂点を探索する
        vector<int> li;
        vector<bool> used((int)g.size());
        rep(i, (int)cp_indegree.size()) {
            int v = cp_indegree[i];
            if (!v) li.push_back(i);
        }

        // 入次数0の頂点を消してDAGを小さくしていくことで、頂点の最大のパスの長さで緩和できる(DP)
        for (int i = 0; i < (int)li.size(); i++) {
            int v = li[i];
            used[v] = true;
            // 入次数のない頂点を配列に格納
            topo_sorted_list.push_back(v);
            for (auto u : g[v]) {
                // vの出次数=uの入次数を消す
                cp_indegree[u]--;
                // 入次数が0ならばリストに追加
                if (!cp_indegree[u]) {
                    li.push_back(u);
                    // 最長経路で緩和
                    // 行き先が今のパスで緩和できる場合,親を記録
                    if (maxdist[u] < maxdist[v] + 1) {
                        maxdist[u] = maxdist[v] + 1;
                        from[u] = v;
                    }
                }
            }
        }

        // ソートが終わった際、すべての頂点を見ていればDAG、そうでないなら非DAG
        for (auto v : used)
            if (!v) dag = false;
    }

    //最長パスを取得する
    vector<int> get_longest_path() {
        vector<int> res;
        // 最長パスの長さの末尾からfromを辿っていく
        // スタートの位置を求める
        int v = max_element(all(maxdist)) - maxdist.begin();
        while (from[v] != v) {
            res.push_back(v);
            v = from[v];
        }
        res.push_back(v);
        reverse(all(res));
        return res;
    }

    //最長経路の長さを取得する
    int get_longestpath_dist() { return *max_element(all(maxdist)); }

    //--------------------------------------------------------------------------
    // debug
    //--------------------------------------------------------------------------

    // トポロジカルソートした順序を出力
    void show_topo_sorted_list() {
        for (auto v : topo_sorted_list) cout << v << " ";
        cout << endl;
    }

    // 最長パスを出力
    void show_longestpath() {
        auto path = get_longest_path();
        for (auto v : path) cout << v << " ";
        cout << endl;
    }
};
//------------------------------------------------------------------------------
// UnionFind(--------------------------------------------------------------------------------
struct UnionFind {
    vector<int> par; // par[i] → root
    vector<int> siz;
    //コンストラクタ
    UnionFind(int N) : par(N), siz(N, 1) { rep(i, N) par[i] = i; }

    void init(int n) {
        siz.assign(n, 1);
        rep(i, n) par[i] = i;
    }

    // xの根を探索
    int root(int x) {
        while (x != par[x]) {
            x = par[x];
        }
        return x;
    }
    // xとyの木を併合
    void merge(int x, int y) {
        int rx = root(x);
        int ry = root(y);
        if (rx == ry) return;
        // x>yの順にして小さいほうを大きいほうにくっつける(経路圧縮)
        if (siz[rx] < siz[ry]) swap(rx, ry);
        siz[rx] += siz[ry];
        par[ry] = rx;
    }

    //同じ木に属するかどうか
    bool same(int x, int y) {
        int rx = root(x);
        int ry = root(y);
        return rx == ry;
    }

    // xの属するグループの数
    int size(int x) {
        int rx = root(x);
        return siz[rx];
    }
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main() {
    //入力
}
