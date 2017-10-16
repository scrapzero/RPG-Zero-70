#include "MyScene.h"

#include "Addons\COButton.h"

bool KeyOK();
bool KeyCancel();
bool KeyRight();
bool KeyLeft();
bool KeyUp();
bool KeyDown();

void CSTitle::Start() {
	SetBackGround("pic/title.png");
	/*textWindow = new CTextWindow("TITLE����[/nfhdh��������/n�����ӂ�/n����������/n������/n������/n�����ӂ�����");
	Map = MCE("");
	product = new CProduce(mySaveData, 0);
	equipmentManager = new CEquipmentManager(mySaveData,0);
	ItemManager = new CItemManager(1, mySaveData);*/

	mySaveData = new CMySaveData(false);
	mySaveData->WriteSaveData();
	mySaveData->WriteSaveDataToOther();
	//Music.Load(0, "test.wav");
}



void CSTitle::Loop() {
	if (KeyOK()) {
		Game.FlipScene(new CSTown(40,34,0),Flip::FADE_OUT_IN);
		//equipmentManager->PushEquipment(0, 1, 3);
		//equipmentManager->PushEquipment(0, 2, 100);
	}
	if (Input.GetKeyEnter(Input.key.C)) {
		//Town.FlipScene(new CSTown(),Flip::FADE_OUT_IN);
		//equipmentManager->SellEquipment();
	}

	//textWindow->Loop();
	//equipmentManager->LoopWindow();
	//ItemManager->WindowLoop();
	//product->WindowLoop();
}

void CSTitle::Draw() {
	//textWindow->Draw();
	//equipmentManager->DrawWindow();
	//ItemManager->WindowDraw();
	//product->WindowDraw();
}

void CSTitle::End() {

	delete mySaveData;
	mySaveData = NULL;

}