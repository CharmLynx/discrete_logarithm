#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

void print128(__int128_t n) {
    if (n==0){
        cout << 0;
        return;
    }
    string res;
    bool neg=n<0;
    if (neg){
        n=-n;
    }
    while(n){
        res+='0'+n%10;
        n/=10;
    }
    if(neg){
        res += '-';
    }
    reverse(res.begin(), res.end());
    cout << res;
}

__int128_t parse128(const string& s) {
    __int128_t res=0;
    bool neg=s[0]=='-';
    for (char c : s) {
        if (isdigit(c)){
            res=res*10+(c-'0');
        }
    }
    return neg ? -res : res;
}

__int128_t bin_pow(__int128_t a, __int128_t b, __int128_t mod){
    __int128_t res = 1;
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
    string sa;
    string sb;
    string sn;
    
    cin>>sa>>sb>>sn;

    __int128_t a=parse128(sa);
    __int128_t b=parse128(sb);
    __int128_t n=parse128(sn);

    __int128_t x=-1;


    

    
    for(__int128_t i=1; i<=n-2; ++i){
        if(bin_pow(a, i, n) == b){
            x=i;
            break;
        }
    }
    

    
    cout << "x = ";
    print128(x);
    cout << endl;

    


    return 0;
}