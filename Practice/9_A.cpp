#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;

struct Item{
    int value;
    int weight;
    double ratio;
};

bool compare(Item a, Item b){
    return a.ratio > b.ratio;
}

double calculateKnapsack(vector<Item> &items, int capacity){
    double finalVal = 0.0;
    for(const auto &item: items){
        if(capacity>= item.weight){
            capacity -= item.weight;
            finalVal += item.value;
        }
        else
        {
            finalVal += (item.ratio * capacity);
            break;
        }
    }
    return finalVal;
}
int main()
{
    cout<<"Enter the number of items: ";
    int n;
    cin>>n;
    vector<Item> items(n);
    cout<<"Enter the value and weight of each item: \n";
    for(int i=0; i<n; i++){
        cout<<"Value of item "<<(i+1)<<": ";
        cin>>items[i].value;
        cout<<"Weight of item "<<(i+1)<<": ";
        cin>>items[i].weight;
        items[i].ratio = static_cast<double>(items[i].value) / items[i].weight;
    }
    cout<<"Enter the knapsack capacity: ";
    int capacity;
    cin>>capacity;

    sort(items.begin(), items.end(), compare);
    double finalVal = calculateKnapsack(items, capacity);
    cout<<"Final Value: "<< finalVal << endl;
    system("pause");
    return 0;
}