#pragma once

#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// A data struct to store a menu item. It will be used by user to navigate
// between client pages.
struct ClientMenuItem{
	// the name, showed in the body of "a" tag
	string name;
	// the description, showed in "title" attribute of "a" tag
	string description;
	// the URL, used in "href" attribute of "a" tag. It may contain "#".
	string url;
	// the number to decide order of items. The smaller, the fronter.
	float orderNumber;
};

////////////////////////////////////////////////////////////////////////////////
// A class to manage data for clients. It provides menu items.
class IClientManager{
public:
	// Destructor.
	virtual ~IClientManager() {}
	// Adds a menu item.
	virtual void addMenuItem(ClientMenuItem item) = 0;
	// Returns all menu items.
	virtual vector<ClientMenuItem> getMenuItems() = 0;
};
