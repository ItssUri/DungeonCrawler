#pragma once
#include <iostream>
const int dungeonLength = 10;
const int dungeonWidth = 5;
const int enemyNumber = 5;
class Personaje
{
private:
	int x;	
	int y;
	int hp;
	int atk;
	int type;
	std::string name;
	int status;
public:
	// Getter - Setter
	int getX(), getY(), getHp(), getAtk(), getType(), getStatus();
	std::string getName();
	void setX(int _x), setY(int _y), setHp(int _hp), setAtk(int _atk), setType(int _type), setName(std::string _name), setStatus(int _status); 
	
	//Methods
	std::string randomName();
	void printCoords();
	void enemyMovement(int(&dungeon)[dungeonLength][dungeonWidth]);
	bool isNearEnemy(Personaje hero, Personaje(&enemyArray)[enemyNumber]);
	void moveHero(char input, int(&dungeon)[dungeonLength][dungeonWidth], Personaje(&enemyArray)[enemyNumber], int dif);
	bool battle(Personaje& enemigo, int dif);

	// Constructor
	Personaje();
	Personaje(int _x, int _y, int _hp, int _atk, int _type, std::string _name, int _status);
	Personaje(int _hp, int _atk, int _type, std::string _name, int _status);
	Personaje(int _hp, int _atk, int _type, int _status);
	Personaje(int _x, int _y, int _hp, int _atk, int _type, int _status);
};
