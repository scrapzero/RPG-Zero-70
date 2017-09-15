#include "MyScene.h"

bool KeyOK();
bool KeyCancel();
bool KeyRight();
bool KeyLeft();
bool KeyUp();
bool KeyDown();

void CSTown::Start() {
	LoadDivGraph("zero/jiki.png", 12, 3, 4, 32, 32,jikiGraph);
	LoadDivGraph("zero/MyMapChip1.png", 156, 26, 6, 32, 32, mapChip);
	TownMap = "zero/MCE/Town.mce";
	mapWidth = TownMap.GetWidth();
	mapHeight = TownMap.GetHeight();
	jikiX = 11 * 32;
	jikiY = 10 * 32;
	jikiMapX = 40;
	jikiMapY = 34;
	scrollX = 29 * 32;
	scrollY = 24 * 32;
	moveDirect = 4;
	graphDirect = 0;
	graphStep = 1;
	moveF = false;
	animeF = false;
	canMoveDown = false;
	canMoveLeft = false;
	canMoveRight = false;
	canMoveUp = false;
	mySaveData = new CMySaveData(true);

}

void CSTown::Loop() {
	int HitKeyNum = 0;
	canMoveDown = true;
	canMoveLeft = true;
	canMoveRight = true;
	canMoveUp = true;
	int checkAround[2] = {};
	int jikiStandChip[2] = { TownMap.Get(TownMap.layer.C, jikiMapX, jikiMapY) -1, TownMap.Get(TownMap.layer.B, jikiMapX, jikiMapY) -1 };

	if (jikiMapX > 0) {
		checkAround[0] = TownMap.Get(TownMap.layer.C, jikiMapX - 1, jikiMapY)-1;
		checkAround[1] = TownMap.Get(TownMap.layer.B, jikiMapX - 1, jikiMapY)-1;

		if (jikiStandChip[0]<26||jikiStandChip[0]%26>=20 ) {
			if (checkAround[0] >= 26 && checkAround[0] % 26 < 20 ) {
				canMoveLeft = false;
			}
			if ( checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
				canMoveLeft = false;
			}
		}
		if (jikiStandChip[1]<26 || jikiStandChip[1] % 26 >= 20) {
			if (jikiStandChip[1] >= 0 && jikiStandChip[1] % 26 != 25) {
				if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
					canMoveLeft = false;
				}
				if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
					canMoveLeft = false;
				}
			}
		}

		if (jikiStandChip[0] >= 27 && jikiStandChip[0]  <40) {
			if (checkAround[0] < 27 || checkAround[0] >=40) {
				if (checkAround[0] >= 0) {
					canMoveLeft = false;
				}
			}
			if (checkAround[1] < 27 || checkAround[1] >= 40 ) {
				if (checkAround[1] >= 0) {
					canMoveLeft = false;
				}
			}
		}

		if (jikiStandChip[1]%26==25) {
			if (checkAround[0] <= 26 || checkAround[0] >= 40) {
				if (checkAround[0] >= 0) {
					canMoveLeft = false;
				}
				else {
					canMoveLeft = true;
				}
			}
			else {
				canMoveLeft = true;
			}
		}

		if (checkAround[1] % 26 == 25 || jikiStandChip[1] % 26 == 25) {
			if (jikiStandChip[0] >= 27 && jikiStandChip[0]  <40) {
				if (checkAround[0] >= 27 && checkAround[0] < 40) {

					canMoveLeft = true;
				}
			}
		}

	}

	if (jikiMapY > 0) {
		checkAround[0] = TownMap.Get(TownMap.layer.C, jikiMapX , jikiMapY-1) - 1;
		checkAround[1] = TownMap.Get(TownMap.layer.B, jikiMapX , jikiMapY-1) - 1;
		
		if (jikiStandChip[0]<26 || jikiStandChip[0] % 26 >= 20) {
			if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
				canMoveUp = false;
			}
			if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
				canMoveUp = false;
			}
		}
		if (jikiStandChip[1]<26 || jikiStandChip[1] % 26 >= 20) {
			if (jikiStandChip[1] >= 0) {
				if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
					canMoveUp = false;
				}
				if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
					canMoveUp = false;
				}
			}
		}

		if (jikiStandChip[0] >= 27 && jikiStandChip[0]  <40) {
			if (checkAround[0] < 27 || checkAround[0] >= 40 ) {
				if (checkAround[0] >= 0) {
					canMoveUp = false;
				}
			}
			if (checkAround[1] < 27 || checkAround[1] >= 40) {
				if (checkAround[1] >= 0) {
					canMoveUp = false;
				}
			}
		}

		if (jikiStandChip[1] % 26 == 25) {
			if (checkAround[0] ==26 || checkAround[0] >= 40) {
				if (checkAround[0] % 26 < 20) {
					canMoveUp = false;
				}
				else {
					canMoveUp = true;
				}
			}
			else {
				canMoveUp = true;
			}
		}

		if (checkAround[1] % 26 == 25) {
			canMoveUp = true;
		}

	}

	if (jikiMapX+1 < mapWidth) {
		checkAround[0] = TownMap.Get(TownMap.layer.C, jikiMapX + 1, jikiMapY) - 1;
		checkAround[1] = TownMap.Get(TownMap.layer.B, jikiMapX + 1, jikiMapY) - 1;

		if (jikiStandChip[0]<26 || jikiStandChip[0] % 26 >= 20) {
			if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
				canMoveRight = false;
			}
			if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
				canMoveRight = false;
			}
		}
		if (jikiStandChip[1]<26 || jikiStandChip[1] % 26 >= 20) {
			if (jikiStandChip[1] >= 0 && jikiStandChip[1] % 26 != 25) {
				if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
					canMoveRight = false;
				}
				if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
					canMoveRight = false;
				}
			}
		}

		if (jikiStandChip[0] >= 27 && jikiStandChip[0]  <40) {
			if (checkAround[0] < 27 || checkAround[0] >= 40) {
				if (checkAround[0] >= 0) {
					canMoveRight = false;
				}
			}
			if (checkAround[1] < 27 || checkAround[1] >= 40) {
				if (checkAround[1] >= 0) {
					canMoveRight = false;
				}
			}
		}

		if (jikiStandChip[1] % 26 == 25) {
			if (checkAround[0] <= 26 || checkAround[0] >= 40) {
				if (checkAround[0] >=0) {
					canMoveRight = false;
				}
				else {
					canMoveRight = true;
				}
			}
			else {
				canMoveRight = true;
			}
		}

		if (checkAround[1] % 26 == 25 || jikiStandChip[1] % 26 == 25) {
			if (jikiStandChip[0] >= 27 && jikiStandChip[0]  <40) {
				if (checkAround[0] >= 27 && checkAround[0] < 40) {

					canMoveRight = true;
				}
			} 
		}

	}

	if (jikiMapY+1 < mapHeight) {
		checkAround[0] = TownMap.Get(TownMap.layer.C, jikiMapX , jikiMapY+1) - 1;
		checkAround[1] = TownMap.Get(TownMap.layer.B, jikiMapX , jikiMapY+1) - 1;

		if (jikiStandChip[0]<26 || jikiStandChip[0] % 26 >= 20) {
			if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
				canMoveDown = false;
			}
			if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
				canMoveDown = false;
			}
		}
		if (jikiStandChip[1]<26 || jikiStandChip[1] % 26 >= 20) {
			if (jikiStandChip[1] >= 0) {
				if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
					canMoveDown = false;
				}
				if (checkAround[1] >= 26 && checkAround[1] % 26 < 20 ) {
					canMoveDown = false;
				}
			}
		}

		if (jikiStandChip[0] >= 27 && jikiStandChip[0]  <40) {
			if (checkAround[0] < 27 || checkAround[0] >= 40) {
				if (checkAround[0] >= 0) {
					canMoveDown = false;
				}
			}
			if (checkAround[1] < 27 || checkAround[1] >= 40) {
				if (checkAround[1] >= 0) {
					canMoveDown = false;
				}
			}
		}

		if (jikiStandChip[1] % 26 == 25) {
			if (checkAround[0] == 26 || checkAround[0] >= 40) {
				if (checkAround[0] % 26 < 20) {
					canMoveDown = false;
				}
				else {
					canMoveDown = true;
				}
			}
			else {
				canMoveDown = true;
			}
		}

		if (checkAround[1] % 26 == 25) {
			canMoveDown = true;
		}

	}

	if (Input.GetKeyDown(Input.key.DOWN)) {
		HitKeyNum++;
	}
	if (Input.GetKeyDown(Input.key.LEFT)) {
		HitKeyNum++;
	}
	if (Input.GetKeyDown(Input.key.RIGHT)) {
		HitKeyNum++;
	}
	if (Input.GetKeyDown(Input.key.UP)) {
		HitKeyNum++;
	}

	if (Input.GetKeyDown(Input.key.DOWN) && moveF==false &&canMoveDown==true) {
		if (HitKeyNum <= 1 || moveDirect != 0) {
			moveF = true;
			moveDirect = 0;
			graphDirect = 0;
		}
	}
	if (Input.GetKeyDown(Input.key.LEFT) &&moveF == false && canMoveLeft == true) {
		if (HitKeyNum <= 1 || moveDirect != 1) {
			moveF = true;
			moveDirect = 1;
			graphDirect = 1;
		}
	}
	if (Input.GetKeyDown(Input.key.RIGHT) && moveF == false && canMoveRight == true) {
		if (HitKeyNum <= 1 || moveDirect != 2) {
			moveF = true;
			moveDirect = 2;
			graphDirect = 2;
		}
	}
	if (Input.GetKeyDown(Input.key.UP) && moveF == false && canMoveUp == true) {
		if (HitKeyNum <= 1 || moveDirect != 3) {
			moveF = true;
			moveDirect = 3;
			graphDirect = 3;
		}
	}
	
	if (moveF == true) {
		switch (moveDirect) {
		case 0:
			if (jikiY == 320 && mapHeight > jikiMapY + 8) {
				scrollY += walkSpeed;

			}
			else {
				jikiY += walkSpeed;
			}
		break;
		case 1:
			if (jikiX == 352 && scrollX>0) {
				scrollX -= walkSpeed;

			}
			else {
				jikiX -= walkSpeed;
			}
		break;
		case 2:
			if (jikiX == 352 && mapWidth > jikiMapX + 11) {
				scrollX += walkSpeed;

			}
			else {
				jikiX += walkSpeed;
			}
		break;
		case 3:
			if (jikiY == 320 && scrollY>0) {
				scrollY -= walkSpeed;

			}
			else {
				jikiY -= walkSpeed;
			}
		break;


		default:break;
		}
	}
	if (moveF == false) {
		moveDirect = 4;
		if (Input.GetKeyDown(Input.key.DOWN)) {
			graphDirect = 0;
			moveDirect = 0;
		}
		if (Input.GetKeyDown(Input.key.LEFT)) {
			graphDirect = 1;
			moveDirect = 1;
		}
		if (Input.GetKeyDown(Input.key.RIGHT)) {
			graphDirect = 2;
			moveDirect = 2;
		}
		if (Input.GetKeyDown(Input.key.UP)) {
			graphDirect = 3;
			moveDirect = 3;
		}
	}

	if ((jikiX + scrollX) % 32 == 0 && (jikiY + scrollY) % 32 == 0) {
		moveF = false;
		graphStep = 1;
	}

	if ((jikiX + scrollX) % 32 == 16 || (jikiY + scrollY) % 32 == 16) {
		if (animeF == true) {
			graphStep = 0;
			animeF = false;
		}
		else {
			graphStep = 2;
			animeF = true;
		}
	}

	if (graphDirect == 3 && KeyOK()) {
		checkAround[0] = TownMap.Get(TownMap.layer.C, jikiMapX, jikiMapY - 1) - 1;
		checkAround[1] = TownMap.Get(TownMap.layer.B, jikiMapX, jikiMapY - 1) - 1;
		
		if (checkAround[0] == 135 || checkAround[1] == 135) {
			FlipScene(new CSProTool(*this), Flip::SLIDE_UP, 10);
		}

		if (checkAround[0] == 136 || checkAround[1] == 136) {
			FlipScene(new CSProEquipment(*this),Flip::SLIDE_UP,10);
		}

		if (checkAround[0] == 137 || checkAround[1] == 137) {
			FlipScene(new CSCook(*this), Flip::SLIDE_UP, 10);
		}

		if (checkAround[0] == 138 || checkAround[1] == 138) {
			FlipScene(new CSGoToQuest(*this), Flip::SLIDE_UP, 10);
		}

		if (checkAround[0] == 139 || checkAround[1] == 139) {
			FlipScene(new CSSorceRemake(*this), Flip::SLIDE_UP, 10);
		}

		if (checkAround[0] == 141 || checkAround[1] == 141) {
			FlipScene(new CSSellItem(*this), Flip::SLIDE_UP, 10);
		}

		if (checkAround[0] == 144 || checkAround[1] == 144) {
			FlipScene(new CSHaniwa(*this), Flip::SLIDE_UP, 10);
		}
	
	
	}

	if (graphDirect == 2 && KeyOK()) {
		checkAround[0] = TownMap.Get(TownMap.layer.C, jikiMapX + 1, jikiMapY) - 1;
		checkAround[1] = TownMap.Get(TownMap.layer.B, jikiMapX + 1, jikiMapY) - 1;

		if (checkAround[0] == 142 || checkAround[1] == 142) {
			FlipScene(new CSItemSet(*this), Flip::SLIDE_UP, 10);
		}

	}

	if (graphDirect == 1 && KeyOK()) {
		checkAround[0] = TownMap.Get(TownMap.layer.C, jikiMapX - 1, jikiMapY) - 1;
		checkAround[1] = TownMap.Get(TownMap.layer.B, jikiMapX - 1, jikiMapY) - 1;

		if (checkAround[0] == 143 || checkAround[1] == 143) {
			FlipScene(new CSSetEquipment(*this), Flip::SLIDE_UP, 10);
		}

	}

	if (Input.GetKeyEnter(Input.key.SPACE)) {
		FlipScene(new CSMenueWindow(*this), Flip::SLIDE_UP, 10);
	}

	jikiMapX = (jikiX + scrollX) / 32;
	jikiMapY = (jikiY + scrollY) / 32;
}


