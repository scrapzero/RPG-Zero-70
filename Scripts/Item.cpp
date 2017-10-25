#include "Item.h"
#include <algorithm>

bool KeyOK();
bool KeyCancel();
bool KeyRight();
bool KeyLeft();
bool KeyUp();
bool KeyDown();

CItemManager::CItemManager(int kind, CMySaveData *CSD) : itemInfo("")
{
	itemKind = kind;
	switch (kind) {
	case 0: 
	mainItemKind = "sorce";
	itemSize = 200;
	itemInfo = "zero/ZeroData/Sorce.csv";
	break;
	case 1:
	mainItemKind = "tool";
	itemSize = 60;
	itemInfo = "zero/ZeroData/Tool.csv";
	break;
	case 2:
	mainItemKind = "food";
	itemSize = 100;
	itemInfo = "zero/ZeroData/Food.csv";
	break;

	}
	savedata = CSD;


	for (int i = 0; i < 200; i++) {
		sorce[i]=CSD->GetItem(0, i);
	}
	for (int i = 0; i < 60; i++) {
		tool[i] = CSD->GetItem(1, i);
	}
	for (int i = 0; i < 100; i++) {
		food[i] = CSD->GetItem(2, i);
	}

	lookLocate = 0;
	lookPage = 0;
	
	window[0] = "zero/TextWindow4.png";
	window[1] = "zero/TextWindow2.png";
	Arrow = "zero/Arrow.png";

}

CItemManager::~CItemManager()
{
	for (int i = 0; i < 200; i++) {
		savedata->SetItem(0, i, sorce[i]);
	}
	for (int i = 0; i < 60; i++) {
		savedata->SetItem(1, i, tool[i]);
	}
	for (int i = 0; i < 100; i++) {
		savedata->SetItem(2, i, food[i]);
	}


	//savedata->WriteSaveData();

}




void CItemManager::WindowLoop()
{
	if (KeyRight()) {
		if (lookLocate % 2 == 1 &&itemSize > (lookPage + 1) * 20) {
			lookPage++;
			if (itemSize <= lookPage * 20 + lookLocate - 1) {
				lookLocate = 0;
			}
			else {
				lookLocate--;
			}
		}
		else if (lookLocate % 2 == 0 &&itemSize>lookPage * 20 + lookLocate + 1) {
			lookLocate++;
		}
	}

	if (KeyLeft()) {
		if (lookLocate % 2 == 0 && 0 <= lookPage - 1) {
			lookPage--;
			lookLocate++;
		}
		else if (lookLocate % 2 == 1) {
			lookLocate--;
		}
	}

	if (KeyUp() && lookLocate >= 2) {
		lookLocate -= 2;
	}

	if (KeyDown()) {
		if (lookLocate <= 17 &&itemSize>lookPage * 20 + lookLocate + 2) {
			lookLocate += 2;
		}
		else if (lookLocate <= 17 &&itemSize>lookPage * 20 + lookLocate + 1) {
			lookLocate++;
		}

	}

}

