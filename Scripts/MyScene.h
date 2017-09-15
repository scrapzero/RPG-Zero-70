
#pragma once

/**
*	@file	MyScene.cpp
*	@brief	シーンクラスの宣言は、ここでしましょう
*	@author	-
*/


#include "Suken.h"
#include "Window.h"
#include "Equipment.h"
#include "SaveData.h"
#include "Item.h"
#include "Produce.h"
#include "Character.h"


struct Squest
{
	int Qnum;
	string Qname;
	int enemy[8];
	int bossTimes;
	int bigBoss[3];
	int boss[3][3][2];//何回目、何体目、種類匹数
	int treasure[5][3];
	int rewardMoney;
	int difficult;
	int qLevel;

};

enum {
	walkSpeed = 4,
	syokyuMap = 1,
	zyoukyuuMap = 0
	
};

using namespace std;


class CSTitle :public CScene {
	CTextWindow *textWindow;
	CEquipmentManager *equipmentManager;
	CMySaveData *mySaveData;
	CItemManager *ItemManager;
	CProduce *product;
	int money;


	//初期化　画像のロードなども
	void Start();
	//処理　毎フレーム呼ばれる
	void Loop();
	//描画　毎フレーム呼ばれる
	void Draw();
	//後片付け	FlipSceneされた時に呼び出される
	void End();
};

class CSTown :public CScene {
	//〜変数宣言〜 22*18



	CMySaveData *mySaveData;
	Graph jikiGraph[12],mapChip[156];
	MCE TownMap;
	int jikiX, jikiY, jikiMapX, jikiMapY;
	int mapWidth, mapHeight,scrollX,scrollY;
	int moveDirect,graphDirect,graphStep;//下左右上止
	bool moveF,animeF;
	bool canMoveLeft, canMoveRight, canMoveDown, canMoveUp;

	class CSProTool :public CScene {
	public:
		CSTown& cstown;
		CTextWindow *textWindow;
		CProduce *produce;
		CSProTool(CSTown& cstown);
		bool classStart;
		int step;

		void Loop();
		void Draw();
		void End();

	};

	class CSProEquipment :public CScene {
	public:
		CSTown& cstown;
		CTextWindow *textWindow;
		CProduce *produce;
		Graph kindSerectWindow, arrowGraph;
		CSProEquipment(CSTown& cstown);
		bool classStart;
		int step, arrowPoint;
		string S;

		void Loop();
		void Draw();
		void End();

	};

	class CSCook :public CScene {
	public:
		CSTown& cstown;
		CTextWindow *textWindow;
		CProduce *produce;
		CSCook(CSTown& cstown);
		bool classStart;
		int step;

		void Loop();
		void Draw();
		void End();

	};

	class CSSorceRemake :public CScene {
	public:
		CSTown& cstown;
		CTextWindow *textWindow;
		CProduce *produce;
		CSSorceRemake(CSTown& cstown);
		bool classStart;
		int step;

		void Loop();
		void Draw();
		void End();

	};

	class CSItemSet :public CScene {
	public:
		CSTown& cstown;
		CTextWindow *textWindow;
		CItemManager *itemManger;
		CSV *ItemInfo[3];
		CSItemSet(CSTown& cstown);
		bool classStart,closeWindow;
		int step, arrowPoint, arrowPoint2,arrowPoint3;
		Graph Arrow,Window[3];

		void Loop();
		void Draw();
		void End();

	};

	class CSSetEquipment :public CScene {
	public:
		CSTown& cstown;
		CTextWindow *textWindow;
		CSV *ItemInfo;
		CEquipmentManager *equipManger;
		CSSetEquipment(CSTown& cstown);
		bool classStart, closeWindow;
		int step, arrowPoint, arrowPoint2, arrowPoint3;
		Graph Arrow, Window[3];

		void Loop();
		void Draw();
		void End();

	};

	class CSSellItem :public CScene {
	public:
		CSTown& cstown;
		CTextWindow *textWindow;
		CSSellItem(CSTown& cstown);
		CEquipmentManager *equipManager;
		CItemManager *itemManager;
		CYesNoWindow *ynWindow;
		CAmountGetWindow *amountGetWindow;
		bool classStart,yn;
		int step, arrowPoint, arrowPoint2, arrowPoint3;
		Graph Arrow, Window[3];

		void Loop();
		void Draw();
		void End();

	};

