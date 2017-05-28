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
		if (checkAround[0] == 137 || checkAround[1] == 137) {
			FlipScene(new CSCook(*this));
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



CSTown::CSCook::CSCook(CSTown & cstown) :cstown(cstown)
{
	textWindow = new CTextWindow("‰½‚ðì‚Á‚Ä—~‚µ‚¢ƒJƒ{H");
	classStart = false;
	step = 0;
}

void CSTown::CSCook::Loop()
{

	if (classStart == true) {

		switch (step)
		{

		case 1:
			produce->WindowLoop();

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
	delete cstown.mySaveData;
	cstown.mySaveData = NULL;
}