void CSTown::Draw() {
	int drawMapLeft = jikiMapX - (jikiX / 32) - 1;
	int drawMapUp = jikiMapY - (jikiY / 32) - 1;
	int drawMapRight = drawMapLeft + 1 + 22 +1;
	int drawMapDown = drawMapUp + 1 + 18 + 1;
	if (drawMapLeft < 0) {
		drawMapLeft = 0;
	}
	if (drawMapUp < 0) {
		drawMapUp = 0;
	}
	if (drawMapRight > mapWidth) {
		drawMapRight= mapWidth;
	}
	if (drawMapDown > mapHeight) {
		drawMapDown=mapHeight;
	}

	for (int i = drawMapLeft; i < drawMapRight; i++) {
		for (int j = drawMapUp; j < drawMapDown; j++) {
			if (TownMap.Get(TownMap.layer.C, i, j) > 0) {
				mapChip[TownMap.Get(TownMap.layer.C, i, j)-1].Draw(i * 32-scrollX, j * 32 - scrollY);
			}
			if (TownMap.Get(TownMap.layer.B, i, j) > 0) {
				mapChip[TownMap.Get(TownMap.layer.B, i, j)-1].Draw(i * 32 - scrollX, j * 32 - scrollY);
			}
		}
	}

	jikiGraph[graphDirect*3+graphStep].Draw(jikiX, jikiY-4);
}

void CSTown::End() {
	mySaveData->WriteSaveData();
	delete mySaveData;
	mySaveData = NULL;
}


CSTown::CSProTool::CSProTool(CSTown & cstown) :cstown(cstown)
{
	textWindow = new CTextWindow("何を作るんだい？");
	classStart = false;
	step = 0;
}

void CSTown::CSProTool::Loop()
{
	if (classStart == true) {

		switch (step)
		{
		case 2:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				cstown.RemoveScene(Flip::SLIDE_DOWN, 10);
			}
			break;
		case 1:
			produce->WindowLoop();
			if (KeyCancel() && produce->GetStepChangeFlag() == false) {
				step = 2;
				textWindow->PushText("また道具を作ってほしかったら、来いよな");
				delete produce;
				produce = NULL;
			}
			break;
		case 0:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				step = 1;
				produce = new CProduce(cstown.mySaveData, 8);
			}
			break;


		default:break;
		}



	}
	classStart = true;
}

void CSTown::CSProTool::Draw()
{
	switch (step)
	{
	case 2:
		textWindow->Draw();
		break;
	case 1:
		produce->WindowDraw();
		break;

	case 0:
		textWindow->Draw();
		break;

	default:break;
	}
}

void CSTown::CSProTool::End()
{
	delete textWindow;
	textWindow = NULL;
}

CSTown::CSCook::CSCook(CSTown & cstown) :cstown(cstown)
{
	textWindow = new CTextWindow("何を作って欲しいカボ？");
	classStart = false;
	step = 0;
}

void CSTown::CSCook::Loop()
{

	if (classStart == true) {

		switch (step)
		{
		case 2:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				cstown.RemoveScene(Flip::SLIDE_DOWN, 10);
			}
			break;
		case 1:
			produce->WindowLoop();
			if (KeyCancel() && produce->GetStepChangeFlag()==false) {
				step = 2;
				textWindow->PushText("また料理を作ってほしかったら、来てくれカボ");
				delete produce;
				produce = NULL;
			}
			break;
		case 0:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				step = 1;
				produce = new CProduce(cstown.mySaveData, 9);
			}
			break;


		default:break;
		}





	}
	classStart = true;
}

void CSTown::CSCook::Draw()
{
	switch (step)
	{
	case 2:
		textWindow->Draw();
		break;
	case 1:
		produce->WindowDraw();
		break;

	case 0:
		textWindow->Draw();
		break;

	default:break;
	}
	
}

void CSTown::CSCook::End()
{
	delete textWindow;
	textWindow = NULL;
}


CSTown::CSProEquipment::CSProEquipment(CSTown & cstown) :cstown(cstown)
{
	kindSerectWindow = "zero/EquipmentWindow.png";
	arrowGraph = "zero/SmallArrow.png";
	step = 0;
	arrowPoint = 0;
	S = "他になんの装備を作るんだ？";
	textWindow = new CTextWindow("どの装備を作るんだ？");
}

void CSTown::CSProEquipment::Loop()
{
	switch (step)
	{
	case 2:
		textWindow->Loop();
		if (textWindow->GetTextEmpty()) {
			cstown.RemoveScene(Flip::SLIDE_DOWN, 10);
		}
		break;

	case 1:
		produce->WindowLoop();
		if (KeyCancel()) {
			step = 0;
			delete produce;
			produce = NULL;
			textWindow->PushText("%s/n（Ｘキーで終了）",S);
		}

		break;

	case 0:
		textWindow->Loop();
		if (KeyDown() && arrowPoint < 6) {
			arrowPoint++;
		}
		if (KeyUp() && arrowPoint > 0) {
			arrowPoint--;
		}
		if (KeyOK()) {
			step = 1;
			produce = new CProduce(cstown.mySaveData, arrowPoint);
		}
		if (KeyCancel()) {
			step = 2;
			textWindow->TextClear();
			textWindow->PushText("またいつでも来てくれ。");
		}

		break;

	default:
		break;
	}

}

void CSTown::CSProEquipment::Draw()
{
	switch (step)
	{
	case 2:
		textWindow->Draw();
		kindSerectWindow(520, 20);
		arrowGraph(550, 40 + 37 * arrowPoint);
		break;

	case 1:
			produce->WindowDraw();
			break;

	case 0:
		textWindow->Draw();
		kindSerectWindow(520, 20);
		arrowGraph(550, 40 + 37* arrowPoint);
			break;

	default:
		break;
	}

}

void CSTown::CSProEquipment::End()
{
	delete textWindow;
	textWindow = NULL;
}


CSTown::CSSorceRemake::CSSorceRemake(CSTown & cstown) :cstown(cstown)
{
	textWindow = new CTextWindow("何を加工すればいい？");
	classStart = false;
	step = 0;
}

void CSTown::CSSorceRemake::Loop()
{

	if (classStart == true) {

		switch (step)
		{
		case 2:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				cstown.RemoveScene(Flip::SLIDE_DOWN, 10);
			}
			break;
		case 1:
			produce->WindowLoop();
			if (KeyCancel() && produce->GetStepChangeFlag() == false) {
				step = 2;
				textWindow->PushText("また加工してほしっかたらここまで来な");
				delete produce;
				produce = NULL;
			}
			break;
		case 0:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				step = 1;
				produce = new CProduce(cstown.mySaveData, 7);
			}
			break;


		default:break;
		}





	}
	classStart = true;
}

void CSTown::CSSorceRemake::Draw()
{
	switch (step)
	{
	case 2:
		textWindow->Draw();
		break;
	case 1:
		produce->WindowDraw();
		break;

	case 0:
		textWindow->Draw();
		break;

	default:break;
	}
}

void CSTown::CSSorceRemake::End()
{
	delete textWindow;
	textWindow = NULL;
}


CSTown::CSItemSet::CSItemSet(CSTown & cstown) :cstown(cstown)
{
	textWindow = new CTextWindow("持っていくアイテムについて何かお困りですか？");
	classStart = false;
	step = 0;
	arrowPoint = 0;
	arrowPoint2 = 0;
	arrowPoint3 = 0;
	closeWindow = true;
	ItemInfo[0] = new CSV("zero/ZeroData/Sorce.csv");
	ItemInfo[1] = new CSV("zero/ZeroData/Tool.csv");
	ItemInfo[2] = new CSV("zero/ZeroData/Food.csv");
	Arrow = "zero/SmallArrow.png";
	Window[0] = "zero/ItemSelectWindow.png";
	Window[1] = "zero/ItemSelectWindow2.png";
}

