#pragma once

#include "suken.h"
#include <stdio.h>
#include <vector>

using namespace std;

class CMySaveData {
private:
	CData *data,*otherData;
	int EquipmentAmount,haveEquipmentKindLevel[400][3];//•ŠííAí—Ş”Ô†ALevel
	int wearEquipmentLocate[5][2];
	int money;
	int sorce[200], tool[60], food[100];
	int test;
	int recipeStep[10];
	typedef pair<int, int> intP;
	intP itemSet[10][10];

public:
	CMySaveData(bool kari);
	void WriteSaveData();
	void WriteSaveDataToOther();

	void SetWearEquipmentLocate(int equipmentKind,int locate1, int locate2);
	void SetEquipmentAmount(int Amoun);
	void SetHaveEquipmentNumLevel(int dataNum,int eKind, int eNum, int eLevel);
	void SetItem(int kind, int num,int amount);
	void SetMoney(int amount);
	void SetItemSet(int setNum,int conNum,int kind, int num);

	int GetEquipmentAmountSaveData();
	int GetHaveEquipmentKindLevelSaveData(int num,int what);
	int GetWearEquipmentLocateSaveData(int equipKind, int which);
	int GetMoneySaveData();
	int GetItem(int kind, int num);
	int GetSetItem(int setNum, int conNum, bool first);
};


