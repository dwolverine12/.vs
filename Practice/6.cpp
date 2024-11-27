#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void findMaxMinMarks(const vector<int>& marks){
    if(marks.empty()){
        cout<<"No marks to process!"<<endl;
        return;
    }

    priority_queue<int, vector<int>, greater<int>> minHeap;

    priority_queue<int> maxHeap;

    for(int marks: marks){
        minHeap.push(marks);
        maxHeap.push(marks);
    }

    int minMarks = minHeap.top();
    int maxMarks = maxHeap.top();

    cout<<"Minimum Marks: "<< minMarks<<endl;
    cout<<"Maximum Marks: "<< maxMarks<<endl;
}

int main(){
    int n;
    cout<<"Enter the number of students: ";
    cin>>n;

    if(n<=0){
        cout<<"Invalid number of students!"<<endl;
        return 0;
    }

    vector<int> marks(n);
    cout<<"Enter marks obtained by the students: ";
    for(int i=0; i<n; i++){
        cin>>marks[i];
    }
    findMaxMinMarks(marks);
    system("pause");
    return 0;
}