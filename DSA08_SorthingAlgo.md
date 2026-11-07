``` cpp

//Decending order
// -> Bubble sort        // -> Insertion sort
// -> Selection Sort    //  -> Counting Sort

#include <iostream>
#include <climits>
using namespace std;

void bubble(int *arr, int n){ 
    for(int j=n-1;j>0;j--){
       for(int i=0;i<j;i++){
           if(arr[i]<arr[i+1]){
               swap(arr[i],arr[i+1]);
           }
       }
    } 
    cout<<"BUBBLE SORT:)-";
    for(int i=0;i<n;i++){
        cout<<arr[i]<<",";
    }
}
//************************************************************
void insertion(int *arr, int n){
    for(int i=1;i<n;i++){
        int key = arr[i];
        int j= i-1;

        while(j>=0 && key>arr[j]){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
cout<<endl<<"Insertion SORT:)-";
    for(int i=0;i<n;i++){
        cout<<arr[i]<<",";
    }   
}
//***************************************************************
void select(int *arr, int n){
    for(int i=0;i<n;i++){
        int min = i;
        for(int j=i+1;j<n;j++){
            if(arr[min]<arr[j]){ min = j;}
        }
        swap(arr[i],arr[min]);
    }
    cout<<endl<<"Sel SORT:)-";
    for(int i=0;i<n;i++){
        cout<<arr[i]<<",";
    }
}
//*************************************************************
void counting(int *arr, int n){
    int minv = arr[0];
    int maxv= arr[0];
    cout<<endl<<"countting sort:";
    for(int i=0;i<n;i++){
        minv = min(minv,arr[i]);
        maxv = max(maxv,arr[i]);
    }

    int range  = maxv-minv+1;
    int c[range] = {0};

    for(int i=0;i<n;i++){
        c[arr[i]-minv]++;
    }
    int idx = 0;

    for(int i=0;i<range;i++){
        while(c[i]<0){
            arr[idx] = i+minv;
            idx++;
            c[i]--;
        }
    }
    for(int i=0;i<n;i++){
        cout<<arr[i]<<",";
    }
    
}

int main() {
    int arr[] = {3, 6, 2, -1};
    int n=4;
    bubble(arr,n);
    insertion(arr,n);
    select(arr,n);
    counting(arr,n);
    return 0;
}
