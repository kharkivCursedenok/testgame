#include <iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <conio.h>
#include<Windows.h>

using namespace std;

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
private:

public:
	Rope() : Item("Rope", "A good rope to climb somewhere down") {}

	void use() override {
		cout << "You used the rope" << endl;
	}
	
};

class Axe : public Item {
private:
	int axeX = rand() % 48 + 1;
	int axeY = rand() % 48 + 1;
public:
	Axe() : Item("Axe", "Seems like it can destroy some chests") {}

	void use() override {
		cout << "You used the axe" << endl;;
	}
	int getX() {
		return axeX;
	}
	int getY() {
		return axeY;
	}
	void setX(int dx) {
		axeX = dx;
	}
	void setY(int dy) {
		axeY = dy;
	}
};

class inventory
{
private:
	vector<Item*> items;
public:
	void resetInv() {
		items.clear();
	}
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
	bool containsItem(Item* itemToFind)  const {
		for (auto it = 0; it < items.size(); it++)
		{
			if (items[it] == itemToFind)
			{
				return true;
			}
		}
		return false;
	}
};

class Player {
private:
	int playerX = 5;
	int playerY = 5;
	inventory inventory;
public:
	void move(int dx, int dy) {
		playerX += dx;
		playerY += dy;
	}
	void displayInv() {
		inventory.displayInventory();
	}
	void resetInv() {
		inventory.resetInv();
	}
	void addItem(Item* item) {
		inventory.addItem(item);
	}
	
	bool hasItem(Item* item) const {
		return inventory.containsItem(item);
	}
	int getX() {
		return playerX;
	}
	int getY() {
		return playerY;
	}
	void setY(int playerY) {
		this->playerY = playerY;
	}
	void setX(int playerX) {
		this->playerX = playerX;
	}
};

class Level {
private:
	int chestX = rand() % 48 + 1;
	int chestY = rand() % 48 + 1;
	int ropePlaceX = rand() % 48 + 1; 
	int ropePlaceY = rand() % 48 + 1;
	
public:
	void destroy(Player* player, Rope* rope) {
		if (player->getX() == chestX && player->getY() == chestY) {
			player->addItem(rope);
			setChestX(1000);
			setChestY(1000);
		}
	}
	void resetLvL(Player* player){
		player->resetInv();
		chestX = rand() % 48 + 1;
		chestY = rand() % 48 + 1;
		ropePlaceX = rand() % 48 + 1;
		ropePlaceY = rand() % 48 + 1;
		player->setX(rand() % 48 + 1);
		player->setY(rand() % 48 + 1);
	}
	int getRopePlX() {
		return ropePlaceX;
	}
	int getRopePlY() {
		return ropePlaceY;
	}
	int getChestX(){
		return chestX;
	}
	int getChestY(){
		return chestY;
	}
	void setRopePlX(int x) {
		ropePlaceX = x;
	}
	void setRopePlY(int y) {
		ropePlaceY = y;
	}
	void setChestX(int x) {
		chestX = x;
	}
	void setChestY(int y) {
		chestY = y;
	}
};

class GameField {
private:
	const int width = 50;
	const int height = 50;
	const int viewRadius = 1;
	char field[50][50];

public:
	GameField() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				field[i][j] = '#';
			}
		}
	}
	void drawField(Player* player, Axe* pickaxe, Level* lvl) {
		system("cls");
		int playerX = player->getX();
		int playerY = player->getY();
		
		for (int y = 0; y <= height; y++) {
			for (int x = 0; x <= width; x++) {
				if (abs(x - playerX) <= viewRadius && abs(y - playerY) <= viewRadius) {
					if (x == playerX && y == playerY) {
						cout << 'P'; // Отображаем игрока
					}
					else if (x == pickaxe->getX() && y == pickaxe->getY()) {
						cout << 'A';
					}
					else if (x == lvl->getChestX() && y == lvl->getChestY()) {
						cout << 'C';
					}
					else if (x == lvl->getRopePlX() && y == lvl->getRopePlY())
					{
						cout << 'O';
					}
					else
					{
						if (field[x][y] == '#')
						{
							field[x][y] = ' ';
							cout << field[x][y]; // Отображаем символы поля
						}
						else {
							cout << field[x][y];
						}
						
					}
				}
				else {
					if (x < 50 && x > 0 && y > 0 && y < 50)
					{
						cout << '#'; // За пределами области видимости отображаем стену
					}
					else
					{
						cout << 'W';
					}
				}
			}
			cout << endl;
		}
		
	}
	void placePlayer(Player* player, int x, int y) {
		player->setX(x);
		player->setY(y);
	}
	void movePlayer(Player* player, int dx, int dy) {
		int oldX = player->getX();
		int oldY = player->getY();
		int newX = oldX + dx;
		int newY = oldY + dy;


		if (newX > 0 && newX < width && newY > 0 && newY < height && field[newY][newX] != 'W') {

			player->move(dx, dy);
		}
		else {
			newX = oldX;
			newY = oldY;
			player->setX(newX);
			player->setY(newY);
		}
	}
};