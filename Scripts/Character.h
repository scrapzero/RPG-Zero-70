#pragma once


#include "Suken.h"
#include "SaveData.h"
#include "Window.h"
#include "Equipment.h"
#include <string>
#include <vector>


using namespace std;

struct Skill
{
	int num;
	string neme;
	int  Point;
	Skill():Point(0){}
	int MP, element,PMode, times;
	int classifyNum;
	int target[3];
	int classify[3];
	int content[3];
	int power[3];
	int speed;

	int targetNum;
	bool ene;

	string experience;

	bool operator < (const Skill& s) {
		return this->speed < s.speed;
	}
	bool operator > (const Skill& s) {
		return this->speed > s.speed;
	}
};



class CCharacterBase {
public:
	CCharacterBase();
	~CCharacterBase();
	virtual void Loop();
	virtual void Draw(int x, int y);
	virtual void Draw(int x,int y, bool nameZurasi);
	void statusHenkaReset();
	void DrawHPBar(int x,int y, bool onlyLive);
	void DrawMPBar(int x, int y, bool onlyLive);
	void DrawStatusWindow(int x, int y);
	void DrawSmallHPBar(int x, int y, bool onlyLive);
	void DrawSmallMPBar(int x, int y, bool onlyLive);
	void DrawDamage();

	void GiveDamge(int amount, CTextWindow *textWindow);
	void GiveButuriDamge(CCharacterBase *atackChar,Skill *atackSkill, int skillNum, CTextWindow *textWindow);
	void GiveMahouDamge(CCharacterBase *atackChar, Skill *atackSkill, int skillNum, CTextWindow *textWindow);
	void Cure(Skill *atackSkill, int skillNum, CTextWindow *textWindow);
	void statusChange(Skill *atackSkill, int skillNum, CTextWindow *textWindow);
	void JoutaiIjou(Skill *atackSkill, int skillNum, CTextWindow *textWindow);
	void DethJudge(CTextWindow *textWindow);

	string name;
	int x, y;
	int MaxHP;
	int MaxMP;
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
	int Status[17];

	int Element;//0Ç©ÇÁèáÇ…Å@ñ≥âŒñÿêÖåıà≈


	bool live;
	int tenmetsu;
	bool doku, mahi, housin, huchi, hirumi;

	int element;
	int damageDisplayTime;
	int displayDamage;


	int statusHenka[8];

	
	Graph charGraph;
	Graph HPBar,MPBar,smallHPBar,smallMPBar;
	Graph Window[2];

	Skill skill[10];
	Skill normalAtack;
	Skill normalDefence;

};

class CJiki :public CCharacterBase{
private:
	CEquipmentManager *equipManager;
	CSV *equipmentInfo;
	CSV *skillInfo;
	CMySaveData *mySaveData;
	int wearWeaponNumLevel[5][3];
	int skillNum[6];

	

public:
	
	CJiki(CMySaveData *mySD);
	~CJiki();
	void Draw(int x, int y);

};


class CHaniwa :public CCharacterBase {
private:
	CMySaveData *mySaveData;
	CSV *haniwaInfo;
	CSV * haniwaSkillInfo;
	CSV * skillInfo;

	int wearWeaponNumLevel[5][3];
	int kind, Level;
	int skillNum[4];


public:
	CHaniwa(CMySaveData *mySD, int kind);
	~CHaniwa();
	void Draw(int x, int y);

};

class CEnemy :public CCharacterBase {
private:
	CMySaveData *mySaveData;
	CSV *enemyInfo;
	CSV *skillInfo;

	int wearWeaponNumLevel[5][3];
	int kind;
	int skillNum[5];
	int Item[4][2];


public:
	CEnemy(CMySaveData *mySD, int kind);
	~CEnemy();
	void Draw(int x,int y,bool nameZurasi);

};

