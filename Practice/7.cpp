#include<iostream>
#include<vector>
#include<list>
#include<string>

using namespace std;

class HashTableChaining{
    vector <list<pair<string, string>>> table;
    int size;

public:
    HashTableChaining(int tableSize) : size(tableSize){
        table.resize(size);
    }

    int hashFunction(const string &key) {
        int hashValue = 0;
        for(char ch: key) hashValue += ch;
        return hashValue % size;
    }

    void insert(const string &name, const string &number) {
        int index = hashFunction(name);
        table[index].push_back(make_pair(name, number));
    }

    string search(const string &name, int &comparisons){
        int index = hashFunction(name);
        for (const auto &entry : table[index]){
            comparisons++;
            if (entry.first == name) return entry.second;
        }
        return "Not Found";
    }
};

class HashTableLinearProbing{
    vector<pair<string, string>> table;
    vector<bool> occupied;
    int size;

public:
    HashTableLinearProbing(int tableSize) : size(tableSize){
        table.resize(size, {"",""});
        occupied.resize(size, false);
    }

    int hashFunction(const string &key) {
        int hashValue = 0;
        for(char ch:key) hashValue += ch;
        return hashValue % size;
    }

    void insert(const string &name, const string &number) {
        int index = hashFunction(name);
        while(occupied[index]) index = (index + 1) % size;
        table[index] = {name, number};
        occupied[index] = true;
    }

    string search(const string &name,  int &comparisons){
        int index = hashFunction(name);
        int startIndex = index;
        while(occupied[index]) {
            comparisons++;
            if(table[index].first == name) return table[index].second;
            index = (index+1) % size;
            if (index == startIndex) break;
        }
        return "Not found";
    }
};

int main(){
    int tableSize;
    cout<<"Enter the size of hash table: ";
    cin>>tableSize;

    HashTableChaining chainingHashTable(tableSize);
    HashTableLinearProbing linearProbingHashTable(tableSize);

    int n;
    cout<<"Enter the number of clients: ";
    cin>>n;

    vector<pair<string, string>> data;
    cout<<"Enter client details (Name TelephoneNumber):\n";
    for(int i=0; i<n; i++){
        string name, number;
        cin>>name>>number;
        chainingHashTable.insert(name, number);
        linearProbingHashTable.insert(name, number);
    }

    int queries;
    cout<<"Enter the number of queries: ";
    cin>>queries;

    vector<string> searchKeys(queries);
    cout<<"Enter search keys (Name):\n";
    for(int i = 0; i<queries; i++) cin>>searchKeys[i];

    cout<<"\nSearching in hash table (Chaining):\n";
    for(const string &key : searchKeys){
        int comparisons = 0;
        string result = chainingHashTable.search(key, comparisons);
        cout<<"Name: "<<key<<" , Number: "<<result<<", Comparisons: "<<comparisons<<endl;
    }

    cout<<"\nSearching in Hash Table (Linear Probing):\n";
    for(const string &key : searchKeys){
        int comparisons = 0;
        string result = linearProbingHashTable.search(key, comparisons);
        cout<<"Name: "<<key<<" , Number: "<<result<<", Comparisons: "<<comparisons<<endl;
    }
    system("pause");
    return 0;
}