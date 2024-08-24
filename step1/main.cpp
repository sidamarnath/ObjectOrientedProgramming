/**
 * @file main.cpp
 * @author Sidharth Amarnath
 *
 * Program main entry point
 */
#include <iostream>
#include "Farm.h"
#include "Cow.h"
#include "Chicken.h"
#include "Ant.h"

using namespace std;

/**
 * Main entry point
 *
 * This is where the program starts.
 * @return
 */

int main()
{
    cout << "Instantiating Farm" << endl;
    Farm farm;

    // This loops continuously until we are done
    bool done = false;
    while (!done)
    {
        // Output user instructions
        cout << endl;
        cout << "Farm management" << endl;
        cout << "1 - Add cow" << endl;
        cout << "2 - Add Chicken" << endl;
        cout << "3 - Add Ant" << endl;
        cout << "8 - Number of defenders" << endl;
        cout << "9 - List inventory" << endl;
        cout << "99 - Exit" << endl;
        cout << "Select Option: ";

        // Get option from the user
        int option;
        cin >> option;

        // Handle invalid  input
        if (!cin)
        {
            option = 1000;
            cin.clear();
            cin.ignore();  // Discard bad input
        }

        // Handle the possible user options
        switch (option)
        {
        case 1:
        {
            cout << "Adding cow" << endl;
            Cow *cow = new Cow();
            cow->ObtainCowInformation();
            farm.AddAnimal(cow);
        }
        break;

        case 2:
        {
            cout << "Adding chicken" << endl;
            Chicken *chicken = new Chicken();
            chicken->ObtainChickenInformation();
            farm.AddAnimal(chicken);
        }
        break;

        case 3:
        {
            cout << "Adding ant" << endl;
            Ant *ant = new Ant();
            ant->ObtainAntInformation();
            farm.AddAnimal(ant);
        }
        break;

        case 8:
        {
            cout << "There are " << farm.NumberOfDefenders() << " defenders" << endl;
        }
            break;

        case 9:
            farm.DisplayInventory();
            break;

        case 99:
            done = true;
            break;

        default:
            cout << "Invalid option" << endl;
            break;
        }
    }

    return 0;
}
