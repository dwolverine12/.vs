#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>

using namespace std;

struct Edge{
    int destination, time;
    Edge(int dest, int t) : destination(dest), time(t) {}
};

struct Compare{
    bool operator()(const pair<int, int>& a, const pair<int, int>& b)
    {
        return a.second > b.second;
    }
};

vector<int> dijkstra(int source, int destination, vector<vector<Edge>>& graph){
    int V = graph.size();

    if(source < 0 || source >= V || destination < 0 || destination >= V){
        cout<<"Error: Invalid source or destination!" << endl;
        return{};
    }

    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

    dist[source] = 0;
    pq.push({source, 0});

    while(!pq.empty()){
        int node = pq.top().first;
        int currentDist = pq.top().second;
        pq.top();

        if(node == destination){
            break;
        }

        for(Edge& edge : graph[node]){
            int neighbour = edge.destination;
            int travelTime = edge.time;

            if(currentDist + travelTime < dist[neighbour]){
                dist[neighbour] = currentDist + travelTime;
                pq.push({neighbour, dist[neighbour]});
                parent[neighbour] = node;    
            }
        }
    }

    if (dist[destination] == INT_MAX){
        cout<<"Destination is unreachable!" << endl;
        return {};
    }

    vector<int> path;
    for(int at = destination; at!= -1; at = parent[at]){
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;

}

void addEdge(vector<vector<Edge>>& graph, int u, int v, int time){
    if(u<0 || v<0 || u>=graph.size() || v>=graph.size()){
        cout<<"Error: Invalid edge between nodes!" << endl;
        return;
    }
    graph[u].push_back(Edge(v,time));
    graph[v].push_back(Edge(u, time));
}

void displayGraph(const vector<vector<Edge>>& graph){
    cout<<"\nGraph representation (Adjacency List):\n";
    for(int i=0; i < graph.size(); i++){
        cout<<"Node "<<char('A'+ i) <<": ";
        for(const Edge& edge : graph[i]){
            cout<<"-> (" << char('A' + edge.destination) << ", "<<edge.time << ") ";
        }
        cout<<endl;
    }
}

int main(){
    int V;
    cout<<"Enter the number of nodes: ";
    cin>>V;

    vector<vector<Edge>> graph(V);
    int choice;

    do{
        cout<<"\nMenu:\n";
        cout<<"1. Add road(edge)\n";
        cout<<"2. Display graph\n";
        cout<<"3. Find shortest path\n";
        cout<<"4. Exit\n";
        cout<<"Enter your choice: ";
        cin>> choice;

        switch (choice){
            case 1:{
                char u, v;
                int time;
                cout<<"Enter the source (A-Z): ";
                cin>>u;
                cout<<"Enter the destination (A-Z): ";
                cin>>v;
                cout<<"Enter the travel time: ";
                cin>>time;

                if(u - 'A' < 0 || v-'A'<0 || u-'A'>=V || v-'A'>=V){
                    cout<<"Error: Invalid node!" << endl;
                } else{
                    addEdge(graph, u-'A', v-'A', time);
                }
                break;
            }
            case 2: {
                displayGraph(graph);
                break;
            }

            case 3:{
                char sourceChar, destChar;
                cout<<"Enter the source (A-Z): ";
                cin>>sourceChar;
                cout<<"Enter destination (A-Z): ";
                cin>>destChar;

                int source = sourceChar - 'A';
                int destination = destChar - 'A';

                if(source < 0 || source >= V || destination < 0 || destination >= V){
                    cout<<"Error: Invalid node!" << endl;
                } else{
                    vector<int> shortestPath = dijkstra(source, destination,  graph);
                    if(!shortestPath.empty()){
                        cout<<"Shortest path from "<< sourceChar << " to "<< destChar<< ": ";
                        for(int node : shortestPath){
                            cout<< (char)(node + 'A') << " ";
                        }
                        cout<<endl;
                    }
                }
                break;
            }
            case 4:{
                cout<<"Exiting the program." << endl;
                break;
            }

            default :
                cout<<"Invalid choice. Please choose a valid option." << endl;
                break;
        }
    } while(choice!=4);

    return 0;
}