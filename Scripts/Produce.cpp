#include "Produce.h"
#include <algorithm>
#include "MyScene.h"

bool KeyOK();
bool KeyCancel();
bool KeyRight();
bool KeyLeft();
bool KeyUp();
bool KeyDown();



CProduce::CProduce(CMySaveData * CSD, int proKind) :RecipeInfo("")
{
	int buf;

	savedata = CSD;

	this->proKind= proKind;
	switch (proKind)
	{

	case 0:	RecipeInfo = "zero/ZeroData/SoadRecipe.csv";
		kindNum=100; 
		recipeNameKind = "剣レシピ";
		break;
	case 1: RecipeInfo = "zero/ZeroData/ArrowRecipe.csv";
		kindNum = 100; 
		recipeNameKind = "弓レシピ";
		break;
	case 2: RecipeInfo = "zero/ZeroData/WandRecipe.csv";
		kindNum=100; 
		recipeNameKind = "杖レシピ";
		break;
	case 3:	RecipeInfo = "zero/ZeroData/ShieldRecipe.csv"; 
		recipeNameKind = "盾レシピ";
		kindNum = 100;
		break;
	case 4: RecipeInfo = "zero/ZeroData/ProtecterRecipe.csv"; 
		recipeNameKind = "胴レシピ";
		kindNum = 100;
		break;
	case 5: RecipeInfo = "zero/ZeroData/ShoesRecipe.csv"; 
		recipeNameKind = "靴レシピ";
		kindNum = 100;
		break;
	case 6: RecipeInfo = "zero/ZeroData/AccessoryRecipe.csv"; 
		recipeNameKind = "装飾品レシピ";
		kindNum = 100;
		break;
	case 7: RecipeInfo = "zero/ZeroData/SorceRecipe.csv"; 
		recipeNameKind = "加工素材レシピ";
		kindNum = 100;
		break;
	case 8: RecipeInfo = "zero/ZeroData/ToolRecipe.csv"; 
		recipeNameKind = "道具レシピ";
		kindNum = 100;
		break;
	case 9: RecipeInfo = "zero/ZeroData/FoodRecipe.csv"; 
		kindNum = 100;
		recipeNameKind = "料理レシピ";
		break;
	default: break;
	}

	SorceInfo[0] = new CSV("zero/ZeroData/Sorce.csv");
	SorceInfo[1] = new CSV("zero/ZeroData/Tool.csv");
	SorceInfo[2] = new CSV("zero/ZeroData/Food.csv");

	lookLocate = 0;
	lookPage = 0;
	step = 0;
	makeMax = 99;
	madeF = false;
	stepChangeF = false;
	sozaiAru = true;

	Window[1] = "zero/RecipeWindow1.png";
	Window[2] = "zero/RecipeWindow2.png";
	Window[3] = "zero/ProductWindow1.png";
	Window[4] = "zero/ProductWindow2.png";
	if (proKind <= 6) {
		Window[0] = "zero/TextWindow4.png"; 
		equipmentWindow = new CEquipmentWindow(proKind,1,0);
		equipManager = new CEquipmentManager(savedata, proKind);
		itemManager = new CItemManager(0, savedata);
	}
	else {
		itemManager = new CItemManager(proKind - 7, savedata);
		buf = RecipeInfo[0][2];
		itemManager->ChangeDrawKind(buf-1);
	}


	Arrow = "zero/SmallArrow.png";


}

CProduce::~CProduce()
{
	if (proKind <= 6) {
		delete equipManager;
		delete equipmentWindow;
		equipManager = NULL;
		equipmentWindow = NULL;
	}
	delete itemManager;
	itemManager = NULL;
}

