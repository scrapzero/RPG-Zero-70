#pragma once


#include "Suken.h"
#include "SaveData.h"
#include "Window.h"
#include "Equipment.h"
#include <string>
#include <vector>

#define effectTime1 60


using namespace std;

class CCharacterBase;

class CEffect1 {
public:
	CEffect1();
	~CEffect1();

	void PushEffect(CCharacterBase *fromChar, CCharacterBase *toChar);
	void DrawEffect();

private:

	struct SEffect {
		int drawTime;
		float x, y, vx, vy;
	};
	vector<SEffect> vSEffect;

	Graph Effect[1];


};

struct Skill
{
	int num;
	string neme;
	int  Point;
	char cardNum;
	bool hajime;
	Skill():Point(0), item(false),hajime(true) {}
	int MP, element,PMode, times;
	int classifyNum;
	int target[3];
	int classify[3];
	int content[3];
	int power[3];
	int speed;
	CCharacterBase *useChar;
	int UseNum;

	int targetNum;
	bool ene;
	bool item;
	int itemKind, itemNum;

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
	void Reset();

	

	virtual void Loop();
	virtual void Draw(int x, int y);
	virtual void Draw(int x,int y, bool nameZurasi);
	virtual void ItemDrop(CMySaveData *mySD ,CTextWindow *txWindow) {};

	void statusHenkaReset();
	void DrawHPBar(int x,int y, bool onlyLive);
	void DrawMPBar(int x, int y, bool onlyLive);
	void DrawStatusWindow(int x, int y);
	void DrawSmallHPBar(int x, int y, bool onlyLive);
	void DrawSmallMPBar(int x, int y, bool onlyLive);
	void DrawDamageAndCure();
	void DrawStatusHenkaWindow(int x,int y);

	void GiveDamge(int amount, CTextWindow *textWindow);
	void GiveCureHP(int amount, CTextWindow *textWindow);
	void GiveDamgeMP(int amount, CTextWindow *textWindow);
	void GiveCureMP(int amount, CTextWindow *textWindow);
	void GiveButuriDamge(CCharacterBase *atackChar,Skill *atackSkill, int skillNum, CTextWindow *textWindow, bool *hazureta);
	void GiveMahouDamge(CCharacterBase *atackChar, Skill *atackSkill, int skillNum, CTextWindow *textWindow, bool *hazureta);
	void Cure(Skill *atackSkill, int skillNum, CTextWindow *textWindow);
	void statusChange(Skill *atackSkill, int skillNum, CTextWindow *textWindow);
	void JoutaiIjou(Skill *atackSkill, int skillNum, CTextWindow *textWindow);
	void Tokusyu(CCharacterBase *atackChar, Skill *atackSkill, int skillNum, CTextWindow *textWindow);
	void DethJudge(CTextWindow *textWindow);

	void GiveDokuDamage(CTextWindow *textWindow, bool boss);

	Skill returnSkill();
	int returnSpead();
	void SkillSpeadRand();
	void skillHatudou(CCharacterBase *atackChar, Skill *atackSkill, int skillNum, CTextWindow *textWindow,bool *oneMore,bool *hazureta);


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

	int Level;

	int drawHP;
	int drawMP;


	int Element;//0Ç©ÇÁèáÇ…Å@ñ≥âŒñÿêÖåıà≈
	int damageCut[2];

	bool live,bigBoss,enemyF;
	int tenmetsu;
	int buturiDamageCut;
	int maHouDamageCut;
	bool doku, mahi, housin, huchi, hirumi;
	bool skill30, skill50;

	int element;
	int damageDisplayTime;
	int displayDamage;
	int cureDisplayTime;
	int displayCure;
	int damageMPDisplayTime;
	int displayDamageMP;
	int cureMPDisplayTime;
	int displayCureMP;
	int statusChangeDisplayTime;
	int displayStatusChange;
	int actTimes;


	int statusHenka[8];


	int dropItem[6][2];
	string dropItemName[6];

	
	Graph charGraph;
	Graph HPBar,MPBar,smallHPBar,smallMPBar;
	Graph Window[2];

	Skill skill[10];
	Skill normalAtack;
	Skill normalDefence;
	Skill *jikiSkillCard[4];

private:
	CEffect1 effect1;

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
	int kind;
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
	CSV *itemInfo;

	int kind;
	int skillNum[10];


public:

	CEnemy(CMySaveData *mySD, int kind,bool bigBoss);
	~CEnemy();
	void Draw(int x,int y,bool nameZurasi);
};



