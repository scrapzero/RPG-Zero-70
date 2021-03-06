#include "Window.h"

using namespace std;

bool KeyOK();
bool KeyCancel();
bool KeyRight();
bool KeyLeft();
bool KeyUp();
bool KeyDown();

CTextWindow::CTextWindow(string text,...) {



	HandleKind = 0;
	TextHandle[0] = CreateFontToHandle("lr o¾©", 24, 9, DX_FONTTYPE_ANTIALIASING);
	//TextHandle[1] = CreateFontToHandle("lr ¾©", 24, 9, DX_FONTTYPE_NORMAL);


	window = "zero/TextWindow1.png";
	textArrow = "zero/TextArrow.png";
	intervalY = (int)GetFontSizeToHandle(TextHandle[HandleKind])+ 10;
	arrowInterval = 1;
	
	string buf = "";
	string kariBuf = "";
	string checkD = "%d";
	string checkN = "/n";
	string checkS = "%s";
	stringstream SNum;
	int num = 0;
	va_list args;
	va_start(args,text);

	while (text.empty() == false) {


		if (IsDBCSLeadByte(text[0]) != 0) {
			buf += text[0];
			buf += text[1];
			text.erase(0, 2);

			if (DxLib::GetDrawStringWidthToHandle(buf.c_str(), buf.size(), TextHandle[HandleKind]) > SWidth) {
				kariBuf = buf;

				buf.pop_back();
				buf.pop_back();

				texts.push(buf);
				buf = kariBuf;
				buf.erase(0, buf.size() - 2);
				kariBuf.clear();

			}

			continue;

		}

		if (text.size() >= 2) {
			if (text[0] == checkD[0] && text[1] == checkD[1]) {//%dÌmF
				text.erase(0, 2);
				buf += va_arg(args, string);
				continue;
			}
		}

		if (text.size() >= 2) {
			if (text[0] == checkN[0] && text[1] == checkN[1]) {// /nÌmF
				text.erase(0, 2);

				if (!buf.empty()) {

					texts.push(buf);
					buf.clear();
				}

				continue;
			}
		}

		if (text.size() >= 2) {
			if (text[0] == checkS[0] && text[1] == checkS[1]) {// %sÌmF
				text.erase(0, 2);
				buf += va_arg(args, string);

				continue;
			}
		}


		if (text.empty() == false) {
			buf += text[0];
			text.erase(0, 1);

			if (DxLib::GetDrawStringWidthToHandle(buf.c_str(), buf.size(), TextHandle[HandleKind]) > SWidth) {
				kariBuf = buf;

				buf.pop_back();

				texts.push(buf);
				buf = kariBuf;
				buf.erase(0, buf.size() - 1);
				kariBuf.clear();

			}
		}


	}





	if (buf.empty() == false) {
		texts.push(buf);
	}


	va_end(args);
	wordAmount = 0;
}

CTextWindow::~CTextWindow()
{
	DeleteFontToHandle(TextHandle[0]);
}

void CTextWindow::Start() {
}


void CTextWindow::PushText(string text,...) {

	textArrow = "zero/TextArrow.png";
	arrowInterval = 0;

	bool motomotDisplayMax = false;
	string buf = "";
	string kariBuf = "";
	string checkD = "%d";
	string checkN = "/n";
	string checkS = "%s";
	stringstream SNum;
	int num = 0;
	va_list args;
	va_start(args, text);
	if (display.size() >= 5) {
		motomotDisplayMax = true;
	}

	while (text.empty() == false) {


		if (IsDBCSLeadByte(text[0]) != 0) {
			buf += text[0];
			buf += text[1];
			text.erase(0, 2);

			if (DxLib::GetDrawStringWidthToHandle(buf.c_str(), buf.size(), TextHandle[HandleKind]) > SWidth) {
				kariBuf = buf;

				buf.pop_back();
				buf.pop_back();

				texts.push(buf);
				buf = kariBuf;
				buf.erase(0, buf.size() - 2);
				kariBuf.clear();

			}

			continue;

		}

		if (text.size() >= 2) {
			if (text[0] == checkD[0] && text[1] == checkD[1]) {//%dÌmF
				text.erase(0, 2);
				buf += va_arg(args, string);
				continue;
			}
		}

		if (text.size() >= 2) {
			if (text[0] == checkN[0] && text[1] == checkN[1]) {// /nÌmF
				text.erase(0, 2);

				if (!buf.empty()) {

					texts.push(buf);
					buf.clear();
				}

				continue;
			}
		}

		if (text.size() >= 2) {
			if (text[0] == checkS[0] && text[1] == checkS[1]) {// %sÌmF
				text.erase(0, 2);
				buf += va_arg(args, string);

				continue;
			}
		}


		if (text.empty() == false) {
			buf += text[0];
			text.erase(0, 1);

			if (DxLib::GetDrawStringWidthToHandle(buf.c_str(), buf.size(), TextHandle[HandleKind]) > SWidth) {
				kariBuf = buf;

				buf.pop_back();

				texts.push(buf);
				buf = kariBuf;
				buf.erase(0, buf.size() - 1);
				kariBuf.clear();

			}
		}


	}




	if (buf.empty() == false) {
		texts.push(buf);
	}


	va_end(args);
	wordAmount = 0;
	if (display.size() >= 5 && motomotDisplayMax==true) {
		display.pop_front();
		display.push_back(texts.front());
		texts.pop();
	}
}


