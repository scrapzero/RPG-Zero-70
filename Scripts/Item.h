#pragma once


//#define Item(name,kindNum) name##[##kindNum##] 

#include "Suken.h"
#include "SaveData.h"
#include "Window.h"
#include <string>
#include <vector>

using namespace std;

typedef pair<int, int> intint;




class CItemManager {
private:
	int sorce[200],tool[60],food[100],itemSize,itemKind; 
	string mainItemKind;
	CSV itemInfo;
	CMySaveData *savedata;
	Graph window[2], Arrow;
	int lookLocate, lookPage;
	

public:
	CItemManager(int kind,CMySaveData *CSD);
	~CItemManager();
	void WindowLoop();
	void WindowDraw();
	void WindowDrawForRecipe();
	void Add(int itemKind,int num,int addAmount);
	void Remove(int itemKind, int num, int  removeAmount);
	void Sell(int amount);
	int GetAmount(int kind, int num);
	int GetPointNum();
	void ChangeDrawKind(int kind);
};
