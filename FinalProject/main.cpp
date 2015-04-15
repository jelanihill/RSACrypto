//
//  main.cpp
//  FinalProject
//
//  Created by Gonzalo Nunez on 4/15/15.
//  Copyright (c) 2015 Gonzalo Nunez. All rights reserved.
//

#include <iostream>

#include "RSAKey.h"

using namespace std;

int main(int argc, const char * argv[])
{
    RSAKey keys = RSAKey();
    cout << "Public Key is " << keys.getPublicKey() << endl;
    cout << "Private Key is " << keys.getPrivateKey() << endl;
    cout << "N is " << keys.getN() << endl;
    
    return 0;
}
