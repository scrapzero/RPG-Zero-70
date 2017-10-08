#include "MyScene.h"
#include <algorithm>

bool KeyOK();
bool KeyCancel();
bool KeyRight();
bool KeyLeft();
bool KeyUp();
bool KeyDown();



CSQuestBase::CSQuestBase(int mapNum,Squest* bufVQ, vector<SItem> *vItemSet)
{
	this->mapNum = mapNum;
	vq = new Squest(*bufVQ);
	this->vItemSet = vItemSet;

	mySaveData = new CMySaveData(true);
	mode[0] = 0;
	mode[1] = 4;
	mapLocateX = 10;
	mapLocateY = 10;
	LoadDivGraph("zero/jiki.png", 12, 3, 4, 32, 32, jikiGraph);
	for (int i = 0; i < 3; i++) {
		takara[i] = true;
	}
	retire = false;

	textWindow = new CTextWindow("クエスト開始");

	character[0] = new CJiki(mySaveData);
	character[1] = new CHaniwa(mySaveData, mySaveData->bringHaniwaKind[0]);
	character[2] = new CHaniwa(mySaveData, mySaveData->bringHaniwaKind[1]);

	startAppearEn =38;
	bossN = 1;


	FlipScene(new CSMap(*this), Flip::ROTATION_RIGHT);

	

}

CSQuestBase::~CSQuestBase()
{
	for (int i = 0; i < vItemSet->size(); i++) {
		switch ((*vItemSet)[i].kind)
		{
		case 0:
			if (mySaveData->sorce[(*vItemSet)[i].num - 1] <9999) {
				mySaveData->sorce[(*vItemSet)[i].num - 1]++;
			}
			break;
		case 1:
			if (mySaveData->tool[(*vItemSet)[i].num - 1] <9999) {
				mySaveData->tool[(*vItemSet)[i].num - 1]++;
			}
			break;
		case 2:
			if (mySaveData->food[(*vItemSet)[i].num - 1] <9999) {
				mySaveData->food[(*vItemSet)[i].num - 1]++;
			}
			break;

		default:
			break;
		}
	}

	

	vItemSet->clear();
	delete vItemSet;
	vItemSet = NULL;
	delete mySaveData;
	mySaveData = NULL;
	delete vq;
	vq = NULL;
	delete textWindow;
	textWindow = NULL;
	

}


