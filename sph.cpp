#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

map<int,int> factorize(int n){
    map<int,int> factors;
    for(int i=2; i*i <=n; ++i){
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

int mod_pow(int a, int b, int mod){
    int c=1;
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

int gcd_extended(int a, int b, int &x, int &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    int x1;
    int y1;
    int d=gcd_extended(b, a%b, x1, y1);
    x=y1;
    y=x1-y1*(a/b);
    return d;
}

int mod_inv(int a, int mod){
    int x;
    int y;
    int d=gcd_extended(a, mod, x, y);
    if(d!=1){
        return -1;
    }
    return (x%mod+mod)%mod;
}

int crt(const vector<int>& a, const vector<int>& m){
    int M=1;
    for(int mod:m){
        M*=mod;
    }
    int x=0;
    for(int i=0; i<a.size(); ++i){
        int Mi=M/m[i];
        x+=a[i]*mod_inv(Mi, m[i])*Mi;
        x%=M;
    }
    return (x+M)%M;
}

int silver_polig_hellman(int a, int b, int n){
    map<int,int> factorization=factorize(n);
    vector<int> remainders;
    vector<int> moduli;
    for(auto& [p,l]:factorization){
        int pl=pow(p, l);
        int e=n/pl;
        vector<int> table(p);
        for(int j=0; j<p;++j){
            table[j]=mod_pow(a, e*j, n);
        }
        int x=0;
        int power=1;
        int be=mod_pow(b, e, n);
        for(int i=0; i<l;++i){
            //int t=mod_pow(be, pow(p, l-i-1), n);
            int exp = 1;
            for (int j=0; j<l-i-1; ++j)
                exp*=p;
            int t=mod_pow(be, exp, n);

            int d=-1;
            for(int j=0; j<p;++j){
                if(table[j]==t){
                    d=j;
                    break;
                }
            }
            if(d==-1){
                return -1;
            }
            x+=d*power;
            power*=p;
            //be=(be*mod_pow(mod_pow(a, -d*power*e/p, n), 1, n))%n;
            int exponent=d*power*e;
            int inv=mod_inv(mod_pow(a, exponent, n), n);
            be=(be*inv)%n;

        }
        remainders.push_back(x);
        moduli.push_back(pl);

    }
    return crt(remainders, moduli);
}

int main(){
    int a=5290; //генератор
    int b=29773; //елемент
    int n=35521; //порядок

    int x = silver_polig_hellman(a, b, n);
    cout << "x = " << x << endl;


    return 0;
}