void CItemManager::WindowDraw()
{
	int myLoop = 0;
	std::string itemName[2] = {"" ,""};
	std::string effectName = "";
	int canUse = 0;
	int buyMoney = 0;

	window[0](0, 7);
	window[1](0, 370);

	Arrow(20 + 345 * (lookLocate % 2), 30 + (lookLocate / 2) * 30);
	itemName[1]=itemInfo[lookLocate + lookPage * 20][1];

	switch (itemKind)
	{
	case 0:
		buyMoney = itemInfo[lookLocate+lookPage * 20][2];
		DrawFormatString(16, 395, BLACK, "%s   個数:%d   売値:%d", itemName[1].c_str(),sorce[lookLocate+lookPage*20],buyMoney);
		break;
	case 1:
		buyMoney = itemInfo[lookLocate+lookPage * 20][3];
		canUse = itemInfo[lookLocate + lookPage*20][2];
		DrawFormatString(16, 395, BLACK, "%s   個数:%d   売値:%d", itemName[1].c_str(), tool[lookLocate + lookPage*20],buyMoney);
		DrawFormatString(16, 455, BLACK, "効果:");
		for (int i = 0; i < 3; i++){
			effectName=itemInfo[lookLocate + lookPage * 20][i+4];
			DrawFormatString(66, 455+i*30, BLACK, "%s", effectName.c_str());
		}

		break;
	case 2:
		buyMoney = itemInfo[lookLocate+lookPage * 20][3];
		canUse = itemInfo[lookLocate + lookPage*20][2];
		DrawFormatString(16, 395, BLACK, "%s   個数:%d   売値:%d", itemName[1].c_str(), food[lookLocate + lookPage*20],buyMoney);
		DrawFormatString(16, 455, BLACK, "効果:");
		for (int i = 0; i < 3; i++) {
			effectName = itemInfo[lookLocate + lookPage * 20][i + 4];
			DrawFormatString(66, 455 + i * 30, BLACK, "%s", effectName.c_str());
		}
		break;


	default:break;
	}

	if (itemKind > 0) {
		switch (canUse) {
		case 0:
			DrawFormatString(16, 425, BLACK, "使用場面:フィールドのみ");
			break;
		case 1:
			DrawFormatString(16, 425, BLACK, "使用場面:戦闘中のみ");
			break;
		case 2:

			DrawFormatString(16, 425, BLACK, "使用場面:フィールド、戦闘中どちらも可"); break;

		default:break;
		}
	}
	

	for (int i = lookPage * 20; i < itemSize; i++) {
		itemName[0] = itemInfo[i][1];
		DrawFormatString(45 + 345 * (i % 2), 32 + ((i % 20) / 2) * 30, BLACK, "%s", itemName[0].c_str());
		switch (itemKind)
		{
		case 0:
		DrawFormatString(245 + 345 * (i % 2), 32 + ((i % 20) / 2) * 30, BLACK, "×%d", sorce[i]);

		break;
		case 1:
		DrawFormatString(245 + 345 * (i % 2), 32 + ((i % 20) / 2) * 30, BLACK, "×%d", tool[i]);
		break;
		case 2:
		DrawFormatString(245 + 345 * (i % 2), 32 + ((i % 20) / 2) * 30, BLACK, "×%d", food[i]);
		break;
		

			default:break;
		}


		myLoop++;
		if (myLoop >= 20) {
			break;
		}
	}

	DrawFormatString(40, 340, BLACK, "ページ　%d/%d" , lookPage + 1, (itemSize - 1) / 20 + 1);



}

void CItemManager::WindowDrawForRecipe()
{
	int myLoop = 0;
	std::string itemName[2] = { "" ,"" };
	std::string effectName = "";
	int canUse = 0;
	int buyMoney = 0;

	window[1](0, 370);

	itemName[1] = itemInfo[lookLocate + lookPage * 20][1];

	switch (itemKind)
	{
	case 0:
		buyMoney = itemInfo[lookLocate + lookPage * 20][2];
		DrawFormatString(16, 395, BLACK, "%s   個数:%d   売値:%d", itemName[1].c_str(), sorce[lookLocate + lookPage * 20], buyMoney);
		break;
	case 1:
		buyMoney = itemInfo[lookLocate + lookPage * 20][3];
		canUse = itemInfo[lookLocate + lookPage * 20][2];
		DrawFormatString(16, 395, BLACK, "%s   個数:%d   売値:%d", itemName[1].c_str(), tool[lookLocate + lookPage * 20], buyMoney);
		DrawFormatString(16, 455, BLACK, "効果:");
		for (int i = 0; i < 3; i++) {
			effectName = itemInfo[lookLocate + lookPage * 20][i + 4];
			DrawFormatString(66, 455 + i * 30, BLACK, "%s", effectName.c_str());
		}

		break;
	case 2:
		buyMoney = itemInfo[lookLocate+lookPage * 20][3];
		canUse = itemInfo[lookLocate + lookPage * 20][2];
		DrawFormatString(16, 395, BLACK, "%s   個数:%d   売値:%d", itemName[1].c_str(), food[lookLocate + lookPage * 20], buyMoney);
		DrawFormatString(16, 455, BLACK, "効果:");
		for (int i = 0; i < 3; i++) {
			effectName = itemInfo[lookLocate + lookPage * 20][i + 4];
			DrawFormatString(66, 455 + i * 30, BLACK, "%s", effectName.c_str());
		}
		break;


	default:break;
	}

	if (itemKind > 0) {
		switch (canUse) {
		case 0:
			DrawFormatString(16, 425, BLACK, "使用場面:フィールドのみ");
			break;
		case 1:
			DrawFormatString(16, 425, BLACK, "使用場面:戦闘中のみ");
			break;
		case 2:

			DrawFormatString(16, 425, BLACK, "使用場面:フィールド、戦闘中どちらも可"); break;

		default:break;
		}
	}

}

