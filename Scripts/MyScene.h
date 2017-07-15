
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
		CSV *ItemInfo[3];
		CSItemSet(CSTown& cstown);
		bool classStart;
		int step, arrowPoint, arrowPoint2;
		Graph Arrow,Window[3];

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