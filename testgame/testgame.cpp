#include <iostream>
#include<conio.h>
#include "inventory.h"
#include "things.h"

Player player;
GameField gameField;
Rope rope;
Pickaxe pickaxe;
Level lvl;
void detectMoving() {
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            switch (ch) {
            case 72:
                player.move(0, -1);
                break;
            case 80:
                player.move(0, 1);
                break;
            case 75:
                player.move(-1, 0);
                break;
            case 77:
                player.move(1, 0);
                break;
            default:
                break;
            }
        }
    }
}

int main()
{
    while (true)
    {
        gameField.drawField();
        detectMoving();

    }
    std::cout << "Hello World!\n";
}