void CSTown::CSItemSet::Loop()
{

	if (classStart == true) {

		switch (step)
		{
		case 6:
			itemManger->WindowLoop();
			if (KeyOK()) {
				cstown.mySaveData->SetItemSet(arrowPoint, arrowPoint2, arrowPoint3 + 1, itemManger->GetPointNum());
				step = 5;
				closeWindow = true;
				delete itemManger;
				itemManger = NULL;
			}
			break;
		case 5:
			if (KeyUp() && 0 < arrowPoint3) {
				arrowPoint3 -= 1;
			}
			if (KeyDown() && 3 > arrowPoint3) {
				arrowPoint3 += 1;
			}

			if (KeyOK()) {
				switch (arrowPoint3)
				{
				case 0:
					itemManger = new CItemManager(1, cstown.mySaveData);
					step = 6;
					break;

				case 1:
					itemManger = new CItemManager(2, cstown.mySaveData);
					step = 6;
					break;

				case 2:
					cstown.mySaveData->SetItemSet(arrowPoint, arrowPoint2, 0, 0);
						break;

				case 3:
					arrowPoint3 = 0;
					step = 4;
					break;
				default:
					break;
				}
			}

			if (KeyCancel()) {
				arrowPoint3 = 0;
				step = 4;
			}

			break;

		case 4:
			if (KeyUp() && 0 < arrowPoint2 / 2) {
				arrowPoint2 -= 2;
			}
			if (KeyDown() && 4 > arrowPoint2 / 2) {
				arrowPoint2 += 2;
			}
			if (KeyLeft() || KeyRight()) {
				if (arrowPoint2 % 2 == 0) {
					arrowPoint2++;
				}
				else {
					arrowPoint2--;
				}
			}

			if (KeyOK()) {
				step = 5;
			}

			if (KeyCancel()) {

				closeWindow = true;
				for (int i = 0; i < 9; i++) {
					for(int j=i+1;j<10;j++){
						if (cstown.mySaveData->GetSetItem(arrowPoint, i, true) != 0 && cstown.mySaveData->GetSetItem(arrowPoint, i, false) != 0) {
							if (cstown.mySaveData->GetSetItem(arrowPoint, i, true) == cstown.mySaveData->GetSetItem(arrowPoint, j, true) && cstown.mySaveData->GetSetItem(arrowPoint, i, false) == cstown.mySaveData->GetSetItem(arrowPoint, j, false)) {
								closeWindow = false;
							}
						}
					}
				}
				if (closeWindow == true) {
					step = 3;
					arrowPoint2 = 0;
				}
			}
			break;

		case 3:
			if (KeyUp() && 0 < arrowPoint2 ) {
				arrowPoint2 -= 1;
			}
			if (KeyDown() && 2 > arrowPoint2 ) {
				arrowPoint2 += 1;
			}

			if (KeyOK()) {
				switch (arrowPoint2)
				{
				case 0:
					cstown.mySaveData->bringItemSet = arrowPoint;
					break;

				case 1:
					step = 4;
					arrowPoint2 = 0;
					break;

				case 2:
					arrowPoint2 = 0;
					step = 1;
					break;
				default:
					break;
				}
			}

			if (KeyCancel()) {
				arrowPoint2 = 0;
				step = 1;
			}

			break;

		case 2:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				cstown.RemoveScene(Flip::SLIDE_DOWN, 10);
			}
			break;
		case 1:
			if (KeyUp() && 0 < arrowPoint / 2) {
				arrowPoint -= 2;
			}
			if (KeyDown() && 4 > arrowPoint / 2) {
				arrowPoint += 2;
			}
			if (KeyLeft() || KeyRight()) {
				if (arrowPoint % 2 == 0) {
					arrowPoint++;
				}
				else {
					arrowPoint--;
				}
			}

			if (KeyOK()) {
				step = 3;
			}

			if (KeyCancel()) {
				step = 2;
				textWindow->PushText("またいつでも来てくださいね。");
			}
			break;
		case 0:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				step = 1;
			}
			break;


		default:break;
		}





	}
	classStart = true;

}

void CSTown::CSItemSet::Draw()
{
	string bufS="";
	int bufInt[2] = {};
	switch (step)
	{
	case 6:
		itemManger->WindowDraw();
		break;
	case 5:
		Window[1].DrawExtend(380, 260, 600, 450);
		DrawFormatString(410, 285, BLACK, "道具");

		DrawFormatString(410, 325, BLACK, "食べ物");
		DrawFormatString(410, 365, BLACK, "消去する");
		DrawFormatString(410, 405, BLACK, "閉じる");
		Arrow(385, 285 + arrowPoint3 * 40);

		Window[0].DrawExtend(5, 5, 370, 255);
		Window[1].DrawExtend(5, 260, 370, 570);

		Arrow(12 + (arrowPoint % 2) * 160, 20 + (arrowPoint / 2) * 50);
		Arrow(12 + (arrowPoint2 % 2) * 160, 290 + (arrowPoint2 / 2) * 50);


		for (int i = 0; i < 10; i++) {
			DrawFormatString(30 + (i % 2) * 160, 20 + (i / 2) * 50, BLACK, "アイテムセット%d", i + 1);

			bufS = "";
			bufInt[0] = cstown.mySaveData->GetSetItem(arrowPoint, i, true);
			bufInt[1] = cstown.mySaveData->GetSetItem(arrowPoint, i, false);
			if (bufInt[1] > 0) {
				bufS = (*ItemInfo[bufInt[0]])[bufInt[1] - 1][1];
			}

			DrawFormatString(30 + (i % 2) * 160, 290 + (i / 2) * 50, BLACK, "%d:%s", i + 1, bufS.c_str());

			if (cstown.mySaveData->bringItemSet == i) {
				DrawFormatString(30 + (i % 2) * 160, 36 + (i / 2) * 50, RED, "（↑セット中）", i + 1);
			}

		}


		break;

	case 4:

		Window[0].DrawExtend(5, 5, 370, 255);
		Window[1].DrawExtend(5, 260, 370, 570);

		Arrow(12 + (arrowPoint % 2) * 160, 20 + (arrowPoint / 2) * 50);

		Arrow(12 + (arrowPoint2 % 2) * 160, 290 + (arrowPoint2 / 2) * 50);

		for (int i = 0; i < 10; i++) {
			DrawFormatString(30 + (i % 2) * 160, 20 + (i / 2) * 50, BLACK, "アイテムセット%d", i + 1);

			bufS = "";
			bufInt[0] = cstown.mySaveData->GetSetItem(arrowPoint, i, true);
			bufInt[1] = cstown.mySaveData->GetSetItem(arrowPoint, i, false);
			if (bufInt[1] > 0) {
				bufS = (*ItemInfo[bufInt[0]])[bufInt[1] - 1][1];
			}

			DrawFormatString(30 + (i % 2) * 160, 290 + (i / 2) * 50, BLACK, "%d:%s", i + 1, bufS.c_str());

			if (cstown.mySaveData->bringItemSet == i) {
				DrawFormatString(30 + (i % 2) * 160, 36 + (i / 2) * 50, RED, "（↑セット中）", i + 1);
			}

		}

		if (closeWindow == false) {
			DrawFormatString(30, 540, RED, "同じアイテムが複数セットされています。");
		}

		break;

	case 3:
		Window[1].DrawExtend(380,5,700,160);
		DrawFormatString(410, 30, BLACK, "このアイテムセットを持っていく");

		DrawFormatString(410, 70, BLACK, "アイテムセットの内容を変更する");
		DrawFormatString(410, 110, BLACK, "閉じる");
		Arrow(385,30+arrowPoint2*40);

		Window[0].DrawExtend(5, 5, 370, 255);
		Window[1].DrawExtend(5, 260, 370, 570);

		Arrow(12 + (arrowPoint % 2) * 160, 20 + (arrowPoint / 2) * 50);

		for (int i = 0; i < 10; i++) {
			DrawFormatString(30 + (i % 2) * 160, 20 + (i / 2) * 50, BLACK, "アイテムセット%d", i + 1);

			bufS = "";
			bufInt[0] = cstown.mySaveData->GetSetItem(arrowPoint, i, true);
			bufInt[1] = cstown.mySaveData->GetSetItem(arrowPoint, i, false);
			if (bufInt[1] > 0) {
				bufS = (*ItemInfo[bufInt[0]])[bufInt[1] - 1][1];
			}

			DrawFormatString(30 + (i % 2) * 160, 290 + (i / 2) * 50, BLACK, "%d:%s", i + 1, bufS.c_str());

			if (cstown.mySaveData->bringItemSet == i) {
				DrawFormatString(30 + (i % 2) * 160, 36 + (i / 2) * 50, RED, "（↑セット中）", i + 1);
			}

		}

		

		break;

	case 2:
		textWindow->Draw();
		break;

	case 1:
		Window[0].DrawExtend(5,5,370,255);
		Window[1].DrawExtend(5, 260, 370, 570);

		Arrow(12 + (arrowPoint % 2) * 160, 20 + (arrowPoint / 2) * 50);
		
		for (int i = 0; i < 10; i++) {
			DrawFormatString(30 + (i % 2) * 160, 20 + (i / 2) * 50, BLACK, "アイテムセット%d", i + 1);

			bufS = "";
			bufInt[0] = cstown.mySaveData->GetSetItem(arrowPoint, i, true);
			bufInt[1] = cstown.mySaveData->GetSetItem(arrowPoint, i, false);
			if (bufInt[1] > 0) {
				bufS = (*ItemInfo[bufInt[0]])[bufInt[1] - 1][1];
			}

			DrawFormatString(30 + (i % 2) * 160, 290 + (i / 2) * 50, BLACK, "%d:%s", i+1,bufS.c_str());

			if (cstown.mySaveData->bringItemSet==i){
				DrawFormatString(30 + (i % 2) * 160, 36 + (i / 2) * 50, RED, "（↑セット中）", i + 1);
			}
		
		}


		break;

	case 0:
		textWindow->Draw();
		break;

	default:break;
	}
}

void CSTown::CSItemSet::End()
{
	delete textWindow;
	textWindow = NULL;
}



CSTown::CSSetEquipment::CSSetEquipment(CSTown & cstown) :cstown(cstown)
{
	step = 0;
	classStart = false;
	textWindow = new CTextWindow("どの装備に変更いたしますか？");
	Arrow = "zero/SmallArrow.png";
	Window[0] = "zero/ItemSelectWindow.png";
	Window[1] = "zero/EquipmentWindow.png";

	arrowPoint = 0;
	arrowPoint2 = 0;
}

void CSTown::CSSetEquipment::Loop()
{
	if (classStart == true) {

		switch (step)
		{
		case 2:
			textWindow->Loop();
			if (textWindow->GetTextEmpty()) {
				cstown.RemoveScene(Flip::SLIDE_DOWN, 10);
			}
			break;

		case 1:
			equipManger->LoopWindow();
			if (KeyCancel()) {
				step = 0;
				arrowPoint2 = 0;
				delete equipManger;
				equipManger = NULL;
				textWindow->PushText("他に装備を変更いたしますか？/n（Ｘキーで終了）");
			}

			if (KeyOK()) {
				if (arrowPoint <= 2) {
					cstown.mySaveData->wearEquipmentLocate[0][0] = arrowPoint;
					cstown.mySaveData->wearEquipmentLocate[0][1] = equipManger->lookLocate + equipManger->lookPage * 20;
					equipManger->wearWeaponLocate[0][0] = arrowPoint;
					equipManger->wearWeaponLocate[0][1] = equipManger->lookLocate + equipManger->lookPage * 20;
				}

				if (arrowPoint > 2) {
					cstown.mySaveData->wearEquipmentLocate[arrowPoint-2][0] = arrowPoint;
					cstown.mySaveData->wearEquipmentLocate[arrowPoint-2][1] = equipManger->lookLocate + equipManger->lookPage * 20;
					equipManger->wearWeaponLocate[arrowPoint - 2][0] = arrowPoint;
					equipManger->wearWeaponLocate[arrowPoint - 2][1] = equipManger->lookLocate + equipManger->lookPage * 20;
				}
			}
			break;

		case 0:
			
			textWindow->Loop();
			if (KeyDown() && arrowPoint < 6) {
				arrowPoint++;
			}
			if (KeyUp() && arrowPoint > 0) {
				arrowPoint--;
			}
			if (KeyOK()) {
				step = 1;
				equipManger = new CEquipmentManager(cstown.mySaveData, arrowPoint);
			}
			if (KeyCancel()) {
				step = 2;
				textWindow->TextClear();
				textWindow->PushText("またいつでもお越しください。");
			}
			break;


		default:break;
		}



	}
	classStart = true;
}

void CSTown::CSSetEquipment::Draw()
{

	switch (step)
	{

	case 2:
		textWindow->Draw();
		Window[1](520, 20);
		Arrow(550, 40 + 37 * arrowPoint);
		break;

	case 1:
		equipManger->DrawWindow();
		break;

	case 0:
		textWindow->Draw();
		Window[1](520, 20);
		Arrow(550, 40 + 37 * arrowPoint);
		break;

	default:
		break;
	}

}

