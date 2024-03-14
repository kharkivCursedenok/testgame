#include<algorithm>
#include<iostream>
#include<vector>
#include<string>


using namespace std;

class Rope;
class Pickaxe;

class Item {
protected:
	string name;
	string description;
public:
	Item(const string& itemName, const string& itemDescription) : name(itemName), description(itemDescription) {}

	virtual void use() {
		cout << "This item cannot be used" << endl;
	}

	const string& getName() const {
		return name;
	}
	const string& getDescription() const {
		return description;
	}
};

class Rope : public Item {
public:
	Rope() : Item("Rope", "A good rope to climb somewhere up") {}

	void use() override {
		cout << "You used the rope" << endl;
	}
};
class Pickaxe : public Item {
public:
	Pickaxe() : Item("Pickaxe", "Seems like it can destroy some weak wall") {}

	void use() override {
		cout << "You used the pickaxe" << endl;;
	}
};

class invetory
{
public:
	void addItem(Item* item) {
		items.push_back(item);
		cout << "The" << item->getName() << "was added to your invenory!";
	}
	void displayInventory() const {
		for (const auto& item : items)
		{
			cout << "Your inventory:" << endl;
			cout << item->getName() << ": " << item->getDescription();
		}
	}
	bool containsItem(const string& itemName)  const {
		auto it = find_if(items.begin(), items.end(), [&](Item* item) {
			return item->getName() == itemName;
			}
		);

		return it != items.end();
	}

private:
	vector<Item*> items;

};

