#include "MyScene.h"

#include "Addons\COButton.h"

bool KeyOK();
bool KeyCancel();
bool KeyRight();
bool KeyLeft();
bool KeyUp();
bool KeyDown();

void CSTitle::Start() {
	//SetBackGround("pic/title.png");
	

	mySaveData = new CMySaveData(false);
	mySaveData->WriteSaveData();
	mySaveData->WriteSaveDataToOther();
	Back = "zero/title1.png";
	Arrow ="zero/titleArrow.png";
	exWindow = "zero/ExStart1.png";
	Music.Load(0, "zero/Music/title.mp3");
	arrowPoint = 0;
	musicF = false;
	exWindowOpen = false;

	//Music.Load(0, "test.wav");
}



void CSTitle::Loop() {
	if (exWindowOpen == false) {
		if (KeyOK()) {
			if (arrowPoint == 0) {
				Game.FlipScene(new CSTown(40, 34, 0), Flip::FADE_OUT_IN);
			}
			else {
				exWindowOpen = true;
			}

		}
		

		if (KeyUp() || KeyDown()) {
			arrowPoint++;
			arrowPoint %= 2;
		}

	}
	else {
		if (KeyCancel()) {
			exWindowOpen = false;
		}
	}

	if (musicF == false) {
		musicF = true;
		Music.PlayLoop(0);
	}

}

void CSTitle::Draw() {
	if (exWindowOpen == false) {
		Back.Draw();
		Arrow.Draw(165, 365 + arrowPoint * 110);
	}
	else {
		exWindow.Draw();
	}
}

void CSTitle::End() {

	delete mySaveData;
	mySaveData = NULL;
	Music.StopLoop(0);
	Music.Delete(0);

}