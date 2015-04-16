//
//  RSAKey.h
//  FinalProject
//
//  Created by Gonzalo Nunez on 4/15/15.
//  Copyright (c) 2015 Gonzalo Nunez. All rights reserved.
//

#include <iostream>

#include <string>
#include <ctime>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "RabinMiller.h"

class RSAKeys {

private:

    // 40 gives us a very satisfactory guarantee that it's prime through the Rabin Miller Test
    static const int kRabinMillerIterations = 40;
    
    longlong n;
    longlong e; // public key
    longlong d; // private key
    
    void generateKeys();
    
    longlong generateRandomPrimeNumber();
    longlong findCoPrime(longlong number);
    longlong greatestCommonDivisor(longlong m, longlong n);
    longlong findPrivateKey(longlong m, longlong e);
    
    bool isLongLong(long double number);
    
    void seedRandomNumber();
    
public:
    
    RSAKeys();
    
    longlong getPublicKey();
    longlong getPrivateKey();
    longlong getN();
};

RSAKeys::RSAKeys()
{
    generateKeys();
}

void RSAKeys::generateKeys()
{
    seedRandomNumber();
    
    longlong p = generateRandomPrimeNumber();
    longlong q = generateRandomPrimeNumber();
    
//    cout << "p:" << p << endl;
//    cout << "q:" << q << endl;
//    cout << endl;
    
    n = p * q;
    longlong m = (p - 1)*(q - 1);
    
    e = findCoPrime(m);
    d = findPrivateKey(m, e);
}

longlong RSAKeys::generateRandomPrimeNumber()
{
    longlong randomNum = rand() % 9000 + 1000;
    
    if (RabinMiller::isRabinMillerPrime(randomNum, kRabinMillerIterations)) {
        return randomNum;
    } else {
        return generateRandomPrimeNumber();
    }
}

longlong RSAKeys::findCoPrime(longlong number)
{
    for (longlong i = 2; i < number; i++) {
        if (greatestCommonDivisor(number, i) == 1) {
            return i;
        }
    }
    return 0;
}

longlong RSAKeys::greatestCommonDivisor(longlong m, longlong n)
{
    if (n == 0) {
        return m;
    }
    return greatestCommonDivisor(n, m%n);
}

longlong RSAKeys::findPrivateKey(longlong m, longlong e)
{
    long double n = 0;
    while (true) {
        long double d = ((1 + (n*m)) / e);
        if (isLongLong(d)) {
            return (longlong)d;
        }
        
        n++;
    }
}

longlong RSAKeys::getPublicKey()
{
    return e;
}

longlong RSAKeys::getPrivateKey()
{
    return d;
}

longlong RSAKeys::getN()
{
    return n;
}

bool RSAKeys::isLongLong(long double number)
{
    return number == (long double)(longlong)number;
}

void RSAKeys::seedRandomNumber()
{
    srand((int)time(NULL));
}


/*
 long toThePowerOf(long base, long exponent)
 {
	long num = base;
	for (long i = 0; i < exponent; i++)
	{
 num = num * base;
	}
	return num;
 }
 
 long encrypt(long message, long publicKey, long n)
 {
	long cipher = toThePowerOf(message, publicKey);
	cipher = cipher % n;
 
	return cipher;
 }
 
 long decrypt(long cipher, long privateKey, long n)
 {
	long message = toThePowerOf(cipher, privateKey);
	message = message % n;
 
	return message;
 }
 */
