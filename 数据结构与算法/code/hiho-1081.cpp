#include <iostream>
#include <vector>
#include <set>
#include <climits>

using namespace std;

#define rep(i,b,e) for(int i = b ; i < e ; i++)

const int UNREACHABLE = INT_MAX; //根据输入的数据范围可知，图中最长路径不会超过INT_MAX，因此可以用于表示节点之间不可达

vector<int> dijkstra(const vector<vector<int> > &graph,int b){
    if(graph.empty() || graph.size() != graph[0].size() || b < 0 || b >= graph.size())
        return vector<int>();

    vector<int> state = graph[b];   //所有顶点到达顶点b的初始距离
    int vertexes = graph.size();    //顶点总数
    set<int> rest_vertexes;         //未处理的顶点集合
    rep(i,0,vertexes)
        if(i != b)
            rest_vertexes.insert(i);

    int min_vertex;                 //每次找出距起点b最近的一个顶点处理
    while(!rest_vertexes.empty()){
        min_vertex = *(rest_vertexes.begin());//初始化为第一个未处理的顶点
        for(int vertex : rest_vertexes)
            if(state[vertex] != UNREACHABLE && state[vertex] < state[min_vertex])
                min_vertex = vertex;

        rest_vertexes.erase(min_vertex);

        //看剩余节点通过min_vertex到达b的距离是否更短
        for(int vertex : rest_vertexes)
            //这个顶点要能到达min_vertex，并且min_vertex能到达b，这个顶点才可能到达b
            if(graph[vertex][min_vertex] != UNREACHABLE && state[min_vertex] != UNREACHABLE){
                if(state[vertex] == UNREACHABLE)
                    state[vertex] = graph[vertex][min_vertex] + state[min_vertex];
                else if (state[vertex] > graph[vertex][min_vertex] + state[min_vertex])
                    state[vertex] = graph[vertex][min_vertex] + state[min_vertex];
            }
    }

    return state;
}

int main(){

    vector<vector<int> > graph;

    //N：地点数
    //M：道路数
    //S：起点
    //T：终点
    //u：每条道路的第一个顶点
    //v：每条道路的第二个顶点
    //length：道路的长度
    int N,M,S,T,u,v,length;
    cin >> N >> M >> S >> T;

    rep(i,0,N){
        vector<int> tp;
        rep(j,0,N){
            if(i == j)  tp.push_back(0);    //顶点到自身的距离为0
            else    tp.push_back(UNREACHABLE);
        }
        graph.push_back(tp);
    }

    rep(i, 0, M) {
        cin >> u >> v >> length;
        if(graph[u - 1][v - 1] > length)
            graph[u - 1][v - 1] = length;
        if(graph[v - 1][u - 1] > length)
            graph[v - 1][u - 1] = length;
    }

    vector<int> state = dijkstra(graph,S - 1);
    cout << state[T - 1] << endl;

    return 0;
}