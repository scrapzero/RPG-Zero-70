#include "MyScene.h"

bool KeyOK();
bool KeyCancel();
bool KeyRight();
bool KeyLeft();
bool KeyUp();
bool KeyDown();



CSQuestBase::CSQuestBase(int mapNum,Squest* bufVQ)
{
	this->mapNum = mapNum;
	vq = new Squest(*bufVQ);


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

	startAppearEn = 0;
	bossN = 1;


	FlipScene(new CSMap(*this), Flip::ROTATION_RIGHT);

	

}

CSQuestBase::~CSQuestBase()
{
	if (retire == false) {
		mySaveData->WriteSaveData();
	}
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
					if (appearEN >= GetRand(80) + 10) {
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
						if (GetRand(19) < 10) {
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
						if (GetRand(19) < 10) {

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
						if (GetRand(19) < 10) {
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
	stringstream bufSS;

	bufSS << "zero/back";
	bufSS << GetRand(1) + 1;
	bufSS << ".png";

	backGraph = bufSS.str().c_str();

	if (boss == true ) {
		enAmount = csQuestBase.vq->boss[bossNum - 1][0][1] + csQuestBase.vq->boss[bossNum - 1][1][1] + csQuestBase.vq->boss[bossNum - 1][2][1];
		if (csQuestBase.vq->bigBoss[bossNum - 1] == true) {
			enemy[enAmount / 2] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->boss[bossNum - 1][0][0]);
			bufI = 0;

			for (int j = 1; j < 3; j++) {
				for (int k = 0; k < csQuestBase.vq->boss[bossNum - 1][j][1]; k++) {
					if (bufI != enAmount) {
						enemy[bufI] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->boss[bossNum - 1][0][j]);
					
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
					enemy[bufI] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->boss[bossNum - 1][0][j]);
					bufI++;

				}
			}
		}

	}
	else
	{
		bufI = GetRand(19);
		if (bufI < 4) {
			enAmount = 2;
		}
		else if (bufI < 10) {
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
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[0]);
			}
			else if (bufI < 8) {
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[1]);
			}
			else if (bufI < 11)
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[2]);
			}
			else if (bufI < 13)
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[3]);
			}
			else if (bufI < 15)
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[4]);
			}
			else if (bufI < 17)
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[5]);
			}
			else if (bufI < 19)
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[6]);
			}
			else
			{
				enemy[i] = new CEnemy(csQuestBase.mySaveData, csQuestBase.vq->enemy[7]);
			}

		}
	}

	csQuestBase.textWindow->PushText("戦闘開始");

}

CSQuestBase::CSBattle::~CSBattle()
{
	for (int i = 0; i < enAmount; i++) {
		delete enemy[i];
		enemy[i] = NULL;
	}

}

void CSQuestBase::CSBattle::Loop()
{
	if (csQuestBase.textWindow->GetTextEmpty() && csQuestBase.textWindow->GetWaitTextEmpty()) {
		if (KeyOK()) {
			csQuestBase.mode[0] = 0;
			csQuestBase.mode[1] = 5;
			csQuestBase.RemoveScene(Flip::DOOR_COME_VERTICAL, 4);
		}
	}
	else
	{
		csQuestBase.textWindow->Loop();
	}

	if (KeyDown())
	{
		enemy[0]->GiveButuriDamge(csQuestBase.character[0], &csQuestBase.character[0]->normalAtack, 0, csQuestBase.textWindow);
		csQuestBase.character[0]->doku = true;
		enemy[0]->doku = true;
		enemy[0]->huchi = true;
		enemy[1]->doku = true;
	}

}

void CSQuestBase::CSBattle::Draw()
{
	backGraph.DrawExtend(0, 0, 704, 576);
	
	for (int i = 0; i < enAmount; i++) {
		enemy[i]->Draw(285 + i*140 - (enAmount/2) * 140 , 120,i%2);
		enemy[i]->DrawDamage();
	}

	for (int i = 0; i < 3; i++) {
		csQuestBase.character[i]->Draw(10 + i * 220, 285);
	}

	if (csQuestBase.textWindow->GetTextEmpty()==false || csQuestBase.textWindow->GetWaitTextEmpty() == false)
	{
		csQuestBase.textWindow->Draw();
	}

}


