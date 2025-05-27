#include <iostream>
#include <vector>
#include <map>
#include <cmath>
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


map<__int128_t,int> factorize(__int128_t n){
    map<__int128_t,int> factors;
    for(__int128_t i=2; i*i <=n; ++i){
        while((n%i)==0){
            factors[i]++;
            n/=i;
        }
    }
    if(n>1){
        factors[n]++;
    }
    return factors;
}

__int128_t mod_pow(__int128_t a, __int128_t b, __int128_t mod){
    __int128_t c=1;
    a%=mod;
    while(b>0){
        if((b%2)==1){
            c=(c*a)%mod;
        }
        a=(a*a)%mod;
        b/=2;
    }
    return c;
}

__int128_t gcd_extended(__int128_t a, __int128_t b, __int128_t &x, __int128_t &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    __int128_t x1;
    __int128_t y1;
    __int128_t d=gcd_extended(b, a%b, x1, y1);
    x=y1;
    y=x1-y1*(a/b);
    return d;
}

__int128_t mod_inv(__int128_t a, __int128_t mod){
    __int128_t x;
    __int128_t y;
    __int128_t d=gcd_extended(a, mod, x, y);
    if(d!=1){
        return -1;
    }
    return (x%mod+mod)%mod;
}

__int128_t crt(const vector<__int128_t>& a, const vector<__int128_t>& m){
    __int128_t M=1;
    for(__int128_t mod:m){
        M*=mod;
    }
    __int128_t x=0;
    for(size_t i=0; i<a.size(); ++i){
        __int128_t Mi=M/m[i];
        x+=a[i]*mod_inv(Mi, m[i])*Mi;
        x%=M;
    }
    return (x+M)%M;
}

__int128_t int_pow(__int128_t base, int exp) {
    __int128_t res=1;
    while(exp--){
        res*= base;
    }
    return res;
}


__int128_t silver_polig_hellman(__int128_t a, __int128_t b, __int128_t n) {
    map<__int128_t, int> factorization = factorize(n);
    vector<__int128_t> remainders;
    vector<__int128_t> moduli;

    for (auto& [p, l] : factorization) {
        __int128_t pl=int_pow(p, l);
        __int128_t e=n/pl;

        __int128_t x=0, power=1;
        __int128_t be=mod_pow(b, e, n);
        __int128_t alpha=mod_pow(a, e, n);

        for (int i=0; i<l; ++i) {
            __int128_t exp=int_pow(p, l-i-1);
            __int128_t t=mod_pow(be, exp, n);
            int d=-1;
            __int128_t current=1;
            for (int j=0; j<p; ++j) {
                if (current==t) {
                    d=j;
                    break;
                }
                current = (current*alpha)%n;
            }
            if (d == -1){
                return -1;
            }
            x+=d*power;
            power*=p;
            __int128_t exponent=d*power*e;
            __int128_t inv=mod_inv(mod_pow(a, exponent, n), n);
            be=(be*inv)%n;
        }
        remainders.push_back(x);
        moduli.push_back(pl);
    }
    return crt(remainders, moduli);
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

    x = silver_polig_hellman(a, b, n);
    
    cout << "x = ";
    print128(x);
    cout << endl;


    return 0;
}
/*#include <chrono>
using namespace std;
using namespace std::chrono;

auto start = high_resolution_clock::now();

// 🔁 Виклик функції
long_mul(A, B, C, count);

auto end = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(end - start);
cout << "Час виконання: " << duration.count() << " мкс" << endl;
*/