void CSTown::CSSetEquipment::End()
{
}






CSTown::CSSellItem::CSSellItem(CSTown & cstown) :cstown(cstown)
{
	step = 0;
	classStart = false;
	textWindow = new CTextWindow("何を売りたいんだい？/n（Ｘキーで閉じる）");
	Arrow = "zero/SmallArrow.png";
	Window[0] = "zero/SellWindow.png";
	Window[1] = "zero/TextWindow1.png";
	yn = false;

	arrowPoint = 0;
	arrowPoint2 = 0;
}

void CSTown::CSSellItem::Loop()
{

	if (classStart == true) {

		switch (step)
		{
		case 2:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				cstown.RemoveScene(Flip::SLIDE_DOWN, 10);
			}
			break;
		case 3:
			if (arrowPoint < 7) {
				ynWindow->Loop();
				if (KeyOK()) {
					step = 1;
					if (yn == true) {
						if (arrowPoint < 7) {
							equipManager->SellEquipment();
						}
					}
					delete ynWindow;
				}
			}
			else {
				amountGetWindow->Loop();
				if (KeyOK()) {
					itemManager->Sell(amountGetWindow->GetAmount());
					delete amountGetWindow;
					step = 1;
				}
				if (KeyCancel()) {
					step = 1;
					delete amountGetWindow;
				}
			}

			break;

		case 1:
			if (arrowPoint < 7) {
				equipManager->LoopWindow();
			}
			else
			{
				itemManager->WindowLoop();
			}

			if (KeyOK()) {
				if (arrowPoint < 7) {
					if (arrowPoint < 3 && equipManager->GetSize(arrowPoint)>1) {
						if (cstown.mySaveData->wearEquipmentLocate[0][0] != arrowPoint || cstown.mySaveData->wearEquipmentLocate[0][1] != (equipManager->lookLocate + equipManager->lookPage * 20)) {
							ynWindow = new CYesNoWindow(&yn, "これを売るのかい？", false, 280, 100);
							step = 3;
						}
					}
					else if (arrowPoint >= 3 && arrowPoint < 7) {
						if (cstown.mySaveData->wearEquipmentLocate[arrowPoint - 3][1] == (equipManager->lookLocate + equipManager->lookPage * 20)) {
							ynWindow = new CYesNoWindow(&yn, "これを売るのかい？", false, 280, 100);
							step = 3;
						}
					}
				}
				if(arrowPoint>=7 && itemManager->GetAmount(arrowPoint - 7, itemManager->GetPointNum())>0)
				{
					amountGetWindow = new CAmountGetWindow("何個売るんだい？", 280, 100, itemManager->GetAmount(arrowPoint-7,itemManager->GetPointNum()));
					step = 3;
				}
			}

			if (KeyCancel()) {
				if (arrowPoint < 7) {
					delete equipManager;
				}
				else {
					delete itemManager;
				}
				step = 0;
				textWindow->PushText("他に売るものはあるかい？/n（Ｘキーで閉じる）");
			}
			break;
		case 0:
			textWindow->Loop();
			if (KeyDown() && arrowPoint < 9) {
				arrowPoint++;
			}
			if (KeyUp() && arrowPoint > 0) {
				arrowPoint--;
			}

			if (KeyOK()) {
				step = 1;
				if (arrowPoint < 7) {
					equipManager = new CEquipmentManager(cstown.mySaveData, arrowPoint);
				}
				else
				{
					itemManager = new CItemManager(arrowPoint - 7, cstown.mySaveData);
				}

			}

			if (KeyCancel()) {
				step = 2;
				textWindow->TextClear();
				textWindow->PushText("来てくれたらいつでも買い取るよ。");
			}
			break;


		default:break;
		}





	}
	classStart = true;

}

void CSTown::CSSellItem::Draw()
{
	switch (step)
	{
	case 2:
		textWindow->Draw();
		break;
	case 3:
		if (arrowPoint < 7) {
			equipManager->DrawWindow();
			ynWindow->Draw();
		}
		else {
			itemManager->WindowDraw();
			amountGetWindow->Draw();
		}


		break;

	case 1:
		if (arrowPoint < 7) {
			equipManager->DrawWindow();
		}
		else {
			itemManager->WindowDraw();
		}

		break;

	case 0:
		Window[0].DrawExtend(500, 10,700,320);
		Arrow.Draw(530, 25 + 29 * arrowPoint);
		textWindow->Draw();
		break;

	default:break;
	}
	Window[1].DrawExtend(450, 543, 700, 568);

	DrawFormatString(470, 548, BLACK, "所持金　　%d", cstown.mySaveData->money);
}

void CSTown::CSSellItem::End()
{
	delete textWindow;
	textWindow = NULL;
	itemManager = NULL;
	equipManager = NULL;
	ynWindow = NULL;
	amountGetWindow = NULL;
}


CSTown::CSMenueWindow::CSMenueWindow(CSTown & cstown):cstown(cstown)
{
	step = 0;
	classStart = false;
	textWindow = new CTextWindow("");
	Arrow = "zero/SmallArrow.png";
	Window[0] = "zero/MenueWindow2.png";
	Window[1] = "zero/TextWindow1.png";
	Window[2] = "zero/SellWindow.png";
	Window[3] = "zero/StatusWindow.png";
	Window[4] = "zero/WearCheckWindow.png";
	yn = false;

	arrowPoint = 0;
	arrowPoint2 = 0;
	int equipmentKind = 0;
	int num = 0;
	int buf = 0;

	for (int i = 0; i < 15; i++) {
		Status[i] = 0;
	}

	for (int i = 0; i < 5; i++) {
		equipManager = new CEquipmentManager(cstown.mySaveData,cstown.mySaveData->wearEquipmentLocate[i][0]);

		equipmentKind = cstown.mySaveData->wearEquipmentLocate[i][0];
		buf = cstown.mySaveData->wearEquipmentLocate[i][1];
		num = equipManager->haveEquipmentNumLevel[equipmentKind][buf].first;
		Level= equipManager->haveEquipmentNumLevel[equipmentKind][buf].second;
		wearWeaponNumLevel[i][0] = equipmentKind;
		wearWeaponNumLevel[i][1] = num;
		wearWeaponNumLevel[i][2] = Level;
		switch (equipmentKind)
		{

		case 0:	equipmentInfo = new CSV("zero/ZeroData/Soad.csv"); break;
		case 1: equipmentInfo = new CSV("zero/ZeroData/Arrow.csv"); break;
		case 2: equipmentInfo = new CSV("zero/ZeroData/Wand.csv"); break;
		case 3:	equipmentInfo = new CSV("zero/ZeroData/Shield.csv"); break;
		case 4: equipmentInfo = new CSV("zero/ZeroData/Protecter.csv"); break;
		case 5: equipmentInfo = new CSV("zero/ZeroData/Shoes.csv"); break;
		case 6: equipmentInfo = new CSV("zero/ZeroData/Accessory.csv"); break;
		}

		HP = (*equipmentInfo)[num - 1][2];
		MP = (*equipmentInfo)[num - 1][3];
		Atc =(*equipmentInfo)[num - 1][4];
		Def =(*equipmentInfo)[num - 1][5];
		MAtc =(*equipmentInfo)[num - 1][6];
		MDef =(*equipmentInfo)[num - 1][7];
		Spd =(*equipmentInfo)[num - 1][8];
		Hit =(*equipmentInfo)[num - 1][9];
		Escape =(*equipmentInfo)[num - 1][10];
		Luck =(*equipmentInfo)[num - 1][11];

		if (equipmentKind <= 2) {
			FireDef =(*equipmentInfo)[num - 1][13];
			WoodDef =(*equipmentInfo)[num - 1][14];
			WaterDef =(*equipmentInfo)[num - 1][15];
			LightDef =(*equipmentInfo)[num - 1][16];
			DarkDef =(*equipmentInfo)[num - 1][17];
		}
		else {
			FireDef =(*equipmentInfo)[num - 1][12];
			WoodDef =(*equipmentInfo)[num - 1][13];
			WaterDef =(*equipmentInfo)[num - 1][14];
			LightDef =(*equipmentInfo)[num - 1][15];
			DarkDef =(*equipmentInfo)[num - 1][16];

		}

		HP *= (1.0 + 0.1*Level);
		MP *= (1.0 + 0.1*Level);
		Atc *= (1.0 + 0.1*Level);
		Def *= (1.0 + 0.1*Level);
		MAtc *= (1.0 + 0.1*Level);
		MDef *= (1.0 + 0.1*Level);
		Spd *= (1.0 + 0.1*Level);
		Hit *= (1.0 + 0.1*Level);
		Escape *= (1.0 + 0.1*Level);
		Luck *= (1.0 + 0.1*Level);
		FireDef *= (1.0 + 0.1*Level);
		WoodDef *= (1.0 + 0.1*Level);
		WaterDef *= (1.0 + 0.1*Level);
		LightDef *= (1.0 + 0.1*Level);
		DarkDef *= (1.0 + 0.1*Level);

		Status[0] += HP;
		Status[1] += MP;
		Status[2] += Atc;
		Status[3] += Def;
		Status[4] += MAtc;
		Status[5] += MDef;
		Status[6] += Spd;
		Status[7] += Hit;
		Status[8] += Escape;
		Status[9] += Luck;
		Status[10] += FireDef;
		Status[11] += WoodDef;
		Status[12] += WaterDef;
		Status[13] += LightDef;
		Status[14] += DarkDef;



		delete equipmentInfo;
		delete equipManager;
		equipmentInfo = NULL;
		equipManager = NULL;

	}

	Status[15] = cstown.mySaveData->money;

}

void CSTown::CSMenueWindow::Loop()
{

	if (classStart == true) {

		switch (step)
		{
		case 5:
			if (KeyUp() && arrowPoint3 > 0) {
				if (0 <= arrowPoint3&&arrowPoint3 < 5) {
					delete equipWindow;
					equipWindow = NULL;
				}
				arrowPoint3--;
				equipWindow = new CEquipmentWindow(wearWeaponNumLevel[arrowPoint3][0], wearWeaponNumLevel[arrowPoint3][1], wearWeaponNumLevel[arrowPoint3][2]);
				
			}

			if (KeyDown() && arrowPoint3 < 5) {
				if (0 <= arrowPoint3&&arrowPoint3 < 5) {
					delete equipWindow;
					equipWindow = NULL;
				}
				arrowPoint3++;

				if (0 <= arrowPoint3&&arrowPoint3 < 5) {
					equipWindow = new CEquipmentWindow(wearWeaponNumLevel[arrowPoint3][0], wearWeaponNumLevel[arrowPoint3][1], wearWeaponNumLevel[arrowPoint3][2]);
				}
			}
			if (KeyOK() && arrowPoint3 == 5) {
				step = 0;
			}

			if (KeyCancel()) {
				step = 0;
				if (0 < arrowPoint3&&arrowPoint3 < 5) {
					delete equipWindow;
					equipWindow = NULL;
				}
			}
			break;
		case 4:
			if (arrowPoint2 < 7) {
				equipManager->LoopWindow();
				if (KeyCancel()) {
					step = 3;
					delete equipManager;
				}
			}
			else{
				itemManager->WindowLoop();
				if (KeyCancel()) {
					step = 3;
					delete itemManager;
				}
			}
			break;
		case 3:
			if (KeyUp() && arrowPoint2 > 0) {
				arrowPoint2--;
			}
			if (KeyDown() && arrowPoint2 < 9) {
				arrowPoint2++;
			}
			if (KeyOK()) {
				if (arrowPoint2 < 7) {
					equipManager = new CEquipmentManager(cstown.mySaveData, arrowPoint2);
					step = 4;
				}
				else
				{
					itemManager = new CItemManager(arrowPoint2 - 7, cstown.mySaveData);
					step = 4;
				}

			}
			if (KeyCancel()) {
				step = 0;
			}

			break;
		case 2:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				step = 0;
			}
			break;
		case 1:
			ynWindow->Loop();
			if (KeyOK()) {
				if (yn == true) {
					cstown.mySaveData->WriteSaveDataToOther();
					step = 2;
					textWindow->PushText("セーブしました。");
				}
				else {
					step = 0;
				}
				delete ynWindow;
			}
			break;
		case 0:
			
			if (KeyUp() && arrowPoint > 0) {
				arrowPoint--;
			}
			if (KeyDown() && arrowPoint < 3) {
				arrowPoint++;
			}

			if (KeyOK()) {
				switch (arrowPoint)
				{
				case 3:
					cstown.RemoveScene(Flip::SLIDE_DOWN, 10);
					break;

				case 2:
					step = 5;
					arrowPoint3 = 0;
					equipWindow = new CEquipmentWindow(wearWeaponNumLevel[0][0], wearWeaponNumLevel[0][1], wearWeaponNumLevel[0][2]);
					break;
				case 1:
					step = 3;
					arrowPoint2 = 0;
					break;
				case 0:
					ynWindow = new CYesNoWindow(&yn, "セーブしてよろしいですか？", false, 245, 10);
					step = 1;
					break;
				default:
					break;
				}

			}

			break;


		default:break;
		}





	}
	classStart = true;

}

