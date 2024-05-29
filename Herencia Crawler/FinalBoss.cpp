#include "FinalBoss.h"
#include <windows.h>
#include <stdio.h>

FinalBoss::FinalBoss(int _hp, int _atk, int _type, std::string _name, int _status, int _fireAttack, int _frozenAttack) 
	: Personaje(_hp,  _atk,  _type, _name,  _status) {
		fireAttack = _fireAttack;
		frozenAttack = _frozenAttack;
}

int FinalBoss::getFireAttack() {
	return fireAttack;
}
int FinalBoss::getFrozenAttack() {
	return frozenAttack;
}
void FinalBoss::setFireAttack(int _FireAttack) {
	fireAttack = _FireAttack;
}
void FinalBoss::setFrozenAttack(int _FrozenAttack) {
	frozenAttack = _FrozenAttack;
}

FinalBoss::FinalBoss()
{
}

void FinalBoss::printDialog()
{
	std::cout << "So you've come... for your death...";
	Sleep(3000);
}
