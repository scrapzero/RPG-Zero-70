#pragma once

#include "suken.h"


class CMySaveData {
private:
	CData *data,*otherData;
	int EquipmentAmount,haveEquipmentKindLevel[400][3];//•ŠííAí—Ş”Ô†ALevel
	int wearEquipmentLocate[5][2];
	int money;
	int sorce[200], tool[60], food[100];
	int test;

public:
	CMySaveData(bool kari);
	void WriteSaveData();
	void WriteSaveDataToOther();

	void SetWearEquipmentLocate(int equipmentKind,int locate1, int locate2);
	void SetEquipmentAmount(int Amoun);
	void SetHaveEquipmentNumLevel(int dataNum,int eKind, int eNum, int eLevel);
	void SetItem(int kind, int num,int amount);

	int GetEquipmentAmountSaveData();
	int GetHaveEquipmentKindLevelSaveData(int num,int what);
	int GetWearEquipmentLocateSaveData(int equipKind, int which);
	int GetMoneySaveData();
	int GetItem(int kind, int num);
};