void CSTown::CSMenueWindow::Draw()
{

	std::string bufS;
	switch (step)
	{
	case 5:
		Window[0].Draw(500, 10);
		Arrow.Draw(510, 30 + arrowPoint * 38);
		Window[4].Draw(315,90);
		Arrow.Draw(355, 121 + arrowPoint3 * 40);
		if (0 <= arrowPoint3&&arrowPoint3 < 5) {
			equipWindow->Draw();
		}

		Window[3].DrawExtend(5, 5, 230, 370);
		DrawFormatString(15, 10, BLACK, "ステータス");

		for (int i = 0; i < 16; i++) {
			switch (i)
			{
			case 0:	bufS = "HP"; break;
			case 1:	bufS = "MP"; break;
			case 2:	bufS = "攻"; break;
			case 3:	bufS = "防"; break;
			case 4:	bufS = "魔攻"; break;
			case 5:	bufS = "魔防"; break;
			case 6:	bufS = "速"; break;
			case 7:	bufS = "命中"; break;
			case 8:	bufS = "回避"; break;
			case 9:	bufS = "運"; break;
			case 10:bufS = "火防"; break;
			case 11:bufS = "木防"; break;
			case 12:bufS = "水防"; break;
			case 13:bufS = "光防"; break;
			case 14:bufS = "闇防"; break;
			case 15:bufS = "所持金"; break;

			default:
				break;
			}
			if (i == 15) {
				DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d G", bufS.c_str(), Status[i]);
			}
			else {
				DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d", bufS.c_str(), Status[i]);
			}
		}

		break;
	case 4:
		if (arrowPoint2 < 7) {
			equipManager->DrawWindow();
		}
		else {
			itemManager->WindowDraw();
		}
		break;
	case 3:

		Window[0].Draw(500, 10);
		Arrow.Draw(510, 30 + arrowPoint * 38);
		Window[2].Draw(315, 60, false);
		Arrow.Draw(325, 73 + arrowPoint2 * 26);

		Window[3].DrawExtend(5, 5, 230, 370);
		DrawFormatString(15, 10, BLACK, "ステータス");

		for (int i = 0; i < 16; i++) {
			switch (i)
			{
			case 0:	bufS = "HP"; break;
			case 1:	bufS = "MP"; break;
			case 2:	bufS = "攻"; break;
			case 3:	bufS = "防"; break;
			case 4:	bufS = "魔攻"; break;
			case 5:	bufS = "魔防"; break;
			case 6:	bufS = "速"; break;
			case 7:	bufS = "命中"; break;
			case 8:	bufS = "回避"; break;
			case 9:	bufS = "運"; break;
			case 10:bufS = "火防"; break;
			case 11:bufS = "木防"; break;
			case 12:bufS = "水防"; break;
			case 13:bufS = "光防"; break;
			case 14:bufS = "闇防"; break;
			case 15:bufS = "所持金"; break;

			default:
				break;
			}
			if (i == 15) {
				DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d G", bufS.c_str(), Status[i]);
			}
			else {
				DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d", bufS.c_str(), Status[i]);
			}
		}
		break;
	case 2:
		Window[0].Draw(500, 10);
		Arrow.Draw(510, 30 + arrowPoint * 38);
		textWindow->Draw();

		Window[3].DrawExtend(5, 5, 230, 370);
		DrawFormatString(15, 10, BLACK, "ステータス");

		for (int i = 0; i < 16; i++) {
			switch (i)
			{
			case 0:	bufS = "HP"; break;
			case 1:	bufS = "MP"; break;
			case 2:	bufS = "攻"; break;
			case 3:	bufS = "防"; break;
			case 4:	bufS = "魔攻"; break;
			case 5:	bufS = "魔防"; break;
			case 6:	bufS = "速"; break;
			case 7:	bufS = "命中"; break;
			case 8:	bufS = "回避"; break;
			case 9:	bufS = "運"; break;
			case 10:bufS = "火防"; break;
			case 11:bufS = "木防"; break;
			case 12:bufS = "水防"; break;
			case 13:bufS = "光防"; break;
			case 14:bufS = "闇防"; break;
			case 15:bufS = "所持金"; break;

			default:
				break;
			}
			if (i == 15) {
				DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d G", bufS.c_str(), Status[i]);
			}
			else {
				DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d", bufS.c_str(), Status[i]);
			}
		}
		break;
	case 1:
		Window[0].Draw(500, 10);
		Arrow.Draw(510, 30 + arrowPoint * 38);
		ynWindow->Draw();
		Window[3].DrawExtend(5, 5, 230, 370);
		DrawFormatString(15, 10, BLACK, "ステータス");

		for (int i = 0; i < 16; i++) {
			switch (i)
			{
			case 0:	bufS = "HP"; break;
			case 1:	bufS = "MP"; break;
			case 2:	bufS = "攻"; break;
			case 3:	bufS = "防"; break;
			case 4:	bufS = "魔攻"; break;
			case 5:	bufS = "魔防"; break;
			case 6:	bufS = "速"; break;
			case 7:	bufS = "命中"; break;
			case 8:	bufS = "回避"; break;
			case 9:	bufS = "運"; break;
			case 10:bufS = "火防"; break;
			case 11:bufS = "木防"; break;
			case 12:bufS = "水防"; break;
			case 13:bufS = "光防"; break;
			case 14:bufS = "闇防"; break;
			case 15:bufS = "所持金"; break;

			default:
				break;
			}
			if (i == 15) {
				DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d G", bufS.c_str(), Status[i]);
			}
			else {
				DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d", bufS.c_str(), Status[i]);
			}
		}


		break;

	case 0:
		Window[0].Draw(500, 10);
		Arrow.Draw(510, 30 + arrowPoint * 38);
		Window[3].DrawExtend(5,5,230,370);
		DrawFormatString(15,10,BLACK,"ステータス");

		for (int i = 0; i < 16; i++) {
			switch (i)
			{
			case 0:	bufS="HP"; break;
			case 1:	bufS = "MP"; break;
			case 2:	bufS = "攻"; break;
			case 3:	bufS = "防"; break;
			case 4:	bufS = "魔攻"; break;
			case 5:	bufS = "魔防"; break;
			case 6:	bufS = "速"; break;
			case 7:	bufS = "命中"; break;
			case 8:	bufS = "回避"; break;
			case 9:	bufS = "運"; break;
			case 10:bufS = "火防"; break;
			case 11:bufS = "木防"; break;
			case 12:bufS = "水防"; break;
			case 13:bufS = "光防"; break;
			case 14:bufS = "闇防"; break;
			case 15:bufS = "所持金"; break;
				
			default:
				break;
			}
			if (i == 15) {
				DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d G", bufS.c_str(), Status[i]);
			}
			else {
				DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d", bufS.c_str(), Status[i]);
			}

		}


		break;

	default:break;
	}
}

void CSTown::CSMenueWindow::End()
{

	delete textWindow;
	textWindow = NULL;
	equipManager = NULL;
	itemManager = NULL;
	ynWindow = NULL;
	equipWindow = NULL;
	equipmentInfo = NULL;
}




CSTown::CSHaniwa::CSHaniwa(CSTown & cstown) :cstown(cstown)
{
	textWindow = new CTextWindow("何か用事があるハニか？");
	classStart = false;
	haniwaSkillInfo= new CSV("zero/ZeroData/HaniwaSkill.csv");
	haniwaInfo = new CSV("zero/ZeroData/Haniwa.csv");
	step = 0;
	arrow = 0;
	Window[0] = "zero/MenueWindow.png";
	Window[1] = "zero/ItemSelectWindow2.png";
	Window[2] = "zero/ItemSelectWindow.png";
	Arrow = "zero/SmallArrow.png";
	arrow2 = 0;
	LvUP = false;

}


void CSTown::CSHaniwa::Loop()
{
	string bufS="";
	stringstream bufSS;
	int bufI=0;

	if (classStart == true) {

		switch (step)
		{
		case 6:
			if (arrow3 >= 1 && KeyUp()) {
				arrow3--;
				if (arrow3 <= 3) {
					haniSkillWindow->ChangeNum(arrow * 4 + arrow3 + 1);
				}
			}
			if (arrow3 <= 3 && KeyDown()) {
				arrow3++;
				if (arrow3 <= 3) {
					haniSkillWindow->ChangeNum(arrow * 4 + arrow3 + 1);
				}
			}

			if (KeyOK() && arrow3 == 4) {
				step = 3;
				arrow3 = 0;
				delete haniSkillWindow;
				haniSkillWindow = NULL;
			}
			if (KeyCancel()) {
				step = 3;
				arrow3 = 0;
				delete haniSkillWindow;
				haniSkillWindow = NULL;
			}

			break;
		case 5:
			ynWindow->Loop();
			if (KeyOK()) {
				if (LvUP == false) {
					step = 3;
					delete ynWindow;
					ynWindow = NULL;
				}
				else if(cstown.mySaveData->money>= (cstown.mySaveData->haniwaLevel[arrow]) * 1000){
					cstown.mySaveData->money -= (cstown.mySaveData->haniwaLevel[arrow]) * 1000;
					cstown.mySaveData->haniwaLevel[arrow]++;
					step = 3;
					delete ynWindow;
					ynWindow = NULL;
					haniwaWindow->ChangeKind(arrow);
				}

			}
			break;
		case 4:
			if (arrow3 >= 1 && KeyUp()) {
				arrow3--;
				haniwaWindow->ChangeKind(cstown.mySaveData->bringHaniwaKind[arrow3]);
			}
			if (arrow3 < 2 && KeyDown()) {
				arrow3++;
				if (arrow3 < 2) {
					haniwaWindow->ChangeKind(cstown.mySaveData->bringHaniwaKind[arrow3]);
				}
			}
			if (KeyOK()) {
				if (arrow3 < 2) {
					cstown.mySaveData->bringHaniwaKind[arrow3] = arrow + 1;
				}
				step = 3;
			
			}
			if (KeyCancel())
			{
				step = 3;
			}

			break;
		case 3:
			if (arrow2 >= 1 && KeyUp()) {
				arrow2--;
			}
			if (arrow2 <= 2 && KeyDown()) {
				arrow2++;
			}
			if (KeyOK()) {
				switch (arrow2)
				{
				case 0:
					if (arrow != cstown.mySaveData->bringHaniwaKind[0] && arrow != cstown.mySaveData->bringHaniwaKind[1]) {
						step = 4;
						arrow3 = 0;
						haniwaWindow->ChangeKind(cstown.mySaveData->bringHaniwaKind[0]);
					}
					break;
				case 1:
					if (cstown.mySaveData->haniwaLevel[arrow] < cstown.mySaveData->Rank * 10 && cstown.mySaveData->haniwaLevel[arrow] < 100) {
						bufI = (cstown.mySaveData->haniwaLevel[arrow]) * 1000;
						bufSS << bufI;
						bufS = bufSS.str();
						bufS += " Gで1Lv上げますか？";
						step = 5;
						ynWindow = new CYesNoWindow(&LvUP, bufS.c_str(), true, 400, 55 + 32 * arrow);
					}
					break;
				case 2:
					step = 6;
					arrow3 = 0;
					haniSkillWindow = new CHaniwaSkillWindow(arrow * 4 + 1, cstown.mySaveData->haniwaLevel[arrow]);
					break;
				case 3:
					step = 1;
					break;

				default:
					break;
				}
			}

			if (KeyCancel()) {
				step = 1;
			}

			break;
		case 2:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				cstown.RemoveScene(Flip::SLIDE_DOWN, 10);
			}
			break;
		case 1:

			if (arrow >= 1 && KeyUp()) {
				arrow --;

				haniwaWindow->ChangeKind(arrow);
			}
			if (arrow<=8 && KeyDown()) {
				arrow ++;

				haniwaWindow->ChangeKind(arrow);
			}

			if (KeyOK()) {
				step = 3;
				arrow2 = 0;
			}

			if (KeyCancel()) {
				step = 2;
				textWindow->PushText("また何かあったら、いつでも来るハニよ");
			}
			break;
		case 0:
			textWindow->Loop();
			if (textWindow->GetTextEmpty() == true) {
				step = 1;
				haniwaWindow = new CHaniwaWindow(cstown.mySaveData, 0);
			}
			break;


		default:break;
		}





	}
	classStart = true;
}

