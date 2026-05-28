// //
// // Created by bobjo on 9/11/2024.
// //

#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
#include <ostream>
#include <vector>

#include "equipment.h"

class inventory {
private:
    vector<equipment> items;
    int maxInventorySize;
    const int defaultMaxInventorySize = 20;

public:
    inventory();
    inventory(int maxInventorySize);
    vector<equipment> getItems();
    int getMaxInventorySize();
    bool addItem(equipment item);
    bool removeItem(int indexOfItem);
    void lootAll(inventory inv2);
};

#endif //INVENTORY_H
