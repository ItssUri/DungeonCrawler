#include <iostream>
#include <iomanip>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string>
#include "pj.h"
#include "FinalBoss.h"
#pragma comment(lib, "winmm.lib")

std::string const FOG_CHAR("□");
std::string const EXIT_CHAR("★");
std::string const ENEMY_CHAR("2");
std::string const PLAYER_CHAR("1");
int difficulty = 0;

int dungeon[dungeonLength][dungeonWidth];
Personaje hero(180, 30, 1,1);
Personaje enemyArray[enemyNumber];
int salidaX;
FinalBoss boss(150,15,3,"Richtofen",1,20,17);

void resetArray() {
    for (int i = 0; i < dungeonLength; i++) {
        for (int y = 0; y < dungeonWidth; y++) {
            dungeon[i][y] = 0;
        }
    }
}
    
void insertEnemies() {
    int randomX, randomY;
    bool isCorrect = false; 
    randomY = rand() % dungeonLength + 1;
    randomX = rand() % dungeonWidth + 1;
    for (int i = 0; i < enemyNumber; i++) {
        isCorrect = false;
        while (!isCorrect) {
            if (dungeon[randomY][randomX] == 0 && randomX <= dungeonWidth - 1 && randomY <= dungeonLength - 1) {
                dungeon[randomY][randomX] = 2;
                enemyArray[i] = Personaje(randomX, randomY, 100, 10, 2, 1);
                enemyArray[i].setName(enemyArray[i].randomName());
                isCorrect = true;
            }
            else {
                randomY = rand() % dungeonLength + 1;
                randomX = rand() % dungeonWidth + 1;
            }
        }
    }
}

void insertHero() {
    int randomX;
    bool isCorrect = false;
    int maxCheck = 0;
    for (int i = 0; i < dungeonWidth; i++)
    {
        if (dungeon[0][i] != 0)
        {
            maxCheck++;
        }
    }
    //std::cout << "\nTheres " << maxCheck << " enemies on line 1";
    randomX = rand() % dungeonWidth;
    while (!isCorrect) {
        if (dungeon[0][randomX] == 0 || maxCheck == dungeonWidth) {
            //std::cout << "Hero placed at [0," << randomX << "]";
            hero.setX(randomX);
            hero.setY(0);
            dungeon[0][randomX] = 1;
            isCorrect = true;
        }
        else {
            randomX = rand() % dungeonWidth;
        }
    }
}

