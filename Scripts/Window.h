#pragma once

#include "Suken.h"
#include "SaveData.h"
#include <list>
#include <queue>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;




class CTextWindow :public CObject{
private:
	int TextHandle[3],HandleKind;
	list<string> display;
	queue<string> texts;
	Graph window,textArrow;
	int wordAmount;
	int arrowInterval;
	int intervalY ;
	bool endDisplay;

	enum {
		WLeft = 0,
		WUp = 376,
		WRight = 704,
		WDown = 576,
		SLeft=WLeft+20,
		SUp=WUp+20,
		SRight=WRight-50,
		SDown=WDown-10,
		SWidth = SRight - SLeft,
		SHigh = SDown-SUp
	};



public:
	

	void Start()override;
	void Loop()override;
	void Draw()override;
	void ChangeFont(int kind);
	void TextClear();
	
	CTextWindow(string text,...);
	~CTextWindow();
	void PushText(string text,...);
	bool GetTextEmpty();
	bool GetWaitTextEmpty();

};


class CEquipmentWindow {
private:
	CSV equipmentInfo;
	CSV *skillInfo;
	Graph Window;
	int equipmentKind;

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
	int ElementNum;//0Ç©ÇÁèáÇ…Å@ñ≥âŒñÿêÖåıà≈
	string Element;
	int FireDef;
	int WoodDef;
	int WaterDef;
	int LightDef;
	int DarkDef;
	int SellMoney;
	string skillName[2];
	int skillMP[2];
	int skillPower[2];
	int skillElementNum[2];
	string skillElement[2];
	string skillPMode[2];
	string skillExperience[2];
	int skillNum[2];

public:

	CEquipmentWindow(int equipmentKind,int num,int level);
	~CEquipmentWindow();
	void ChangeKind( int num, int level);
	void Draw();

};

class CYesNoWindow {
private:
	Graph Window[2];
	bool yes;
	bool *RF;
	int x, y;
	std::string Text;
public:
	CYesNoWindow(bool *RF, std::string Text,bool yes,int x,int y);
	void Loop();
	void Draw();

};

class CAmountGetWindow {
private:
	Graph Window;
	int x, y,amount,max;
	std::string Text;
public:
	CAmountGetWindow( std::string Text, int x, int y,int max);
	void Loop();
	void Draw();
	int GetAmount();

};

class CHaniwaWindow {
private:
	CSV *haniwaInfo;
	Graph Window;
	CMySaveData *mySaveData;

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
	int FireDef;
	int WoodDef;
	int WaterDef;
	int LightDef;
	int DarkDef;

public:

	CHaniwaWindow(CMySaveData *savedata,int kind);
	~CHaniwaWindow();
	void Draw();
	void ChangeKind(int kind);

};

class CSkillWindow {
private:
	Graph windowGraph;
	int num, haniLevel, lvChange;
	CSV *jikiSkill;


public:
	CSkillWindow(int num);
	~CSkillWindow();
	void Draw(int y);
	void ChangeNum(int num);


};

class CHaniwaSkillWindow {
private:
	Graph windowGraph;
	int num,haniLevel,lvChange;
	CSV *haniSkill;


public:
	CHaniwaSkillWindow(int num,int haniLevel);
	~CHaniwaSkillWindow();
	void Draw();
	void Draw(int y);
	void ChangeNum(int num);
	void ChangeLevel(int level);


};


class CExplainWindow {
public:
	CExplainWindow(int kind);
	void Loop();
	void Draw();
	int amountPage;
	int lookPage;
	Graph exGraph[4];

};

