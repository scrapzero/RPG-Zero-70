
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
	//～変数宣言～ 22*18

	enum {
		walkSpeed = 4

	};

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

	//初期化　画像のロードなども
	void Start();
	//処理　毎フレーム呼ばれる
	void Loop();
	//描画　毎フレーム呼ばれる
	void Draw();
	//後片付け	必要なら使おう
	void End();
};