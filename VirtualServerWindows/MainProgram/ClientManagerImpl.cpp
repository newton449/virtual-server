#include "ClientManagerImpl.h"
#include "../interfaces/ILogger.h"

void ClientManagerImpl::addMenuItem(ClientMenuItem item){
    // insertion sort with binary search. good for small amount numbers.
    size_t start = 0;
    size_t end = items.size();
    while (end != start){
        float mid = items[(start + end) / 2].orderNumber;
        if (item.orderNumber >= mid){
            start = (start + end) / 2 + 1; // This "+1" is the point!
        }
        else{
            end = (start + end) / 2;
        }
    }
    items.insert(items.begin() + start, item);
    LOG(TRACE) << "Added client menu item: " << item.name << " -> " << item.url;
}

vector<ClientMenuItem> ClientManagerImpl::getMenuItems(){
    return items;
}