void CTextWindow::Loop() {


	if (KeyOK()){
		if (wordAmount !=  display.back().size()) {
			wordAmount = display.back().size();
		}
		else if (texts.empty()) {
			display.clear();
			endDisplay = false;
		}
		else if (endDisplay == true ) {
		//else{
			if (display.empty() == false) {
				display.pop_front();
			}
			display.push_back(texts.front());
			texts.pop();
			wordAmount = 0;
			endDisplay = false;
		}
	}

	if (texts.empty()) {
		arrowInterval++;
		if (arrowInterval > 60) {
			arrowInterval = 0;
		}
	}


}



void CTextWindow::Draw() {


	window.DrawExtend(WLeft,WUp,WRight,WDown);
	string S[10];
	string kariS[10];
	int repeat=0;
	wordAmount++;
	endDisplay = false;
	intervalY = (int)GetFontSizeToHandle(TextHandle[HandleKind]) + 10;
	

	while (texts.empty() == false && display.size()<SHigh / intervalY) {
		display.push_back(texts.front());
		texts.pop();
	}



	for (auto i = display.begin(); i != display.end(); i++) {
		repeat++;
		if (repeat >= 10) {
			break;
		}
		kariS[repeat - 1] = *i;
		

		if (repeat == display.size()) {
			if (wordAmount >= kariS[repeat - 1].size()) {
				wordAmount = kariS[repeat - 1].size();
				endDisplay = true;
			}

			for (int k = 0; k < wordAmount; k++) {
				if (IsDBCSLeadByte(kariS[repeat - 1][k]) != 0) {
					S[repeat - 1] += kariS[repeat - 1][k];
					if (k + 1 < wordAmount) {
						S[repeat - 1] += kariS[repeat - 1][k + 1];
						k++;
					}
				}
				else {
					S[repeat - 1] += kariS[repeat - 1][k];
				}
			}
		}
		else {
			S[repeat - 1] = kariS[repeat - 1];
		}

		if (Input.GetKeyEnter(Input.key.RETURN) && Input.GetKeyEnter(Input.key.Z)) {
			int a;
			a = 0;
		}

	}
	




	for (int i = 0; i < repeat;i++) {
		DrawFormatStringToHandle(SLeft, SUp + intervalY*i,BLACK, TextHandle[HandleKind],"%s",S[i].c_str(),true);
	}

	if (texts.empty() && !display.empty()&&arrowInterval < 30) {
		textArrow(SRight, SUp + intervalY*(repeat - 1), true);
	}

}

bool CTextWindow::GetTextEmpty() {
	return display.empty();
}

bool CTextWindow::GetWaitTextEmpty()
{
	return texts.empty();
}

void CTextWindow::ChangeFont(int kind) {
	if (HandleKind = 0) {
		kind = 1;
	}

	HandleKind = kind;


}

void CTextWindow::TextClear()
{
		display.clear();
}