void CSQuestBase::Loop()
{
	switch (mode[0])
	{
	case 0:
		switch (mode[1])
		{
		case 0:
			FlipScene(new CSMap(*this), Flip::CROSS_FADE,8);
			break;
		case 1:
			FlipScene(new CSMap(*this), Flip::CROSS_FADE,8);
			break;
		case 2:
			FlipScene(new CSMap(*this), Flip::CROSS_FADE,8);
			break;
		case 3:
			FlipScene(new CSMap(*this), Flip::CROSS_FADE,8);
			break;
		case 4:
			FlipScene(new CSMap(*this), Flip::CROSS_FADE, 8);
			break;
		case 5:
			FlipScene(new CSMap(*this), Flip::DOOR_COME_VERTICAL, 8);
			break;

		default:
			break;
		}

		break;
	case 1:
		switch (mode[1])
		{
		case 0:
			FlipScene(new CSBattle(*this,false,0), Flip::DOOR_COME_VERTICAL, 4);
			break;
		case 1:
			FlipScene(new CSBattle(*this, true,bossN), Flip::DOOR_COME_VERTICAL, 4);
			break;
		case 2:

			break;
		default:
			break;
		}
		break;

	case 2:
		switch (mode[1])
		{
		case 0:
			if (retire == false) {
				mySaveData->WriteSaveData();
			}

			Game.FlipScene(new CSTown(40, 3,1), Flip::FADE_OUT_IN);
			
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
}

void CSQuestBase::Draw()
{
}

void CSQuestBase::End()
{
}



CSQuestBase::CSMap::CSMap(CSQuestBase & csQuestBase) :csQuestBase(csQuestBase)
{
	stringstream bufSS;
	string bufS;
	bool bufF = false;
	int bufI = 13;


	LoadDivGraph("zero/MyMapChip1.png", 156, 26, 6, 32, 32, mapChip);

	bufSS << "zero/MCE/Map";
	bufSS << csQuestBase.mapNum;
	bufSS << "X";
	bufSS << csQuestBase.mapLocateX;
	bufSS << "Y";
	bufSS << csQuestBase.mapLocateY;
	bufSS << ".mce";
	bufS = bufSS.str();

	QuestMap = bufS.c_str();
	mapWidth = QuestMap.GetWidth();
	mapHeight = QuestMap.GetHeight();
	bufF = false;
	graphDirect = 0;

	switch (csQuestBase.mode[1])
	{
	case 0:bufI = 6; graphDirect = 2; break;
	case 1:bufI = 5; graphDirect = 1; break;
	case 2:bufI = 8; graphDirect = 3; break;
	case 3:bufI = 7; graphDirect = 0; break;
	case 4:bufI = 13;graphDirect = 0; break;

	default:
		break;
	}

	if (csQuestBase.mode[1] <= 4) {
		for (int i = 0; i < mapWidth; i++) {
			for (int j = 0; j < mapHeight; j++) {
				if (QuestMap.Get(QuestMap.layer.A, i, j) == bufI) {
					jikiMapX = i;
					jikiMapY = j;
					bufF = true;
					break;
				}
			}
			if (bufF) {
				bufF = false;
				break;
			}
		}

		if (jikiMapX < 11) {
			jikiX = jikiMapX * 32;
			scrollX = 0;
		}
		else if (jikiMapX - (mapWidth - 1 - 21) >= 10) {
			jikiX = (jikiMapX - (mapWidth - 1 - 21)) * 32;
			scrollX = (mapWidth - 1 - 21) * 32;
		}
		else {
			jikiX = 11 * 32;
			scrollX = (jikiMapX - 11) * 32;
		}

		if (jikiMapY < 10) {
			jikiY = jikiMapY * 32;
			scrollY = 0;
		}
		else if (jikiMapY - (mapHeight - 1 - 17) >= 6) {
			jikiY = (jikiMapY - (mapHeight - 1 - 17)) * 32;
			scrollY = (mapHeight - 1 - 17) * 32;
		}
		else
		{
			jikiY = 10 * 32;
			scrollY = (jikiMapY - 10) * 32;
		}
	}
	else
	{
		jikiMapX = csQuestBase.bufjikiMapX;
		jikiMapY = csQuestBase.bufjikiMapY;
		jikiX = csQuestBase.bufjikiX;
		jikiY = csQuestBase.bufjikiY;
		scrollX = csQuestBase.bufscrollX;
		scrollY = csQuestBase.bufscrollY;
	}


	moveDirect = 4;
	graphStep = 1;
	moveF = false;
	animeF = false;
	canMoveDown = false;
	canMoveLeft = false;
	canMoveRight = false;
	canMoveUp = false;
	appearEN = csQuestBase.startAppearEn;

}

CSQuestBase::CSMap::~CSMap()
{
	csQuestBase.bufjikiMapX = jikiMapX;
	csQuestBase.bufjikiMapY = jikiMapY;
	csQuestBase.bufjikiX = jikiX;
	csQuestBase.bufjikiY = jikiY;
	csQuestBase.bufscrollX = scrollX;
	csQuestBase.bufscrollY = scrollY;

}



void CSQuestBase::CSMap::takaraGet( int reado)
{
	string bufS="";
	stringstream bufSS;
	switch (csQuestBase.vq->treasure[0 + reado][0])
	{
	case 0:
		csQuestBase.mySaveData->sorce[csQuestBase.vq->treasure[0+reado][1] -1] += csQuestBase.vq->treasure[0+reado][2];
		if (csQuestBase.mySaveData->sorce[csQuestBase.vq->treasure[0+reado][1] - 1] >= 9999) {
			csQuestBase.mySaveData->sorce[csQuestBase.vq->treasure[0+reado][1]-1] = 9999;
		}
		csQuestBase.itemInfo = new CSV("zero/ZeroData/Sorce.csv");
		bufSS << csQuestBase.vq->treasure[0 + reado][2];
		bufS = (*csQuestBase.itemInfo)[csQuestBase.vq->treasure[0+reado][1] - 1][1];
		bufS += "を";
		bufS += bufSS.str();
		bufS += "個手に入れました";

		csQuestBase.textWindow->PushText(bufS.c_str());
		delete csQuestBase.itemInfo;
		csQuestBase.itemInfo = NULL;
		break;
	case 1:
		csQuestBase.mySaveData->tool[csQuestBase.vq->treasure[0+reado][1] - 1] += csQuestBase.vq->treasure[0+reado][2];
		if (csQuestBase.mySaveData->tool[csQuestBase.vq->treasure[0+reado][1] - 1] >= 9999) {
			csQuestBase.mySaveData->tool[csQuestBase.vq->treasure[0+reado][1] - 1] = 9999;
		}
		csQuestBase.itemInfo = new CSV("zero/ZeroData/Tool.csv");
		bufSS << csQuestBase.vq->treasure[0 + reado][2];
		bufS = (*csQuestBase.itemInfo)[csQuestBase.vq->treasure[0 + reado][1] - 1][1];
		bufS += "を";
		bufS += bufSS.str();
		bufS += "個手に入れました";
		csQuestBase.textWindow->PushText(bufS.c_str()); delete csQuestBase.itemInfo;
		csQuestBase.itemInfo = NULL;
		break;
	case 2:
		csQuestBase.mySaveData->food[csQuestBase.vq->treasure[0+reado][1]-1] += csQuestBase.vq->treasure[0+reado][2];
		if (csQuestBase.mySaveData->food[csQuestBase.vq->treasure[0+reado][1]-1] >= 9999) {
			csQuestBase.mySaveData->food[csQuestBase.vq->treasure[0+reado][1]-1] = 9999;
		}
		csQuestBase.itemInfo = new CSV("zero/ZeroData/Food.csv");
		bufSS << csQuestBase.vq->treasure[0 + reado][2];
		bufS = (*csQuestBase.itemInfo)[csQuestBase.vq->treasure[0 + reado][1] - 1][1];
		bufS += "を";
		bufS += bufSS.str();
		bufS += "個手に入れました";
		csQuestBase.textWindow->PushText(bufS.c_str()); delete csQuestBase.itemInfo;
		csQuestBase.itemInfo = NULL;
		break;

	default:
		break;
	}


}

void CSQuestBase::CSMap::Loop()
{
	bool bufF=false;
	string bufS = "";
	int bufI=0;

	int HitKeyNum = 0;
	canMoveDown = true;
	canMoveLeft = true;
	canMoveRight = true;
	canMoveUp = true;
	int checkAround[2] = {};
	int jikiStandChip[3] = { QuestMap.Get(QuestMap.layer.C, jikiMapX, jikiMapY) - 1, QuestMap.Get(QuestMap.layer.B, jikiMapX, jikiMapY) - 1 , QuestMap.Get(QuestMap.layer.A, jikiMapX, jikiMapY) - 1 };

	if (csQuestBase.textWindow->GetTextEmpty() && csQuestBase.textWindow->GetWaitTextEmpty()) {
		if (Input.GetKeyDown(Input.key.RIGHT) && bufF == false) {
			if (jikiStandChip[2] == 0 || jikiStandChip[2] == 4) {
				if (jikiX % 32 == 0) {
					csQuestBase.mode[1] = 0;
					csQuestBase.mapLocateX++;
					csQuestBase.RemoveScene(Flip::CROSS_FADE, 8);
					bufF = true;
				}
			}
		}
		if (Input.GetKeyDown(Input.key.LEFT) && bufF == false) {
			if (jikiStandChip[2] == 1 || jikiStandChip[2] == 5) {
				if (jikiX % 32 == 0) {
					csQuestBase.mode[1] = 1;
					csQuestBase.mapLocateX--;
					csQuestBase.RemoveScene(Flip::CROSS_FADE, 8);
					bufF = true;
				}
			}
		}
		if (Input.GetKeyDown(Input.key.UP) && bufF == false) {
			if (jikiStandChip[2] == 2 || jikiStandChip[2] == 6) {
				if (jikiY % 32 == 0) {
					csQuestBase.mode[1] = 2;
					csQuestBase.mapLocateY--;
					csQuestBase.RemoveScene(Flip::CROSS_FADE, 8);
					bufF = true;
				}
			}
		}
		if (Input.GetKeyDown(Input.key.DOWN) && bufF == false) {
			if (jikiStandChip[2] == 3 || jikiStandChip[2] == 7) {
				if (jikiY % 32 == 0) {
					csQuestBase.mode[1] = 3;
					csQuestBase.mapLocateY++;
					csQuestBase.RemoveScene(Flip::CROSS_FADE, 8);
					bufF = true;
				}
			}
		}

		if (bufF == false) {
			if (jikiMapX > 0) {
				checkAround[0] = QuestMap.Get(QuestMap.layer.C, jikiMapX - 1, jikiMapY) - 1;
				checkAround[1] = QuestMap.Get(QuestMap.layer.B, jikiMapX - 1, jikiMapY) - 1;

				if (jikiStandChip[0] < 26 || jikiStandChip[0] % 26 >= 20) {
					if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
						canMoveLeft = false;
					}
					if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
						canMoveLeft = false;
					}
				}
				if (jikiStandChip[1] < 26 || jikiStandChip[1] % 26 >= 20) {
					if (jikiStandChip[1] >= 0 && jikiStandChip[1] % 26 != 25) {
						if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
							canMoveLeft = false;
						}
						if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
							canMoveLeft = false;
						}
					}
				}

				if (jikiStandChip[0] >= 27 && jikiStandChip[0] < 40) {
					if (checkAround[0] < 27 || checkAround[0] >= 40) {
						if (checkAround[0] >= 0) {
							canMoveLeft = false;
						}
					}
					if (checkAround[1] < 27 || checkAround[1] >= 40) {
						if (checkAround[1] >= 0) {
							canMoveLeft = false;
						}
					}
				}

				if (jikiStandChip[1] % 26 == 25) {
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
					if (jikiStandChip[0] >= 27 && jikiStandChip[0] < 40) {
						if (checkAround[0] >= 27 && checkAround[0] < 40) {

							canMoveLeft = true;
						}
					}
				}

			}

			if (jikiMapY > 0) {
				checkAround[0] = QuestMap.Get(QuestMap.layer.C, jikiMapX, jikiMapY - 1) - 1;
				checkAround[1] = QuestMap.Get(QuestMap.layer.B, jikiMapX, jikiMapY - 1) - 1;

				if (jikiStandChip[0] < 26 || jikiStandChip[0] % 26 >= 20) {
					if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
						canMoveUp = false;
					}
					if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
						canMoveUp = false;
					}
				}
				if (jikiStandChip[1] < 26 || jikiStandChip[1] % 26 >= 20) {
					if (jikiStandChip[1] >= 0) {
						if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
							canMoveUp = false;
						}
						if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
							canMoveUp = false;
						}
					}
				}

				if (jikiStandChip[0] >= 27 && jikiStandChip[0] < 40) {
					if (checkAround[0] < 27 || checkAround[0] >= 40) {
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
					if (checkAround[0] == 26 || checkAround[0] >= 40) {
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

			if (jikiMapX + 1 < mapWidth) {
				checkAround[0] = QuestMap.Get(QuestMap.layer.C, jikiMapX + 1, jikiMapY) - 1;
				checkAround[1] = QuestMap.Get(QuestMap.layer.B, jikiMapX + 1, jikiMapY) - 1;

				if (jikiStandChip[0] < 26 || jikiStandChip[0] % 26 >= 20) {
					if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
						canMoveRight = false;
					}
					if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
						canMoveRight = false;
					}
				}
				if (jikiStandChip[1] < 26 || jikiStandChip[1] % 26 >= 20) {
					if (jikiStandChip[1] >= 0 && jikiStandChip[1] % 26 != 25) {
						if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
							canMoveRight = false;
						}
						if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
							canMoveRight = false;
						}
					}
				}

				if (jikiStandChip[0] >= 27 && jikiStandChip[0] < 40) {
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
						if (checkAround[0] >= 0) {
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
					if (jikiStandChip[0] >= 27 && jikiStandChip[0] < 40) {
						if (checkAround[0] >= 27 && checkAround[0] < 40) {

							canMoveRight = true;
						}
					}
				}

			}

			if (jikiMapY + 1 < mapHeight) {
				checkAround[0] = QuestMap.Get(QuestMap.layer.C, jikiMapX, jikiMapY + 1) - 1;
				checkAround[1] = QuestMap.Get(QuestMap.layer.B, jikiMapX, jikiMapY + 1) - 1;

				if (jikiStandChip[0] < 26 || jikiStandChip[0] % 26 >= 20) {
					if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
						canMoveDown = false;
					}
					if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
						canMoveDown = false;
					}
				}
				if (jikiStandChip[1] < 26 || jikiStandChip[1] % 26 >= 20) {
					if (jikiStandChip[1] >= 0) {
						if (checkAround[0] >= 26 && checkAround[0] % 26 < 20) {
							canMoveDown = false;
						}
						if (checkAround[1] >= 26 && checkAround[1] % 26 < 20) {
							canMoveDown = false;
						}
					}
				}

				if (jikiStandChip[0] >= 27 && jikiStandChip[0] < 40) {
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

			if (Input.GetKeyDown(Input.key.DOWN) && moveF == false && canMoveDown == true) {
				if (HitKeyNum <= 1 || moveDirect != 0) {
					moveF = true;
					moveDirect = 0;
					graphDirect = 0;
				}
			}
			if (Input.GetKeyDown(Input.key.LEFT) && moveF == false && canMoveLeft == true) {
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
					if (jikiX == 352 && scrollX > 0) {
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
					if (jikiY == 320 && scrollY > 0) {
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
				if (moveF == true) {
					appearEN++;
					if (appearEN/2 >= GetRand(80) + 12) {
						csQuestBase.mode[0] = 1;
						csQuestBase.mode[1] = 0;
						csQuestBase.RemoveScene(Flip::DOOR_COME_VERTICAL, 4);
					}
				}
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


			if (graphDirect == 3 && KeyOK() && jikiX%32==0 && jikiY%32==0) {

				checkAround[0] = QuestMap.Get(QuestMap.layer.C, jikiMapX, jikiMapY - 1) - 1;
				checkAround[1] = QuestMap.Get(QuestMap.layer.B, jikiMapX, jikiMapY - 1) - 1;
				
				switch (checkAround[1]) {
				case 62:
					if (csQuestBase.takara[0] == true) {
						csQuestBase.takara[0] = false;
						if (GetRand(19) < 12) {
							takaraGet(0);
						}
						else if (GetRand(19) < 17 ) {
							takaraGet(1);
						}
						else {
							takaraGet(2);
						}

					}
					break;
				case 63:
					if (csQuestBase.takara[1] == true) {
						csQuestBase.takara[1] = false;
						if (GetRand(19) < 12) {

							takaraGet(1);
						}
						else if (GetRand(19) < 17) {

							takaraGet(2);
						}
						else {
							takaraGet(3);
						}

					}
					break;
				case 64:
					if (csQuestBase.takara[2] == true) {
						csQuestBase.takara[2] = false;
						if (GetRand(19) < 12) {
							takaraGet(2);
						}
						else if (GetRand(19) < 17) {
							takaraGet(3);
						}
						else {
							takaraGet(4);
						}

					}
					break;
				}
	

			}

			if (graphDirect == 2 && KeyOK() && jikiX % 32 == 0 && jikiY % 32 == 0) {
				checkAround[0] = QuestMap.Get(QuestMap.layer.C, jikiMapX + 1, jikiMapY) - 1;
				checkAround[1] = QuestMap.Get(QuestMap.layer.B, jikiMapX + 1, jikiMapY) - 1;

				if (checkAround[0] == 142 || checkAround[1] == 142) {
				}

			}

			if (graphDirect == 1 && KeyOK() && jikiX % 32 == 0 && jikiY % 32 == 0) {
				checkAround[0] = QuestMap.Get(QuestMap.layer.C, jikiMapX - 1, jikiMapY) - 1;
				checkAround[1] = QuestMap.Get(QuestMap.layer.B, jikiMapX - 1, jikiMapY) - 1;


			}

			if (graphDirect == 0 && KeyOK() && jikiX % 32 == 0 && jikiY % 32 == 0) {
				checkAround[0] = QuestMap.Get(QuestMap.layer.C, jikiMapX , jikiMapY + 1 ) - 1;
				checkAround[1] = QuestMap.Get(QuestMap.layer.B, jikiMapX , jikiMapY + 1 ) - 1;


			}

		}

	}
	else {
		csQuestBase.textWindow->Loop();
	}

	

	jikiMapX = (jikiX + scrollX) / 32;
	jikiMapY = (jikiY + scrollY) / 32;
}

void CSQuestBase::CSMap::Draw()
{
	int drawMapLeft = jikiMapX - (jikiX / 32) - 1;
	int drawMapUp = jikiMapY - (jikiY / 32) - 1;
	int drawMapRight = drawMapLeft + 1 + 22 + 1;
	int drawMapDown = drawMapUp + 1 + 18 + 1;
	if (drawMapLeft < 0) {
		drawMapLeft = 0;
	}
	if (drawMapUp < 0) {
		drawMapUp = 0;
	}
	if (drawMapRight > mapWidth) {
		drawMapRight = mapWidth;
	}
	if (drawMapDown > mapHeight) {
		drawMapDown = mapHeight;
	}

	for (int i = drawMapLeft; i < drawMapRight; i++) {
		for (int j = drawMapUp; j < drawMapDown; j++) {
			if (QuestMap.Get(QuestMap.layer.C, i, j) > 0) {
				mapChip[QuestMap.Get(QuestMap.layer.C, i, j) - 1].Draw(i * 32 - scrollX, j * 32 - scrollY);
			}

			if (QuestMap.Get(QuestMap.layer.B, i, j) > 0) {
				if (csQuestBase.takara[0] == false && QuestMap.Get(QuestMap.layer.B, i, j) == 63) {
					mapChip[112].Draw(i * 32 - scrollX, j * 32 - scrollY);
				}
				else if (csQuestBase.takara[1] == false && QuestMap.Get(QuestMap.layer.B, i, j) == 64) {
					mapChip[113].Draw(i * 32 - scrollX, j * 32 - scrollY);
				}
				else if (csQuestBase.takara[2] == false && QuestMap.Get(QuestMap.layer.B, i, j) == 65) {
					mapChip[114].Draw(i * 32 - scrollX, j * 32 - scrollY);
				}
				else {
					mapChip[QuestMap.Get(QuestMap.layer.B, i, j) - 1].Draw(i * 32 - scrollX, j * 32 - scrollY);
				}
			}
		}
	}


	if (csQuestBase.textWindow->GetTextEmpty() == false || csQuestBase.textWindow->GetWaitTextEmpty() == false) {
		csQuestBase.textWindow->Draw();
	}

	csQuestBase.jikiGraph[graphDirect * 3 + graphStep].Draw(jikiX, jikiY - 4);



}

CSQuestBase::CSBattle::CSBattle(CSQuestBase & csQuestBase ,bool boss ,int bossNum):csQuestBase(csQuestBase)
{
	
	this->boss = boss;
	this->bossNum = bossNum;
	int bufI = 0;
	stringstream bufSS,bufSS2;
	string bufS = "A";

	for (int i = 0; i < 3; i++) {
		csQuestBase.character[i]->Reset();
	}

	bWindow[0] = "zero/ItemSelectWindow.png";
	bWindow[1] = "zero/MenueWindow.png";
	bWindow[2] = "zero/ItemSelectWindow2.png";
	bWindow[3] = "zero/ItemSelectWindow3.png";
	bArrowG = "zero/SmallArrow.png";
	bArrowG2 = "zero/SmallArrowDown.png";
	cardG[0] = "zero/cardA.png";
	cardG[1] = "zero/cardB.png";
	cardG[2] = "zero/cardC.png";
	cardG[3] = "zero/cardD.png";
	cardG[4] = "zero/cardE.png";
	cardG[5] = "zero/cardF.png";

	bufSS << "zero/back";
	bufSS << GetRand(1) + 1;
	bufSS << ".png";

	backGraph = bufSS.str().c_str();
	preStep = 0;
	step = 0;
	nigeru = 0;

	for (int i = 0; i < 4; i++) {
		bArrow[i] = 0;
	}

	if (boss == true ) {
		enAmount = csQuestBase.vq->boss[bossNum - 1][0][1] + csQuestBase.vq->boss[bossNum - 1][1][1] + csQuestBase.vq->boss[bossNum - 1][2][1];
		if (csQuestBase.vq->bigBoss[bossNum - 1] == true) {
			enemy[enAmount / 2] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->boss[bossNum - 1][0][0],true);
			bufI = 0;

			for (int j = 1; j < 3; j++) {
				for (int k = 0; k < csQuestBase.vq->boss[bossNum - 1][j][1]; k++) {
					if (bufI != enAmount) {
						enemy[bufI] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->boss[bossNum - 1][0][j],false);
					
					}
					else {
						k--;
					}
					bufI++;

				}
			}
		}
		else {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < csQuestBase.vq->boss[bossNum - 1][j][1]; k++) {
					enemy[bufI] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->boss[bossNum - 1][0][j],false);
					bufI++;

				}
			}
		}

	}
	else
	{
		bufI = GetRand(19);
		if (bufI < 3) {
			enAmount = 2;
		}
		else if (bufI < 9) {
			enAmount = 3;
		}
		else if (bufI < 17) {
			enAmount = 4;
		}
		else {
			enAmount = 5;
		}


		for (int i = 0; i < enAmount; i++) {
			bufI = GetRand(19);
			if (bufI < 4) {
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[0],false);
			}
			else if (bufI < 8) {
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[1], false);
			}
			else if (bufI < 11)
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[2], false);
			}
			else if (bufI < 13)
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[3], false);
			}
			else if (bufI < 15)
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[4], false);
			}
			else if (bufI < 17)
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[5], false);
			}
			else if (bufI < 19)
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[6], false);
			}
			else
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[7], false);
			}
			enemy[i]->name += "[";
			enemy[i]->name += bufS.c_str();
			enemy[i]->name += "]";

			bufS[0]+=1;
		}

	}

	for (int i = 0; i < 3; i++) {
		nigeru += csQuestBase.character[i]->Spd*120;
		csQuestBase.character[i]->normalAtack.UseNum = i;
		csQuestBase.character[i]->normalDefence.UseNum = i;
		for (int j = 0; j < 10; j++) {
			csQuestBase.character[i]->skill[j].UseNum = i;
		}
	}
	bufI = 0;
	for (int i = 0; i < enAmount; i++) {
		bufI += enemy[i]->Spd;
		for (int j = 0; j < 10; j++) {
			enemy[i]->skill[j].UseNum = i;
		}

	}
	bufI *= 3;
	bufI /= enAmount;
	nigeru /= bufI;
	nigeta = false;
	battleStart = false;
	skTimes = 0;
	actNext = false;
	zentaiStep = -1;//一回目は技でないため
	preActNext = false;
	hazureta = false;
	winTextStep = 0;
	preStep2 = 0;
	drawSkillWindow = true;

	for (int i = 0; i < 4; i++) {
		csQuestBase.character[0]->SkillSpeadRand();
		skillCard[i] = csQuestBase.character[0]->skill[GetRand(5)];
		skillCard[i].Point = GetRand(9) + 1;
		skillCard[i].cardNum = i;
		csQuestBase.character[0]->jikiSkillCard[i] = &skillCard[i];
	}

	csQuestBase.textWindow->PushText("戦闘開始");

}