	class CSMenueWindow :public CScene {
	public:
		CSTown& cstown;
		CTextWindow *textWindow;
		CSMenueWindow(CSTown& cstown);
		CEquipmentManager *equipManager;
		CItemManager *itemManager;
		CEquipmentWindow *equipWindow;
		CYesNoWindow *ynWindow;
		bool classStart, yn;
		char wearWeaponNumLevel[5][3];
		int step, arrowPoint, arrowPoint2, arrowPoint3;
		Graph Arrow, Window[5];
		CSV *equipmentInfo;
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
		int Status[16];

		void Loop();
		void Draw();
		void End();

	};


	class CSHaniwa :public CScene {
	public:
		CSTown& cstown;
		CTextWindow *textWindow;
		CSHaniwa(CSTown& cstown);
		CHaniwaSkillWindow *haniSkillWindow;
		CSV *haniwaInfo;
		CSV *haniwaSkillInfo;
		bool classStart;
		int step,arrow,arrow2,arrow3;
		Graph Arrow, Window[4];
		CYesNoWindow *ynWindow;
		CHaniwaWindow *haniwaWindow;
		bool LvUP;


		void Loop();
		void Draw();
		void End();

	};

	class CSGoToQuest :public CScene {
	private:
		

		Graph Arrow, Window[4];
	public:
		CSTown& cstown;
		CTextWindow *textWindow;
		CSV *questInfo;
		CSV *enemyInfo;
		CSV *bigBossInfo;
		CYesNoWindow *ynWindow;
		Squest bufq;
		vector <Squest> *vq;
		CSGoToQuest(CSTown& cstown);
		~CSGoToQuest();
		int qLevel;
		bool classStart;
		bool goQuest;
		int step;
		int arrowPoint[3];


		void Loop();
		void Draw();
		void End();

	};


	//初期化　画像のロードなども
	void Start();
	//処理　毎フレーム呼ばれる
	void Loop();
	//描画　毎フレーム呼ばれる
	void Draw();
	//後片付け	必要なら使おう
	void End();
};

class CSQuestBase :public CScene {
public:
	CSQuestBase(int mapNum,Squest *bufVQ);
	~CSQuestBase();
private:

	CTextWindow *textWindow;
	Squest *vq;
	int mapLocateX, mapLocateY;
	CMySaveData *mySaveData;
	Graph jikiGraph[12];
	int mapNum;
	int mode[2];
	CSV *itemInfo;
	bool takara[3];
	bool retire;
	int startAppearEn,bossN;

	int bufjikiX, bufjikiY, bufjikiMapX, bufjikiMapY;
	int  bufscrollX, bufscrollY;

	CCharacterBase *character[3];

	//初期化　画像のロードなども
	void Start() {};
	//処理　毎フレーム呼ばれる
	void Loop();
	//描画　毎フレーム呼ばれる
	void Draw();
	//後片付け	FlipSceneされた時に呼び出される
	void End() {};


	class CSMap :public CScene {
	public:
		CSMap(CSQuestBase& csQuestBase);
		~CSMap();
	private:
		Graph mapChip[156];
		CSQuestBase & csQuestBase;
		MCE QuestMap;
		int jikiX, jikiY, jikiMapX, jikiMapY;
		int mapWidth, mapHeight, scrollX, scrollY;
		int moveDirect, graphDirect, graphStep;//下左右上止
		bool moveF, animeF;
		bool canMoveLeft, canMoveRight, canMoveDown, canMoveUp;
		int appearEN;

		void takaraGet(int reado);

		//初期化　画像のロードなども
		void Start() {};
		//処理　毎フレーム呼ばれる
		void Loop();
		//描画　毎フレーム呼ばれる
		void Draw();
		//後片付け	FlipSceneされた時に呼び出される
		void End() {};
	};

	class CSBattle :public CScene {
	public:
		CSBattle(CSQuestBase& csQuestBase, bool boss, int bossNum);
		~CSBattle();
	private:
		Graph backGraph;
		CSQuestBase & csQuestBase;
		int enAmount;
		CCharacterBase *enemy[5];
		bool boss;
		int bossNum;
		int arrow[3];

		


		//初期化　画像のロードなども
		void Start() {};
		//処理　毎フレーム呼ばれる
		void Loop();
		//描画　毎フレーム呼ばれる
		void Draw();
		//後片付け	FlipSceneされた時に呼び出される
		void End() {};
	};



};