CEquipmentWindow::CEquipmentWindow(int equipmentKind, int num, int level): equipmentInfo("")
{
	this->equipmentKind = equipmentKind;
	Window = "zero/TextWindow2.png";
	skillInfo = new CSV("zero/ZeroData/Skill.csv");
	int bufI[2] = {};

	switch (equipmentKind)
	{

	case 0:	equipmentInfo = "zero/ZeroData/Soad.csv"; break;
	case 1: equipmentInfo = "zero/ZeroData/Arrow.csv"; break;
	case 2: equipmentInfo = "zero/ZeroData/Wand.csv"; break;
	case 3:	equipmentInfo = "zero/ZeroData/Shield.csv"; break;
	case 4: equipmentInfo = "zero/ZeroData/Protecter.csv"; break;
	case 5: equipmentInfo = "zero/ZeroData/Shoes.csv"; break;
	case 6: equipmentInfo = "zero/ZeroData/Accessory.csv"; break;
	}

	KindNum = num;
	Level = level;

	name = equipmentInfo[num - 1][1];
	HP = equipmentInfo[num - 1][2];
	MP = equipmentInfo[num - 1][3];
	Atc = equipmentInfo[num - 1][4];
	Def = equipmentInfo[num - 1][5];
	MAtc = equipmentInfo[num - 1][6];
	MDef = equipmentInfo[num - 1][7];
	Spd = equipmentInfo[num - 1][8];
	Hit = equipmentInfo[num - 1][9];
	Escape = equipmentInfo[num - 1][10];
	Luck = equipmentInfo[num - 1][11];


	if (equipmentKind <= 2) {
		skillNum[0]= equipmentInfo[num - 1][19];
		skillNum[1] = equipmentInfo[num - 1][20];
		ElementNum = equipmentInfo[num - 1][12];
		FireDef = equipmentInfo[num - 1][13];
		WoodDef = equipmentInfo[num - 1][14];
		WaterDef = equipmentInfo[num - 1][15];
		LightDef = equipmentInfo[num - 1][16];
		DarkDef = equipmentInfo[num - 1][17];
		SellMoney = equipmentInfo[num - 1][18];

		skillName[0] = (*skillInfo)[skillNum[0]-1][1];
		skillMP[0] = (*skillInfo)[skillNum[0]-1][2];
		skillPower[0] = (*skillInfo)[skillNum[0]-1][10];
		skillElementNum[0] = (*skillInfo)[skillNum[0]-1][3];
		bufI[0] = (*skillInfo)[skillNum[0]-1][4];
		skillExperience[0] = (*skillInfo)[skillNum[0]-1][19];

		skillName[1] = (*skillInfo)[skillNum[1]-1][1];
		skillMP[1] = (*skillInfo)[skillNum[1]-1][2];
		skillPower[1] = (*skillInfo)[skillNum[1]-1][10];
		skillElementNum[1] = (*skillInfo)[skillNum[1]-1][3];
		bufI[1] = (*skillInfo)[skillNum[1] - 1][4];
		skillExperience[1] = (*skillInfo)[skillNum[1]-1][19];
		for (int i = 0; i < 2; i++) {
			switch (bufI[i])
			{
			case 0: skillPMode[i] = "_[WÁ"; break;
			case 1: skillPMode[i] = "í_¸­"; break;
			case 2: skillPMode[i] = "¨Uã¸"; break;
			case 3: skillPMode[i] = "¨hã¸"; break;
			case 4: skillPMode[i] = "Uã¸"; break;
			case 5: skillPMode[i] = "hã¸"; break;
			case 6: skillPMode[i] = "¬xã¸"; break;
			case 7: skillPMode[i] = "½ã¸"; break;
			case 8: skillPMode[i] = "ñðã¸"; break;
			case 9: skillPMode[i] = "^ã¸"; break;
			case 10: skillPMode[i] = "ñÊÁ"; break;
			case 11: skillPMode[i] = "æ§"; break;
			case 12: skillPMode[i] = "ñÁ"; break;
			case 13: skillPMode[i] = "m¦ã¸"; break;
			case 14: skillPMode[i] = "ÁïMP¸­"; break;
			case 15: skillPMode[i] = "ê"; break;
			}
		}

	}
	else {

		skillNum[0] = equipmentInfo[num - 1][18];
		FireDef = equipmentInfo[num - 1][12];
		WoodDef = equipmentInfo[num - 1][13];
		WaterDef = equipmentInfo[num - 1][14];
		LightDef = equipmentInfo[num - 1][15];
		DarkDef = equipmentInfo[num - 1][16];
		SellMoney = equipmentInfo[num - 1][17];
		skillName[0] = (*skillInfo)[skillNum[0] - 1][1];
		skillMP[0] = (*skillInfo)[skillNum[0] - 1][2];
		skillPower[0] = (*skillInfo)[skillNum[0] - 1][10];
		skillElementNum[0] = (*skillInfo)[skillNum[0] - 1][3];
		bufI[0] = (*skillInfo)[skillNum[0] - 1][4];
		skillExperience[0] = (*skillInfo)[skillNum[0] - 1][19];

		switch (bufI[0]) {
		case 0: skillPMode[0] = "_[WÁ"; break;
		case 1: skillPMode[0] = "í_¸­"; break;
		case 2: skillPMode[0] = "¨Uã¸"; break;
		case 3: skillPMode[0] = "¨hã¸"; break;
		case 4: skillPMode[0] = "Uã¸"; break;
		case 5: skillPMode[0] = "hã¸"; break;
		case 6: skillPMode[0] = "¬xã¸"; break;
		case 7: skillPMode[0] = "½ã¸"; break;
		case 8: skillPMode[0] = "ñðã¸"; break;
		case 9: skillPMode[0] = "^ã¸"; break;
		case 10: skillPMode[0] = "ñÊÁ"; break;
		case 11: skillPMode[0] = "æ§"; break;
		case 12: skillPMode[0] = "ñÁ"; break;
		case 13: skillPMode[0] = "m¦ã¸"; break;
		case 14: skillPMode[0] = "ÁïMP¸­"; break;
		case 15: skillPMode[0] = "ê"; break;
		}

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
	SellMoney *= (1.0 + 0.1*Level);


	switch (ElementNum)
	{
	case 0: Element = "³"; break;
	case 1: Element = "Î"; break;
	case 2: Element = "Ø"; break;
	case 3: Element = ""; break;
	case 4: Element = "õ"; break;
	case 5: Element = "Å"; break;
	default: break;
	}

	switch (skillElementNum[0])
	{
	case 0: skillElement[0] = "³"; break;
	case 1: skillElement[0] = "Î"; break;
	case 2: skillElement[0] = "Ø"; break;
	case 3: skillElement[0] = ""; break;
	case 4: skillElement[0] = "õ"; break;
	case 5: skillElement[0] = "Å"; break;
	default: break;
	}

	switch (skillElementNum[1])
	{
	case 0: skillElement[1] = "³"; break;
	case 1: skillElement[1] = "Î"; break;
	case 2: skillElement[1] = "Ø"; break;
	case 3: skillElement[1] = ""; break;
	case 4: skillElement[1] = "õ"; break;
	case 5: skillElement[1] = "Å"; break;
	default: break;
	}



}

CEquipmentWindow::~CEquipmentWindow()
{
	delete skillInfo;
	skillInfo = NULL;
}

void CEquipmentWindow::ChangeKind( int num, int level)
{

	int bufI[2] = {};
	KindNum = num;
	Level = level;

	name = equipmentInfo[num - 1][1];
	HP = equipmentInfo[num - 1][2];
	MP = equipmentInfo[num - 1][3];
	Atc = equipmentInfo[num - 1][4];
	Def = equipmentInfo[num - 1][5];
	MAtc = equipmentInfo[num - 1][6];
	MDef = equipmentInfo[num - 1][7];
	Spd = equipmentInfo[num - 1][8];
	Hit = equipmentInfo[num - 1][9];
	Escape = equipmentInfo[num - 1][10];
	Luck = equipmentInfo[num - 1][11];

	if (equipmentKind <= 2) {
		skillNum[0] = equipmentInfo[num - 1][19];
		skillNum[1] = equipmentInfo[num - 1][20];
		ElementNum = equipmentInfo[num - 1][12];
		FireDef = equipmentInfo[num - 1][13];
		WoodDef = equipmentInfo[num - 1][14];
		WaterDef = equipmentInfo[num - 1][15];
		LightDef = equipmentInfo[num - 1][16];
		DarkDef = equipmentInfo[num - 1][17];
		SellMoney = equipmentInfo[num - 1][18];

		skillName[0] = (*skillInfo)[skillNum[0] - 1][1];
		skillMP[0] = (*skillInfo)[skillNum[0] - 1][2];
		skillPower[0] = (*skillInfo)[skillNum[0] - 1][10];
		skillElementNum[0] = (*skillInfo)[skillNum[0] - 1][3];
		bufI[0] = (*skillInfo)[skillNum[0] - 1][4];
		skillExperience[0] = (*skillInfo)[skillNum[0] - 1][19];

		skillName[1] = (*skillInfo)[skillNum[1] - 1][1];
		skillMP[1] = (*skillInfo)[skillNum[1] - 1][2];
		skillPower[1] = (*skillInfo)[skillNum[1] - 1][10];
		skillElementNum[1] = (*skillInfo)[skillNum[1] - 1][3];
		bufI[1] = (*skillInfo)[skillNum[1] - 1][4];
		skillExperience[1] = (*skillInfo)[skillNum[1] - 1][19];
		for (int i = 0; i < 2; i++) {
			switch (bufI[i]) {
			case 0: skillPMode[i] = "_[WÁ"; break;
			case 1: skillPMode[i] = "í_¸­"; break;
			case 2: skillPMode[i] = "¨Uã¸"; break;
			case 3: skillPMode[i] = "¨hã¸"; break;
			case 4: skillPMode[i] = "Uã¸"; break;
			case 5: skillPMode[i] = "hã¸"; break;
			case 6: skillPMode[i] = "¬xã¸"; break;
			case 7: skillPMode[i] = "½ã¸"; break;
			case 8: skillPMode[i] = "ñðã¸"; break;
			case 9: skillPMode[i] = "^ã¸"; break;
			case 10: skillPMode[i] = "ñÊÁ"; break;
			case 11: skillPMode[i] = "æ§"; break;
			case 12: skillPMode[i] = "ñÁ"; break;
			case 13: skillPMode[i] = "m¦ã¸"; break;
			case 14: skillPMode[i] = "ÁïMP¸­"; break;
			case 15: skillPMode[i] = "ê"; break;
			}
		}

	}
	else {

		skillNum[0] = equipmentInfo[num - 1][18];
		FireDef = equipmentInfo[num - 1][12];
		WoodDef = equipmentInfo[num - 1][13];
		WaterDef = equipmentInfo[num - 1][14];
		LightDef = equipmentInfo[num - 1][15];
		DarkDef = equipmentInfo[num - 1][16];
		SellMoney = equipmentInfo[num - 1][17];
		skillName[0] = (*skillInfo)[skillNum[0] - 1][1];
		skillMP[0] = (*skillInfo)[skillNum[0] - 1][2];
		skillPower[0] = (*skillInfo)[skillNum[0] - 1][10];
		skillElementNum[0] = (*skillInfo)[skillNum[0] - 1][3];
		bufI[0] = (*skillInfo)[skillNum[0] - 1][4];
		skillExperience[0] = (*skillInfo)[skillNum[0] - 1][19];

		switch (bufI[0]) {
		case 0: skillPMode[0] = "_[WÁ"; break;
		case 1: skillPMode[0] = "í_¸­"; break;
		case 2: skillPMode[0] = "¨Uã¸"; break;
		case 3: skillPMode[0] = "¨hã¸"; break;
		case 4: skillPMode[0] = "Uã¸"; break;
		case 5: skillPMode[0] = "hã¸"; break;
		case 6: skillPMode[0] = "¬xã¸"; break;
		case 7: skillPMode[0] = "½ã¸"; break;
		case 8: skillPMode[0] = "ñðã¸"; break;
		case 9: skillPMode[0] = "^ã¸"; break;
		case 10: skillPMode[0] = "ñÊÁ"; break;
		case 11: skillPMode[0] = "æ§"; break;
		case 12: skillPMode[0] = "ñÁ"; break;
		case 13: skillPMode[0] = "m¦ã¸"; break;
		case 14: skillPMode[0] = "ÁïMP¸­"; break;
		case 15: skillPMode[0] = "ê"; break;
		}

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
	SellMoney *= (1.0 + 0.1*Level);
	FireDef *= (1.0 + 0.1*Level);
	WoodDef *= (1.0 + 0.1*Level);
	WaterDef *= (1.0 + 0.1*Level);
	LightDef *= (1.0 + 0.1*Level);
	DarkDef *= (1.0 + 0.1*Level);


	switch (ElementNum)
	{
	case 0: Element = "³"; break;
	case 1: Element = "Î"; break;
	case 2: Element = "Ø"; break;
	case 3: Element = ""; break;
	case 4: Element = "õ"; break;
	case 5: Element = "Å"; break;
	}

	switch (skillElementNum[0])
	{
	case 0: skillElement[0] = "³"; break;
	case 1: skillElement[0] = "Î"; break;
	case 2: skillElement[0] = "Ø"; break;
	case 3: skillElement[0] = ""; break;
	case 4: skillElement[0] = "õ"; break;
	case 5: skillElement[0] = "Å"; break;
	default: break;
	}

	switch (skillElementNum[1])
	{
	case 0: skillElement[1] = "³"; break;
	case 1: skillElement[1] = "Î"; break;
	case 2: skillElement[1] = "Ø"; break;
	case 3: skillElement[1] = ""; break;
	case 4: skillElement[1] = "õ"; break;
	case 5: skillElement[1] = "Å"; break;
	default: break;
	}



}

void CEquipmentWindow::Draw()
{
	Window(0, 376);
	
	if (equipmentKind<=2) {
		DrawFormatString(16, 395, BLACK, "%s   No.%d  lF%d@®«:%s", name.c_str(),KindNum, SellMoney, Element.c_str());
	}
	else {
		DrawFormatString(16, 395, BLACK, "%s     lF%d", name.c_str(), SellMoney);
	}
	DrawFormatString(16,420, BLACK, "Xe[^Xã¸l:");
	DrawFormatString(175, 420, BLACK, "HP %d  MP %d  U %d   h %d  U %d  h %d",HP, MP,Atc,Def,MAtc,MDef);
	DrawFormatString(175, 440, BLACK, "Îh %d  Øh %d  h %d  õh %d  Åh %d",FireDef,WoodDef,WaterDef,LightDef,DarkDef);
	DrawFormatString(175, 460, BLACK, "¬ %d  ½ %d  ñð %d  ^ %d", Spd,Hit,Escape,Luck);
	DrawFormatString(16, 485, BLACK, "Z1 %sFÁïMP %d   ÐÍ %d@®« %s  PÓ°ÄÞ %s", skillName[0].c_str(), skillMP[0], skillPower[0], skillElement[0].c_str(),skillPMode[0].c_str());
	DrawFormatString(16, 505, BLACK,"ÁêøÊ:%s",skillExperience[0].c_str());
	if (equipmentKind <= 2) {
		DrawFormatString(16, 525, BLACK, "Z2 %sFÁïMP %d   ÐÍ %d@®« %s  PÓ°ÄÞ %s", skillName[1].c_str(), skillMP[1], skillPower[1], skillElement[1].c_str(),skillPMode[1].c_str());
		DrawFormatString(16, 545, BLACK, "ÁêøÊ:%s", skillExperience[1].c_str());
	}

}

CYesNoWindow::CYesNoWindow(bool * RF, std::string Text, bool yes,int x,int y)
{
	Window[0] = "zero/NoWindow.png";
	Window[1] = "zero/YesWindow.png";
	this->RF = RF;
	this->Text = Text;
	this->yes = yes;
	this->x = x;
	this->y = y;
}

void CYesNoWindow::Loop()
{
	if (KeyOK()) {
		if (yes == true) {
			*RF = true;
		}
		else{
			*RF = false;
		}
	}

	if (KeyUp() || KeyDown()) {
		if (yes == true) {
			yes = false;
		}
		else {
			yes = true;
		}
	}

}

void CYesNoWindow::Draw()
{
	if (yes == false) {
		Window[0](x, y);
	}
	else {
		Window[1](x, y);
	}

	DrawFormatString(x + 10, y + 25, BLACK, "%s", Text.c_str());

}

CAmountGetWindow::CAmountGetWindow(std::string Text, int x, int y,int max)
{
	Window = "zero/GetAmountWindow.png";
	this->Text = Text;
	this->x = x;
	this->y = y;
	this->max = max;
	amount = 1;
	if (max > 99) {
		max = 99;
	}
}

void CAmountGetWindow::Loop()
{
	if (KeyUp() == true && amount < max) {
		amount++;
	}
	if (KeyDown() == true && amount >1) {
		amount--;
	}

	if (KeyRight() == true && amount < max) {
		amount+=10;
	}
	if (KeyLeft() == true && amount >1) {
		amount-=10;
	}

	if (amount > max){
		amount = max;
	}

	if (amount < 1) {
		amount = 1;
	}

}

void CAmountGetWindow::Draw()
{
	Window(x, y);

	DrawFormatString(x + 10, y + 25, BLACK, "%s", Text.c_str());

	DrawFormatString(x + 30, y + 55, BLACK, "~%d", amount);
}

int CAmountGetWindow::GetAmount()
{
	return amount;
}


CHaniwaWindow::CHaniwaWindow(CMySaveData * savedata, int kind)
{
	mySaveData = savedata;
	haniwaInfo = new CSV("zero/ZeroData/Haniwa.csv");
	Window = "zero/TextWindow4.png";
	float bufFlo;
	int bufI;

	KindNum = kind;
	Level = mySaveData->haniwaLevel[kind];

	name = (*haniwaInfo)[kind][1];

	for (int i = 0; i < 15; i++) {
		bufI = (*haniwaInfo)[kind][2 + i];
		bufFlo = (*haniwaInfo)[kind][17 + i];
		switch (i)
		{
		case 0:
			HP = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][0];
			break;
		case 1:
			MP = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][1];
			break;
		case 2:
			Atc = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][2];
			break;
		case 3:
			Def = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][3];
			break;
		case 4:
			MAtc = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][4];
			break;
		case 5:
			MDef = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][5];
			break;
		case 6:
			Spd = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][6];
			break;
		case 7:
			Hit = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][7];
			break;
		case 8:
			Escape = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][8];
			break;
		case 9:
			Luck = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][9];
			break;
		case 10:
			FireDef = bufI + bufFlo*Level;
			break;
		case 11:
			WoodDef = bufI + bufFlo*Level;
			break;
		case 12:
			WaterDef = bufI + bufFlo*Level;
			break;
		case 13:
			LightDef = bufI + bufFlo*Level;
			break;
		case 14:
			DarkDef = bufI + bufFlo*Level;
			break;

		default:
			break;
		}
	}



}