CSQuestBase::CSBattle::~CSBattle()
{
	for (int i = 0; i < enAmount; i++) {
		delete enemy[i];
		enemy[i] = NULL;
	}

	for (int i = 0; i < 3; i++) {
		while (!vSkill[i].empty()) {
			vSkill[i].pop_back();
		}
	}

	targetSelectSkill = NULL;

}

void CSQuestBase::CSBattle::charAct(bool jiki, Skill *bufSk ,char *death)
{

	int bufI = 0;
	int bufRand = 0;
	int bufUseMP = 0;
	bool hajimeBuf = bufSk->hajime;
	bool bufF = false;
	bool oneMore=true;
	bool target9 = false;
	char bufEnd = 0;
	char bufWin = 0;
	char bufTarget = 0;
	string bufS = "";
	*death = 0;



	for (int i = 0; i < 3; i++) {
		if (csQuestBase.character[i]->live == false) {
			bufEnd += 1;
		}
	}
	if (bufEnd >= 3) {
		*death = 1;
	}

	

	
	//

	while (oneMore)
	{
		if (bufSk->hajime) {
			if (zentaiStep < 10000) {
				csQuestBase.textWindow->TextClear();
			}
			zentaiStep = -1;
		}

		oneMore = false;
		bufEnd = 0;
		bufWin = 0;
		bufF = false;
		target9 = false;
		bufUseMP =bufSk->MP;

		for (int i = 0; i < enAmount; i++) {
			if (enemy[i]->live == false) {
				bufWin++;
			}
		}


		if (bufWin >= enAmount) {
			break;
		}

		if (bufSk->useChar->live) {
			if(bufSk->useChar->hirumi && bufSk->hajime){
				bufS.clear();
				bufS = bufSk->useChar->name.c_str();
				bufS += "はひるんで動けない！";
				csQuestBase.textWindow->PushText(bufS.c_str());
				bufSk->useChar->hirumi = false;
				stepAct[1] = 0;
				vSkill[stepAct[0]].erase(vSkill[stepAct[0]].begin());
				break;
			}
			else if (bufSk->useChar->mahi && bufSk->hajime && GetRand(9)<3 ) {
				bufS.clear();
				bufS = bufSk->useChar->name.c_str();
				bufS += "はしびれて動けない！";
				csQuestBase.textWindow->PushText(bufS.c_str());
				stepAct[1] = 0;
				vSkill[stepAct[0]].erase(vSkill[stepAct[0]].begin());
				break;
			}
			else if (bufSk->useChar->Status[1] < bufUseMP && jiki && bufSk->hajime) {
				bufS.clear();
				bufS = bufSk->useChar->name.c_str();
				bufS += "は";
				bufS += bufSk->neme.c_str();
				bufS += "を発動しようとしたがMPが足りなかった。";
				csQuestBase.textWindow->PushText(bufS.c_str());
				stepAct[1] = 0;
				vSkill[stepAct[0]].erase(vSkill[stepAct[0]].begin());
				break;
			}
			else if (jiki && *death == 0) {


				/*oneMore = false;
				bufEnd = 0;
				bufF = false;
				target9 = false;*/

				if (bufSk->target[stepAct[1]] == 9) {
					bufTarget = bufSk->target[0];
					target9 = true;
				}
				else {
					bufTarget = bufSk->target[stepAct[1]];
				}

				if (bufSk->hajime) {
					bufSk->useChar->Status[1] -= bufUseMP;
					if (bufSk->useChar->Status[1] < 0) {
						bufSk->useChar->Status[1] = 0;
					}
					bufSk->useChar->drawMP = bufSk->useChar->Status[1];
				}

				switch (bufTarget)
				{
				case 0:
					if (bufSk->hajime) {
						skTimes--;
					}

					if (enemy[bufSk->targetNum]->live==false) {
						bufI = GetRand(enAmount - 1);

						for (int j = 0; j < 400; j++) {
							if (enemy[bufI]->live == true) {
								bufSk->targetNum = bufI;
								break;
							}
							bufI = GetRand(enAmount - 1);
							if (j == 399) {
								for (int i = 0; i < enAmount; i++) {
									if (enemy[i]->live) {
										bufSk->targetNum = i;
										break;
									}
								}
							}

						}

					}

					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}

					enemy[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 1:
					bufSk->targetNum = zentaiStep;
					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}
					enemy[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 2:

					if (target9 == false) {
						bufI = GetRand(enAmount - 1);
						if (bufSk->hajime) {
							skTimes--;
						}

						for (int j = 0; j < 400; j++) {
							if (enemy[bufI]->live == true) {
								bufSk->targetNum = bufI;
								break;
							}
							bufI = GetRand(enAmount - 1);
							if (j == 399) {
								for (int i = 0; i < enAmount; i++) {
									if (enemy[i]->live) {
										bufSk->targetNum = i;
										break;
									}
								}
							}

						}

					}

					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}

					enemy[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;

				case 3:
					if (bufSk->hajime) {
						skTimes--;
					}

					if (csQuestBase.character[bufSk->targetNum]->live == false) {
						bufI = GetRand(2);
						bufRand = GetRand(1) * 2 - 1;

						for (int i = 0; i < 3; i++) {
							if (csQuestBase.character[bufI]->live) {
								bufSk->targetNum = bufI;
								break;
							}
							bufI += bufRand;
							if (bufI >= 3) {
								bufI = 0;
							}
							if (bufI <= -1) {
								bufI = 2;
							}
						}

					}

					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}

					csQuestBase.character[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;

				case 4:
					bufSk->targetNum = zentaiStep;
					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}
					csQuestBase.character[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);

					break;
				case 5:

					if (target9 == false) {
						bufI = GetRand(2);
						bufRand = GetRand(1) * 2 - 1;
						if (bufSk->hajime) {
							skTimes--;
						}

						for (int i = 0; i < 3; i++) {
							if (csQuestBase.character[bufI]->live) {
								bufSk->targetNum = bufI;
								break;
							}
							bufI += bufRand;
							if (bufI >= 3) {
								bufI = 0;
							}
							if (bufI <= -1) {
								bufI = 2;
							}
						}

					}
					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}

					csQuestBase.character[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 6:
					if (bufSk->hajime) {
						skTimes--;
					}
					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}
					bufSk->targetNum = bufSk->UseNum;
					csQuestBase.character[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 7:

					if (bufSk->hajime) {
						skTimes--;
					}

					/*if (csQuestBase.character[bufSk->targetNum]->live == true) {
						bufI = GetRand(2);
						bufRand = GetRand(1) * 2 - 1;

						for (int i = 0; i < 3; i++) {
							if (csQuestBase.character[bufI]->live) {
								bufSk->targetNum = bufI;
								break;
							}
							bufI += bufRand;
							if (bufI >= 3) {
								bufI = 0;
							}
							if (bufI <= -1) {
								bufI = 2;
							}
						}

					}*/
					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}

					csQuestBase.character[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 8:
					bufSk->targetNum = zentaiStep;
					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}
					csQuestBase.character[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 10:
					if (bufSk->hajime) {
						skTimes--;
					}
					bufSk->targetNum = 0;
					csQuestBase.character[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				default:
					break;
				}


				//


				if (stepAct[1] + 1 < bufSk->classifyNum && hajimeBuf == false) {
					stepAct[1]++;
					if (bufSk->target[stepAct[1]] == 9) {
						continue;
					}
					else
					{
						stepAct[1]--;
					}
				}


				if (bufSk->target[stepAct[1]] == 9) {
					zentaiStep++;
					hazureta = false;

					if (zentaiStep >= enAmount && bufSk->target[0] == 1) {
						bufF = true;
					}
					if (zentaiStep >= 3 && bufSk->target[0] == 4) {
						bufF = true;
					}
					if (zentaiStep >= 3 && bufSk->target[0] == 8) {
						bufF = true;
					}
					if (bufSk->target[0] != 1 && bufSk->target[0] != 4 && bufSk->target[0] != 8) {
						bufF = true;
					}

					if (bufF) {
						zentaiStep = 0;
						skTimes++;
						if (skTimes >= bufSk->times) {
							skTimes = 0;
							stepAct[1]++;
							if (stepAct[1] >= bufSk->classifyNum) {
								stepAct[1] = 0;

								if (vSkill[stepAct[0]][0].cardNum >= 0) {
									csQuestBase.character[0]->SkillSpeadRand();
									skillCard[vSkill[stepAct[0]][0].cardNum] = csQuestBase.character[0]->skill[GetRand(5)];
									skillCard[vSkill[stepAct[0]][0].cardNum].Point = GetRand(9) + 1;
									skillCard[vSkill[stepAct[0]][0].cardNum].cardNum = vSkill[stepAct[0]][0].cardNum;
								}
								vSkill[stepAct[0]].erase(vSkill[stepAct[0]].begin());
								//preActNext = true;
								actNext = false;
								if (vSkill[stepAct[0]].empty()) {
									stepAct[0]++;
									if (stepAct[0] > 2) {
										step = 0;
										bArrow[0] = 0;
										actNext = true;
										skTimes = 0;
										stepAct[0] = 0;
										stepAct[1] = 0;
										for (int i = 0; i < 3; i++) {
											csQuestBase.character[i]->damageCut[0] = 0;
											csQuestBase.character[i]->damageCut[1] = 0;
										}

										for (int i = 0; i < enAmount; i++) {
											enemy[i]->damageCut[0] = 0;
											enemy[i]->damageCut[1] = 0;
										}

										break;
									}
									else {
										break;
									}
								}
								else {
									break;
								}
							}
						}
						else
						{
							stepAct[1] = 0;
						}
					}
					else
					{
						stepAct[1] = 0;
					}

				}
				else {
					zentaiStep++;
					hazureta = false;

					if (zentaiStep >= enAmount && bufSk->target[stepAct[1]] == 1) {
						bufF = true;
					}
					if (zentaiStep >= 3 && bufSk->target[stepAct[1]] == 4) {
						bufF = true;
					}
					if (zentaiStep >= 3 && bufSk->target[stepAct[1]] == 8) {
						bufF = true;
					}
					if (bufSk->target[stepAct[1]] != 1 && bufSk->target[stepAct[1]] != 4 && bufSk->target[stepAct[1]] != 8) {
						bufF = true;
					}

					if (bufF) { //元々はelse if(bufSk->target[stepAct[1]] ==1 || bufSk->target[stepAct[1]] == 4){					
						zentaiStep = 0;
						skTimes++;
						if (skTimes >= bufSk->times || stepAct[1] != 0) {
							skTimes = 0;
							stepAct[1]++;
							if (stepAct[1] >= bufSk->classifyNum) {
								stepAct[1] = 0;

								if (vSkill[stepAct[0]][0].cardNum >= 0) {
									csQuestBase.character[0]->SkillSpeadRand();
									skillCard[vSkill[stepAct[0]][0].cardNum] = csQuestBase.character[0]->skill[GetRand(5)];
									skillCard[vSkill[stepAct[0]][0].cardNum].Point = GetRand(9) + 1;
									skillCard[vSkill[stepAct[0]][0].cardNum].cardNum = vSkill[stepAct[0]][0].cardNum;
								}
								vSkill[stepAct[0]].erase(vSkill[stepAct[0]].begin());
								//preActNext = true;
								actNext = false;
								if (vSkill[stepAct[0]].empty()) {
									stepAct[0]++;
									if (stepAct[0] > 2) {
										step = 0;
										bArrow[0] = 0;
										actNext = true;
										skTimes = 0;
										stepAct[0] = 0;
										stepAct[1] = 0;
										for (int i = 0; i < 3; i++) {
											csQuestBase.character[i]->damageCut[0] = 0;
											csQuestBase.character[i]->damageCut[1] = 0;
										}

										for (int i = 0; i < enAmount; i++) {
											enemy[i]->damageCut[0] = 0;
											enemy[i]->damageCut[1] = 0;
										}
										break;
									}
									else {
										break;
									}
								}
								else {
									break;
								}
							}
						}
					}
				}


			}
			else if (*death == 0)
			{

				oneMore = false;
				bufEnd = 0;
				bufF = false;
				target9 = false;

				if (bufSk->target[stepAct[1]] == 9) {
					bufTarget = bufSk->target[0];
					target9 = true;
				}
				else {
					bufTarget = bufSk->target[stepAct[1]];
				}


				switch (bufTarget)
				{
				case 0:

					if (stepAct[1] == 0 && skTimes == 0 && target9 == false) {
						bufI = GetRand(2);
						bufRand = GetRand(1) * 2 - 1;
						if (bufSk->hajime) {
							skTimes--;
						}

						for (int i = 0; i < 3; i++) {
							if (csQuestBase.character[bufI]->live) {
								bufSk->targetNum = bufI;
								break;
							}
							bufI += bufRand;
							if (bufI >= 3) {
								bufI = 0;
							}
							if (bufI <= -1) {
								bufI = 2;
							}
						}

					}

					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}

					csQuestBase.character[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 1:
					bufSk->targetNum = zentaiStep;
					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}
					csQuestBase.character[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 2:
					if (target9 == false) {
						bufI = GetRand(2);
						bufRand = GetRand(1) * 2 - 1;
						if (bufSk->hajime) {
							skTimes--;
						}

						for (int i = 0; i < 3; i++) {
							if (csQuestBase.character[bufI]->live) {
								bufSk->targetNum = bufI;
								break;
							}
							bufI += bufRand;
							if (bufI >= 3) {
								bufI = 0;
							}
							if (bufI <= -1) {
								bufI = 2;
							}
						}

					}

					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}

					csQuestBase.character[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;

				case 3:

					if (stepAct[1] == 0 && skTimes == 0 && target9 == false) {
						bufI = GetRand(enAmount - 1);
						if (bufSk->hajime) {
							skTimes--;
						}

						for (int j = 0; j < 400; j++) {
							if (enemy[bufI]->live == true) {
								bufSk->targetNum = bufI;
								break;
							}
							bufI = GetRand(enAmount - 1);
							if (j == 399) {
								for (int i = 0; i < enAmount; i++) {
									if (enemy[i]->live) {
										bufSk->targetNum = i;
										break;
									}
								}
							}

						}

					}

					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}

					enemy[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;

				case 4:
					bufSk->targetNum = zentaiStep;
					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}
					enemy[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 5:

					if (target9 == false) {
						bufI = GetRand(enAmount - 1);
						if (bufSk->hajime) {
							skTimes--;
						}

						for (int j = 0; j < 400; j++) {
							if (enemy[bufI]->live == true) {
								bufSk->targetNum = bufI;
								break;
							}
							bufI = GetRand(enAmount - 1);
							if (j == 399) {
								for (int i = 0; i < enAmount; i++) {
									if (enemy[i]->live) {
										bufSk->targetNum = i;
										break;
									}
								}
							}

						}

					}

					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}

					enemy[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 6:
					if (bufSk->hajime) {
						skTimes--;
					}

					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}

					bufSk->targetNum = bufSk->UseNum;
					enemy[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 7:

					if (stepAct[1] == 0 && skTimes == 0 && target9 == false) {
						bufI = GetRand(enAmount - 1);
						if (bufSk->hajime) {
							skTimes--;
						}

						for (int j = 0; j < 300; j++) {
							if (enemy[bufI]->live == false) {
								bufSk->targetNum = bufI;
								break;
							}
							bufI = GetRand(enAmount - 1);
							if (j == 399) {
								for (int i = 0; i < enAmount; i++) {
									bufSk->targetNum = i;
									if (enemy[i]->live == false) {
										break;
									}
									if (i == enAmount - 1) {
										bufSk->targetNum = GetRand(enAmount - 1);
										break;
									}
								}
							}

						}

					}

					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}

					enemy[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;
				case 8:
					bufSk->targetNum = zentaiStep;
					if (bufSk->targetNum < 0) {
						bufSk->targetNum = 0;
					}
					enemy[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);
					break;

				case 10:
					bufSk->targetNum = 0;
					csQuestBase.character[bufSk->targetNum]->skillHatudou(bufSk->useChar, bufSk, stepAct[1], csQuestBase.textWindow, &oneMore, &hazureta);

					break;
				default:
					break;
				}


				//


				if (stepAct[1] + 1 < bufSk->classifyNum && hajimeBuf == false) {
					stepAct[1]++;
					if (bufSk->target[stepAct[1]] == 9) {
						continue;
					}
					else
					{
						stepAct[1]--;
					}
				}


				if (bufSk->target[stepAct[1]] == 9) {
					zentaiStep++;
					hazureta = false;

					if (zentaiStep >= 3 && bufSk->target[0] == 1) {
						bufF = true;
					}
					if (zentaiStep >= enAmount && bufSk->target[0] == 4) {
						bufF = true;
					}
					if (zentaiStep >= enAmount && bufSk->target[0] == 8) {
						bufF = true;
					}
					if (bufSk->target[0] != 1 && bufSk->target[0] != 4 && bufSk->target[0] != 8) {
						bufF = true;
					}

					if (bufF) {
						zentaiStep = 0;
						skTimes++;
						if (skTimes >= bufSk->times) {
							skTimes = 0;
							stepAct[1]++;
							if (stepAct[1] >= bufSk->classifyNum) {
								stepAct[1] = 0;
								vSkill[stepAct[0]].erase(vSkill[stepAct[0]].begin());
								//preActNext = true;
								actNext = false;
								if (vSkill[stepAct[0]].empty()) {
									stepAct[0]++;
									if (stepAct[0] > 2) {
										step = 0;
										bArrow[0] = 0;
										actNext = true;
										skTimes = 0;
										stepAct[0] = 0;
										stepAct[1] = 0;
										break;
									}
									else {
										break;
									}
								}
								else {
									break;
								}
							}
						}
						else
						{
							stepAct[1] = 0;
						}
					}
					else
					{
						stepAct[1] = 0;
					}

				}
				else {
					zentaiStep++;
					hazureta = false;

					if (zentaiStep >= 3 && bufSk->target[stepAct[1]] == 1) {
						bufF = true;
					}
					if (zentaiStep >= enAmount && bufSk->target[stepAct[1]] == 4) {
						bufF = true;
					}
					if (zentaiStep >= enAmount && bufSk->target[stepAct[1]] == 8) {
						bufF = true;
					}
					if (bufSk->target[stepAct[1]] != 1 && bufSk->target[stepAct[1]] != 4 && bufSk->target[stepAct[1]] != 8) {
						bufF = true;
					}

					if (bufF) { //元々はelse if(bufSk->target[stepAct[1]] ==1 || bufSk->target[stepAct[1]] == 4){					
						zentaiStep = 0;
						skTimes++;
						if (skTimes >= bufSk->times || stepAct[1] != 0) {
							skTimes = 0;
							stepAct[1]++;
							if (stepAct[1] >= bufSk->classifyNum) {
								stepAct[1] = 0;
								vSkill[stepAct[0]].erase(vSkill[stepAct[0]].begin());
								//preActNext = true;
								actNext = false;
								if (vSkill[stepAct[0]].empty()) {
									stepAct[0]++;
									if (stepAct[0] > 2) {
										step = 0;
										bArrow[0] = 0;
										actNext = true;
										skTimes = 0;
										stepAct[0] = 0;
										stepAct[1] = 0;
										break;
									}
									else {
										break;
									}
								}
								else {
									break;
								}
							}
						}
					}
				}
				/*else {
					skTimes++;
					if (skTimes >= bufSk->times) {
						skTimes = 0;
						stepAct[1]++;
						if (stepAct[1] >= bufSk->classifyNum) {
							stepAct[1] = 0;
							vSkill[stepAct[0]].erase(vSkill[stepAct[0]].begin());
							//preActNext = true;
							actNext = false;
							if (vSkill[stepAct[0]].empty()) {
								stepAct[0]++;
								if (stepAct[0] > 2) {
									step = 0;
									bArrow[0] = 0;
									actNext = true;
									skTimes = 0;
									stepAct[0] = 0;
									stepAct[1] = 0;
									break;
								}
								else {
									break;
								}
							}
							else {
								break;
							}
						}
					}
					else if (bufSk->target[stepAct[1]] != 9 && stepAct[1] >= 1) {
						skTimes = 0;
						stepAct[1]++;
						if (stepAct[1] >= bufSk->classifyNum) {
							stepAct[1] = 0;
							//preActNext = true;
							actNext = false;
							vSkill[stepAct[0]].erase(vSkill[stepAct[0]].begin());
							if (vSkill[stepAct[0]].empty()) {
								stepAct[0]++;
								if (stepAct[0] > 2) {
									step = 0;
									bArrow[0] = 0;
									actNext = true;
									skTimes = 0;
									stepAct[0] = 0;
									stepAct[1] = 0;
									break;
								}
								else {
									break;
								}
							}
							else {
								break;
							}
						}
					}
				}*/
				//


			}
		}
		else {
			stepAct[1] = 0;
			vSkill[stepAct[0]].erase(vSkill[stepAct[0]].begin());
			oneMore = true;
			//preActNext = true;
			if (vSkill[stepAct[0]].empty()) {
				stepAct[0]++;
				while (stepAct[0]<=2 && vSkill[stepAct[0]].empty())
				{
					stepAct[0]++;
				}
				if (stepAct[0] > 2) {
					step = 0;
					bArrow[0] = 0;
					actNext = false;
					skTimes = 0;
					stepAct[0] = 0;
					stepAct[1] = 0;
					break;
				}
				else {
					if (!vSkill[stepAct[0]].empty()) {
						bufSk = &vSkill[stepAct[0]][0];
						jiki = !bufSk->ene;
					}
				}
			}
			else {
				if (!vSkill[stepAct[0]].empty()) {
					bufSk = &vSkill[stepAct[0]][0];
					jiki = !bufSk->ene;
				}
			}
		}
	}
	
	

}

