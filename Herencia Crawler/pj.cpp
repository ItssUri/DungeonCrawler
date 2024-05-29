#include "pj.h"
#include "FinalBoss.h"
#include <conio.h>
#include <windows.h>
int Personaje::getX() {
	return x;
}

int Personaje::getY()
{
	return y;
}

int Personaje::getHp()
{
	return hp;
}

int Personaje::getAtk()
{
	return atk;
}

int Personaje::getType()
{
	return type;
}

std::string Personaje::getName()
{
	return name;
}

std::string Personaje::randomName()
{
	std::string enemies[12] = { "Goblin Warrior", "Skeleton Archer", "Orc Berserker", "Dark Mage", "Cave Troll", "Infernal Dragon", "Ancient Lich", "Fire Demon", "Swamp Hydra", "Giant Serpent", "Night Vampire", "Enraged Minotaur" };
	return enemies[rand() % 12];
}

int Personaje::getStatus()
{
	return status;
}

void Personaje::printCoords()
{
	std::cout << "\n" << name << " (Y: " << y << " X : " << x << ")\n";
}

void Personaje::setX(int _x)
{
	x = _x;
}

void Personaje::setY(int _y)
{
	y = _y;
}

void Personaje::setHp(int _hp)
{
	hp = _hp;
}

void Personaje::setAtk(int _atk)
{
	atk = _atk;
}

void Personaje::setName(std::string _name)
{
	name = _name;
}

void Personaje::setType(int _type)
{
	type = _type;
}

void Personaje::setStatus(int _status) {
	status = _status;
}

Personaje::Personaje()
{
}

Personaje::Personaje(int _x, int _y, int _hp, int _atk, int _type, std::string _name, int _status)
{
	x = _x;
	y = _y;
	hp = _hp;
	atk = _atk;
	type = _type;
	name = _name;
	status = _status;
}

Personaje::Personaje(int _hp, int _atk, int _type, std::string _name, int _status)
{
	hp = _hp;
	atk = _atk;
	type = _type;
	name = _name;
	status = 1;
}

Personaje::Personaje(int _hp, int _atk, int _type, int _status)
{
	hp = _hp;
	atk = _atk;
	type = _type;
	status = _status;
}

Personaje::Personaje(int _x, int _y, int _hp, int _atk, int _type, int _status)
{
	x = _x; 
	y = _y;
	hp = _hp;
	atk = _atk;
	type = _type;
	status = _status;
}

void Personaje::enemyMovement(int(&dungeon)[dungeonLength][dungeonWidth]) {
	int moveChance = (rand() % 3) + 1;
	bool isDone = false;
	
	if (moveChance == 3) {
		while (!isDone)
		{
			int direccion = (rand() % 4) + 1;
			switch (direccion)
			{
			case 1:
				if (!(y == 0) && dungeon[y - 1][x] == 0) {
					//dungeon[y - 1][x] = 2;
					//dungeon[y][x] = 0;
					y -= 1;
					//std::cout << "Moved enemy" << std::endl;
					isDone = true;
				}
				break;
			case 2:
				if (!(x == dungeonWidth-1) && dungeon[y][x+1] == 0) {
					//dungeon[y][x+1] = 2;
					//dungeon[y][x] = 0;
					x += 1;
					//std::cout << "Moved enemy" << std::endl;
					isDone = true;
				}
				break;
			case 3:
				if (!(y == dungeonLength-1) && dungeon[y+1][x] == 0) {
					//dungeon[y+1][x] = 2;
					//dungeon[y][x] = 0;
					y += 1;
					//std::cout << "Moved enemy" << std::endl;
					isDone = true;
				}
				break;
			case 4:
				if (!(x == 0) && dungeon[y][x-1] == 0) {
					//dungeon[y][x-1] = 2;
					//dungeon[y][x] = 0;
					x -= 1;
					//std::cout << "Moved enemy" << std::endl;
					isDone = true;
				}
				break;
			default:
				break;
			}
		}
		
	}
}

