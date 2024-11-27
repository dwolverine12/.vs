#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<climits>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adjMatrix;
    vector<pair<int, pair<int, int>>> edges;

    public:
        Graph(int V){
            this->V = V;
            adjMatrix.resize(V, vector<int>(V,0));
        }

        void addEdge(int u, int v, int w){
            adjMatrix[u][v] = w;
            adjMatrix[v][u] = w;
            edges.push_back({w, {u, v}});
        }

        int findParent(int i, vector<int> &parent){
            if (parent[i] == i)
                return i;
            return findParent(parent[i], parent);
        }

        void unionSets(int u, int v, vector<int> &parent, vector<int> &rank){
            int rootU = findParent(u, parent);
            int rootV = findParent(v, parent);

            if (rank[rootU] < rank[rootV]){
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]){
                parent[rootV] = rootU;
            }
            else{
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }

        void kruskal(){
            vector<pair<int, pair<int, int>>> mst;
            sort(edges.begin(), edges.end());

            vector<int> parent(V);
            vector<int> rank(V, 0);

            for (int i=0; i< V ; i++) 
                parent[i] = i;
            
            int totalWeight = 0;
            for (auto edge : edges){
                int weight = edge.first;
                int u = edge.second.first;
                int v = edge.second.second;

                int setU = findParent(u, parent);
                int setV = findParent(v, parent);

                // If adding this edge does not form a cycle, add it to the result

                if(setU != setV) {
                    mst.push_back({weight, {u, v}});
                    totalWeight += weight;
                    unionSets(setU, setV, parent, rank);
                }
            }

            cout<<"\n Kruskal's MST:\n";
            for (auto edge : mst){
                cout<<edge.second.first << " -- " << edge.second.second << " : " << edge.first<<endl;
            }
            cout<<"Total weight of MST :"<< totalWeight << endl;
        }
};

void menu(){
    int V;
    cout<<"Enter the number of vertices: ";
    cin >> V;
    Graph g(V);

    while(true){
        cout<<"\n Menu:\n";
        cout<<"1. Add Edge\n";
        cout<<"2. Find MST\n";
        cout<<"3. Exit\n";
        int choice;
        cin >> choice;

        if(choice == 1){
            int u, v,w;
            cout<<"Enter starting node: ";
            cin >> u;
            cout<<"Enter ending node: ";
            cin >> v;
            cout << "Enter weight : ";
            cin >> w;
            g.addEdge(u, v, w);
        } else if(choice == 2){
            g.kruskal();
        }
        else if (choice == 3){
            break;
        }
        else{
            cout<<"Invalid choice\n";
        }
    }
}

int main(){
    menu();
    return 0;
}