#pragma once
#include "pj.h"
class FinalBoss : public Personaje
{
private:
	int fireAttack;
	int frozenAttack;
public:

	// Getter - Setter
	int getFireAttack();
	int getFrozenAttack();
	void setFireAttack(int pFireAttack);
	void setFrozenAttack(int pFrozenAttack);

	// Methods
	void printDialog();
	
	//Constructors
	FinalBoss();
	FinalBoss(int _hp, int _atk, int _type, std::string _name, int _status, int _fireAttack, int _frozenAttack);
	
};