void CSTown::CSHaniwa::Draw()
{
	int bufI = 0;
	string bufS = "";


	switch (step)
	{
	case 6:
		haniwaWindow->Draw();
		Window[0].DrawExtend(5, 5, 240, 365);
		Window[1].DrawExtend(245, 15 + 32 * arrow, 390, 140 + 32 * arrow);
		Window[1].DrawExtend(400, 15 + 32 * arrow, 700, 180 + 32 * arrow);
		Arrow.Draw(15, 30 + 32 * arrow);
		Arrow.Draw(253, 25 + 32 * arrow + 30 * arrow2);
		Arrow.Draw(410, 25 + 32 * arrow + 30 * arrow3);
		DrawFormatString(270, 25 + 32 * arrow + 30 * 0, BLACK, "お供にする", bufS.c_str());
		DrawFormatString(270, 25 + 32 * arrow + 30 * 1, BLACK, "LEVELを上げる");
		DrawFormatString(270, 25 + 32 * arrow + 30 * 2, BLACK, "技確認");
		DrawFormatString(270, 25 + 32 * arrow + 30 * 3, BLACK, "閉じる");

		if (cstown.mySaveData->haniwaLevel[arrow] >= cstown.mySaveData->Rank * 10) {
			if (cstown.mySaveData->haniwaLevel[arrow] >= 100) {
				DrawFormatString(310, 400, RED, "レベル上限にたっしています。");
			}
			else {
				DrawFormatString(310, 400, RED, "今のランクでのレベル上限にたっしています。");
			}
		}

		for (int i = 0; i<10; i++) {
			bufS = (*haniwaInfo)[i][1];
			DrawFormatString(40, 30 + 32 * i, BLACK, "%s", bufS.c_str());
		}
		for (int i = 0; i<2; i++) {
			DrawFormatString(40, 45 + 32 * cstown.mySaveData->bringHaniwaKind[i], RED, "（お供選択中↑）");
		}

		for (int i = 0; i < 4; i++) {
			bufS = (*haniwaSkillInfo)[arrow*4+i][1];
			DrawFormatString(430, 25 + 32 * arrow + 30 * i, BLACK, "技%d:%s", i + 1, bufS.c_str());
		}
		DrawFormatString(430, 25 + 32 * arrow + 30 * 4, BLACK, "閉じる");

		haniSkillWindow->Draw();


		break;
	case 5:
		haniwaWindow->Draw();
		Window[0].DrawExtend(5, 5, 240, 365);
		Window[1].DrawExtend(245, 15 + 32 * arrow, 390, 140 + 32 * arrow);
		Window[1].DrawExtend(400, 10 + 32 * arrow, 680, 50 + 32 * arrow);
		Arrow.Draw(15, 30 + 32 * arrow);
		Arrow.Draw(253, 25 + 32 * arrow + 30 * arrow2);
		DrawFormatString(270, 25 + 32 * arrow + 30 * 0, BLACK, "お供にする", bufS.c_str());
		DrawFormatString(270, 25 + 32 * arrow + 30 * 1, BLACK, "LEVELを上げる");
		DrawFormatString(270, 25 + 32 * arrow + 30 * 2, BLACK, "技確認");
		DrawFormatString(270, 25 + 32 * arrow + 30 * 3, BLACK, "閉じる");
		DrawFormatString(410, 19 + 32 * arrow, BLACK, "所持金:%d G", cstown.mySaveData->money);

		ynWindow->Draw();

		if (cstown.mySaveData->haniwaLevel[arrow] >= cstown.mySaveData->Rank * 10) {
			if (cstown.mySaveData->haniwaLevel[arrow] >= 100) {
				DrawFormatString(310, 400, RED, "レベル上限にたっしています。");
			}
			else {
				DrawFormatString(310, 400, RED, "今のランクでのレベル上限にたっしています。");
			}
		}

		for (int i = 0; i < 10; i++) {
			bufS = (*haniwaInfo)[i][1];
			DrawFormatString(40, 30 + 32 * i, BLACK, "%s", bufS.c_str());
		}
		for (int i = 0; i < 2; i++) {
			DrawFormatString(40, 45 + 32 * cstown.mySaveData->bringHaniwaKind[i], RED, "（お供選択中↑）");
		}

		break;
	case 4:
		haniwaWindow->Draw();
		Window[0].DrawExtend(5, 5, 240, 365);
		Window[1].DrawExtend(245, 15 + 32 * arrow, 390, 140 + 32 * arrow);
		Window[1].DrawExtend(400, 15 + 32 * arrow, 650, 180 + 32 * arrow);
		Arrow.Draw(15, 30 + 32 * arrow);
		Arrow.Draw(253, 25 + 32 * arrow + 30 * arrow2);
		Arrow.Draw(410, 25 + 32 * arrow + 30 * arrow3);
		DrawFormatString(270, 25 + 32 * arrow + 30 * 0, BLACK, "お供にする", bufS.c_str());
		DrawFormatString(270, 25 + 32 * arrow + 30 * 1, BLACK, "LEVELを上げる");
		DrawFormatString(270, 25 + 32 * arrow + 30 * 2, BLACK, "技確認");
		DrawFormatString(270, 25 + 32 * arrow + 30 * 3, BLACK, "閉じる");

		if (cstown.mySaveData->haniwaLevel[arrow] >= cstown.mySaveData->Rank * 10) {
			if (cstown.mySaveData->haniwaLevel[arrow] >= 100) {
				DrawFormatString(310, 400, RED, "レベル上限にたっしています。");
			}
			else {
				DrawFormatString(310, 400, RED, "今のランクでのレベル上限にたっしています。");
			}
		}

		for (int i = 0; i < 2; i++) {
			bufS = (*haniwaInfo)[cstown.mySaveData->bringHaniwaKind[i]][1];
			DrawFormatString(430, 25 + 32 * arrow + 30 * i, BLACK, "お供%d:%s", i + 1, bufS.c_str());
		}
		DrawFormatString(430, 25 + 32 * arrow + 30 * 2, BLACK, "閉じる");
		DrawFormatString(410, 25 + 32 * arrow + 30 * 4, BLUE, "Z又はEnterキーで入れ替え");

		for (int i = 0; i < 10; i++) {
			bufS = (*haniwaInfo)[i][1];
			DrawFormatString(40, 30 + 32 * i, BLACK, "%s", bufS.c_str());
		}
		for (int i = 0; i < 2; i++) {
			DrawFormatString(40, 45 + 32 * cstown.mySaveData->bringHaniwaKind[i], RED, "（お供選択中↑）");
		}
		break;

	case 3:
		haniwaWindow->Draw();
		Window[0].DrawExtend(5, 5, 240, 365);
		Window[1].DrawExtend(245, 15 + 32 * arrow, 390, 140 + 32 * arrow);
		Arrow.Draw(15, 30 + 32 * arrow);
		Arrow.Draw(253, 25 + 32 * arrow + 30 * arrow2);
		DrawFormatString(270, 25 + 32 * arrow + 30 * 0, BLACK, "お供にする", bufS.c_str());
		DrawFormatString(270, 25 + 32 * arrow + 30 * 1, BLACK, "LEVELを上げる");
		DrawFormatString(270, 25 + 32 * arrow + 30 * 2, BLACK, "技確認");
		DrawFormatString(270, 25 + 32 * arrow + 30 * 3, BLACK, "閉じる");

		if (cstown.mySaveData->haniwaLevel[arrow] >= cstown.mySaveData->Rank * 10) {
			if (cstown.mySaveData->haniwaLevel[arrow] >= 100) {
				DrawFormatString(310, 400, RED, "レベル上限にたっしています。");
			}
			else {
				DrawFormatString(310, 400, RED, "今のランクでのレベル上限にたっしています。");
			}
		}

		for (int i = 0; i<10; i++) {
			bufS = (*haniwaInfo)[i][1];
			DrawFormatString(40, 30 + 32 * i, BLACK, "%s", bufS.c_str());
		}
		for (int i = 0; i<2; i++) {
			DrawFormatString(40, 45 + 32 * cstown.mySaveData->bringHaniwaKind[i], RED, "（お供選択中↑）");
		}

		break;
	case 2:
		textWindow->Draw();
		break;
	case 1:

		haniwaWindow->Draw();
		Window[0].DrawExtend(5, 5, 240, 365);
		Arrow.Draw(15, 30 + 32 * arrow);
		for (int i = 0; i<10; i++) {
			bufS = (*haniwaInfo)[i][1];
			DrawFormatString(40, 30+32*i, BLACK, "%s",bufS.c_str());
		}
		for (int i = 0; i<2; i++) {
			DrawFormatString(40, 45 + 32 * cstown.mySaveData->bringHaniwaKind[i], RED, "（お供選択中↑）");
		}

		if (cstown.mySaveData->haniwaLevel[arrow] >= cstown.mySaveData->Rank * 10) {
			if (cstown.mySaveData->haniwaLevel[arrow] >= 100) {
				DrawFormatString(310, 400, RED, "レベル上限にたっしています。");
			}
			else {
				DrawFormatString(310, 400, RED, "今のランクでのレベル上限にたっしています。");
			}
		}

		break;

	case 0:
		textWindow->Draw();
		break;
	default:break;
	}

}

void CSTown::CSHaniwa::End()
{

	delete textWindow;
	textWindow = NULL;
	delete haniwaInfo;
	haniwaInfo = NULL;
	delete haniwaSkillInfo;
	haniwaSkillInfo = NULL;
	delete haniwaWindow;
	haniwaWindow = NULL;
	haniSkillWindow = NULL;
	ynWindow = NULL;

}


