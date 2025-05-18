#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int a=4; //генератор
    int b=16; //елемент
    int n=23; //порядок

    int x = 0;

    for(int i=1; i<=n-2; i++){
        if(pow(a,i)==b){
            x=i;
            cout<<x<<endl;
            break;
        }
    }
    


    return 0;
}