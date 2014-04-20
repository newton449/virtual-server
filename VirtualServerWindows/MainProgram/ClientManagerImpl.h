#pragma once

#include <string>
#include <vector>
#include "../interfaces/IClientManager.h"
#include <mutex>

using namespace std;


class ClientManagerImpl : public IClientManager{
public:
	void addMenuItem(ClientMenuItem item);
	vector<ClientMenuItem> getMenuItems();
private:
	vector<ClientMenuItem> items;
    std::mutex lock;
};