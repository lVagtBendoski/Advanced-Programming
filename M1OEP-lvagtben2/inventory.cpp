//
// Created by bobjo on 9/11/2024.
//
//
// Created by bobjo on 9/11/2024.
//

#include <vector>
#include "inventory.h"
#include "equipment.h"

inventory::inventory() {
    maxInventorySize = defaultMaxInventorySize;
}

inventory::inventory(int maxInventorySize) {
    this->maxInventorySize = maxInventorySize;
}
vector<equipment> inventory::getItems() {
    return items;
}
int inventory::getMaxInventorySize() {
    return maxInventorySize;
}
bool inventory::addItem(equipment item) {
    if(items.size() < maxInventorySize) {
        items.push_back(item);
        return true;
    }
    return false;
}
bool inventory::removeItem(int indexOfItem) {
    if(!(indexOfItem < 0 || indexOfItem >= items.size())) {
        for(int i = 0; i < items.size(); i++) {
            if(i == indexOfItem) {
                items[i].reset();
            }
        }
        return true;
    }else {
        return false;
    }
}
void inventory::lootAll(inventory inv2) {
    for( int i = 0; i < inv2.getMaxInventorySize(); i++) {
        if(items.size() < maxInventorySize) {
            items.push_back(inv2.getItems()[i]);
        }
    }
}


