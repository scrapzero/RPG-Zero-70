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
	TextHandle[0] = CreateFontToHandle("‚l‚r ‚o–¾’©", 24, 9, DX_FONTTYPE_ANTIALIASING);
	//TextHandle[1] = CreateFontToHandle("‚l‚r –¾’©", 24, 9, DX_FONTTYPE_NORMAL);


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

		if (text.size()>=2 ) {
			 if (text[0] == checkD[0] && text[1] == checkD[1]) {//%d‚ÌŠm”F
				text.erase(0, 2);
				buf += va_arg(args,string);
				continue;
			 }
		 }

		if (text.size() >= 2) {
			if (text[0] == checkN[0] && text[1] == checkN[1]) {// /n‚ÌŠm”F
				text.erase(0, 2);

				if (!buf.empty()) {

					texts.push(buf);
					buf.clear();
				}

				continue;
			}
		}

		if (text.size() >= 2) {
			if (text[0] == checkS[0] && text[1] == checkS[1]) {// /n‚ÌŠm”F
				text.erase(0, 2);
				buf += va_arg(args, string);

				continue;
			}
		}


		if (buf.empty() == true) {
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

	string buf = "";
	string kariBuf = "";
	string checkD = "%d";
	string checkN = "/n";
	string checkS = "%s";
	stringstream SNum;
	int num = 0;
	va_list args;
	va_start(args, text);

	while (text.empty() == false) {


		if (IsDBCSLeadByte(text[0]) != 0) {
			buf += text[0];
			buf += text[1];
			text.erase(0, 2);

			if (DxLib::GetDrawStringWidthToHandle(buf.c_str(), buf.size(),TextHandle[HandleKind]) > SWidth) {
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
			if (text[0] == checkD[0] && text[1] == checkD[1]) {//%d‚ÌŠm”F
				text.erase(0, 2);
				num = va_arg(args, int);
				SNum << num;
				buf += SNum.str();
				continue;
			}
		}

		if (text.size() >= 2) {
			if (text[0] == checkN[0] && text[1] == checkN[1]) {// /n‚ÌŠm”F
				text.erase(0, 2);

				if (!buf.empty()) {

					texts.push(buf);
					buf.clear();
				}

				continue;
			}
		}

		if (text.size() >= 2) {
			if (text[0] == checkS[0] && text[1] == checkS[1]) {//%d‚ÌŠm”F
				text.erase(0, 2);
				buf += va_arg(args, string);
				continue;
			}
		}

		if (buf.empty()==true) {
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


	while (texts.empty() == false && display.size()<SHigh / intervalY) {
		display.push_back(texts.front());
		texts.pop();
	}

	va_end(args);
	wordAmount = 0;
}


void CTextWindow::Loop() {


	if (KeyOK()) {
		if (texts.empty()) {
			display.clear();
		}
		else if (endDisplay == true ) {
			display.pop_front();
			display.push_back(texts.front());
			texts.pop();
			wordAmount = 0;
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



	for (auto i = display.begin(); i != display.end();i++) {
		repeat++;
		kariS[repeat-1] = *i;

		if (repeat ==display.size()) {
			if (wordAmount >= kariS[repeat - 1].size()) {
				wordAmount = kariS[repeat - 1].size();
				endDisplay = true;
			}

			for (int k = 0; k < wordAmount; k++) {
				if (IsDBCSLeadByte(kariS[repeat - 1][0]) != 0) {
					S[repeat-1] += kariS[repeat - 1][k];
					S[repeat-1] += kariS[repeat - 1][k+1];
					k++;
				}
				else {
					S[repeat-1] += kariS[repeat - 1][k];
				}
			}
		}
		else {
			S[repeat-1] = kariS[repeat - 1];
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
	switch (equipmentKind)
	{

	case 0:	equipmentInfo = "zero/ZeroData/Soad.txt"; break;
	case 1: equipmentInfo = "zero/ZeroData/Arrow.txt"; break;
	case 2: equipmentInfo = "zero/ZeroData/Wand.txt"; break;
	case 3:	equipmentInfo = "zero/ZeroData/Shield.txt"; break;
	case 4: equipmentInfo = "zero/ZeroData/Protecter.txt"; break;
	case 5: equipmentInfo = "zero/ZeroData/Shoes.txt"; break;
	case 6: equipmentInfo = "zero/ZeroData/Accessory.txt"; break;
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
		ElementNum = equipmentInfo[num - 1][12];
		FireDef = equipmentInfo[num - 1][13];
		WoodDef = equipmentInfo[num - 1][14];
		WaterDef = equipmentInfo[num - 1][15];
		LightDef = equipmentInfo[num - 1][16];
		DarkDef = equipmentInfo[num - 1][17];
		SellMoney = equipmentInfo[num - 1][18];
		skillName[0] = equipmentInfo[num - 1][19];
		skillMP[0] = equipmentInfo[num - 1][20];
		skillPower[0] = equipmentInfo[num - 1][21];
		skillElementNum[0] = equipmentInfo[num - 1][22];
		skillRatioKind[0] = equipmentInfo[num - 1][23];
		skillExperience[0] = equipmentInfo[num - 1][24];
		skillName[1] = equipmentInfo[num - 1][25];
		skillMP[1] = equipmentInfo[num - 1][26];
		skillPower[1] = equipmentInfo[num - 1][27];
		skillElementNum[1] = equipmentInfo[num - 1][28];
		skillRatioKind[1] = equipmentInfo[num - 1][29];
		skillExperience[1] = equipmentInfo[num - 1][30];
	}
	else {
		FireDef = equipmentInfo[num - 1][12];
		WoodDef = equipmentInfo[num - 1][13];
		WaterDef = equipmentInfo[num - 1][14];
		LightDef = equipmentInfo[num - 1][15];
		DarkDef = equipmentInfo[num - 1][16];
		SellMoney = equipmentInfo[num - 1][17];
		skillName[0] = equipmentInfo[num - 1][18];
		skillMP[0] = equipmentInfo[num - 1][19];
		skillPower[0] = equipmentInfo[num - 1][20];
		skillElementNum[0] = equipmentInfo[num - 1][21];
		skillRatioKind[0] = equipmentInfo[num - 1][22];
		skillExperience[0] = equipmentInfo[num - 1][23];

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
	case 0: Element = "–³"; break;
	case 1: Element = "‰Î"; break;
	case 2: Element = "–Ø"; break;
	case 3: Element = "…"; break;
	case 4: Element = "Œõ"; break;
	case 5: Element = "ˆÅ"; break;
	}

	switch (skillElementNum[0])
	{
	case 0: skillElement[0] = "–³"; break;
	case 1: skillElement[0] = "‰Î"; break;
	case 2: skillElement[0] = "–Ø"; break;
	case 3: skillElement[0] = "…"; break;
	case 4: skillElement[0] = "Œõ"; break;
	case 5: skillElement[0] = "ˆÅ"; break;
	}

	switch (skillElementNum[1])
	{
	case 0: skillElement[1] = "–³"; break;
	case 1: skillElement[1] = "‰Î"; break;
	case 2: skillElement[1] = "–Ø"; break;
	case 3: skillElement[1] = "…"; break;
	case 4: skillElement[1] = "Œõ"; break;
	case 5: skillElement[1] = "ˆÅ"; break;
	}



}

void CEquipmentWindow::ChangeKind( int num, int level)
{

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
		ElementNum = equipmentInfo[num - 1][12];
		FireDef = equipmentInfo[num - 1][13];
		WoodDef = equipmentInfo[num - 1][14];
		WaterDef = equipmentInfo[num - 1][15];
		LightDef = equipmentInfo[num - 1][16];
		DarkDef = equipmentInfo[num - 1][17];
		SellMoney = equipmentInfo[num - 1][18];
		skillName[0] = equipmentInfo[num - 1][19];
		skillMP[0] = equipmentInfo[num - 1][20];
		skillPower[0] = equipmentInfo[num - 1][21];
		skillElementNum[0] = equipmentInfo[num - 1][22];
		skillRatioKind[0] = equipmentInfo[num - 1][23];
		skillExperience[0] = equipmentInfo[num - 1][24];
		skillName[1] = equipmentInfo[num - 1][25];
		skillMP[1] = equipmentInfo[num - 1][26];
		skillPower[1] = equipmentInfo[num - 1][27];
		skillElementNum[1] = equipmentInfo[num - 1][28];
		skillRatioKind[1] = equipmentInfo[num - 1][29];
		skillExperience[1] = equipmentInfo[num - 1][30];
	}
	else {
		FireDef = equipmentInfo[num - 1][12];
		WoodDef = equipmentInfo[num - 1][13];
		WaterDef = equipmentInfo[num - 1][14];
		LightDef = equipmentInfo[num - 1][15];
		DarkDef = equipmentInfo[num - 1][16];
		SellMoney = equipmentInfo[num - 1][17];
		skillName[0] = equipmentInfo[num - 1][18];
		skillMP[0] = equipmentInfo[num - 1][19];
		skillPower[0] = equipmentInfo[num - 1][20];
		skillElementNum[0] = equipmentInfo[num - 1][21];
		skillRatioKind[0] = equipmentInfo[num - 1][22];
		skillExperience[0] = equipmentInfo[num - 1][23];

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
	case 0: Element = "–³"; break;
	case 1: Element = "‰Î"; break;
	case 2: Element = "–Ø"; break;
	case 3: Element = "…"; break;
	case 4: Element = "Œõ"; break;
	case 5: Element = "ˆÅ"; break;
	}

	switch (skillElementNum[0])
	{
	case 0: skillElement[0] = "–³"; break;
	case 1: skillElement[0] = "‰Î"; break;
	case 2: skillElement[0] = "–Ø"; break;
	case 3: skillElement[0] = "…"; break;
	case 4: skillElement[0] = "Œõ"; break;
	case 5: skillElement[0] = "ˆÅ"; break;
	}

	switch (skillElementNum[1])
	{
	case 0: skillElement[1] = "–³"; break;
	case 1: skillElement[1] = "‰Î"; break;
	case 2: skillElement[1] = "–Ø"; break;
	case 3: skillElement[1] = "…"; break;
	case 4: skillElement[1] = "Œõ"; break;
	case 5: skillElement[1] = "ˆÅ"; break;
	}



}

void CEquipmentWindow::Draw()
{
	Window(0, 376);
	
	if (equipmentKind<=2) {
		DrawFormatString(16, 395, BLACK, "%s   No.%d   LEVEL:%d   ”„’lF%d@‘®«:%s", name.c_str(),KindNum, Level, SellMoney, Element.c_str());
	}
	else {
		DrawFormatString(16, 395, BLACK, "%s     LEVEL:%d     ”„’lF%d", name.c_str(), Level, SellMoney);
	}
	DrawFormatString(16,420, BLACK, "ƒXƒe[ƒ^ƒXã¸’l:");
	DrawFormatString(175, 420, BLACK, "HP %d  MP %d  U %d   –h %d  –‚U %d  –‚–h %d",HP, MP,Atc,Def,MAtc,MDef);
	DrawFormatString(175, 440, BLACK, "‰Î–h %d  –Ø–h %d  …–h %d  Œõ–h %d  ˆÅ–h %d",FireDef,WoodDef,WaterDef,LightDef,DarkDef);
	DrawFormatString(175, 460, BLACK, "‘¬ %d  –½’† %d  ‰ñ”ð %d  ‰^ %d", Spd,Hit,Escape,Luck);
	DrawFormatString(16, 485, BLACK, "SKILL1 %sFÁ”ïMP %d   ˆÐ—Í %d@‘®« %s  PÓ°ÄÞ %s", skillName[0].c_str(), skillMP[0], skillPower[0], skillElement[0].c_str(),skillRatioKind[0].c_str());
	DrawFormatString(16, 505, BLACK,"“ÁŽêŒø‰Ê:%s",skillExperience[0].c_str());
	if (equipmentKind <= 2) {
		DrawFormatString(16, 525, BLACK, "SKILL2 %sFÁ”ïMP %d   ˆÐ—Í %d@‘®« %s  PÓ°ÄÞ %s", skillName[1].c_str(), skillMP[1], skillPower[1], skillElement[1].c_str(),skillRatioKind[1].c_str());
		DrawFormatString(16, 545, BLACK, "“ÁŽêŒø‰Ê:%s", skillExperience[1].c_str());
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
