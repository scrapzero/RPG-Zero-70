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

		if (checkAround[0] == 141 || checkAround[1] == 141) {
			FlipScene(new CSSellItem(*this), Flip::SLIDE_UP, 10);
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
	textWindow = new CTextWindow("�������񂾂��H");
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
				textWindow->PushText("�܂����������Ăق���������A�������");
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
	textWindow = new CTextWindow("��������ė~�����J�{�H");
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
				textWindow->PushText("�܂�����������Ăق���������A���Ă���J�{");
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
	S = "���ɂȂ�̑��������񂾁H";
	textWindow = new CTextWindow("�ǂ̑��������񂾁H");
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
			textWindow->PushText("%s/n�i�w�L�[�ŏI���j",S);
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
			textWindow->PushText("�܂����ł����Ă���B");
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
	textWindow = new CTextWindow("�������H����΂����H");
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
				textWindow->PushText("�܂����H���Ăق��������炱���܂ŗ���");
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
	textWindow = new CTextWindow("�����Ă����A�C�e���ɂ��ĉ���������ł����H");
	classStart = false;
	step = 0;
	arrowPoint = 0;
	arrowPoint2 = 0;
	arrowPoint3 = 0;
	closeWindow = true;
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
				textWindow->PushText("�܂����ł����Ă��������ˁB");
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
		DrawFormatString(410, 285, BLACK, "����");

		DrawFormatString(410, 325, BLACK, "�H�ו�");
		DrawFormatString(410, 365, BLACK, "��������");
		DrawFormatString(410, 405, BLACK, "����");
		Arrow(385, 285 + arrowPoint3 * 40);

		Window[0].DrawExtend(5, 5, 370, 255);
		Window[1].DrawExtend(5, 260, 370, 570);

		Arrow(12 + (arrowPoint % 2) * 160, 20 + (arrowPoint / 2) * 50);
		Arrow(12 + (arrowPoint2 % 2) * 160, 290 + (arrowPoint2 / 2) * 50);


		for (int i = 0; i < 10; i++) {
			DrawFormatString(30 + (i % 2) * 160, 20 + (i / 2) * 50, BLACK, "�A�C�e���Z�b�g%d", i + 1);

			bufS = "";
			bufInt[0] = cstown.mySaveData->GetSetItem(arrowPoint, i, true);
			bufInt[1] = cstown.mySaveData->GetSetItem(arrowPoint, i, false);
			if (bufInt[1] > 0) {
				bufS = (*ItemInfo[bufInt[0]])[bufInt[1] - 1][1];
			}

			DrawFormatString(30 + (i % 2) * 160, 290 + (i / 2) * 50, BLACK, "%d:%s", i + 1, bufS.c_str());

			if (cstown.mySaveData->bringItemSet == i) {
				DrawFormatString(30 + (i % 2) * 160, 36 + (i / 2) * 50, RED, "�i���Z�b�g���j", i + 1);
			}

		}


		break;

	case 4:

		Window[0].DrawExtend(5, 5, 370, 255);
		Window[1].DrawExtend(5, 260, 370, 570);

		Arrow(12 + (arrowPoint % 2) * 160, 20 + (arrowPoint / 2) * 50);

		Arrow(12 + (arrowPoint2 % 2) * 160, 290 + (arrowPoint2 / 2) * 50);

		for (int i = 0; i < 10; i++) {
			DrawFormatString(30 + (i % 2) * 160, 20 + (i / 2) * 50, BLACK, "�A�C�e���Z�b�g%d", i + 1);

			bufS = "";
			bufInt[0] = cstown.mySaveData->GetSetItem(arrowPoint, i, true);
			bufInt[1] = cstown.mySaveData->GetSetItem(arrowPoint, i, false);
			if (bufInt[1] > 0) {
				bufS = (*ItemInfo[bufInt[0]])[bufInt[1] - 1][1];
			}

			DrawFormatString(30 + (i % 2) * 160, 290 + (i / 2) * 50, BLACK, "%d:%s", i + 1, bufS.c_str());

			if (cstown.mySaveData->bringItemSet == i) {
				DrawFormatString(30 + (i % 2) * 160, 36 + (i / 2) * 50, RED, "�i���Z�b�g���j", i + 1);
			}

		}

		if (closeWindow == false) {
			DrawFormatString(30, 540, RED, "�����A�C�e���������Z�b�g����Ă��܂��B");
		}

		break;

	case 3:
		Window[1].DrawExtend(380,5,700,160);
		DrawFormatString(410, 30, BLACK, "���̃A�C�e���Z�b�g�������Ă���");

		DrawFormatString(410, 70, BLACK, "�A�C�e���Z�b�g�̓��e��ύX����");
		DrawFormatString(410, 110, BLACK, "����");
		Arrow(385,30+arrowPoint2*40);

		Window[0].DrawExtend(5, 5, 370, 255);
		Window[1].DrawExtend(5, 260, 370, 570);

		Arrow(12 + (arrowPoint % 2) * 160, 20 + (arrowPoint / 2) * 50);

		for (int i = 0; i < 10; i++) {
			DrawFormatString(30 + (i % 2) * 160, 20 + (i / 2) * 50, BLACK, "�A�C�e���Z�b�g%d", i + 1);

			bufS = "";
			bufInt[0] = cstown.mySaveData->GetSetItem(arrowPoint, i, true);
			bufInt[1] = cstown.mySaveData->GetSetItem(arrowPoint, i, false);
			if (bufInt[1] > 0) {
				bufS = (*ItemInfo[bufInt[0]])[bufInt[1] - 1][1];
			}

			DrawFormatString(30 + (i % 2) * 160, 290 + (i / 2) * 50, BLACK, "%d:%s", i + 1, bufS.c_str());

			if (cstown.mySaveData->bringItemSet == i) {
				DrawFormatString(30 + (i % 2) * 160, 36 + (i / 2) * 50, RED, "�i���Z�b�g���j", i + 1);
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
			DrawFormatString(30 + (i % 2) * 160, 20 + (i / 2) * 50, BLACK, "�A�C�e���Z�b�g%d", i + 1);

			bufS = "";
			bufInt[0] = cstown.mySaveData->GetSetItem(arrowPoint, i, true);
			bufInt[1] = cstown.mySaveData->GetSetItem(arrowPoint, i, false);
			if (bufInt[1] > 0) {
				bufS = (*ItemInfo[bufInt[0]])[bufInt[1] - 1][1];
			}

			DrawFormatString(30 + (i % 2) * 160, 290 + (i / 2) * 50, BLACK, "%d:%s", i+1,bufS.c_str());

			if (cstown.mySaveData->bringItemSet==i){
				DrawFormatString(30 + (i % 2) * 160, 36 + (i / 2) * 50, RED, "�i���Z�b�g���j", i + 1);
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
	textWindow = new CTextWindow("�ǂ̑����ɕύX�������܂����H");
	equipManger = NULL;
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
				textWindow->PushText("���ɑ�����ύX�������܂����H/n�i�w�L�[�ŏI���j");
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
				textWindow->PushText("�܂����ł����z�����������B");
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
	textWindow = new CTextWindow("���𔄂肽���񂾂��H/n�i�w�L�[�ŕ���j");
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
							ynWindow = new CYesNoWindow(&yn, "����𔄂�̂����H", false, 280, 100);
							step = 3;
						}
					}
					else if (arrowPoint >= 3 && arrowPoint < 7) {
						if (cstown.mySaveData->wearEquipmentLocate[arrowPoint - 3][1] == (equipManager->lookLocate + equipManager->lookPage * 20)) {
							ynWindow = new CYesNoWindow(&yn, "����𔄂�̂����H", false, 280, 100);
							step = 3;
						}
					}
				}
				if(arrowPoint>=7 && itemManager->GetAmount(arrowPoint - 7, itemManager->GetPointNum())>0)
				{
					amountGetWindow = new CAmountGetWindow("������񂾂��H", 280, 100, itemManager->GetAmount(arrowPoint-7,itemManager->GetPointNum()));
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
				textWindow->PushText("���ɔ�����̂͂��邩���H/n�i�w�L�[�ŕ���j");
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
				textWindow->PushText("���Ă��ꂽ�炢�ł���������B");
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

	DrawFormatString(470, 548, BLACK, "�������@�@%d", cstown.mySaveData->money);
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

		case 0:	equipmentInfo = new CSV("zero/ZeroData/Soad.txt"); break;
		case 1: equipmentInfo = new CSV("zero/ZeroData/Arrow.txt"); break;
		case 2: equipmentInfo = new CSV("zero/ZeroData/Wand.txt"); break;
		case 3:	equipmentInfo = new CSV("zero/ZeroData/Shield.txt"); break;
		case 4: equipmentInfo = new CSV("zero/ZeroData/Protecter.txt"); break;
		case 5: equipmentInfo = new CSV("zero/ZeroData/Shoes.txt"); break;
		case 6: equipmentInfo = new CSV("zero/ZeroData/Accessory.txt"); break;
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
					textWindow->PushText("�Z�[�u���܂����B");
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
					ynWindow = new CYesNoWindow(&yn, "�Z�[�u���Ă�낵���ł����H", false, 245, 10);
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
		DrawFormatString(15, 10, BLACK, "�X�e�[�^�X");

		for (int i = 0; i < 16; i++) {
			switch (i)
			{
			case 0:	bufS = "HP"; break;
			case 1:	bufS = "MP"; break;
			case 2:	bufS = "�U"; break;
			case 3:	bufS = "�h"; break;
			case 4:	bufS = "���U"; break;
			case 5:	bufS = "���h"; break;
			case 6:	bufS = "��"; break;
			case 7:	bufS = "����"; break;
			case 8:	bufS = "���"; break;
			case 9:	bufS = "�^"; break;
			case 10:bufS = "�Ζh"; break;
			case 11:bufS = "�ؖh"; break;
			case 12:bufS = "���h"; break;
			case 13:bufS = "���h"; break;
			case 14:bufS = "�Ŗh"; break;
			case 15:bufS = "������"; break;

			default:
				break;
			}

			DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d", bufS.c_str(), Status[i]);
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
		DrawFormatString(15, 10, BLACK, "�X�e�[�^�X");

		for (int i = 0; i < 16; i++) {
			switch (i)
			{
			case 0:	bufS = "HP"; break;
			case 1:	bufS = "MP"; break;
			case 2:	bufS = "�U"; break;
			case 3:	bufS = "�h"; break;
			case 4:	bufS = "���U"; break;
			case 5:	bufS = "���h"; break;
			case 6:	bufS = "��"; break;
			case 7:	bufS = "����"; break;
			case 8:	bufS = "���"; break;
			case 9:	bufS = "�^"; break;
			case 10:bufS = "�Ζh"; break;
			case 11:bufS = "�ؖh"; break;
			case 12:bufS = "���h"; break;
			case 13:bufS = "���h"; break;
			case 14:bufS = "�Ŗh"; break;
			case 15:bufS = "������"; break;

			default:
				break;
			}

			DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d", bufS.c_str(), Status[i]);
		}
		break;
	case 2:
		Window[0].Draw(500, 10);
		Arrow.Draw(510, 30 + arrowPoint * 38);
		textWindow->Draw();

		Window[3].DrawExtend(5, 5, 230, 370);
		DrawFormatString(15, 10, BLACK, "�X�e�[�^�X");

		for (int i = 0; i < 16; i++) {
			switch (i)
			{
			case 0:	bufS = "HP"; break;
			case 1:	bufS = "MP"; break;
			case 2:	bufS = "�U"; break;
			case 3:	bufS = "�h"; break;
			case 4:	bufS = "���U"; break;
			case 5:	bufS = "���h"; break;
			case 6:	bufS = "��"; break;
			case 7:	bufS = "����"; break;
			case 8:	bufS = "���"; break;
			case 9:	bufS = "�^"; break;
			case 10:bufS = "�Ζh"; break;
			case 11:bufS = "�ؖh"; break;
			case 12:bufS = "���h"; break;
			case 13:bufS = "���h"; break;
			case 14:bufS = "�Ŗh"; break;
			case 15:bufS = "������"; break;

			default:
				break;
			}

			DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d", bufS.c_str(), Status[i]);
		}
		break;
	case 1:
		Window[0].Draw(500, 10);
		Arrow.Draw(510, 30 + arrowPoint * 38);
		ynWindow->Draw();
		Window[3].DrawExtend(5, 5, 230, 370);
		DrawFormatString(15, 10, BLACK, "�X�e�[�^�X");

		for (int i = 0; i < 16; i++) {
			switch (i)
			{
			case 0:	bufS = "HP"; break;
			case 1:	bufS = "MP"; break;
			case 2:	bufS = "�U"; break;
			case 3:	bufS = "�h"; break;
			case 4:	bufS = "���U"; break;
			case 5:	bufS = "���h"; break;
			case 6:	bufS = "��"; break;
			case 7:	bufS = "����"; break;
			case 8:	bufS = "���"; break;
			case 9:	bufS = "�^"; break;
			case 10:bufS = "�Ζh"; break;
			case 11:bufS = "�ؖh"; break;
			case 12:bufS = "���h"; break;
			case 13:bufS = "���h"; break;
			case 14:bufS = "�Ŗh"; break;
			case 15:bufS = "������"; break;

			default:
				break;
			}

			DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d", bufS.c_str(), Status[i]);
		}


		break;

	case 0:
		Window[0].Draw(500, 10);
		Arrow.Draw(510, 30 + arrowPoint * 38);
		Window[3].DrawExtend(5,5,230,370);
		DrawFormatString(15,10,BLACK,"�X�e�[�^�X");

		for (int i = 0; i < 16; i++) {
			switch (i)
			{
			case 0:	bufS="HP"; break;
			case 1:	bufS = "MP"; break;
			case 2:	bufS = "�U"; break;
			case 3:	bufS = "�h"; break;
			case 4:	bufS = "���U"; break;
			case 5:	bufS = "���h"; break;
			case 6:	bufS = "��"; break;
			case 7:	bufS = "����"; break;
			case 8:	bufS = "���"; break;
			case 9:	bufS = "�^"; break;
			case 10:bufS = "�Ζh"; break;
			case 11:bufS = "�ؖh"; break;
			case 12:bufS = "���h"; break;
			case 13:bufS = "���h"; break;
			case 14:bufS = "�Ŗh"; break;
			case 15:bufS = "������"; break;
				
			default:
				break;
			}

			DrawFormatString(15, 30 + 20 * i, BLACK, "%s;%d",bufS.c_str(), Status[i]);
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