CSTown::CSGoToQuest::CSGoToQuest(CSTown & cstown) :cstown(cstown)
{
	step = 0;
	classStart = false;
	textWindow = new CTextWindow("どのクエストを受けますか？");
	Arrow = "zero/SmallArrow.png";
	Window[0] = "zero/ItemSelectWindow.png";
	Window[1] = "zero/MenueWindow.png";
	Window[2] = "zero/ItemSelectWindow2.png";
	Window[3] = "zero/TextWindow4.png";
	vq = new vector<Squest>;

	for (int i = 0; i < 3; i++) {
		arrowPoint[i] = 0;
	}

	goQuest = false;


}

CSTown::CSGoToQuest::~CSGoToQuest()
{

delete textWindow;
textWindow = NULL;
delete vq;
vq = NULL;

}

void CSTown::CSGoToQuest::Loop()
{
	int bufI;
	string bufS;

	Squest bufSQ;


	if (classStart == true) {

		switch (step)
		{
		case 9:
			textWindow->Loop();
			if (textWindow->GetTextEmpty()) {
				bufSQ = (*vq)[arrowPoint[2]];
				(*vq).clear();
				delete vq;
				vq = NULL;
				Game.FlipScene(new CSQuestBase(GetRand(syokyuMap-1)+1, &bufSQ), Flip::ROTATION_RIGHT);
				
			}
			break;

		case 7:
			ynWindow->Loop();
			if (KeyOK()) {
				delete ynWindow;
				ynWindow = NULL;
				if (goQuest) {
					step=9;
					textWindow->PushText("それでは、行ってらっしゃい");
				}
				else {
					step = 5;
				}


			}

			break;
		case 6:
			if (KeyUp() && arrowPoint[2] > 0) {
				arrowPoint[2]--;
			}

			if (KeyDown() && arrowPoint[2] <(*vq).size() - 1) {
				arrowPoint[2]++;
			}



			if (KeyCancel()) {
				step = 3;
				(*vq).clear();
				delete questInfo;
				questInfo = NULL;
				delete enemyInfo;
				enemyInfo = NULL;
				delete bigBossInfo;
				bigBossInfo = NULL;
			}
			break;
		case 5:
			if (KeyUp() && arrowPoint[2] > 0) {
				arrowPoint[2]--;
			}

			if (KeyDown() && arrowPoint[2] <(*vq).size()-1) {
				arrowPoint[2]++;
			}

			if (KeyOK()) {
				step = 7;
				ynWindow = new CYesNoWindow(&goQuest, "このクエストにしますか？", false, 305, 30 + 25 * (arrowPoint[2] + 1));
			}

			if (KeyCancel()) {
				step = 3;
				(*vq).clear();
				delete questInfo;
				questInfo = NULL;
				delete enemyInfo;
				enemyInfo = NULL;
				delete bigBossInfo;
				bigBossInfo = NULL;
			}
			break;

		case 4:
			if (KeyUp() && arrowPoint[1] > 0) {
				arrowPoint[1]--;
			}

			if (KeyDown() && arrowPoint[1] < cstown.mySaveData->Rank - 6 && arrowPoint[1]<6) {
				arrowPoint[1]++;
			}
			if (KeyOK()) {
				qLevel = arrowPoint[1] + 11;
				questInfo = new CSV("zero/ZeroData/Quest.csv");
				enemyInfo = new CSV("zero/ZeroData/Enemy.csv");
				bigBossInfo = new CSV("zero/ZeroData/BigBoss.csv");

				for (int i = 0; i < questInfo->GetLineNum(); i++) {
					bufI = (*questInfo)[i][1];
					if (bufI == qLevel) {
						bufq.Qnum = (*questInfo)[i][0];
						bufq.Qname = (*questInfo)[i][2];
						for (int j = 0; j < 8; j++) {
							bufq.enemy[j] = (*questInfo)[i][3 + j];
						}
						bufq.bossTimes = (*questInfo)[i][11];
						for (int j = 0; j < 3; j++) {
							bufq.bigBoss[j] = (*questInfo)[i][12 + 7 * j];
							for (int k = 0; k < 3; k++) {
								for (int l = 0; l < 2; l++) {
									bufq.boss[j][k][l] = (*questInfo)[i][13 + 7 * j + k * 2 + l];
								}
							}
						}

						for (int k = 0; k < 5; k++) {
							for (int j = 0; j < 3; j++) {
								bufq.treasure[k][j] = (*questInfo)[i][33 + 3 * k + j];
							}
						}

						bufq.rewardMoney = (*questInfo)[i][48];

						bufq.difficult = arrowPoint[0];
						bufq.qLevel = arrowPoint[1];

						(*vq).push_back(bufq);

					}

					if(bufI == qLevel + 100 && cstown.mySaveData->clearAmount[arrowPoint[0]][arrowPoint[1]]>=5) {
						bufq.Qnum = (*questInfo)[i][0];
						bufq.Qname = (*questInfo)[i][2];
						for (int j = 0; j < 8; j++) {
							bufq.enemy[j] = (*questInfo)[i][3 + j];
						}
						bufq.bossTimes = (*questInfo)[i][11];
						for (int j = 0; j < 3; j++) {
							bufq.bigBoss[j] = (*questInfo)[i][12 + 7 * j];
							for (int k = 0; k < 3; k++) {
								for (int l = 0; l < 2; l++) {
									bufq.boss[j][k][l] = (*questInfo)[i][13 + 7 * j + k * 2 + l];
								}
							}
						}

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 3; j++) {
								bufq.treasure[i][j] = (*questInfo)[i][33 + 3 * i + j];
							}
						}

						bufq.rewardMoney = (*questInfo)[i][48];
						bufq.difficult = arrowPoint[0];
						bufq.qLevel = arrowPoint[1];

						(*vq).push_back(bufq);

					}

				}



				step = 6;
				arrowPoint[2] = 0;
				break;
			}

			if (KeyCancel()) {
				step = 2;
			}

			break;
		case 3:
			if (KeyUp() && arrowPoint[1] > 0) {
				arrowPoint[1]--;
			}

			if (KeyDown() && arrowPoint[1] < cstown.mySaveData->Rank-1 && arrowPoint[1]<4) {
				arrowPoint[1]++;
			}

			if (KeyOK()) {
				qLevel = arrowPoint[1] + 1;
				questInfo = new CSV("zero/ZeroData/Quest.csv");
				enemyInfo = new CSV("zero/ZeroData/Enemy.csv");
				bigBossInfo = new CSV("zero/ZeroData/BigBoss.csv");

				for (int i = 0; i < questInfo->GetLineNum(); i++) {
					bufI = (*questInfo)[i][1];
					if (bufI == qLevel) {
						bufq.Qnum = (*questInfo)[i][0];
						bufq.Qname = (*questInfo)[i][2];
						for (int j = 0; j < 8; j++) {
							bufq.enemy[j] = (*questInfo)[i][3+j];
						}
						bufq.bossTimes = (*questInfo)[i][11];
						for (int j = 0; j < 3; j++) {
							bufq.bigBoss[j] = (*questInfo)[i][12+7*j];
							for (int k = 0; k < 3; k++) {
								for (int l = 0; l < 2; l++) {
									bufq.boss[j][k][l] = (*questInfo)[i][13+7*j+k*2+l];
								}
							}
						}

						for (int k = 0; k < 5; k++) {
							for (int j = 0; j < 3; j++) {
								bufq.treasure[k][j] = (*questInfo)[i][33 + 3 * k + j];
							}
						}

						bufq.rewardMoney = (*questInfo)[i][48];

						bufq.difficult = arrowPoint[0];
						bufq.qLevel = arrowPoint[1];

						(*vq).push_back(bufq);

					}

					if (bufI == qLevel + 100 && cstown.mySaveData->clearAmount[arrowPoint[0]][arrowPoint[1]] >= 5) {
						bufq.Qnum = (*questInfo)[i][0];
						bufq.Qname = (*questInfo)[i][2];
						for (int j = 0; j < 8; j++) {
							bufq.enemy[j] = (*questInfo)[i][3 + j];
						}
						bufq.bossTimes = (*questInfo)[i][11];
						for (int j = 0; j < 3; j++) {
							bufq.bigBoss[j] = (*questInfo)[i][12 + 7 * j];
							for (int k = 0; k < 3; k++) {
								for (int l = 0; l < 2; l++) {
									bufq.boss[j][k][l] = (*questInfo)[i][13 + 7 * j + k * 2 + l];
								}
							}
						}

						for (int k = 0; k < 5; k++) {
							for (int j = 0; j < 3; j++) {
								bufq.treasure[k][j] = (*questInfo)[i][33 + 3 * k + j];
							}
						}

						bufq.rewardMoney = (*questInfo)[i][48];

						bufq.difficult = arrowPoint[0];
						bufq.qLevel = arrowPoint[1];

						(*vq).push_back(bufq);

					}
				}

				step = 5;
				arrowPoint[2] = 0;
				break;
			}

			if (KeyCancel()) {
				step = 2;
			}

			break;

		case 2:
			

			if (KeyUp() && arrowPoint[0] > 0) {
				arrowPoint[0]--;
			}

			if (KeyDown() && arrowPoint[0] < 2) {
				arrowPoint[0]++;
			}

			if (KeyOK()) {

				switch (arrowPoint[0])
				{
				case 0:
					step = 3;
					arrowPoint[1] = 0;
					break;

				case 1:
					if (cstown.mySaveData->Rank > 5) {
						step = 4;
						arrowPoint[1] = 0;
					}
					break;

				case 2:
					step = 1;
					textWindow->TextClear();
					textWindow->PushText("また準備ができたら、話しかけてください。");
					break;

				default:
					break;
				}

			}


			if (KeyCancel()) {
				step = 1;
				textWindow->TextClear();
				textWindow->PushText("また準備ができたら、話しかけてください。");
			}

			break;

		case 1:
			textWindow->Loop();
			if (textWindow->GetTextEmpty()) {
				cstown.RemoveScene(Flip::SLIDE_DOWN, 10);
			}
			
			break;

		case 0:

			textWindow->Loop();
			
			if (textWindow->GetTextEmpty()) {
				step = 2;
			}
			
			break;


		default:break;
		}



	}
	classStart = true;
}