void insertExit() {
    int randomX;
    bool isCorrect = false;
    int maxCheck = 0;
    for (int i = 0; i < dungeonWidth; i++)
    {
        if (dungeon[dungeonLength-1][i] != 0)
        {
            maxCheck++;
        }
    }
    randomX = rand() % dungeonWidth;
    while (!isCorrect) {
        if (dungeon[dungeonLength - 1][randomX] == 0 || maxCheck == dungeonWidth) {
            //std::cout << "\nExit placed ["<<dungeonLength-1<< "," << randomX << "]" << std::endl << std::endl;
            salidaX = randomX;
            dungeon[dungeonLength - 1][randomX] = 9;
            isCorrect = true;
            boss.setX(randomX);
            boss.setY(dungeonLength - 1);
        }
        else {
            randomX = rand() % dungeonWidth;
        }
    }
}
void updateArray() {
    resetArray();
    for (int i = 0; i < enemyNumber; i++)
    {
        if (enemyArray[i].getStatus() == 1)
        {
            dungeon[enemyArray[i].getY()][enemyArray[i].getX()] = 2;
        }
    }
    dungeon[hero.getY()][hero.getX()] = 1;
    dungeon[dungeonLength - 1][salidaX] = 9;
}
void printArray() {
    for (int i = 0; i < dungeonLength; i++) {
        for (int y = 0; y < dungeonWidth; y++) {
            if (difficulty==0)
            {
                if (dungeon[i][y] == 0) {
                    std::cout << FOG_CHAR << "    ";
                }
                else if (dungeon[i][y] == 1) {
                    std::cout << PLAYER_CHAR << "    ";
                }
                else if (dungeon[i][y] == 2) {
                    std::cout << ENEMY_CHAR << "    ";
                }
                else if (dungeon[i][y] == 9) {
                    std::cout << EXIT_CHAR << "    ";
                }
                else {
                    std::cout << dungeon[i][y] << "    ";
                }
            }
            else {
                 if (dungeon[i][y] == 1) {
                    std::cout << PLAYER_CHAR << "    ";
                }
                else {
                    std::cout << FOG_CHAR << "    ";
                }
            }
            
            
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
void moveEnemies() {
    for (int i = 0; i < enemyNumber; i++)
    {
        if (enemyArray[i].getStatus() == 1)
        {
            enemyArray[i].enemyMovement(dungeon);
        } 
    }
}

void startDungeon() {
    resetArray();
    std::cout << std::endl;
    insertEnemies();
    insertHero();
    insertExit();
    //hero.printCoords();
}
void turno(bool& finish) {
    int aliveEnemies = 0;
    for (int i = 0; i < enemyNumber; i++)
    {
        if (enemyArray[i].getStatus() == 1)
        {
            aliveEnemies++;
        }
    }
    std::cout << hero.getName() << "  |  " << hero.getHp() << "♥" << "  |  " << hero.getAtk() << "⚔" << "  |  " << aliveEnemies << "☠" << std::endl;
    moveEnemies();
    updateArray();
    bool isEnemyClose = hero.isNearEnemy(hero,enemyArray);
    //std::cout << isEnemyClose << std::endl;
    if (isEnemyClose) {
        PlaySound(TEXT("enemy_music.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
    else
    {
        PlaySound(NULL, NULL, 0);
    }
    
    printArray();
    char keyboardInput = _getch();
    hero.moveHero(keyboardInput, dungeon, enemyArray, difficulty);
    system("CLS");
    if (hero.getX() == boss.getX() && hero.getY() == boss.getY()) {
        finish = true;
    }
    
}
int main()
{   
    std::string heroName;
    std::cout << "!-- SELECT YOUR DIFFICULTY (0-1) : ";
    std::cin >> difficulty;
    std::cout << "!-- Brave hero... What is your name? : ";
    std::cin >> heroName;
    hero.setName(heroName);
    bool bossMet = false;
    std::setlocale(LC_ALL, "");
    srand(time(NULL));
    
    startDungeon();
    while (!bossMet)
    {
        turno(bossMet);
    }
    boss.printDialog();

        bool ganado = true;
        std::cout << "\nTe enfrentas al boss final " << boss.getName();
        std::cout << "!! Preparate para pelear... !!\n";
        Sleep(3000);
        while (boss.getHp() > 0 && hero.getHp() > 0) {
            std::cout << "Atacas al boss con una fuerza de " << hero.getAtk() << " puntos de vida.";
            boss.setHp((boss.getHp() - hero.getAtk()));
            if (boss.getHp() <= 0)
            {
                boss.setHp(0);
                boss.setStatus(0);
                ganado = true;
            }
            std::cout << "\nAl boss le quedan " << boss.getHp() << " puntos de vida.\n";
            if (boss.getHp() == 0)
            {
                break;
            }
            std::cin.ignore();

            int specialChance = (rand() % 4) + 1;
            if (specialChance >= 3) {
                int specialMove = (rand() % 2) + 1;
                if (specialMove == 1)
                {
                    std::cout << boss.getName() << " te ataca con MAGIA DE FUEGO, quitándote " << boss.getFireAttack() << " puntos de vida.\nEl boss se hace mas fuerte!";
                    hero.setHp((hero.getHp()-boss.getFireAttack()));
                    boss.setFireAttack((boss.getFireAttack() + 5));
                }
                else {
                    std::cout << boss.getName() << " te ataca con MAGIA HELADA, quitándote " << boss.getFrozenAttack() << " puntos de vida.\nEl boss se hace mas fuerte!";
                    hero.setHp((hero.getHp() - boss.getFrozenAttack()));
                    boss.setFireAttack((boss.getFrozenAttack() + 5));
                }
            }
            else {
                std::cout << "Prepárate... " << boss.getName() << " te ataca, quitándote " << boss.getAtk() << " puntos de vida.\n";
                hero.setHp((hero.getHp() - boss.getAtk()));
            }

        }

        std::cout << "Te quedan " << hero.getHp() << " puntos de vida";
        std::cin.ignore();

        if (ganado)
        {
            std::cout << "\nFelicidades! Has derrotado a " << boss.getName() << "\nHas salvado el reino!";
            std::cin.ignore();
        }
        else {
            std::cout << "... Has perdido ...";
            std::cin.ignore();
        }

}
