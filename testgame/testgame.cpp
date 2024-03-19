#include <iostream>
#include<conio.h>
#include<thread>
#include "things.h"

using namespace std;


Player* player = new Player();
GameField gameField;
Rope* rope = new Rope();
Axe* axe = new Axe();
Level* lvl = new Level();
void detectMoving() {
    
    while (true) {
        int x = player->getX();
        int y = player->getY();
        
        if (_kbhit()) {
            char ch = tolower(_getch());
            switch (ch) {
            case 'a':
                gameField.movePlayer(player, -1, 0);
                break;
            case 'd':
                gameField.movePlayer(player, 1, 0);
                break;
            case 'w':
                gameField.movePlayer(player, 0, -1);
                break;
            case 's':
                gameField.movePlayer(player, 0, 1);
                break;
            default:
                break;
            }
            gameField.drawField(player, axe, lvl); // Обновляем поле после каждого действия игрока
            cout << x << "   " << y << endl;
            cout << endl << axe->getX() << "   " << axe->getY() << endl;
            cout << endl << lvl->getChestX() << "   " << lvl->getChestY() << endl;
            cout << endl << lvl->getRopePlX() << "   " << lvl->getRopePlY() << endl;
            player->displayInv();
        }
    }
    
}
void checkLocation() {
    if (player->getX() == axe->getX() && player->getY() == axe->getY())
    {
        player->addItem(axe);
        axe->setX(1000);
        axe->setY(1000);
    }
    if (player->getX() == lvl->getChestX() && lvl->getChestY() == player->getY() && player->hasItem(axe))
    {
        lvl->destroy(player, rope);
    }
    if (player->getX() == lvl->getRopePlX() && player->getY() == lvl->getChestY() && player->hasItem(rope))
    {
        lvl->resetLvL(player);
    }
}

int main() {
    thread Moving(detectMoving);
    while (true)
    {
        checkLocation();
    }

    Moving.join();
}