CHaniwaWindow::~CHaniwaWindow()
{
	delete haniwaInfo;
	haniwaInfo = NULL;
	mySaveData = NULL;


}

void CHaniwaWindow::Draw()
{
	Window.DrawExtend(4, 375, 700, 570);
	DrawFormatString(40, 550, BLACK, "()ÌÍnjK`ÉæévXl");

	DrawFormatString(20, 400, BLACK, "%s  Level:%d", name.c_str(),Level);
	DrawFormatString(20, 430, BLACK, "HP:%d(%d)  MP:%d(%d) ", HP,mySaveData->haniStatusPlus[KindNum][0],MP, mySaveData->haniStatusPlus[KindNum][1]);
	DrawFormatString(20, 460, BLACK, "U:%d(%d) @hF%d(%d)  U:%d(%d) @hF%d(%d) ", Atc,mySaveData->haniStatusPlus[KindNum][2], Def,mySaveData->haniStatusPlus[KindNum][3], MAtc, mySaveData->haniStatusPlus[KindNum][4], MDef, mySaveData->haniStatusPlus[KindNum][5]);
	DrawFormatString(20, 490, BLACK, "¬:%d(%d) @½F%d(%d)  ñð:%d(%d) @^F%d(%d) ", Spd, mySaveData->haniStatusPlus[KindNum][6], Hit, mySaveData->haniStatusPlus[KindNum][7], Escape, mySaveData->haniStatusPlus[KindNum][8], Luck, mySaveData->haniStatusPlus[KindNum][9]);
	DrawFormatString(20, 520, BLACK, "h:%d@ØhF%d h:%d@õhF%d@ÅhF%d", FireDef, WoodDef, WaterDef, LightDef, DarkDef);

}

