#include<iostream>
#include<algorithm>
using namespace std;

int partition(string names[], int credits[], int start, int end) {
    int pivot = credits[start];
    int count = 0;

    for(int i=start+1; i<=end; i++) {
        if(credits[i] >= pivot) {
            count++;
        }
    }

    int pivotIndex = start + count;
    swap(credits[pivotIndex], credits[start]);
    swap(names[pivotIndex], names[start]);

    int i=start, j=end;
    while(i<pivotIndex && j>pivotIndex) {
        while(credits[i]>=pivot) i++;
        while(credits[j]<pivot) j--;
        if(i<pivotIndex && j>pivotIndex) {
            swap(credits[i], credits[j]);
            swap(names[i], names[j]);
        }
    }

    return pivotIndex;
}

void quickSort(string names[], int credits[], int start, int end) {
    if (start<end){
        int p = partition(names, credits, start, end);
        quickSort(names, credits, start, p-1);
        quickSort(names, credits, p+1, end);
    }
}

int main(){
    int n;
    cout<<"Enter the number of students: ";
    cin>>n;

    string names[n];
    int credits[n];

    cin.ignore();
    for(int i=0; i<n; i++){
        cout<<"Enter the name of student "<<i+1<<": ";
        getline(cin, names[i]);
        cout<<"Enter the credits of student "<<names[i]<<": ";
        cin>>credits[i];
        cin.ignore();
    }
    quickSort(names, credits, 0, n - 1);
    cout<<"\nStudents sorted by credits in descending order:\n"<<endl;
    for(int i = 0; i<n; i++){
        cout<<names[i]<<" with credits: "<<credits[i]<<endl;
    }

    cout<<"\nTop students based on credits: "<<endl;
    for(int i = 0; i<min(5, n); i++){
        cout<< i+1 << ". "<< names[i]<<" with credits: "<<credits[i]<<endl;
    }
    system("pause");
    return 0;

}