/*
 * Name: Kevin Li
 * EID: kal3552
 * Project 7, CRM part 2
 * EE 312H, Spring 2020
 */

#include <stdio.h>
#include <iostream>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"
using namespace std;

void readString(UTString&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(UTString word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(UTString word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(UTString type) {
    Customer* result = 0;
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}

void processPurchase() {
    UTString bottles = UTString("Bottles");
    UTString diapers = UTString("Diapers");
    UTString rattles = UTString("Rattles");
    UTString name;
    UTString item;
    int quantity;
    readString(name);
    readString(item);
    readNum(quantity);
    if(quantity > 0)
    {
        if (item == bottles) {
            if(quantity <= num_bottles)
            {
                database[name].bottles += quantity;
                num_bottles -= quantity;
            }
            else
            {
                cout << "Sorry " << name.c_str() << ", we only have " << num_bottles << " Bottles" << endl;
            }
        }
        else if (item == rattles) {
            if(quantity <= num_rattles)
            {
                database[name].rattles += quantity;
                num_rattles -= quantity;
            }
            else
            {
                cout << "Sorry " << name.c_str() << ", we only have " << num_rattles << " Rattles" << endl;
            }
        }
        else if (item == diapers) {
            if(quantity <= num_diapers)
            {
                database[name].diapers += quantity;
                num_diapers -= quantity;
            }
            else
            {
                cout << "Sorry " << name.c_str() << ", we only have " << num_diapers << " Diapers" << endl;
            }
        }
    }
}

void processSummarize() {
    int num_customers = database.size();
    cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory" << endl;
    cout << "we have had a total of " << num_customers << " different customers" << endl;
    Customer* maxDiaperCustomer = findMax("Diapers");
    Customer* maxRattleCustomer = findMax("Rattles");
    Customer* maxBottleCustomer = findMax("Bottles");
    if(maxBottleCustomer == NULL)
    {
        cout << "no one has purchased any Bottles" << endl;
    }
    else
    {
        cout << maxBottleCustomer->name.c_str() << " has purchased the most bottles " << "("
             << maxBottleCustomer->bottles << ")" << endl;
    }
    if(maxDiaperCustomer == NULL)
    {
        cout << "no one has purchased any Diapers" << endl;
    }
    else
    {
        cout << maxDiaperCustomer->name.c_str() << " has purchased the most diapers " << "("
             << maxDiaperCustomer->diapers << ")" << endl;
    }
    if(maxRattleCustomer == NULL)
    {
        cout << "no one has purchased any Rattles" << endl;
    }
    else
    {
        cout << maxRattleCustomer->name.c_str() << " has purchased the most rattles " << "("
             << maxRattleCustomer->rattles << ")" << endl;
    }
}

void processInventory() {
    UTString item;
    int num;
    UTString bottles = UTString("Bottles");
    UTString diapers = UTString("Diapers");
    UTString rattles = UTString("Rattles");
    readString(item);
    readNum(num);
    if(item == bottles)
    {
        num_bottles += num;
    }
    else if(item == diapers)
    {
        num_diapers += num;
    }
    else if(item == rattles)
    {
        num_rattles += num;
    }
}
