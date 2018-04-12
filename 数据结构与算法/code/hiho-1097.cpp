#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define rep(i,b,e) for(int i = b ; i < e ; i++)

int prim(const vector<vector<int> > &graph) {
    if(graph.empty() || graph.size() != graph[0].size())   return 0;

    int vertex_number = graph.size();   //图顶点总数
    set<int> rest_vertexes;             //所有未加入MST的顶点
    rep(i,0,vertex_number)  rest_vertexes.insert(i);
    rest_vertexes.erase(0);             //一开始所有顶点都未加入MST，所有顶点距MST的路径都是0，将序号最小的顶点加入MST
    vector<int> min_path = graph[0];    //现在MST中只包含顶点0，其它顶点距MST的最小距离就是该顶点和顶点0的距离

    //一直处理到所有顶点都加入MST
    while(!rest_vertexes.empty()){
        int min_vertex = *(rest_vertexes.begin());
        //找到一个距MST最近的顶点
        for(int vertex : rest_vertexes)
            if(min_path[vertex] < min_path[min_vertex])
                min_vertex = vertex;
        //将这个顶点添加到MST，更新剩余节点到MST的最短距离
        rest_vertexes.erase(min_vertex);
        for(int vertex : rest_vertexes)
            if(graph[min_vertex][vertex] < min_path[vertex])
                min_path[vertex] = graph[min_vertex][vertex];
    }

    //返回MST所有边的权值和
    int weight = 0;
    rep(i,0,vertex_number)  weight += min_path[i];

    return  weight;
}

int main(){

    vector<vector<int> > graph;
    int edge;

    int n;
    cin >> n;

    rep(i, 0, n) {
        vector<int> tp;
        rep(j, 0, n) {
            cin >> edge;
            tp.push_back(edge);
        }
        graph.push_back(tp);
    }

    cout << prim(graph) << endl;

    return 0;
}