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

class RSAKey {
    
private:
    
    longlong n;
    longlong e; // public key
    longlong d; // private key
    
    void generateKeys();
    
    longlong generateRandomPrimeNumber();
    longlong findCoPrime(longlong number);
    longlong greatestCommonDivisor(longlong m, longlong n);
    longlong findPrivateKey(longlong m, longlong e);
    
    bool isPrime(longlong number);
    bool isInteger(double number);
    
public:
    
    RSAKey();
    
    longlong getPublicKey();
    longlong getPrivateKey();
    longlong getN();
};

RSAKey::RSAKey()
{
    generateKeys();
}

void RSAKey::generateKeys()
{
    longlong p = generateRandomPrimeNumber();
    longlong q = generateRandomPrimeNumber();
    
    n = p * q;
    longlong m = (p - 1)*(q - 1);
    
    e = findCoPrime(m);
    d = findPrivateKey(m,e);
}

bool RSAKey::isPrime(longlong number)
{
    if (number < 2)
        return false;
    if (number == 2)
        return true;
    if (number % 2 == 0)
        return false;
    
    for (int i = 3; i <= sqrt(number) + 1; i = i + 2) {
        if (number%i == 0) {
            return false;
        }
    }
    return true;
}

longlong RSAKey::generateRandomPrimeNumber()
{
    srand(time(NULL));
    long randomNum = rand() % 1000 + 100;
    
    while (true) {
        if (isPrime(randomNum)) {
            return randomNum;
        }
        randomNum++;
    }
}

longlong RSAKey::findCoPrime(longlong number)
{
    for (long i = 2; i < number; i++) {
        if (greatestCommonDivisor(number, i) == 1) {
            return i;
        }
    }
    return 0;
}

longlong RSAKey::greatestCommonDivisor(longlong m, longlong n)
{
    if (n == 0) {
        return m;
    }
    return greatestCommonDivisor(n, m%n);
}

longlong RSAKey::findPrivateKey(longlong m, longlong e)
{
    double n = 0;
    while (true) {
        double d = ((1 + (n*m)) / e);
        if (isInteger(d)) {
            return (long)d;
        }
        
        n++;
    }
}

longlong RSAKey::getPublicKey()
{
    return e;
}

longlong RSAKey::getPrivateKey()
{
    return d;
}

longlong RSAKey::getN()
{
    return n;
}

bool RSAKey::isInteger(double number)
{
    return number == (float)(int)number;
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