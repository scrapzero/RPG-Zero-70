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

		if (checkAround[0] == 139 || checkAround[1] == 139) {
			FlipScene(new CSSorceRemake(*this), Flip::SLIDE_UP, 10);
		}

	
	
	}

	if (graphDirect == 2 && KeyOK()) {
		checkAround[0] = TownMap.Get(TownMap.layer.C, jikiMapX + 1, jikiMapY) - 1;
		checkAround[1] = TownMap.Get(TownMap.layer.B, jikiMapX + 1, jikiMapY) - 1;

		if (checkAround[0] == 142 || checkAround[1] == 142) {
			FlipScene(new CSItemSet(*this), Flip::SLIDE_UP, 10);
		}

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
			textWindow->PushText("%s",S);
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
	ItemInfo[0] = new CSV("zero/ZeroData/Sorce.txt");
	ItemInfo[1] = new CSV("zero/ZeroData/Tool.txt");
	ItemInfo[2] = new CSV("zero/ZeroData/Food.txt");
	Arrow = "zero/SmallArrow.png";
	Window[0] = "zero/ItemSelectWindow.png";
	Window[1] = "zero/ItemSelectWindow2.png";
}

void CSTown::CSItemSet::Loop()
{
	if (classStart == true) {

		switch (step)
		{
		case 3:
			if (KeyUp() && 0 < arrowPoint2 ) {
				arrowPoint2 -= 1;
			}
			if (KeyDown() && 2 > arrowPoint2 ) {
				arrowPoint2 += 1;
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
	case 2:
		textWindow->Draw();
		break;
	case 3:
		Window[1].DrawExtend(380,5,700,160);
		DrawFormatString(410, 30, BLACK, "このアイテムセットを持っていく");

		DrawFormatString(410, 70, BLACK, "アイテムセットの内容を変更する");
		DrawFormatString(410, 110, BLACK, "閉じる");
		Arrow(385,30+arrowPoint2*40);

	case 1:
		Window[0].DrawExtend(5,5,370,250);
		Window[1].DrawExtend(5, 260, 370, 570);

		Arrow(12 + (arrowPoint % 2) * 160, 20 + (arrowPoint / 2) * 50);
		for (int i = 0; i < 10; i++) {
			DrawFormatString(30 + (i % 2) * 160, 20 + (i / 2) * 50, BLACK, "アイテムセット%d", i+1);
		}
		for (int i = 0; i < 10; i++) {
			bufS = "";
			bufInt[0] = cstown.mySaveData->GetSetItem(arrowPoint, i, true);
			bufInt[1] = cstown.mySaveData->GetSetItem(arrowPoint, i, false);
			if (bufInt[1] > 0) {
				bufS = (*ItemInfo[bufInt[0]])[bufInt[1] - 1][1];
			}

			DrawFormatString(30 + (i % 2) * 160, 290 + (i / 2) * 50, BLACK, "%d:%s", i+1,bufS.c_str());
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