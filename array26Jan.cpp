//-----6} Three Great Candidates
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

void rev(vector <int> &arr,int n){
   int f = INT_MIN;
   int s = INT_MIN;
   int t = INT_MIN;
    
   for(int x:arr){
    if(x>f){
        t=s;
        s=f;
        f=x;
    }else if(x<f && x>s){
        t=s;
        s=x;
    }else if(x<s && x>t){
        t=x;
    }
}
cout<<f<<s<<t;
}
int main(){
    vector <int> arr={50,90,80,98,78,63};
    int n = 6;
    
    rev(arr,n);
    
return 0;
}