#pragma once

#include "Suken.h"
#include "SaveData.h"
#include "Window.h"
#include "Item.h"
#include "Equipment.h"
#include <string>
#include <vector>

class CProduce{

private:
	CMySaveData *savedata;
	CEquipmentWindow *equipmentWindow;
	Graph Arrow, Window[5];
	CSV RecipeInfo;
	CSV *SorceInfo[3];
	CEquipmentManager *equipManager;
	CItemManager *itemManager;
	CYesNoWindow *yesNoWindow;
	CAmountGetWindow *amountGetWindow;
	int lookLocate, lookPage,proKind,kindNum;
	std::string recipeNameKind;
	int step,makeMax;
	bool madeF,stepChangeF,sozaiAru;

public:
	CProduce(CMySaveData *CSD,int proKind);
	~CProduce();
	void WindowLoop();
	void WindowDraw();
	bool GetStepChangeFlag();

};
