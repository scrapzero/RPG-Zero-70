#pragma once


#include "Suken.h"
#include "SaveData.h"
#include "Window.h"
#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> intint;

struct SEquipment
{
	
	string name;
	int Level;
	int KindNum;
	int HP;
	int MP;
	int Atc;
	int Def;
	int MAtc;
	int MDef;
	int Spd;
	int Hit;
	int Escape;
	int Luck;
	int Element;//0‚©‚ç‡‚É@–³‰Î–Ø…ŒõˆÅ
	int FireDef;
	int WoodDef;
	int WaterDef;
	int LightDef;
	int DarkDef;
	int SellMoney;
	string skillName[2];
	int SkillMp[2];
	int SkillPower[2];
	int SkillElement[2];
	int ratioKind;
	string skillExperience[2];


};

enum {
	Soad,
	Arrow,
	Wand,
	Shield,
	Protecter,
	Shoes,
	Accesaly
};

class CEquipmentManager {
private:
	CMySaveData *savedata;
	
	int  bufWearNumLevel[2];
	int equipmentKind,equipmentAmount;
	CEquipmentWindow * equipmentWindow;
	Graph Window,Arrow;
	CSV equipmentInfo;
	enum {
		maxHaving = 50
	};

public:
	CEquipmentManager(CMySaveData* CSD,int equipKind);
	~CEquipmentManager();
	int lookLocate, lookPage,wearWeaponLocate[5][2];
	vector<intint> haveEquipmentNumLevel[7];

	void Draw();
	void LoopWindow();
	void DrawWindow();
	void PushEquipment(int equipKind,int equipNum,int equipLevel);
	int SellEquipment();
	int GetSize(int equipKind);
};