void CHaniwaWindow::ChangeKind(int kind)
{

	float bufFlo;
	int bufI;

	KindNum = kind;
	Level = mySaveData->haniwaLevel[kind];

	name = (*haniwaInfo)[kind][1];

	for (int i = 0; i < 15; i++) {
		bufI = (*haniwaInfo)[kind][2 + i];
		bufFlo = (*haniwaInfo)[kind][17 + i];
		switch (i)
		{
		case 0:
			HP = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][0];
			break;
		case 1:
			MP = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][1];
			break;
		case 2:
			Atc = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][2];
			break;
		case 3:
			Def = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][3];
			break;
		case 4:
			MAtc = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][4];
			break;
		case 5:
			MDef = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][5];
			break;
		case 6:
			Spd = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][6];
			break;
		case 7:
			Hit = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][7];
			break;
		case 8:
			Escape = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][8];
			break;
		case 9:
			Luck = bufI + bufFlo*Level + mySaveData->haniStatusPlus[KindNum][9];
			break;
		case 10:
			FireDef = bufI + bufFlo*Level;
			break;
		case 11:
			WoodDef = bufI + bufFlo*Level;
			break;
		case 12:
			WaterDef = bufI + bufFlo*Level;
			break;
		case 13:
			LightDef = bufI + bufFlo*Level;
			break;
		case 14:
			DarkDef = bufI + bufFlo*Level;
			break;

		default:
			break;
		}
	}


}