void CItemManager::Add(int itemKind, int num, int addAmount)
{
	switch (itemKind)
	{
	case 0:
		if (num <= 200) {
			sorce[num-1] += addAmount;
		}
		if (sorce[num - 1] > 9999) {
			sorce[num - 1] = 9999;
		}
		break;
	case 1:
		if (num <= 60) {
			tool[num-1] += addAmount;
		}
		if (tool[num - 1] > 9999) {
			tool[num - 1] = 9999;
		}
		break;
	case 2:
		if (num <= 100) {
			food[num-1] += addAmount;
		}
		if (food[num - 1] > 9999) {
			food[num - 1] = 9999;
		}
		break;

	default:break;
	}
}

void CItemManager::Remove(int itemKind, int num, int removeAmount)
{

	switch (itemKind)
	{
	case 0:
		if (num > 0) {
			sorce[num-1] -= removeAmount;
		}
		if (sorce[num-1] < 0) {
			sorce[num-1] = 0;
		}

		break;
	case 1:
		if (num >0) {
			tool[num-1] -= removeAmount;
		}

		if (tool[num-1] < 0) {
			tool[num-1] = 0;
		}
		break;
	case 2:
		if (num >0) {
			food[num-1] -= removeAmount;
		}
		if (food[num-1] <0) {
			food[num-1] = 0;
		}

		break;

	default:break;
	}


}

void CItemManager::Sell(int amount)
{
	int num = lookLocate + (lookPage * 20) + 1;
	int buff=0;

	switch (itemKind)
	{
	case 0:
		if (num > 0) {
			sorce[num - 1] -= amount;
		}
		if (sorce[num - 1] < 0) {
			sorce[num - 1] = 0;
		}
		buff = itemInfo[num - 1][2];
		buff *= amount;
		savedata->money += buff;
		break;
	case 1:
		if (num >0) {
			tool[num - 1] -= amount;
		}

		if (tool[num - 1] < 0) {
			tool[num - 1] = 0;
		}
		buff = itemInfo[num - 1][3];
		buff *= amount;
		savedata->money += buff;
		break;
	case 2:
		if (num >0) {
			food[num - 1] -= amount;
		}
		if (food[num - 1] <0) {
			food[num - 1] = 0;
		}

		buff = itemInfo[num - 1][3];
		buff *= amount;
		savedata->money += buff;
		break;

	default:break;
	}

	if (savedata->money>99999999) {
		savedata->money = 99999999;
	}

}

int CItemManager::GetAmount(int kind, int num)
{
	switch (kind) {
	case 0:return sorce[num-1]; break;
	case 1:return tool[num-1]; break;
	case 2:return food[num-1]; break;
	}
	return 0;

}

int CItemManager::GetPointNum()
{
	return lookLocate+lookPage*20+1;
}

void CItemManager::ChangeDrawKind(int kind)
{
	lookLocate = kind % 20;
	lookPage = kind / 20;

}