void CSTown::CSGoToQuest::Draw()
{
	int bufI;
	string bufS;

	if (step >= 2&& step<=8) {
		Window[1].DrawExtend(5, 5,120,160);
		Arrow.Draw(10, 30 + 25 * arrowPoint[0]);
		DrawFormatString(28, 30 + 25 * 0, BLACK, "下級");
		DrawFormatString(28, 30 + 25 * 1, BLACK, "上級");
		DrawFormatString(28, 30 + 25 * 2, BLACK, "閉じる");
	}

	switch (step)
	{
	case 9:
		textWindow->Draw();
		break;
	case 8:

		Window[1].DrawExtend(125, 5, 290, 250);
		Window[2].DrawExtend(300, 5, 680, 310);
		Window[2].DrawExtend(5, 360, 700, 574);


		Arrow.Draw(137, 30 + 25 * arrowPoint[1]);
		Arrow.Draw(305, 30 + 25 * arrowPoint[2]);

		for (int i = 0; i < cstown.mySaveData->Rank; i++) {
			if (i > 4) {
				break;
			}

			DrawFormatString(159, 30 + 25 * i, BLACK, "LEVEL.%d", i + 1);

		}
		DrawFormatString(132, 30 + 25 * 7, BLACK, "X又はback space");
		DrawFormatString(132, 30 + 25 * 8, BLACK, "キーで閉じる");

		for (int i = 0; i < (*vq).size(); i++) {
			bufS = (*vq)[i].Qname;
			DrawFormatString(325, 30 + 25 * i, BLACK, "%d:%s", i + 1, bufS.c_str());
			DrawFormatString(325, 30 + 25 * 10, BLACK, "X又はback spaceキーで閉じる");

		}
		bufS.clear();
		bufS += (*vq)[arrowPoint[2]].Qname;
		if (cstown.mySaveData->questClear[(*vq)[arrowPoint[2]].Qnum]) {
			bufS += "　　clear済み";
		}

		DrawFormatString(20, 370 + 30 * 0, BLACK, "<%s>", bufS.c_str());
		bufS.clear();
		if ((*vq)[arrowPoint[2]].bossTimes >= 2) {

			for (int i = 0; i<(*vq)[arrowPoint[2]].bossTimes; i++) {
				if ((*vq)[arrowPoint[2]].bigBoss[i]) {
					bufS += (*bigBossInfo)[((*vq)[arrowPoint[2]].boss[i][0][0]) - 1][1];
				}
				else {
					bufS += (*enemyInfo)[((*vq)[arrowPoint[2]].boss[i][0][0]) - 1][1];
				}
				if (i == (*vq)[arrowPoint[2]].bossTimes - 1) {
					bufS += "の連続討伐";
					break;
				}
				bufS += "と";
			}


		}
		else {
			if ((*vq)[arrowPoint[2]].bigBoss[0]) {
				bufS += (*bigBossInfo)[((*vq)[arrowPoint[2]].boss[0][0][0]) - 1][1];
			}
			else {
				bufS += (*enemyInfo)[((*vq)[arrowPoint[2]].boss[0][0][0]) - 1][1];
			}
			bufS += "の討伐";
		}

		DrawFormatString(20, 370 + 30 * 1, BLACK, "クエスト内容:%s", bufS.c_str());

		bufI = (*vq)[arrowPoint[2]].rewardMoney;

		DrawFormatString(20, 400 + 30 * 1, BLACK, "報酬金:%d", bufI);

		break;

	case 7:

		Window[1].DrawExtend(125, 5, 290, 250);
		Window[2].DrawExtend(300, 5, 680, 310);
		Window[2].DrawExtend(5, 360, 700, 574);


		Arrow.Draw(137, 30 + 25 * arrowPoint[1]);
		Arrow.Draw(305, 30 + 25 * arrowPoint[2]);

		for (int i = 0; i < cstown.mySaveData->Rank; i++) {
			if (i > 4) {
				break;
			}

			DrawFormatString(159, 30 + 25 * i, BLACK, "LEVEL.%d", i + 1);

		}
		DrawFormatString(132, 30 + 25 * 7, BLACK, "X又はback space");
		DrawFormatString(132, 30 + 25 * 8, BLACK, "キーで閉じる");

		for (int i = 0; i < (*vq).size(); i++) {
			bufS = (*vq)[i].Qname;
			DrawFormatString(325, 30 + 25 * i, BLACK, "%d:%s", i + 1, bufS.c_str());
			DrawFormatString(325, 30 + 25 * 10, BLACK, "X又はback spaceキーで閉じる");

		}
		bufS.clear();
		bufS += (*vq)[arrowPoint[2]].Qname;
		if (cstown.mySaveData->questClear[(*vq)[arrowPoint[2]].Qnum]) {
			bufS += "　　clear済み";
		}

		DrawFormatString(20, 370 + 30 * 0, BLACK, "<%s>", bufS.c_str());
		bufS.clear();
		if ((*vq)[arrowPoint[2]].bossTimes >= 2) {

			for (int i = 0; i<(*vq)[arrowPoint[2]].bossTimes; i++) {
				if ((*vq)[arrowPoint[2]].bigBoss[i]) {
					bufS += (*bigBossInfo)[((*vq)[arrowPoint[2]].boss[i][0][0]) - 1][1];
				}
				else {
					bufS += (*enemyInfo)[((*vq)[arrowPoint[2]].boss[i][0][0]) - 1][1];
				}
				if (i == (*vq)[arrowPoint[2]].bossTimes - 1) {
					bufS += "の連続討伐";
					break;
				}
				bufS += "と";
			}


		}
		else {
			if ((*vq)[arrowPoint[2]].bigBoss[0]) {
				bufS += (*bigBossInfo)[((*vq)[arrowPoint[2]].boss[0][0][0]) - 1][1];
			}
			else {
				bufS += (*enemyInfo)[((*vq)[arrowPoint[2]].boss[0][0][0]) - 1][1];
			}
			bufS += "の討伐";
		}

		DrawFormatString(20, 370 + 30 * 1, BLACK, "クエスト内容:%s", bufS.c_str());

		bufI = (*vq)[arrowPoint[2]].rewardMoney;

		DrawFormatString(20, 400 + 30 * 1, BLACK, "報酬金:%d", bufI);
		
		ynWindow->Draw();

		break;

	case 6:

		Window[1].DrawExtend(125, 5, 290, 250);
		Window[2].DrawExtend(300, 5, 680, 310);
		Window[2].DrawExtend(5, 360, 700, 574);


		Arrow.Draw(137, 30 + 25 * arrowPoint[1]);
		Arrow.Draw(305, 30 + 25 * arrowPoint[2]);

		for (int i = 0; i < cstown.mySaveData->Rank; i++) {
			if (i > 4) {
				break;
			}

			DrawFormatString(159, 30 + 25 * i, BLACK, "LEVEL.%d", i + 1);

		}
		DrawFormatString(132, 30 + 25 * 7, BLACK, "X又はback space");
		DrawFormatString(132, 30 + 25 * 8, BLACK, "キーで閉じる");

		for (int i = 0; i < (*vq).size(); i++) {
			bufS = (*vq)[i].Qname;
			DrawFormatString(325, 30 + 25 * i, BLACK, "%d:%s", i + 1, bufS.c_str());
			DrawFormatString(325, 30 + 25 * 10, BLACK, "X又はback spaceキーで閉じる");

		}
		bufS.clear();
		bufS += (*vq)[arrowPoint[2]].Qname;
		if (cstown.mySaveData->questClear[(*vq)[arrowPoint[2]].Qnum]) {
			bufS += "　　clear済み";
		}

		DrawFormatString(20, 370 + 30 * 0, BLACK, "<%s>", bufS.c_str());
		bufS.clear();
		if ((*vq)[arrowPoint[2]].bossTimes >= 2) {

			for (int i = 0; i<(*vq)[arrowPoint[2]].bossTimes; i++) {
				if ((*vq)[arrowPoint[2]].bigBoss[i]) {
					bufS += (*bigBossInfo)[((*vq)[arrowPoint[2]].boss[i][0][0]) - 1][1];
				}
				else {
					bufS += (*enemyInfo)[((*vq)[arrowPoint[2]].boss[i][0][0]) - 1][1];
				}
				if (i == (*vq)[arrowPoint[2]].bossTimes - 1) {
					bufS += "の連続討伐";
					break;
				}
				bufS += "と";
			}


		}
		else {
			if ((*vq)[arrowPoint[2]].bigBoss[0]) {
				bufS += (*bigBossInfo)[((*vq)[arrowPoint[2]].boss[0][0][0]) - 1][1];
			}
			else {
				bufS += (*enemyInfo)[((*vq)[arrowPoint[2]].boss[0][0][0]) - 1][1];
			}
			bufS += "の討伐";
		}

		DrawFormatString(20, 370 + 30 * 1, BLACK, "クエスト内容:%s", bufS.c_str());

		bufI = (*vq)[arrowPoint[2]].rewardMoney;

		DrawFormatString(20, 400 + 30 * 1, BLACK, "報酬金:%d", bufI);

		break;

	case 5:

		Window[1].DrawExtend(125, 5, 290, 250);
		Window[2].DrawExtend(300, 5, 680, 310);
		Window[2].DrawExtend(5, 360, 700, 574);


		Arrow.Draw(137, 30 + 25 * arrowPoint[1]);
		Arrow.Draw(305, 30 + 25 * arrowPoint[2]);

		for (int i = 0; i < cstown.mySaveData->Rank; i++) {
			if (i > 4) {
				break;
			}

			DrawFormatString(159, 30 + 25 * i, BLACK, "LEVEL.%d", i + 1);

		}
		DrawFormatString(132, 30 + 25 * 7, BLACK, "X又はback space");
		DrawFormatString(132, 30 + 25 * 8, BLACK, "キーで閉じる");

		for (int i = 0; i < (*vq).size(); i++) {
			bufS = (*vq)[i].Qname;
			DrawFormatString(325, 30 + 25 * i, BLACK, "%d:%s", i + 1, bufS.c_str());
			DrawFormatString(325, 30 + 25 * 10, BLACK, "X又はback spaceキーで閉じる");

		}
		bufS.clear();
		bufS += (*vq)[arrowPoint[2]].Qname;
		if (cstown.mySaveData->questClear[(*vq)[arrowPoint[2]].Qnum]) {
			bufS += "　　clear済み";
		}

		DrawFormatString(20,370 + 30*0, BLACK, "<%s>", bufS.c_str());
		bufS.clear();
		if ((*vq)[arrowPoint[2]].bossTimes >= 2) {

			for(int i=0;i<(*vq)[arrowPoint[2]].bossTimes;i++){
				if ((*vq)[arrowPoint[2]].bigBoss[i]) {
					bufS += (*bigBossInfo)[((*vq)[arrowPoint[2]].boss[i][0][0])-1][1];
				}
				else {
					bufS += (*enemyInfo)[((*vq)[arrowPoint[2]].boss[i][0][0]) - 1][1];
				}
				if (i == (*vq)[arrowPoint[2]].bossTimes - 1) {
					bufS += "の連続討伐";
					break;
				}
				bufS += "と";
			}

			
		}
		else {
			if ((*vq)[arrowPoint[2]].bigBoss[0]) {
				bufS += (*bigBossInfo)[((*vq)[arrowPoint[2]].boss[0][0][0]) - 1][1];
			}
			else {
				bufS += (*enemyInfo)[((*vq)[arrowPoint[2]].boss[0][0][0]) - 1][1];
			}
			bufS += "の討伐";
		}

		DrawFormatString(20, 370 + 30 * 1, BLACK, "クエスト内容:%s", bufS.c_str());

		bufI = (*vq)[arrowPoint[2]].rewardMoney;

		DrawFormatString(20, 400 + 30 * 1, BLACK, "報酬金:%d", bufI);

		break;

	case 4:
		Window[1].DrawExtend(125, 5, 290, 310);

		Arrow.Draw(137, 30 + 25 * arrowPoint[1]);

		for (int i = 0; i < cstown.mySaveData->Rank-5; i++) {
			if (i>6) {
				break;
			}

			DrawFormatString(159, 30 + 25 * i, BLACK, "LEVEL.%d", i + 1);

		}
		DrawFormatString(132, 30 + 25 * 8, BLACK, "X又はback space");
		DrawFormatString(132, 30 + 25 * 9, BLACK, "キーで閉じる");
		break;

	case 3:
		Window[1].DrawExtend(125, 5, 290, 250);

		Arrow.Draw(137, 30 + 25 * arrowPoint[1]);

		for (int i = 0; i < cstown.mySaveData->Rank; i++) {
			if(i>4){
				break;
			}

			DrawFormatString(159, 30 + 25 * i, BLACK, "LEVEL.%d",i+1);

		}
		DrawFormatString(132, 30 + 25 * 7, BLACK, "X又はback space");
		DrawFormatString(132, 30 + 25 * 8, BLACK, "キーで閉じる");
		break;

	case 2:
		break;

	case 1:
		textWindow->Draw();
		break;

	case 0:
		textWindow->Draw();
		break;

	default:
		break;
	}

}

void CSTown::CSGoToQuest::End()
{
}