CSkillWindow::CSkillWindow(int num)
{
	this->num = num;
	windowGraph= "zero/TextWindow4.png";
	jikiSkill = new CSV("zero/ZeroData/Skill.csv");
	
}

CSkillWindow::~CSkillWindow()
{
	delete jikiSkill;
	jikiSkill = NULL;

}


void CSkillWindow::Draw(int y)
{
	int bufI[5];
	string bufS;
	string buffS;

	windowGraph.DrawExtend(4, y, 700, y+120);

	bufS = (*jikiSkill)[num - 1][1];
	bufI[0] = (*jikiSkill)[num - 1][2];

	bufI[1] = (*jikiSkill)[num - 1][4];
	switch (bufI[1])
	{
	case 0: buffS = "_[WÁ"; break;
	case 1: buffS = "í_¸­"; break;
	case 2: buffS = "¨Uã¸"; break;
	case 3: buffS = "¨hã¸"; break;
	case 4: buffS = "Uã¸"; break;
	case 5: buffS = "hã¸"; break;
	case 6: buffS = "¬xã¸"; break;
	case 7: buffS = "½ã¸"; break;
	case 8: buffS = "ñðã¸"; break;
	case 9: buffS = "^ã¸"; break;
	case 10: buffS = "ñÊÁ"; break;
	case 11: buffS = "æ§"; break;
	case 12: buffS = "ñÁ"; break;
	case 13: buffS = "m¦ã¸"; break;
	case 14: buffS = "ÁïMP¸­"; break;
	case 15: buffS = "ê"; break;
	}

	DrawFormatString(40, y+20, BLACK, "%s  ÁïMP:%d  P[h:%s", bufS.c_str(), bufI[0], buffS.c_str());

	bufI[0] = (*jikiSkill)[num - 1][3];

	switch (bufI[0])
	{
	case 0: bufS = "³"; break;
	case 1: bufS = "Î"; break;
	case 2: bufS = "Ø"; break;
	case 3: bufS = ""; break;
	case 4: bufS = "õ"; break;
	case 5: bufS = "Å"; break;
	}

	

	bufI[1] = (*jikiSkill)[num - 1][5];
	bufI[2] = (*jikiSkill)[num - 1][10];

	DrawFormatString(40, y+50, BLACK, "®«:%s ñ:%d ÐÍ:%d", bufS.c_str(), bufI[1], bufI[2]);


	bufS = (*jikiSkill)[num - 1][19];

	DrawFormatString(40, y+80, BLACK, "à¾:%s", bufS.c_str());
}

