#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
#include<string>

using namespace std;

class Graph{
    unordered_map<string, vector<pair<string, int>>> adjList;

    public:
        void addCity(string city){
            if(adjList.find(city) == adjList.end()){
                adjList[city] = vector<pair<string, int>>();
            } else{
                cout<<"City already exists! "<< endl;
            }

        }

        void addFlight(string city1, string city2, int cost){
            adjList[city1].push_back(make_pair(city2, cost));
            adjList[city2].push_back(make_pair(city1, cost));
        }

        void displayFlights(){
            if (adjList.empty()){
                cout<<"No flights available!"<<endl;
                return;
            }
            cout<<"List of all flights:\n";
            for(const auto& city : adjList){
                for(const auto& flight : city.second) {
                    cout << city.first << "->" << flight.first << ": Cost = " << flight.second << endl;
                }
            }
        } 

        void isConnected() {
            if (adjList.empty()) {
                cout << "No cities in the graph!" << endl;
                return;
            }

            unordered_map<string, bool> visited;
            int component_count = 0;

            for (auto& city : adjList){
                if (!visited[city.first]){
                    component_count++;
                    BFS(city.first, visited);
                }
            }

            if(component_count == 1){
                cout << "The graph is connected." << endl;
            } else{
                cout << "The graph is not connected. Number of components: "<< component_count << endl;
            }
        }

        private:
            void BFS(string start, unordered_map<string, bool>& visited){
                queue<string> q;
                q.push(start);
                visited[start] = true;

                while(!q.empty()) {
                    string city = q.front();
                    q.pop();

                    for(auto& neighbour : adjList[city]){
                        if (!visited[neighbour.first]){
                            visited[neighbour.first] = true;
                            q.push(neighbour.first);
                        }
                    }
                }
            }
};
int main(){
    Graph g;
    int choice;

    do{
        cout << "1. Add city\n";
        cout << "2. Add Flight Path\n";
        cout << "3. Check if graph is connected\n";
        cout << "4. Display all Flights\n";
        cout << "5. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;

        switch(choice){
            case 1:{
                string city;
                cout<<"Enter city name: ";
                cin>>city;
                g.addCity(city);
                cout<<"City added!"<< endl;
                break;
            }
            case 2:{
                string city1, city2;
                int cost;
                cout<<"Enter first city: ";
                cin>> city1;
                cout<<"Enter second city: ";
                cin>>city2;
                cout<<"Enter cost: ";
                cin>>cost;
                g.addFlight(city1, city2, cost);
                break;
            }
            case 3:
                g.isConnected();
                break;

            case 4:
                g.displayFlights();
                break;
            case 5:
                cout<<"Exiting..."<<endl;
                break;
            default:
                cout << "Invalid option"<<endl; 
        }
    } while(choice != 5);

    return 0;
}