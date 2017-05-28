#pragma once

#include "Suken.h"


class CJikiStatus{
private:
	int atc, def, Matc, Mdef, spd, escape, hit, luck;
	int money;

public:
	CJikiStatus(int atc, int def, int Matc, int Mdef, int spd, int escape, int hit, int luck);
	void ReSetStatus();

};
