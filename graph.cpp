#include<iostream>
#include<vector>
#include <utility>
using namespace std;
#include<queue>
typedef pair<int,int> pii;

///==================Class Graph==========================///

class Node{
public:
    vector<int> incoming_edge;
    vector<int> outgoing_edge;
    int type; // type==0 (s) type==1 (i) type==2 (t)
};

class Graph{
    Node* G;
    int n;
    int src_id;
    int sinc_id;
    int **weight;
    public:

    Graph(){
        int N;
        cout<< "\n Enter the number of nodes \n";
        cin >>N;
        this->n=N;
        G = new Node[N];
        G[0].type=0;
        G[N-1].type=2;
        weight=new int*[N];
        for (int i=0;i<N;i++){
            weight[i]=new int[N];
            for (int j=0;j<N;j++){
                weight[i][j]=-1;
            }
        }
        src_id=0;
        sinc_id=N-1;
        add_edge();
    }

    void add_edge(){
            cout << "\n Enter edges(a,b,c) where a is start node, b is end node ,c is capacity, SRC Node=0 Sink Node=" << sinc_id << " \n";
            cout << "press -1 to exit\n";
            while(true){
                int a,b,c;
                cin >>a;
                if (a==-1) break;
                else{
                    cin >> b >> c;
                    G[b].incoming_edge.push_back(a);
                    G[a].outgoing_edge.push_back(b);
                    G[a].incoming_edge.push_back(b);
                    G[b].outgoing_edge.push_back(a);
                    weight[a][b]=c;
                    weight[b][a]=0;
                }

            }
            Network_flow();
    }

    void reachable(bool& reachable, vector<int>& path){

        queue<int> nodes;
        int visited[n];
        int parent[n];
        for (int i=0;i<n;i++){ visited[i]=0; parent[i]=-1;}
        nodes.push(0);
        visited[0]=1;
        while(!nodes.empty()){
            int a =nodes.front();
            nodes.pop();
            for (int i=0;i<G[a].outgoing_edge.size();i++){
                if (weight[a][G[a].outgoing_edge[i]]>0 && visited[G[a].outgoing_edge[i]]==0){
                    parent[G[a].outgoing_edge[i]]=a;
                    visited[G[a].outgoing_edge[i]]=1;
                    nodes.push(G[a].outgoing_edge[i]);
                }
            }
        }
        reachable= visited[n-1];
        if (reachable){
            int x=n-1;
            while(x!=0){
                path.push_back(x);
                x=parent[x];
            }
            path.push_back(0);
            reverse(path.begin(),path.end());
        }
    }

    void Network_flow(){
        bool reached=false;
        vector<int>path;
        reachable(reached,path);
        int flow=0;
        vector<int> flow_inc;
        vector<vector<int> > update_schedule;
        while(reached){
            int min_weight=0;
            update_weight(path,min_weight);
            flow_inc.push_back(min_weight);
            update_schedule.push_back(path);
            flow += min_weight;
            path.clear();
            reached=false;
            reachable(reached,path);
        }

        for (int i=0;i<update_schedule.size();i++){
            cout << i+1<<"nd update to flow is\n";
            for(int j=0;j<update_schedule[i].size();j++){
                cout<<update_schedule[i][j]<<" ";
            
            }
            cout << "\n";
            cout << "flow increased by "<< flow_inc[i]<<"\n";
        }
        cout << "Max flow is " << flow << endl;
    }

    void update_weight(vector<int>& path,int& w){
       w=weight[path[0]][path[1]];
       for (int i=1;i<path.size()-1;i++){
            w=min(w,weight[path[i]][path[i+1]]);
       }
       for (int i=0;i<path.size()-1;i++){
            weight[path[i]][path[i+1]] -=w;
            weight[path[i+1]][path[i]] +=w;
       }
    }

};

int main(){
    Graph g;
}