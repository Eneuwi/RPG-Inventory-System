#pragma once
#include "Collection.h"
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include <list>
#include <array>
#include <functional>

using namespace std;

class Inventory : public Collection <const Item>
{
public:
	virtual unsigned int getSize() const;
	virtual void forEach(const std::function<void(const Item&)>& accept) const;
	virtual void forEach(const std::function<void(const Item&)>& accept);
	const Item* getLast();
	void add(const Item& item);
	void remove(const Item& item);
	double getRatio(const Item& item);
private:
	list<const Item*> inventoryList;
};



inline unsigned int Inventory::getSize() const
{
	return inventoryList.size();
}


inline void Inventory::forEach(const std::function<void(const Item&)>& accept) const
{
	for (const Item* item : inventoryList)
	{
		accept(*item);
	}
};

inline void Inventory::forEach(const std::function<void(const Item&)>& accept)
{
	for (const Item* item : inventoryList)
	{
		accept(*item);
	}
}

inline const Item* Inventory::getLast()
{
	const Item* last = inventoryList.back();
	return last;
}

inline void Inventory::add(const Item& item)
{
	auto i = inventoryList.begin();
	while(i != inventoryList.end() && item.getGoldValue()/item.getWeight() < getRatio(**i))
	{
		i++;
	}
	inventoryList.insert(i,&item);
}

inline void Inventory::remove(const Item& item)
{
	int counter = 0;
	for (auto x : inventoryList)
	{
		if (x == &item)
		{
			inventoryList.remove(&item);
			break;
		}
		else
		{
			counter++;
		}
	}
	if (counter >= inventoryList.size())
	{
		throw logic_error("Item not found");
	}

}

inline double Inventory::getRatio(const Item& item)
{
	return item.getGoldValue() / item.getWeight();
}

