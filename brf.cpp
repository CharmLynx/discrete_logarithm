#include <iostream>

using namespace std;

long long bin_pow(long long a, long long b, long long mod){
    long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
int main(){
    long long a=5290; //генератор
    long long b=29773; //елемент
    long long n=35521; //порядок

    for(int i=1; i<=n-2; ++i){
        if(bin_pow(a, i, n) == b){
            cout<<i<<endl;
            break;
        }
    }
    


    return 0;
}