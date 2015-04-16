//
//  main.cpp
//  FinalProject
//
//  Created by Gonzalo Nunez on 4/15/15.
//  Copyright (c) 2015 Gonzalo Nunez. All rights reserved.
//

#include <iostream>
#include <string>

#include "RSAKeys.h"

using namespace std;

enum InstructionType {
    NoInstruction, // default
    EncryptMessage, // 1
    DecryptMessage, // 2
    ShowOptions, // 3
    Exit // 4
};

enum ErrorType {
    GeneralError,
    InvalidInstruction,
    InvalidMessage
};

//-------- Forward Declarations --------

void performInteraction();

void runEncryptionWorkflow();
void runDecryptionWorkflow();

InstructionType instructionForInt(const int choice);

void displayOptionsWithPrompt(const bool shouldPrompt);
void displayErrorMessageForError(const ErrorType err);
void promptForMessage();

bool isValidInput(const int input);
bool isValidInput(const string input);

//--------------------------------------

//-------- Constants -------

static const int kMaxOption = 4;

//--------------------------


InstructionType chosenInstruction = NoInstruction;

int main(int argc, const char * argv[])
{
    displayOptionsWithPrompt(true);
    while (Exit != chosenInstruction) {
        
        int chosenOption = 0;
        cin >> chosenOption;
        
        if (!isValidInput(chosenOption)) {
            displayErrorMessageForError(InvalidInstruction);
        }
        
        chosenInstruction = instructionForInt(chosenOption);
        performInteraction();
        
    }
    
    RSAKeys keys = RSAKeys();
    cout << "Public Key is " << keys.getPublicKey() << endl;
    cout << "Private Key is " << keys.getPrivateKey() << endl;
    cout << "N is " << keys.getN() << endl;
    
    return 0;
}

void performInteraction() {
    switch (chosenInstruction) {
        case EncryptMessage:
            runEncryptionWorkflow();
            break;
        case DecryptMessage:
            runDecryptionWorkflow();
            break;
        case ShowOptions:
            displayOptionsWithPrompt(false);
            break;
        case Exit:
        default:
            break;
    }
}

void runEncryptionWorkflow() {
    
    promptForMessage();
    string message;
    
    cin.ignore();
    getline(cin, message);
    
    if (!isValidInput(message)) {
        displayErrorMessageForError(InvalidMessage);
    }
    
    
    cout << endl;
    
    
    
    
    
    
    
}

void runDecryptionWorkflow() {
    
}

// Helpers

void promptForMessage() {
    cout << "Please enter the message you'd like to encrypt." << endl;
    cout << endl;
}

InstructionType instructionForInt(const int choice) {
    switch (choice) {
        case 1:
            return EncryptMessage;
        case 2:
            return DecryptMessage;
        case 3:
            return ShowOptions;
        case 4:
            return Exit;
        default:
            return NoInstruction;
    }
}


void displayOptionsWithPrompt(const bool shouldPrompt) {
    cout << "1. Encypt Message" << endl;
    cout << "2. Decrypt Message" << endl;
    cout << "3. Show Options" << endl;
    cout << "4. Exit Program" << endl;
    cout << endl;
    
    if (shouldPrompt) {
        cout << "Please select an option." << endl;
        cout << endl;
    }
}

void displayErrorMessageForError(const ErrorType err) {
    switch (err) {
        case InvalidInstruction:
            cout << "Invalid instruction. Please try again.";
            break;
        case InvalidMessage:
            cout << "Invalid message, it must be less than 140 characters.";
            break;
        case GeneralError:
            cout << "A general error occured.";
            break;
    }
    cout << "Please try again." << endl;
}

bool isValidInput(const int input) {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore rest of the buffer for the line
        return false;
    }
    return input > 0 && input <= kMaxOption;
}

bool isValidInput(const string input) {
    return input.length() <= 140;
}