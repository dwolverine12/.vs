#include <iostream>
using namespace std;
void merge(int arr[], int start, int mid, int end)
{
    int temp[end - start + 1];
    int left = start;
    int right = mid + 1;
    int k = 0;
    while (left <= mid && right <= end)
    {
        if (arr[left] < arr[right])
        {
            temp[k] = arr[left];
            left++;
        }
        else
        {
            temp[k] = arr[right];
            right++;
        }
        k++;
    }
    while(left<=mid)
    {
        temp[k] = arr[left];
        left++;
        k++;
    }
    while(right <= end){
        temp[k] = arr[right];
        right++;
        k++;
    }
    for(int t =0; t<k; t++)
    {
        arr[start+t] = temp[t];
    }
}
void mergeSort(int arr[], int start, int end)
{
    if(start<end){
        int mid = (start+end)/2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid+1, end);
        merge(arr, start, mid, end);
    }
}

int main(){
    int n;
    cout<<"Enter number of students: ";
    cin>>n;
    cout<<endl<<"Enter Credits: ";
    int arr[n-1];
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    cout<<"Before Sorting: ";
    for(int i=0; i<n-1; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    mergeSort(arr,0,n-1);
    cout<<"After Sorting: ";
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    system("pause");
    return 0;

}