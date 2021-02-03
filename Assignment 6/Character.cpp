#include "Character.h"
#include "Collection.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Item.h"
#include "Armor.h"

const Collection<const Item>& Character::getInventory()
{
	return myInventory;
}

void Character::addItem(const Item& item)
{
	try {
		const Weapon& newWeapon = dynamic_cast<const Weapon&>(item);
		WeaponList.push_front(newWeapon);
		Weapon* Weaponptr = &WeaponList.front();
		myInventory.add(*Weaponptr);
	}
	catch (bad_cast)
	{
		try {
			const Armor& newArmor = dynamic_cast<const Armor&>(item);
			ArmorList.push_front(newArmor);
			Armor* Armorptr = &ArmorList.front();
			myInventory.add(*Armorptr);
		}
		catch (bad_cast)
		{
			const Item& newItem = dynamic_cast<const Item&>(item);
			ItemList.push_front(newItem);
			Item* Itemptr = &ItemList.front();
			myInventory.add(*Itemptr);
		}
	}
}

void Character::dropItem(const Item& item)
{
	if (myInventory.getSize() > 0)
	{
		myInventory.remove(item);
	}
}

double Character::getTotalWeight() const
{
	double Wtotal = 0;
	double Atotal = 0;
	double Itotal = 0;

	for (auto x : WeaponList)
	{
		Wtotal += x.getWeight();
	}
	for (auto x : ArmorList)
	{
		Atotal += x.getWeight();
	}
	for (auto x : ItemList)
	{
		Itotal += x.getWeight();
	}
	double total = Wtotal + Atotal + Itotal;

	return total;
}

const Armor * Character::getEquippedArmor(unsigned int slotID) const
{
	for (int i = 0; i < ArmorSet.size(); i++)
	{ 
		if (ArmorSet[i] != nullptr)
		{
			if (ArmorSet[i]->getSlotID() == slotID)
			{
				return ArmorSet[i];
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			return nullptr;
		}
	}
}

unsigned int Character::getTotalArmorRating() const
{
	int total = 0;
	for (int i = 0; i < ArmorSet.size(); i++)
	{
		if (ArmorSet[i] != nullptr)
		{
			total += ArmorSet[i]->getRating();
		}
		else
		{
			total += 0;
		}
		
	}
	return total;
}

void Character::equipArmor(const Armor & armor)
{
	for (auto x : ArmorList)
	{
		if (&x == &armor)
		{
			myInventory.remove(armor);
			ArmorSet[armor.getSlotID()] = &armor;
		}
		else
		{
			throw "logic_error";
		}
	}
}

void Character::unequipArmor(unsigned int slotID)
{
	for (int i = 0; i < ArmorSet.size(); i++)
	{
		if (ArmorSet[i]->getSlotID() == slotID)
		{
			myInventory.add(*ArmorSet[i]);
			ArmorSet[i] = nullptr;
		}
		else
		{

		}
	}
}

const Weapon * Character::getEquippedWeapon() const
{
	if(EquippedWeapon.empty())
	{
		return nullptr;
	}
	else {
		return EquippedWeapon.front();
	}

}

void Character::equipWeapon(const Weapon & weapon)
{
	
	EquippedWeapon.resize(1);
	if (EquippedWeapon.empty())
	{
		EquippedWeapon.push_front(&weapon);
		myInventory.remove(weapon);
	}
	else
	{
		myInventory.add(*EquippedWeapon.front());
		EquippedWeapon.pop_front();
		EquippedWeapon.push_front(&weapon);
	}
}

void Character::unequipWeapon()
{
	myInventory.add(*EquippedWeapon.front());
	EquippedWeapon.pop_front();
}

void Character::optimizeInventory(double maximumWeight)
{
}

void Character::optimizeEquipment()
{
}
