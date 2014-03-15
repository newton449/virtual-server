#include "ClientManagerImpl.h"
#include "../interfaces/ILogger.h"

void ClientManagerImpl::addMenuItem(ClientMenuItem item){
	// TODO design
	items.push_back(item);
	LOG(TRACE) << "Added client menu item: " << item.name << " -> " << item.url;
}

vector<ClientMenuItem> ClientManagerImpl::getMenuItems(){
	// TODO design
	return items;
}