void CSQuestBase::CSBattle::Loop()
{
	int bufI = 0;
	bool bufRepeat = true;
	bool oneMore = false;
	char skillJunjo = 1;
	char bufDeath = 0;
	char bufEnd = 0;
	char bufEndWin = 0;
	string bufS="";
	Skill bufSkill;

	if (battleStart) {

		while (bufRepeat)
		{
			bufRepeat = false;
			switch (step)
			{
			case 12:
				if (KeyUp() && bArrow[3] > 0) {
					bArrow[3]--;
					if (drawSkillWindow == true) {
						csQuestBase.haniwaSkillWindow->ChangeNum(csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].num);
					}
				}

				if (KeyDown() && bArrow[3] < 4) {
					bArrow[3]++;
					if (drawSkillWindow == true && bArrow[3] <= 3) {
						csQuestBase.haniwaSkillWindow->ChangeNum(csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].num);
					}
				}
				if (KeyOK()) {

					if (bArrow[3] <= 3) {

						if (csQuestBase.character[preStep2 - 3]->Status[1] >= csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].MP) {
							preStep = 12;
							if (drawSkillWindow == true) {
								delete csQuestBase.haniwaSkillWindow;
								csQuestBase.haniwaSkillWindow = NULL;
							}
							csQuestBase.character[preStep2 - 3]->SkillSpeadRand();
							targetSelectSkill = &(csQuestBase.character[preStep2 - 3]->skill[bArrow[3]]);

							switch (csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].target[0]) {
							case 0:step = 7; break;
							case 3:step = 8; break;
							case 7:step = 9; break;
							default:
								csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].targetNum = preStep - 3;
								if (csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].classify[0] <= 1 && csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].content[0] == 6) {
									skillJunjo = 0;
								}
								else if (csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].classify[0] <= 1 && csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].content[0] == 7) {
									skillJunjo = 2;
								}
								else {
									skillJunjo = 1;
								}

								vSkill[skillJunjo].push_back(csQuestBase.character[preStep2 - 3]->skill[bArrow[3]]);
								step = preStep2 + 1;
								bArrow[1] = 0;

								break;
							}
						}

					}

					else {
						if (drawSkillWindow == true) {
							delete csQuestBase.haniwaSkillWindow;
							csQuestBase.haniwaSkillWindow = NULL;
						}
						step = preStep2;
					}

					break;
				}

				if (Input.GetKeyEnter(Input.key.A) || Input.GetKeyEnter(Input.key.SPACE)) {
					if (drawSkillWindow == true) {
						drawSkillWindow = false;
						delete csQuestBase.haniwaSkillWindow;
						csQuestBase.haniwaSkillWindow = NULL;
					}
					else {
						drawSkillWindow = true;
						csQuestBase.haniwaSkillWindow = new CHaniwaSkillWindow(csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].num, csQuestBase.mySaveData->haniwaLevel[csQuestBase.mySaveData->bringHaniwaKind[preStep2 - 4]]);
					}
					break;
				}

				if (KeyCancel()) {
					step = preStep2;
					if (drawSkillWindow == true) {
						delete csQuestBase.haniwaSkillWindow;
						csQuestBase.haniwaSkillWindow = NULL;
					}
					break;
				}


				break;
			case 11:
				if (KeyLeft() && bArrow[3] > 0) {
					bArrow[3]--;
					if (drawSkillWindow) {
						csQuestBase.skillWindow->ChangeNum(skillCard[bArrow[3]].num);
					}
				}

				if (KeyRight() && bArrow[3] < 3) {
					bArrow[3]++;
					if (drawSkillWindow) {
						csQuestBase.skillWindow->ChangeNum(skillCard[bArrow[3]].num);
					}
				}

				if (KeyOK()) {
					if (csQuestBase.character[0]->Status[1] >= skillCard[bArrow[3]].MP) {
						preStep = 11;
						delete csQuestBase.skillWindow;
						if (drawSkillWindow) {
							csQuestBase.skillWindow = NULL;
							targetSelectSkill = &(skillCard[bArrow[3]]);
						}

						switch (skillCard[bArrow[3]].target[0]) {
						case 0:step = 7; break;
						case 3:step = 8; break;
						case 7:step = 9; break;
						default:
							skillCard[bArrow[3]].targetNum = preStep - 3;
							if (skillCard[bArrow[3]].classify[0] <= 1 && skillCard[bArrow[3]].content[0] == 6) {
								skillJunjo = 0;
							}
							else if (skillCard[bArrow[3]].classify[0] <= 1 && skillCard[bArrow[3]].content[0] == 7) {
								skillJunjo = 2;
							}
							else {
								skillJunjo = 1;
							}

							vSkill[skillJunjo].push_back(skillCard[bArrow[3]]);
							step = preStep2 + 1;
							bArrow[1] = 0;

							break;
						}
					}

				}

				if (Input.GetKeyEnter(Input.key.A) || Input.GetKeyEnter(Input.key.SPACE)) {
					if (drawSkillWindow == true) {
						drawSkillWindow = false;
						delete csQuestBase.skillWindow;
						csQuestBase.skillWindow = NULL;
					}
					else {
						drawSkillWindow = true;
						csQuestBase.skillWindow = new CSkillWindow(skillCard[bArrow[3]].num);
					}
					break;
				}

				if (KeyCancel()) {
					step = preStep2;

					if (drawSkillWindow) {
						delete csQuestBase.skillWindow;
						csQuestBase.skillWindow = NULL;
					}
					break;
				}

				break;
			case 10:
				csQuestBase.textWindow->Loop();
				if (winTextStep < enAmount && csQuestBase.textWindow->GetWaitTextEmpty() && KeyOK()) {
					
					if (boss) {
						if (enemy[winTextStep]->bigBoss) {

						}
						else {
							bufS = enemy[winTextStep]->name.c_str();
							bufS += "から";
							for (int j = 0; j < 3; j++) {
								bufS += enemy[winTextStep]->dropItemName[j].c_str();
								bufS += "、/n";
							}
							bufS += "を手に入れた。";
						}
					}
					else {
						bufS = enemy[winTextStep]->name.c_str();
						bufS += "から";
						bufS += enemy[winTextStep]->dropItemName[0].c_str();
						bufS += "を手に入れた。";

						csQuestBase.textWindow->PushText(bufS.c_str());
					}
					winTextStep++;

				}
				else if (csQuestBase.textWindow->GetTextEmpty() && csQuestBase.textWindow->GetWaitTextEmpty()) {

					itemM = new CItemManager(0, csQuestBase.mySaveData);
					if (boss) {
						for (int i = 0; i < enAmount; i++) {
							if (enemy[i]->bigBoss == true) {
							}
							else {
								itemM->Add(enemy[i]->dropItem[0][0], enemy[i]->dropItem[0][1], 1);
								itemM->Add(enemy[i]->dropItem[1][0], enemy[i]->dropItem[1][1], 1);
								itemM->Add(enemy[i]->dropItem[2][0], enemy[i]->dropItem[2][1], 1);
							}
						}

					}
					else {
						csQuestBase.mode[0] = 0;
						csQuestBase.mode[1] = 5;
						for (int i = 0; i < enAmount; i++) {
							itemM->Add(enemy[i]->dropItem[0][0], enemy[i]->dropItem[0][1], 1);
						}
						csQuestBase.RemoveScene(Flip::DOOR_COME_VERTICAL, 4);
					}
				
					delete itemM;
					itemM=NULL;
				}

				break;
			case 9:
				if (KeyRight()) {
					for (int i = bArrow[2] + 1; i < 3; i++) {
						bArrow[2] = i;
						break;
					}
				}

				if (KeyLeft()) {
					for (int i = bArrow[2] - 1; i >= 0; i--) {
						bArrow[2] = i;
						break;
					}
				}

				if (KeyOK()) {
					targetSelectSkill->targetNum = bArrow[2];
					if (targetSelectSkill->classify[0] <= 1 && targetSelectSkill->content[0] == 6) {
						skillJunjo = 0;
					}
					else if (targetSelectSkill->classify[0] <= 1 && targetSelectSkill->content[0] == 7) {
						skillJunjo = 2;
					}
					else {
						skillJunjo = 1;
					}

					vSkill[skillJunjo].push_back(*targetSelectSkill);

					bArrow[2] = 0;
					bArrow[1] = 0;
					skillJunjo = 1;

					if (targetSelectSkill->useChar == csQuestBase.character[0]) {
						step = 4;
					}
					else if (targetSelectSkill->useChar == csQuestBase.character[1]) {
						step = 5;
					}
					else
					{
						step = 6;
					}

				}

				if (KeyCancel()) {
					step = preStep;
					if (KeyCancel()) {
						step = preStep;
						if (preStep == 12 && drawSkillWindow == true) {
							csQuestBase.haniwaSkillWindow = new CHaniwaSkillWindow(csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].num, csQuestBase.mySaveData->haniwaLevel[csQuestBase.mySaveData->bringHaniwaKind[preStep2 - 4]]);
						}

						if (preStep == 11 && drawSkillWindow == true) {
							csQuestBase.skillWindow = new CSkillWindow(skillCard[bArrow[3]].num);
						}
					}

				}


				break;
			case 8:
				if (csQuestBase.character[bArrow[2]]->live == false) {
					for (int j = 0; j < 3; j++) {
						if (csQuestBase.character[j]->live) {
							bArrow[2] = j;
							break;
						}
					}
				}

				if (KeyRight()) {
					for (int i = bArrow[2] + 1; i < 3; i++) {
						if (csQuestBase.character[i]->live) {
							bArrow[2] = i;
							break;
						}
					}
				}

				if (KeyLeft()) {
					for (int i = bArrow[2] - 1; i >= 0; i--) {
						if (csQuestBase.character[i]->live) {
							bArrow[2] = i;
							break;
						}
					}
				}

				if (KeyOK() && csQuestBase.character[bArrow[2]]->live) {
					targetSelectSkill->targetNum = bArrow[2];
					if (targetSelectSkill->classify[0] <= 1 && targetSelectSkill->content[0] == 6) {
						skillJunjo = 0;
					}
					else if (targetSelectSkill->classify[0] <= 1 && targetSelectSkill->content[0] == 7) {
						skillJunjo = 2;
					}
					else {
						skillJunjo = 1;
					}

					vSkill[skillJunjo].push_back(*targetSelectSkill);

					bArrow[2] = 0;
					bArrow[1] = 0;
					skillJunjo = 1;

					if (targetSelectSkill->useChar == csQuestBase.character[0]) {
						step = 4;
					}
					else if (targetSelectSkill->useChar == csQuestBase.character[1]) {
						step = 5;
					}
					else
					{
						step = 6;
					}

				}

				if (KeyCancel()) {
					step = preStep;
					if (preStep == 12 && drawSkillWindow==true) {
						csQuestBase.haniwaSkillWindow = new CHaniwaSkillWindow(csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].num, csQuestBase.mySaveData->haniwaLevel[csQuestBase.mySaveData->bringHaniwaKind[preStep2 - 4]]);
					}

					if (preStep == 11 && drawSkillWindow == true) {
						csQuestBase.skillWindow = new CSkillWindow(skillCard[bArrow[3]].num);
					}
				}

				break;
			case 7:

				if (enemy[bArrow[2]]->live == false) {
					for (int j = 0; j < enAmount; j++) {
						if (enemy[j]->live) {
							bArrow[2] = j;
							break;
						}
					}
				}

				if (KeyRight()) {
					for (int i = bArrow[2] + 1; i < enAmount; i++) {
						if (enemy[i]->live) {
							bArrow[2] = i;
							break;
						}
					}
				}

				if (KeyLeft()) {
					for (int i = bArrow[2] - 1; i >= 0; i--) {
						if (enemy[i]->live) {
							bArrow[2] = i;
							break;
						}
					}
				}

				if (KeyOK() && enemy[bArrow[2]]->live) {
					targetSelectSkill->targetNum = bArrow[2];
					if (targetSelectSkill->classify[0] <= 1 && targetSelectSkill->content[0] == 6) {
						skillJunjo = 0;
					}
					else if (targetSelectSkill->classify[0] <= 1 && targetSelectSkill->content[0] == 7) {
						skillJunjo = 2;
					}
					else {
						skillJunjo = 1;
					}

					vSkill[skillJunjo].push_back(*targetSelectSkill);

					bArrow[2] = 0;
					bArrow[1] = 0;
					skillJunjo = 1;

					if (targetSelectSkill->useChar == csQuestBase.character[0]) {
						step = 4;
					}
					else if (targetSelectSkill->useChar == csQuestBase.character[1]) {
						step = 5;
					}
					else
					{
						step = 6;
					}

				}

				if (KeyCancel()) {
					step = preStep;
					if (KeyCancel()) {
						step = preStep;
						if (preStep == 12 && drawSkillWindow == true) {
							csQuestBase.haniwaSkillWindow = new CHaniwaSkillWindow(csQuestBase.character[preStep2 - 3]->skill[bArrow[3]].num, csQuestBase.mySaveData->haniwaLevel[csQuestBase.mySaveData->bringHaniwaKind[preStep2 - 4]]);
						}

						if (preStep == 11 && drawSkillWindow == true) {
							csQuestBase.skillWindow = new CSkillWindow(skillCard[bArrow[3]].num);
						}
					}

				}


				break;
			case 6:
				for (int i = 0; i < enAmount; i++) {
					if (i == 0 && csQuestBase.vq->bigBoss[bossNum] == true && boss == true) {
						if (enemy[i]->live) {

						}

					}
					else if (enemy[i]->live) {
						bufSkill = enemy[i]->returnSkill();
						if (bufSkill.classify[0] <= 1 && bufSkill.content[0] == 6) {
							vSkill[0].push_back(bufSkill);
						}
						else if (bufSkill.classify[0] <= 1 && bufSkill.content[0] == 7) {
							vSkill[2].push_back(bufSkill);
						}
						else {
							vSkill[1].push_back(bufSkill);
						}

					}
				}
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < vSkill[i].size(); j++) {
						for (int k = 0; k < vSkill[i][j].classifyNum; k++) {
							if (vSkill[i][j].classify[k] == 5) {
								switch (vSkill[i][j].content[k])
								{
								case 7:
									vSkill[i][j].useChar->damageCut[0] = vSkill[i][j].power[k];
									break;
								case 8:
									vSkill[i][j].useChar->damageCut[1] = vSkill[i][j].power[k];
									break;
								case 9:
									vSkill[i][j].useChar->damageCut[0] = vSkill[i][j].power[k];
									vSkill[i][j].useChar->damageCut[1] = vSkill[i][j].power[k];
									break;
								default:
									break;
								}
							}
						}
					}
				}
				actNext = true;
				skTimes = 0;
				step = 1;
				stepAct[0] = 0;
				stepAct[1] = 0;

				for (int i = 0; i < 3; i++)
				{
					sort(vSkill[i].begin(), vSkill[i].end());
					reverse(vSkill[i].begin(), vSkill[i].end());
				}
				break;
			case 5:

				if (csQuestBase.character[step - 3]->live) {
					if (KeyUp() && bArrow[1] > 0) {
						bArrow[1]--;
					}
					if (KeyDown() && bArrow[1] < 4) {
						bArrow[1]++;
					}
					if (KeyOK()) {
						preStep = step;
						switch (bArrow[1])
						{
						case 0:
							csQuestBase.character[step - 3]->SkillSpeadRand();
							targetSelectSkill = &csQuestBase.character[step - 3]->normalAtack;
							step = 7;
							for (int j = 0; j < enAmount; j++) {
								if (enemy[j]->live) {
									bArrow[2] = j;
									break;
								}
							}

							break;
						case 1:
							preStep2 = step;
							step = 12;
							bArrow[3] = 0;
							if (drawSkillWindow == true) {
								csQuestBase.haniwaSkillWindow = new CHaniwaSkillWindow(csQuestBase.character[preStep2 - 3]->skill[0].num, csQuestBase.mySaveData->haniwaLevel[csQuestBase.mySaveData->bringHaniwaKind[preStep2 - 4]]);
							}
							break;
						case 3:
							csQuestBase.character[step - 3]->normalDefence.targetNum = step - 3;
							csQuestBase.character[step - 3]->SkillSpeadRand();
							vSkill[1].push_back(csQuestBase.character[step - 3]->normalDefence);
							step = 6;
							bArrow[1] = 0;
							break;
						case 4:
							if (csQuestBase.character[1]->live) {
								step = 4;
								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < vSkill[i].size(); j++) {
										if (vSkill[i][j].useChar == csQuestBase.character[step - 3]) {
											vSkill[i].pop_back();
											break;
										}
									}
								}
							}
							else if (csQuestBase.character[0]->live) {
								step = 3;
								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < vSkill[i].size(); j++) {
										if (vSkill[i][j].useChar == csQuestBase.character[step - 3]) {
											vSkill[i].pop_back();
											break;
										}
									}
								}
							}
							else {
								step = 0;
								bArrow[0] = 0;
							}
							bArrow[0] = 0;
							break;

						default:
							break;
						}
					}
				}
				else
				{
					step = 6;
					bArrow[1] = 0;
					bufRepeat = true;
				}

				if (KeyCancel()) {
					if (csQuestBase.character[1]->live) {
						step = 4;
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < vSkill[i].size(); j++) {
								if (vSkill[i][j].useChar == csQuestBase.character[step - 3]) {
									vSkill[i].pop_back();
									break;
								}
							}
						}
					}
					else if (csQuestBase.character[0]->live) {
						step = 3;
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < vSkill[i].size(); j++) {
								if (vSkill[i][j].useChar == csQuestBase.character[step - 3]) {
									vSkill[i].pop_back();
									break;
								}
							}
						}
					}
					else {
						step = 0;
						bArrow[0] = 0;
					}
					bArrow[0] = 0;
				}

				break;
			case 4:

				if (csQuestBase.character[step - 3]->live) {
					if (KeyUp() && bArrow[1] > 0) {
						bArrow[1]--;
					}
					if (KeyDown() && bArrow[1] < 4) {
						bArrow[1]++;
					}
					if (KeyOK()) {
						preStep = step;
						switch (bArrow[1])
						{
						case 0:
							csQuestBase.character[step - 3]->SkillSpeadRand();
							targetSelectSkill = &csQuestBase.character[step - 3]->normalAtack;
							step = 7;
							for (int j = 0; j < enAmount; j++) {
								if (enemy[j]->live) {
									bArrow[2] = j;
									break;
								}
							}

							break;
						case 1:
							preStep2 = step;
							step = 12;
							bArrow[3] = 0;
							if (drawSkillWindow == true) {
								csQuestBase.haniwaSkillWindow = new CHaniwaSkillWindow(csQuestBase.character[preStep2 - 3]->skill[0].num, csQuestBase.mySaveData->haniwaLevel[csQuestBase.mySaveData->bringHaniwaKind[preStep2-4]]);
							}

							break;
						case 3:
							csQuestBase.character[step - 3]->normalDefence.targetNum = step - 3;
							csQuestBase.character[step - 3]->SkillSpeadRand();
							vSkill[1].push_back(csQuestBase.character[step - 3]->normalDefence);
							step = 5;
							bArrow[1] = 0;
							break;
						case 4:
							if (csQuestBase.character[0]->live) {
								step = 3;
								for (int i = 0; i < 3; i++) {
									for (int j = 0; j < vSkill[i].size(); j++) {
										if (vSkill[i][j].useChar == csQuestBase.character[step - 3]) {
											vSkill[i].pop_back();
											break;
										}
									}
								}
							}
							else {
								step = 0;
								bArrow[0] = 0;
							}
							bArrow[0] = 0;
							break;

						default:
							break;
						}
					}
				}
				else
				{
					step = 5;
					bArrow[1] = 0;
					bufRepeat = true;
				}

				if (KeyCancel()) {
					if (csQuestBase.character[0]->live) {
						step = 3;
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < vSkill[i].size(); j++) {
								if (vSkill[i][j].useChar == csQuestBase.character[step - 3]) {
									vSkill[i].pop_back();
									break;
								}
							}
						}
					}
					else {
						step = 0;
						bArrow[0] = 0;
					}
					bArrow[0] = 0;
				}

				break;
			case 3:

				if (csQuestBase.character[step - 3]->live) {
					if (KeyUp() && bArrow[1] > 0) {
						bArrow[1]--;
					}
					if (KeyDown() && bArrow[1] < 4) {
						bArrow[1]++;
					}
					if (KeyOK()) {
						preStep = step;
						switch (bArrow[1])
						{
						case 0:
							csQuestBase.character[step - 3]->SkillSpeadRand();
							targetSelectSkill = &csQuestBase.character[step - 3]->normalAtack;
							step = 7;
							for (int j = 0; j < enAmount; j++) {
								if (enemy[j]->live) {
									bArrow[2] = j;
									break;
								}
							}

							break;
						case 1:

							preStep2 = step;
							step = 11;
							bArrow[3] = 0;

							if (drawSkillWindow == true) {
								csQuestBase.skillWindow = new CSkillWindow(skillCard[0].num);
							}

							break;
						case 3:
							csQuestBase.character[step - 3]->normalDefence.targetNum = step - 3;
							csQuestBase.character[step - 3]->SkillSpeadRand();
							vSkill[1].push_back(csQuestBase.character[step - 3]->normalDefence); step = 4;
							step = 4;
							bArrow[1] = 0;
							break;
						case 4:
							step = 0;
							bArrow[0] = 0;
							break;

						default:
							break;
						}
					}
				}
				else
				{
					step = 4;
					bArrow[1] = 0;
					bufRepeat = true;
				}

				if (KeyCancel()) {
					step = 0;
					bArrow[0] = 0;
				}

				break;
			case 2:
				csQuestBase.textWindow->Loop();
				if (csQuestBase.textWindow->GetTextEmpty() && csQuestBase.textWindow->GetWaitTextEmpty()) {
					csQuestBase.mode[0] = 2;
					csQuestBase.mode[1] = 0;
					csQuestBase.RemoveScene(Flip::FADE_OUT_IN, 3);
				}
				break;
			case 1:
				if (actNext) {
					//
					switch (stepAct[0])
					{
					case 0:
						if (vSkill[0].empty()) {
							stepAct[0]++;
							actNext = true;
							skTimes = 0;
							stepAct[1] = 0;
							preActNext = true;
						}
						else
						{
							charAct(!vSkill[0][0].ene, &vSkill[0][0], &bufDeath);
							break;
						}
					case 1:
						if (vSkill[1].empty()) {
							stepAct[0]++;
							actNext = true;
							skTimes = 0;
							stepAct[1] = 0;
							preActNext = true;
						}
						else
						{
							charAct(!vSkill[1][0].ene, &vSkill[1][0], &bufDeath);
							break;
						}
					case 2:
						if (vSkill[2].empty()) {
							step = 0;
							bArrow[0] = 0;
							actNext = true;
							skTimes = 0;
							stepAct[0] = 0;
							stepAct[1] = 0;
							preActNext = true;
							for (int i = 0; i < 3; i++) {
								csQuestBase.character[i]->damageCut[0] = 0;
								csQuestBase.character[i]->damageCut[1] = 0;
							}

							for (int i = 0; i < enAmount; i++) {
								enemy[i]->damageCut[0] = 0;
								enemy[i]->damageCut[1] = 0;
							}

							break;
						}
						else
						{
							charAct(!vSkill[2][0].ene, &vSkill[2][0], &bufDeath);
							break;
						}
					default:
						break;
					}
				}

				//


				actNext = false;
				preActNext = true;
				if (preActNext == true && KeyOK() && csQuestBase.textWindow->GetWaitTextEmpty()) {
					preActNext = false;
					actNext = true;
				}
				else if (KeyOK())
				{
					csQuestBase.textWindow->Loop();

				}

				for (int i = 0; i < 3; i++) {
					if (csQuestBase.character[i]->live == false) {
						bufEnd += 1;
					}
				}

				for (int i = 0; i < enAmount; i++) {
					if (enemy[i]->live == false) {
						bufEndWin += 1;
					}
				}

				if (bufDeath == 1 || bufEnd >= 3) {
					csQuestBase.textWindow->TextClear();
					csQuestBase.textWindow->PushText("全滅してしまった．．．/n町へ戻ります。");
					step = 2;
				}
				else if (bufEndWin >= enAmount) {
					csQuestBase.textWindow->TextClear();
					csQuestBase.textWindow->PushText("全ての敵を倒した。");
					step = 10;
				}


				break;
			case 0:
				if (csQuestBase.textWindow->GetTextEmpty() && csQuestBase.textWindow->GetWaitTextEmpty()) {


					if (nigeta)
					{
						csQuestBase.mode[0] = 0;
						csQuestBase.mode[1] = 5;
						csQuestBase.RemoveScene(Flip::DOOR_COME_VERTICAL, 4);
					}

					if (KeyUp() || KeyDown()) {
						bArrow[0] = (bArrow[0] + 1) % 2;
					}
					if (KeyOK()) {

						if (bArrow[0] == 0) {

							actNext = true;
							bArrow[1] = 0;
							skTimes = 0;
							step = 3;
							stepAct[0] = 0;
							stepAct[1] = 0;

						}
						else if (boss == false)
						{
							if (nigeru <= GetRand(255)) {
								csQuestBase.textWindow->PushText("逃げようとしたが追い付かれた。");
								for (int i = 0; i < enAmount; i++) {
									if (i == 0 && csQuestBase.vq->bigBoss[bossNum] == true && boss == true) {
										if (enemy[i]->live) {

										}

									}
									else if (enemy[i]->live) {
										bufSkill = enemy[i]->returnSkill();
										if (bufSkill.classify[0] <= 1 && bufSkill.content[0] == 6) {
											vSkill[0].push_back(bufSkill);
										}
										else if (bufSkill.classify[0] <= 1 && bufSkill.content[0] == 7) {
											vSkill[2].push_back(bufSkill);
										}
										else {
											vSkill[1].push_back(bufSkill);
										}

									}
								}
								for (int i = 0; i < 3; i++)
								{
									sort(vSkill[i].begin(), vSkill[i].end());
									reverse(vSkill[i].begin(), vSkill[i].end());
								}
								actNext = true;
								skTimes = 0;
								step = 1;
								stepAct[0] = 0;
								stepAct[1] = 0;
								zentaiStep = 100000;
							}
							else {
								csQuestBase.textWindow->PushText("うまく逃げ切れた。");
								nigeta = true;
							}
						}

					}

				}
				else
				{
					csQuestBase.textWindow->Loop();
				}

				break;
			default:
				break;
			}

		}
	}


	battleStart = true;

}

