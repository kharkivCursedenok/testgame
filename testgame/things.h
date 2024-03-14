#include <iostream>
#include "inventory.h"
using namespace std;
class Player;
class Gamefield;
class Level {
private:
	int wallX; // walls will be everywhere, cause it will be a cave, but wall with rope in it will be only one
	int wallY;
	int ropePlaceX; // coordinates where rope will have to be placed, to escape the cave
	int ropePlaceY;
	bool wallIsDestroyed = false;
public:
	void destroy(invetory* inv, int playerX, int playerY) {
		if (playerX == wallX && playerY == wallY) {
			wallIsDestroyed = true;
			Rope* rope = new Rope();
			inv->addItem(rope);
		}
		else
			cout << "You are too far from the wall" << endl;
	}
	int getWallX(){
		return wallX;
	}
	int getWallY(){
		return wallY;
	}
};
class GameField {
private:
	const int width = 10;
	const int height = 10;
	char field[10][10];

public:
	GameField() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				field[i][j] = '#';
			}
		}
	}
	void drawField() const {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cout << field[i][j];
			}
			cout << endl;
		}
	}
	void placePlayer(Player* player, int x, int y) {
		field[y][x] = 'P';
	}
	void movePlayer(Player* player, int dx, int dy) {
		int oldX = player->getX();
		int oldY = player->getY();
		int newX = oldX + dx;
		int newY = oldY + dy;


		if (newX >= 0 && newX < width && newY >= 0 && newY < height && field[newY][newX] != '#') {
			player->move(dx, dy);

			// Оновлюємо поле
			field[oldY][oldX] = '#'; // Стара позиція гравця стає пустою
			field[newY][newX] = 'P'; // Нова позиція гравця
		}
		else {
			newX = oldX;
			newY = oldY;
			player->setX(newX);
			player->setY(newY);
		}
	}
};
class Player {
private:
	int playerX = 5;
	int playerY = 5;
	invetory invetory;
public:
	void move(int dx, int dy) {
		playerX += dx;
		playerY += dy;
	}
	
	void addItem(Item* item) {
		invetory.addItem(item);
	}

	bool hasItem(const string& itemName) const {
		return invetory.containsItem(itemName);
	}
	int getX() {
		return playerX;
	}
	int getY() {
		return playerY;
	}
	int setY(int playerY) {
		this->playerY = playerY;
	}
	int setX(int playerX) {
		this->playerX = playerX;
	}
};