/**
 * @file Ant.cpp
 * @author Sid Amarnath
 */

#include <iostream>
#include <string>
#include <cctype>
#include "Ant.h"
using namespace std;

void Ant::ObtainAntInformation()
{
    cout << endl;
    cout << "Input information about the ant" << endl;

    // Obtain the ant's code
    while (true)
    {
        cout << "Code: ";
        cin >> mCode;
        if (mCode.length() != 3)
        {
            cout << "Code has to be 3 letters" << endl;
            cin.clear();
            cin.ignore();
            continue;
        }
        bool lowercase = false;
        for (int i = 0; i < mCode.length(); i++)
        {
            if (islower(mCode[i]))
            {
                lowercase = true;
            }
        }
        if (lowercase) {
            cout << "Code must be all uppercase letters" << endl;
            continue;
        }
        break;
    }

    // Obtain the type using a menu. We have a loop so
    // we can handle errors.
    bool valid = false;
    while (!valid)
    {
        cout << "1: Worker Ant" << endl;
        cout << "2: Soldier Ant" << endl;
        cout << "3: Drone Ant" << endl;
        cout << "4: Queen Ant" << endl;
        cout << "Enter selection and return: ";
        int option;
        cin >> option;
        if (!cin)
        {
            // We have an error. Clear the input and try again
            cin.clear();
            cin.ignore();
            continue;
        }

        switch (option)
        {
        case 1:
            mType = Type::Worker;
            valid = true;
            break;

        case 2:
            mType = Type::Soldier;
            valid = true;
            break;

        case 3:
            mType = Type::Drone;
            valid = true;
            break;
        case 4:
            mType = Type::Queen;
            valid = true;
            break;
        }

    }

    if (mType == Type::Worker || mType == Type::Soldier || mType == Type::Drone || mType == Type::Queen)
    {
        valid = false;
        while (!valid)
        {
            cout << "Enter radiation level in millisieverts per hour: ";

            cin.clear();
            cin.ignore();
            cin >> mRadiationLevel;
            if (cin)
            {
                valid = true;
            }
        }
    }
}

void Ant::DisplayAnimal()
{
    switch (mType) {
    case Type::Worker:
        cout << "Ant " << mCode << " is a " << "Worker Ant with a radiation level of " << mRadiationLevel << " mSv/hr" << endl;
        break;

    case Type::Soldier:
        cout << "Ant " << mCode << " is a " << "Soldier Ant with a radiation level of " << mRadiationLevel << " mSv/hr" << endl;
        break;

    case Type::Drone:
        cout << "Ant " << mCode << " is a " << "Drone Ant with a radiation level of " << mRadiationLevel << " mSv/hr" << endl;
        break;

    case Type::Queen:
        cout << "Ant " << mCode << " is a " << "Queen Ant with a radiation level of " << mRadiationLevel << " mSv/hr" << endl;
        break;
    }
}

bool Ant::IsDefender()
{
    if (mType == Type::Soldier) {
        return true;
    }
    return false;
}