void CSQuestBase::CSBattle::Draw()
{
	if (KeyOK()) {
		int a = 0;
	}
	backGraph.DrawExtend(0, 0, 704, 576);

	for (int i = 0; i < enAmount; i++) {
		enemy[i]->Draw(285 + i * 140 - (enAmount / 2) * 140, 120, i % 2);
	
		enemy[i]->DrawDamageAndCure();
	}

	for (int i = 0; i < 3; i++) {
		csQuestBase.character[i]->Draw(10 + i * 230, 265);
		csQuestBase.character[i]->DrawDamageAndCure();
	}

	if (csQuestBase.textWindow->GetTextEmpty() == false || csQuestBase.textWindow->GetWaitTextEmpty() == false) {
		csQuestBase.textWindow->Draw();
	}

	if (csQuestBase.textWindow->GetTextEmpty()==false || csQuestBase.textWindow->GetWaitTextEmpty() == false)
	{
		csQuestBase.textWindow->Draw();
	}

	if ((3 <= step && step <= 5) || (7 <= step && step <= 9) || step >= 11) {
		bWindow[1].DrawExtend(5, 374, 120, 474);
		DrawFormatString(30, 384, BLACK, "戦う");
		DrawFormatString(30, 414, BLACK, "逃げる");
		bArrowG.Draw(10, 384 + bArrow[0] * 30);

		bWindow[1].DrawExtend(124, 374, 240, 560);
		DrawFormatString(149, 384, BLACK, "攻撃");
		DrawFormatString(149, 414, BLACK, "スキル");
		DrawFormatString(149, 444, BLACK, "アイテム");
		DrawFormatString(149, 474, BLACK, "防御");
		DrawFormatString(149, 504, BLACK, "戻る");
		bArrowG.Draw(129, 384 + bArrow[1] * 30);

		bWindow[3].DrawExtend(244, 374, 700, 405);
		if (3 <= step && step <= 5) {
			DrawFormatString(256, 380, BLACK, "%sはどうする？", csQuestBase.character[step - 3]->name.c_str());
		}
		if (7 <= step && step <= 9) {
			DrawFormatString(256, 380, BLACK, "技の対象を選ぼう！");
			bArrowG2.Draw(285 + bArrow[2] * 140 - (enAmount / 2) * 140 + 53, 40, bArrow[2] % 2);
			if (preStep == 12) {
				bWindow[3].DrawExtend(244, 420, 650, 570);
				for (int i = 0; i < 4; i++) {
					DrawFormatString(286, 425 + i * 20, BLACK, "%s", csQuestBase.character[preStep2 - 3]->skill[i].neme.c_str());
				}
				DrawFormatString(286, 425 + 4 * 20, BLACK, "閉じる");
				bArrowG.Draw(250, 425 + bArrow[3] * 20);
			}

			if (preStep == 11) {
				for (int i = 0; i < 4; i++) {
					cardG[skillCard[i].classify[0]].DrawExtend(250 + i * 115, 430, 340 + i * 115, 572);
					if (skillCard[i].Point == 10) {
						DrawFormatString(255 + i * 115, 435, BLACK, "%d", skillCard[i].Point);
					}
					else {
						DrawFormatString(259 + i * 115, 435, BLACK, "%d", skillCard[i].Point);
					}
				}
				bArrowG2.Draw(288 + bArrow[3] * 115, 408);
			}

		}

		if (step == 11) {
			DrawFormatString(256, 380, BLACK, "使用する技を選ぼう！");
			for (int i = 0; i < 4; i++) {
				cardG[skillCard[i].classify[0]].DrawExtend(250 + i * 115, 430, 340 + i * 115, 572);
				if (skillCard[i].Point == 10) {
					DrawFormatString(255 + i * 115, 435, BLACK, "%d", skillCard[i].Point);
				}
				else {
					DrawFormatString(259 + i * 115, 435, BLACK, "%d", skillCard[i].Point);
				}
			}
			bArrowG2.Draw(288 + bArrow[3] * 115, 408);

			if (drawSkillWindow == true) {
				csQuestBase.skillWindow->Draw(250);
			}
		}

		if (step == 12) {
			DrawFormatString(256, 380, BLACK, "使用する技を選ぼう！");

			bWindow[3].DrawExtend(244, 420, 700, 572);
			for (int i = 0; i < 4; i++) {
				DrawFormatString(286, 425 + i * 20, BLACK, "%s", csQuestBase.character[preStep2 - 3]->skill[i].neme.c_str());
			}
			DrawFormatString(286, 425 + 4 * 20, BLACK, "閉じる");
			bArrowG.Draw(250, 425 + bArrow[3] * 20);

			DrawFormatString(270, 425 + 5 * 20 + 10, BLACK, "※A又はスペースキーでスキル内容の表示、");
			DrawFormatString(286, 425 + 6 * 20 + 10, BLACK, "非表示を切り替える。");
			

			if (drawSkillWindow == true) {
				csQuestBase.haniwaSkillWindow->Draw(250);
			}

		}

	}

	

	if (csQuestBase.textWindow->GetTextEmpty() && csQuestBase.textWindow->GetWaitTextEmpty()) {
		switch (step)
		{
		case 7:

			break;
		case 0:
			bWindow[1].DrawExtend(5, 374, 120, 474);
			DrawFormatString(30, 384, BLACK, "戦う");
			DrawFormatString(30, 414, BLACK, "逃げる");
			bArrowG.Draw(10, 384 + bArrow[0] * 30);
			break;
		default:
			break;
		}
	}

	if (Input.GetKeyDown(Input.key.LSHIFT) || Input.GetKeyDown(Input.key.RSHIFT)) {
		for (int i = 0; i < 3; i++) {
			csQuestBase.character[i]->DrawStatusHenkaWindow(10 + i * 230, 265 + 35);
		}
		for (int i = 0; i < enAmount; i++) {
			if (enemy[i]->live) {
				enemy[i]->DrawStatusHenkaWindow(enemy[i]->x-4, enemy[i]->y);
			}
		}

	}

	for (int i = 0; i < vSkill[1].size(); i++)
	{
		DrawFormatString(0, i*30, BLACK, "%d", vSkill[1][i].targetNum);

	}
		

}