void CSkillWindow::ChangeNum(int num)
{
	this->num = num;
}

CHaniwaSkillWindow::CHaniwaSkillWindow(int num, int haniLevel)
{
	this->num = num;
	windowGraph= "zero/TextWindow4.png";
	haniSkill = new CSV("zero/ZeroData/HaniwaSkill.csv");
	this->haniLevel = haniLevel;
	if (haniLevel < 30) {
		lvChange = 0;
	}
	else if (haniLevel < 50) {
		lvChange = 1;
	}
	else if (haniLevel < 70) {
		lvChange = 2;
	}
	else {
		lvChange = 3;
	}

}

CHaniwaSkillWindow::~CHaniwaSkillWindow()
{
	delete haniSkill;
	haniSkill = NULL;

}

void CHaniwaSkillWindow::Draw() {
	int bufI[5];
	string bufS;

	windowGraph.DrawExtend(4, 370, 700, 570);

	bufS = (*haniSkill)[num - 1][1];
	bufI[0]= (*haniSkill)[num - 1][2+lvChange];
	DrawFormatString(40,390,BLACK,"%s  ÁïMP:%d", bufS.c_str(),bufI[0]);

	bufI[0]= (*haniSkill)[num - 1][6];

	switch (bufI[0])
	{
	case 0: bufS = "³"; break;
	case 1: bufS = "Î"; break;
	case 2: bufS = "Ø"; break;
	case 3: bufS = ""; break;
	case 4: bufS = "õ"; break;
	case 5: bufS = "Å"; break;
	}

	bufI[1] = (*haniSkill)[num - 1][7];
	bufI[2] = (*haniSkill)[num - 1][12+lvChange];

	DrawFormatString(40, 430, BLACK, "®«:%s ñ:%d ÐÍ:%d", bufS.c_str(), bufI[1],bufI[2]);


	bufS = (*haniSkill)[num - 1][30];

	DrawFormatString(40, 470, BLACK, "à¾:%s", bufS.c_str());

}

