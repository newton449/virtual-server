#pragma once

#include <string>

using namespace std;


struct ClientMenuItem{
	string name;
	string description;
	string url;
	float orderNumber;
};

class IClientManager{
public:
	virtual ~IClientManager() {}
	// Adds a menu item.
	virtual void addMenuItem(ClientMenuItem item) = 0;
	// Returns all menu items.
	virtual vector<ClientMenuItem> getMenuItems() = 0;
};