void CProduce::WindowLoop()
{
	stepChangeF = false;
	sozaiAru = true;
	makeMax = 99;
	int bu = 0;
	int buf = 0;
	int buff, bufff;

	for (int i = 0, looptime = RecipeInfo[lookLocate + lookPage * 20][4]; i < looptime; i++) {
		
		buf = RecipeInfo[lookLocate + lookPage * 20][5 + i * 3];
		buff = RecipeInfo[lookLocate + lookPage * 20][6 + i * 3];
		bufff = RecipeInfo[lookLocate + lookPage * 20][7 + i * 3];
		if (itemManager->GetAmount(buf - 7, buff) < bufff) {
			sozaiAru = false;
		}
		if (makeMax > itemManager->GetAmount(buf - 7, buff) / bufff) {
			makeMax = itemManager->GetAmount(buf - 7, buff) / bufff;
		}
	}



	if (step == 0) {

		if (KeyRight()) {
			if (lookLocate % 2 == 1 && kindNum > (lookPage + 1) * 20) {
				lookPage++;
				if (kindNum <= lookPage * 20 + lookLocate - 1) {
					lookLocate = 0;
				}
				else {
					lookLocate--;
				}
			}
			else if (lookLocate % 2 == 0 && kindNum > lookPage * 20 + lookLocate + 1) {
				lookLocate++;
			}

			if (proKind <= 6) {
				equipmentWindow->ChangeKind(RecipeInfo[lookLocate + (lookPage * 20)][2],0);
			}
			else {
				buf = RecipeInfo[lookLocate + (lookPage * 20)][2];
				itemManager->ChangeDrawKind(buf-1);
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

			if (proKind <= 6) {
				equipmentWindow->ChangeKind(RecipeInfo[lookLocate + (lookPage * 20)][2], 0);
			}
			else {
				buf = RecipeInfo[lookLocate + (lookPage * 20)][2];
				itemManager->ChangeDrawKind(buf - 1);
			}
		}

		if (KeyUp() && lookLocate >= 2) {
			lookLocate -= 2;
			if (proKind <= 6) {
				equipmentWindow->ChangeKind(RecipeInfo[lookLocate + (lookPage * 20)][2], 0);
			}
			else {
				buf = RecipeInfo[lookLocate + (lookPage * 20)][2];
				itemManager->ChangeDrawKind(buf - 1);
			}
		}

		if (KeyDown()) {
			if (lookLocate <= 17 && kindNum > lookPage * 20 + lookLocate + 2) {
				lookLocate += 2;
			}
			else if (lookLocate <= 17 && kindNum > lookPage * 20 + lookLocate + 1) {
				lookLocate++;
			}
			if (proKind <= 6) {
				equipmentWindow->ChangeKind(RecipeInfo[lookLocate + (lookPage * 20)][2], 0);
			}
			else {
				buf = RecipeInfo[lookLocate + (lookPage * 20)][2];
				itemManager->ChangeDrawKind(buf - 1);
			}

		}

		if (KeyOK() && stepChangeF == false && sozaiAru == true) {
			step = 1;
			stepChangeF = true;
			if (proKind <= 6) {
				yesNoWindow = new CYesNoWindow(&madeF, "この武器を作るんだな？", true, 90, 120);
			}
			else {
				amountGetWindow = new CAmountGetWindow("何個作る？", 90, 120, makeMax);
			}
		}
	}

	if (step == 1) {
		if (proKind <= 6) {
			yesNoWindow->Loop();
			if (KeyOK() && stepChangeF == false) {
				stepChangeF = true;
				step = 0;
				delete yesNoWindow;
				yesNoWindow = NULL;
				if (madeF == true) {
					bu = RecipeInfo[lookLocate + lookPage * 20][2];
					equipManager->PushEquipment(proKind, bu, 0);
					for (int i = 0, looptime = RecipeInfo[lookLocate + lookPage * 20][4]; i < looptime; i++) {
						buf = RecipeInfo[lookLocate + lookPage * 20][5 + i * 3];
						buff = RecipeInfo[lookLocate + lookPage * 20][6 + i * 3];
						bufff = RecipeInfo[lookLocate + lookPage * 20][7 + i * 3];
						itemManager->Remove(buf-7, buff, bufff);
					}

				}
			}
		}

		if (proKind >= 7) {
			amountGetWindow->Loop();
			if (KeyOK() && stepChangeF == false) {
				stepChangeF = true;
				step = 0;
					bu=RecipeInfo[lookLocate + lookPage * 20][2];
					itemManager->Add(proKind - 7, bu, amountGetWindow->GetAmount());
					for (int i = 0, looptime = RecipeInfo[lookLocate + lookPage * 20][4]; i < looptime; i++) {
						buf = RecipeInfo[lookLocate + lookPage * 20][5 + i * 3];
						buff = RecipeInfo[lookLocate + lookPage * 20][6 + i * 3];
						bufff = RecipeInfo[lookLocate + lookPage * 20][7 + i * 3];
						bufff *= amountGetWindow->GetAmount();
						itemManager->Remove(buf - 7, buff, bufff);
				}

					delete amountGetWindow;
					amountGetWindow = NULL;

			}
			else if (KeyCancel()) {
				stepChangeF = true;
				step = 0;
				delete amountGetWindow;
				amountGetWindow = NULL;
			}

		}


	}


}


void CProduce::WindowDraw()
{
	int buf, buff, bufff,buffff;
	std::string name = "";

	
	if (step <= 1) {
		Window[2](2, 10);
		Window[1](450, 10);
		DrawFormatString(40, 20, BLACK, "%s",recipeNameKind.c_str());
		Arrow(18 + (lookLocate % 2) * 200, 52 + (lookLocate / 2) * 30);

		if (proKind <= 6) {
			equipmentWindow->Draw();
		}
		if (proKind >6) {
			itemManager->WindowDrawForRecipe();
		}

		for (int i = lookPage * 20; i < (lookPage * 20) + 20; i++) {
			name = RecipeInfo[i][3];
			DrawFormatString(40 + ( i% 2) * 200, 52 + ((i % 20) / 2) * 30, BLACK, "%s", name.c_str());
			if (i >= kindNum) {
				break;
			}
		}

		for (int i = 0, looptime = RecipeInfo[lookLocate + lookPage * 20][4]; i < looptime; i++) {
			buf = RecipeInfo[lookLocate + lookPage * 20][5 + i * 3];
			buff = RecipeInfo[lookLocate + lookPage * 20][6 + i * 3];
			bufff = RecipeInfo[lookLocate + lookPage * 20][7 + i * 3];
			buffff=RecipeInfo[lookLocate + lookPage * 20][2];
			name = (*SorceInfo[buf - 7])[buff - 1][1];
			DrawFormatString(460, 80 + i * 56, BLACK, "%s  ×%d /%d個所持", name.c_str(), bufff,itemManager->GetAmount(buf-7,buff));
		}
		if (sozaiAru == false) {
			DrawFormatString(500, 330, RED_DP, "素材が足りません");
			if (proKind <= 6 && equipManager->GetSize(proKind)>=50) {
				DrawFormatString(500, 330, RED_DP, "これ以上この装備類はもてません。");
			}
			if (proKind > 6 && itemManager->GetAmount(proKind-7,buffff) >= 999) {
				DrawFormatString(500, 330, RED_DP, "これ以上このアイテムはもてません。");
			}
		}

	}

	if (step == 1) {
		if (proKind <=6) {
			yesNoWindow->Draw();
		}
		else {
			amountGetWindow->Draw();
		}

	}

}

bool CProduce::GetStepChangeFlag()
{
	return stepChangeF;
}