bool Personaje::isNearEnemy(Personaje hero, Personaje(&enemyArray)[enemyNumber]) {
	int heroX = hero.getX();
	int heroY = hero.getY();
	int enemyX, enemyY;
	for (int i = 0; i < enemyNumber; i++)
	{
		enemyX = enemyArray[i].getX();
		enemyY = enemyArray[i].getY();
		if (enemyArray[i].getStatus() == 1)
		{
			if ((heroX + 1 == enemyX && heroY == enemyY) || (heroX - 1 == enemyX && heroY == enemyY) || (heroX == enemyX && heroY + 1 == enemyY) || (heroX == enemyX && heroY - 1 == enemyY)) {
				return true;
			}
		}
		
	}
	return false;

}

void Personaje::moveHero(char input, int(&dungeon)[dungeonLength][dungeonWidth], Personaje(&enemyArray)[enemyNumber], int dif) {
	int oldX = x;
	int oldY = y;
	switch (input)
	{
	case 72: case 119: //up | w
		if (y!=0)
		{
			y -= 1;
		}
		break;
	case 80: case 115: //dwn | s
		if (y != dungeonLength-1)
		{
			y += 1;
		}
		break;
	case 75: case 97: //lft | a
		if (x!=0)
		{
			x -= 1;
		}
		break;
	case 77: case 100: //rgt | d
		if (x!=dungeonWidth-1)
		{
			x += 1;
		}
		break;
	default:
		break;
	}
	for (int i = 0; i < enemyNumber; i++)
		{
			if (enemyArray[i].getX() == x && enemyArray[i].getY() == y && enemyArray[i].getStatus() == 1) {
				//dungeon[oldY][oldX] = 0;
				bool won = battle(enemyArray[i], dif);
				if (won)
				{
					//dungeon[oldY][oldX] = 0;
					//dungeon[y][x] = 1
					enemyArray[i].setStatus(0);
				}
				else {
					system("CLS");
					std::cout << "Game over....";
					exit(0);
				}
			}
		}
		
	}


bool Personaje::battle(Personaje& enemigo, int dif)
{
	bool ganado = true;
	if (enemigo.getX() == x && enemigo.getY() == y && enemigo.getStatus() == 1) {
		std::cout << "\nTe enfrentas al enemigo " << enemigo.getName();
		std::cout << "!! Preparate para pelear !!\n";
		Sleep(3000);
		while (enemigo.getHp() > 0 && hp > 0) {
			std::cout << "Atacas al enemigo con una fuerza de " << atk << " puntos de vida.";
			enemigo.setHp((enemigo.getHp() - atk));
			if (enemigo.getHp() <= 0)
			{
				enemigo.setHp(0);
				enemigo.setStatus(0);
				ganado = true; 
			}
			std::cout << "\nAl enemigo le quedan " << enemigo.getHp() << " puntos de vida.\n";
			if (enemigo.getHp() == 0)
			{
				break;
			}
			std::cin.ignore();
			if (enemigo.getType() == 2)
			{
				std::cout << "\n!!! Te atacan. Enemigo " << enemigo.getName() << " te quita " << enemigo.getAtk() << " puntos de vida.\n";
				hp -= enemigo.getAtk();
				if (hp <= 0)
				{
					hp = 0;
					ganado = false;
				}
			}
			
				else {
					std::cout << "Prepárate... " << enemigo.getName() << " te ataca, quitándote " << enemigo.getAtk() << " puntos de vida.\n";
					hp -= enemigo.getAtk();
				}
				
			}
			
			std::cout << "Te quedan " << hp << " puntos de vida";
			std::cin.ignore();
		}
		if (ganado)
		{
			std::cout << "Felicidades! Has derrotado a " << enemigo.getName();
			//std::cout << "La dificultad es : " << dif;
			if (dif == 0)
			{
				std::cout << "\nEl poder de la determinación te cura! +20HP";
				hp += 20;
			}
			std::cin.ignore();
		}
		return ganado;
}