void CHaniwaSkillWindow::Draw(int y)
{
	int bufI[5];
	string bufS;

	windowGraph.DrawExtend(4, y, 700, y+120);

	bufS = (*haniSkill)[num - 1][1];
	bufI[0] = (*haniSkill)[num - 1][2 + lvChange];
	DrawFormatString(40, y+20, BLACK, "%s  ÁïMP:%d", bufS.c_str(), bufI[0]);

	bufI[0] = (*haniSkill)[num - 1][6];

	switch (bufI[0])
	{
	case 0: bufS = "³"; break;
	case 1: bufS = "Î"; break;
	case 2: bufS = "Ø"; break;
	case 3: bufS = ""; break;
	case 4: bufS = "õ"; break;
	case 5: bufS = "Å"; break;
	}

	bufI[1] = (*haniSkill)[num - 1][7];
	bufI[2] = (*haniSkill)[num - 1][12 + lvChange];

	DrawFormatString(40, y+50, BLACK, "®«:%s ñ:%d ÐÍ:%d", bufS.c_str(), bufI[1], bufI[2]);


	bufS = (*haniSkill)[num - 1][30];

	DrawFormatString(40, y+80, BLACK, "à¾:%s", bufS.c_str());
}

void CHaniwaSkillWindow::ChangeNum(int num)
{
	this->num = num;
}

void CHaniwaSkillWindow::ChangeLevel(int level)
{
	this->haniLevel = level;
	if (haniLevel < 30) {
		lvChange = 0;
	}
	else if (haniLevel < 50) {
		lvChange = 1;
	}
	else if (haniLevel < 70) {
		lvChange = 2;
	}
	else {
		lvChange = 3;
	}
}

CExplainWindow::CExplainWindow(int kind)
{
	lookPage = 0;
	amountPage = 0;

	switch (kind)
	{
	case 0:
		amountPage = 1;
		exGraph[0] = "zero/ExKihon1.png";
		break;
	case 1:
		amountPage = 1;
		exGraph[0] = "zero/ExTown1.png";
		break;
	case 2:
		amountPage = 2;
		exGraph[0] = "zero/ExHaniwa1.png";
		exGraph[1] = "zero/ExHaniwa2.png";
		break;
	case 3:
		amountPage = 1;
		exGraph[0] = "zero/ExEquipment1.png";
		break;
	case 4:
		amountPage = 2;
		exGraph[0] = "zero/ExItem1.png";
		exGraph[1] = "zero/ExItem2.png";
		break;
	case 5:
		amountPage = 4;
		exGraph[0] = "zero/ExSkill1.png";
		exGraph[1] = "zero/ExSkill2.png";
		exGraph[2] = "zero/ExSkill3.png";
		exGraph[3] = "zero/ExSkill4.png";
		break;
	case 6:
		amountPage = 2;
		exGraph[0] = "zero/ExQuest1.png";
		exGraph[1] = "zero/ExQuest2.png";
		break;
	case 7:
		amountPage = 3;
		exGraph[0] = "zero/ExBattle1.png";
		exGraph[1] = "zero/ExBattle2.png";
		exGraph[2] = "zero/ExBattle3.png";
		break;
	default:
		break;
	}

}

void CExplainWindow::Loop()
{
	if (KeyRight() && lookPage<amountPage-1) {
		lookPage++;
	}
	if (KeyLeft() && lookPage>0) {
		lookPage--;
	}

}

void CExplainWindow::Draw()
{
	exGraph[lookPage].Draw();

	DrawFormatString(20, 555, BLACK, "XÍback spaceL[ÅÂ¶éB@©%d/%d¨", lookPage + 1, amountPage);

}
