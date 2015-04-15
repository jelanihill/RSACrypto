//
//  RabinMiller.h
//  FinalProject
//
//  Created by Gonzalo Nunez on 4/15/15.
//  Copyright (c) 2015 Gonzalo Nunez. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long longlong;

class RabinMiller {
    
private:
    longlong mulMod(longlong a, longlong b, longlong mod);
    longlong modulo(longlong base, longlong exponent, longlong mod);
    
public:
    bool isRabinMillerPrime(longlong p, int iteration);
    
};

// Public

bool RabinMiller::isRabinMillerPrime(longlong p, int iteration)
{
    if (p < 2) {
        return false;
    }
    
    if (p != 2 && (p % 2 == 0)) {
        return false;
    }
    
    longlong s = p - 1;
    while (s % 2 == 0) {
        s /= 2;
    }
    
    for (int i = 0; i < iteration; i++) {
        
        longlong a = rand() % (p - 1) + 1;
        longlong temp = s;
        longlong mod = modulo(a, temp, p);
        
        while (temp != p - 1 && mod != 1 && mod != p - 1) {
            mod = mulMod(mod, mod, p);
            temp *= 2;
        }
        
        if (mod != p - 1 && temp % 2 == 0) {
            return false;
        }
    }
    
    return true;
}


// Private Helpers

longlong RabinMiller::mulMod(longlong a, longlong b, longlong mod)
{
    longlong x = 0;
    longlong y = a % mod;
    
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

longlong RabinMiller::modulo(longlong base, longlong exponent, longlong mod)
{
    longlong x = 1;
    longlong y = base;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            x = (x * y) % mod;
        }
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

//#endif


