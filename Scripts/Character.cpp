#include "Character.h"
#include "MyScene.h"
#include "math.h"

bool KeyOK();
bool KeyCancel();
bool KeyRight();
bool KeyLeft();
bool KeyUp();
bool KeyDown();





CCharacterBase::CCharacterBase()
{
	live = true;
	HPBar = "zero/HPBar.png";
	MPBar = "zero/MPBar.png";
	smallHPBar = "zero/SmallHPBar.png";
	smallMPBar = "zero/SmallMPBar.png";
	Window[0]= "zero/SellWindow.png";
	for (int i = 0; i < 8; i++) {
		statusHenka[i] = 0;
	}

	doku = false;
	mahi = false;
	housin = false;
	huchi = false;
	hirumi = false;
	damageDisplayTime = 121;
	displayDamage = 121;

}

CCharacterBase::~CCharacterBase()
{
}

void CCharacterBase::Loop()
{
}

void CCharacterBase::Draw(int x, int y)
{
}

void CCharacterBase::Draw(int x,int y, bool nameZurasi)
{
}

void CCharacterBase::statusHenkaReset()
{
	for (int i = 0; i < 8; i++) {
		statusHenka[i] = 0;
	}

}


void CCharacterBase::GiveDamge(int amount,CTextWindow *textWindow)
{
	Status[0] -= amount;
	DethJudge(textWindow);

	tenmetsu = 0;
	damageDisplayTime = 0;
	displayDamage = amount;
}

void CCharacterBase::GiveButuriDamge(CCharacterBase *atackChar, Skill *atackSkill,int skillNum ,CTextWindow *textWindow)
{
	int damage=0;
	int bufI = 0;
	int buffI = 1;
	stringstream bufSS;
	string bufS;
	bufI = Status[8] * 250/ atackChar->Status[7] /6;
	bufI+=2;

	if (bufI < GetRand(255)) {
		damage = atackSkill->power[skillNum] * sqrt((double)atackChar->Atc) * atackChar->Atc / Def / 50;
		if (atackSkill->content[skillNum] == 1) {
			damage = atackSkill->power[skillNum] * sqrt((double)atackChar->MAtc) * atackChar->Atc / Def / 50;
		}
		
		switch (atackSkill->element)
		{
		case 0:break;
		case 1:damage *= (260 - FireDef); break;
		case 2:damage *= (260 - WoodDef); break;
		case 3:damage *= (260 - WaterDef); break;
		case 4:damage *= (260 - LightDef); break;
		case 5:damage *= (260 - DarkDef) ; break;
		default:
			break;
		}

		bufI = atackChar->Luck;

		if (atackChar->statusHenka[7] > 0) {
			bufI *= (10 + statusHenka[7] * 4);
			bufI / 10;
		}
		if (atackChar->statusHenka[7] < 0) {
			bufI *= (10 + statusHenka[7]);
			bufI /= 10;
		}

		if (atackSkill->content[skillNum] == 3) {
			buffI = 7;
		}
		if (GetRand(250) < buffI *(10 + bufI) / 2) {
			damage *= 2.5;
			textWindow->PushText("クリティカルヒット！");
		}


		

		if (atackChar->statusHenka[0] > 0) {
			damage *= (10 + atackChar->statusHenka[0] * 2);
			damage /= 10;
		}
		if (atackChar->statusHenka[0] < 0) {
			damage *= (10 + atackChar->statusHenka[0]);
			damage /= 10;
		}

		if (statusHenka[1] < 0) {
			damage *= (10 - statusHenka[1] * 2);
			damage /= 10;
		}
		if (statusHenka[1] > 0) {
			damage *= (10 - statusHenka[1]);
			damage /= 10;
		}
		if (damage <= 0) {
			damage = 1;
		}

		damage *= (GetRand(15) + 100);
		if (atackSkill->PMode == 0) {
			damage *= (20+atackSkill->Point);
			damage /= 20;
		}
		damage /= 100;
		if (atackSkill->element > 0) {
			damage /= 200;
		}

		bufSS << name.c_str();
		bufSS<< "に";
		bufSS << damage;
		bufSS << "ダメージ与えた。";
		textWindow->PushText(bufSS.str().c_str());
		GiveDamge(damage, textWindow);
		bufSS.clear();

		if (atackSkill->content[skillNum] == 4) {
			atackChar->Status[0] += damage*0.12 + 1;
			if (atackChar->Status[0] > atackChar->MaxHP) {
				atackChar->Status[0] = atackChar->MaxHP;
			}
			bufSS << atackChar->name.c_str();
			bufSS << "はHPを回復した。";
			textWindow->PushText(bufSS.str().c_str());
		}

		if (atackSkill->content[skillNum] == 5) {
			atackChar->MP += damage*0.06 +1 ;
			if (atackChar->MP > atackChar->MaxMP) {
				atackChar->MP = atackChar->MaxMP;
			}
			bufSS << atackChar->name.c_str();
			bufSS << "はMPを回復した。";
			textWindow->PushText(bufSS.str().c_str());
		}


	}
	else {
		bufS += "攻撃が外れた。";
		textWindow->PushText(bufS.c_str());
	}

}

void CCharacterBase::GiveMahouDamge(CCharacterBase * atackChar, Skill * atackSkill, int skillNum, CTextWindow * textWindow)
{
	int damage = 0;
	int bufI = 0;
	int buffI = 1;
	stringstream bufSS;
	string bufS;
	bufI = Status[8] * 250 / atackChar->Status[7] / 6;
	bufI += 2;

	if (bufI < GetRand(255)) {
		damage = atackSkill->power[skillNum] * sqrt((double)atackChar->MAtc) * atackChar->MAtc / MDef / 50;
		if (atackSkill->content[skillNum] == 1) {
			damage = atackSkill->power[skillNum] * sqrt((double)atackChar->Atc) * atackChar->MAtc / MDef / 50;
		}
		
		switch (atackSkill->element)
		{
		case 0:break;
		case 1:damage *= (260 - FireDef); break;
		case 2:damage *= (260 - WoodDef); break;
		case 3:damage *= (260 - WaterDef); break;
		case 4:damage *= (260 - LightDef); break;
		case 5:damage *= (260 - DarkDef); break;
		default:
			break;
		}

		bufI = atackChar->Luck;

		if (atackChar->statusHenka[7] > 0) {
			bufI *= (10 + statusHenka[7] * 4);
			bufI / 10;
		}
		if (atackChar->statusHenka[7] < 0) {
			bufI *= (10 + statusHenka[7]);
			bufI /= 10;
		}

		if (atackSkill->content[skillNum] == 3) {
			buffI = 7;
		}

		if (GetRand(250) < buffI * (10 + bufI) / 2) {
			damage *= 2.5;
			textWindow->PushText("クリティカルヒット！");
		}



		if (atackChar->statusHenka[2] > 0) {
			damage *= (10 + atackChar->statusHenka[2] * 2);
			damage /= 10;
		}
		if (atackChar->statusHenka[2] < 0) {
			damage *= (10 + atackChar->statusHenka[2]);
			damage /= 10;
		}

		if (statusHenka[3] < 0) {
			damage *= (10 - statusHenka[3] * 2);
			damage /= 10;
		}
		if (statusHenka[3] > 0) {
			damage *= (10 - statusHenka[3]);
			damage /= 10;
		}


		damage *= (GetRand(15) + 100);
		if (atackSkill->PMode == 0) {
			damage *= (20+atackSkill->Point);
			damage /= 20;
		}
		damage /= 100;
		if (atackSkill->element > 0) {
			damage /= 200;
		}

		if (damage <= 0) {
			damage = 1;
		}


		bufSS << name.c_str();
		bufSS << "に";
		bufSS << damage;
		bufSS << "ダメージ与えた。";
		textWindow->PushText(bufSS.str().c_str());
		GiveDamge(damage, textWindow);
		bufSS.clear();
		
		if (atackSkill->content[skillNum] == 4) {
			atackChar->Status[0] += damage*0.12 + 1;
			if (atackChar->Status[0] > atackChar->MaxHP) {
				atackChar->Status[0] = atackChar->MaxHP;
			}
			bufSS << atackChar->name.c_str();
			bufSS << "はHPを回復した。";
			textWindow->PushText(bufSS.str().c_str());
		}

		if (atackSkill->content[skillNum] == 5) {
			atackChar->MP += damage*0.06 + 1;
			if (atackChar->MP > atackChar->MaxMP) {
				atackChar->MP = atackChar->MaxMP;
			}
			bufSS << atackChar->name.c_str();
			bufSS << "はMPを回復した。";
			textWindow->PushText(bufSS.str().c_str());
		}

	}
	else {
		bufS += "攻撃が外れた。";
		textWindow->PushText(bufS.c_str());
	}
}



void CCharacterBase::Cure(Skill * atackSkill, int skillNum, CTextWindow * textWindow)
{
	int bufI=0;
	string bufS = name.c_str();
	bufS += "の";
	stringstream bufSS;
	bufSS << name.c_str();
	bufSS << "の";

	switch (atackSkill->content[skillNum])
	{
	case 0:
		bufI = Status[0];
		Status[0] += MaxHP*atackSkill->power[skillNum] / 100;
		if (Status[0] > MaxHP) {
			Status[0] = MaxHP;
		}
		bufSS << "HPが";
		bufSS << (Status[0] - bufI);
		bufSS << "回復した。";
		break;
	case 1:
		bufI = Status[0];
		Status[0] +=atackSkill->power[skillNum];
		if (Status[0] > MaxHP) {
			Status[0] = MaxHP;
		}
		bufSS << "HPが";
		bufSS << (Status[0] - bufI);
		bufSS << "回復した。";
		break;
	case 2:
		bufI = Status[1];
		Status[1] += MaxMP*atackSkill->power[skillNum] / 100;
		if (Status[1] > MaxMP) {
			Status[1] = MaxMP;
		}
		bufSS << "MPが";
		bufSS << (Status[1] - bufI);
		bufSS << "回復した。";
		break;
	case 3:
		bufI = Status[1];
		Status[1] += atackSkill->power[skillNum];
		if (Status[1] > MaxMP) {
			Status[1] = MaxMP;
		}
		bufSS << "MPが";
		bufSS << (Status[1] - bufI);
		bufSS << "回復した。";
		break;
	case 4:
		bufS = "毒の状態が治った。";
		doku = false;
		break;
	case 5:
		bufS = "麻痺の状態が治った。";
		mahi = false;
		break;
	case 6:
		bufS = "放心の状態が治った。";
		housin = false;
		break;
	case 7:
		bufS = "不治の状態が治った。";
		huchi = false;
		break;

	case 9:
		bufS = "全ての状態以上が治った。";
		doku = false;
		mahi = false;
		housin = false;
		huchi = false;
		break;
	case 10:
		if (live == false) {
			bufS = name.c_str();
			bufS += "が生き返った。";
			Status[0] = MaxHP / 2;
		}
		else
		{
			bufS = "しかし、死んではいなかった。";
		}

		live = true;
		break;

	default:
		break;
	}

	if (atackSkill->content[skillNum] <= 3) {
		textWindow->PushText(bufSS.str().c_str());
	}
	else {
		textWindow->PushText(bufS.c_str());
	}

}


void CCharacterBase::statusChange(Skill *atackSkill, int skillNum, CTextWindow *textWindow)
{
	int kind = atackSkill->content[skillNum];
	int amount = atackSkill->power[skillNum];
	int bufI = statusHenka[kind];
	int buffI = 0;
	stringstream bufSS;

	if (kind <= 7) {
		statusHenka[kind] += amount;
		if (amount >= 5) {
			statusHenka[kind] = 5;
		}

		if (amount <= -5) {
			statusHenka[kind] = -5;
		}

		buffI = statusHenka[kind] - bufI;
		bufSS << name.c_str();
		bufSS << "の";

		switch (kind)
		{
		case 0: bufSS << "物攻が"; break;
		case 1: bufSS << "物防が"; break;
		case 2: bufSS << "魔攻が"; break;
		case 3: bufSS << "魔防が"; break;
		case 4: bufSS << "速さが"; break;
		case 5: bufSS << "命中が"; break;
		case 6: bufSS << "回避が"; break;
		case 7: bufSS << "運が"; break;
		default:
			break;
		}

		if (buffI > 0) {
			bufSS << buffI;
			bufSS << "上がった。";
		}
		else if (buffI < 0)
		{
			buffI *= -1;
			bufSS << buffI;
			bufSS << "下がった。";
		}
		else {
			bufSS << "変化しなった。";
		}
	}

	if (16 <= kind && kind <= 20) {
		bufSS << name.c_str();
		if (kind == 16) {
			for (int i = 0; i < 8; i++) {
				if (statusHenka[i] > 0) {
					statusHenka[i] = 0;
				}
			}

			bufSS << "の+のステータス変化が0になった。";
		}
		if (kind == 17) {
			bufSS << "の-のステータス変化効果が0になった。";
			for (int i = 0; i < 8; i++) {
				if (statusHenka[i] < 0) {
					statusHenka[i] = 0;
				}
			}

		}
		if (kind == 18) {
			for (int i = 0; i < 8; i++) {
				statusHenka[i] = 0;
				
			}
			bufSS << "の全てのステータス変化効果が0になった。";
		}

		if (kind == 19) {
			bufSS << "の全てのステータスが";
			bufSS << amount;
			bufSS << "上がった。（5が最大）";
			for (int i = 0; i < 8; i++) {
				statusHenka[i] += amount;
				if (statusHenka[i] >= 5) {
					statusHenka[i] = 5;
				}
			}
		}

		if (kind == 20) {
			bufSS << "の全てのステータスが";
			bufSS << amount;
			bufSS << "下がった。（-5が最小）";
			for (int i = 0; i < 8; i++) {
				statusHenka[i] -= amount;
				if (statusHenka[i] <= -5 ) {
					statusHenka[i] = -5;
				}
			}

		}

	}

	


	textWindow->PushText(bufSS.str().c_str());
}

void CCharacterBase::JoutaiIjou(Skill *atackSkill, int skillNum, CTextWindow *textWindow)
{


	string bufS=name.c_str();
	int bufI =atackSkill->power[skillNum] * 255 / 100;

	if (bufI >= GetRand(255)) {
		switch (atackSkill->content[skillNum])
		{
		case 0:bufS+="は毒状態になった。";  break;
		case 1:bufS += "は麻痺状態になった。";  break;
		case 2:bufS += "は放心状態になった。";  break;
		case 3:bufS += "は不治状態になった。";  break;
		case 4:bufS += "はひるんだ。";  break;
		case 5:
			bufS += "は毒、麻痺、放心、不治状態になった。";
			break;
		default:
			break;
		}

		switch (atackSkill->content[skillNum])
		{
		case 0:doku = true;  break;
		case 1:mahi = true;  break;
		case 2:housin = true;  break;
		case 3:huchi = true;  break;
		case 4:hirumi = true;  break;
		case 5:
			doku = true;
			mahi = true;
			housin = true;
			hirumi = true;
			break;
		default:
			break;
		}

	}
	else {
		switch (atackSkill->content[skillNum])
		{
		case 0:bufS = "は毒状態にならなかった。";  break;
		case 1:bufS = "は麻痺状態にならなかった。";  break;
		case 2:bufS = "は放心状態にならなかった。";  break;
		case 3:bufS = "は不治状態になならなかった。";  break;
		case 4:bufS = "はひるまなかった。";  break;
		case 5:
			bufS = "は毒、麻痺、放心、不治状態にならなかった。";
			break;
		default:
			break;
		}
	}


	textWindow->PushText(bufS.c_str());

}

void CCharacterBase::DethJudge(CTextWindow *textWindow)
{
	string bufS =name.c_str();
	bufS += "は倒れた。";

	if (Status[0] <= 0) {
		Status[0] = 0;
		live = false;
		textWindow->PushText(bufS.c_str());
	}


}


void CCharacterBase::DrawHPBar(int x, int y, bool onlyLive)
{
	if (onlyLive == false || live == true) {
		int bufI = 124 * Status[0] / Status[15];
		HPBar.Draw(x, y);
		if (Status[0] <= MaxHP*0.2) {

			DrawBox(x + 50, y + 4, x + 50 + bufI, y + 19, RED_B, true);
		}
		else if (Status[0] <= MaxHP*0.5) {

			DrawBox(x + 50, y + 4, x + 50 + bufI, y + 19, YELLOW_B, true);
		}
		else {
			DrawBox(x + 50, y + 4, x + 50 + bufI, y + 19, GREEN_B, true);
		}
	}
}

void CCharacterBase::DrawMPBar(int x, int y, bool onlyLive)
{
	if (onlyLive == false || live == true) {
		int bufI = 124 * Status[1] / Status[16];
		MPBar.Draw(x, y);
		DrawBox(x + 50, y + 4, x + 50 + bufI, y + 19, BLUE_B, true);
	}
}

void CCharacterBase::DrawStatusWindow(int x, int y)
{
	string bufS="";
	Window[0].DrawExtend(5, 5, 250, 420);
	DrawFormatString(15, 10, BLACK, "ステータス");

	for (int i = 0; i < 15; i++) {
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
		
		if (i == 0) {
			DrawFormatString(15, 50 + 20 * i * 2, BLACK, "%s;%d / %d", bufS.c_str(), Status[i], Status[i + 15]);
			DrawHPBar(15, 70 + 20 * i * 2,false);
		}
		else if (i == 1) {
			DrawFormatString(15, 50 + 20 * i*2, BLACK, "%s;%d / %d", bufS.c_str(), Status[i],Status[i+15]);
			DrawMPBar(15, 70 + 20 * i * 2,false);
		}
		else {
			DrawFormatString(15, 90 + 20 * i, BLACK, "%s;%d", bufS.c_str(), Status[i]);
		}

	}

}

void CCharacterBase::DrawSmallHPBar(int x, int y, bool onlyLive)
{

	int bufI = 82 * Status[0] / Status[15];
	if (onlyLive == false || live == true) {
		smallHPBar.Draw(x, y);
		if (Status[0] <= MaxHP*0.2) {

			DrawBox(x + 34, y + 4, x + 34 + bufI, y + 16, RED_B, true);
		}
		else if (Status[0] <= MaxHP*0.5) {

			DrawBox(x + 34, y + 4, x + 34 + bufI, y + 16, YELLOW_B, true);
		}
		else {
			DrawBox(x + 34, y + 4, x + 34 + bufI, y + 16, GREEN_B, true);
		}
	}

}

void CCharacterBase::DrawSmallMPBar(int x, int y, bool onlyLive)
{

	int bufI = 82 * Status[1] / Status[16];
	if (onlyLive == false || live == true) {
		smallMPBar.Draw(x, y);
		DrawBox(x + 34, y + 4, x + 34 + bufI, y + 16, BLUE_B, true);
	}

}

void CCharacterBase::DrawDamage()
{
	int bufI= damageDisplayTime / 2;
	if (bufI > 40) {
		bufI = 40;
	}
	if (damageDisplayTime <= 120) {
		damageDisplayTime++;
		DrawFormatString(x, y - 15 - bufI, RED,"%d", displayDamage*-1);
	}

}



CJiki::CJiki(CMySaveData *mySD)
{
	name = "勇者";
	charGraph = "zero/jiki1.png";

	int equipmentKind = 0;
	int num = 0;
	int buf = 0;
	int Level=0;
	for (int i = 0; i < 17; i++) {
		Status[i] = 0;
	}

	mySaveData = mySD;

	for (int i = 0; i < 5; i++) {
		equipManager = new CEquipmentManager(mySaveData, mySaveData->wearEquipmentLocate[i][0]);

		equipmentKind = mySaveData->wearEquipmentLocate[i][0];
		buf = mySaveData->wearEquipmentLocate[i][1];
		num = equipManager->haveEquipmentNumLevel[equipmentKind][buf].first;
		Level = equipManager->haveEquipmentNumLevel[equipmentKind][buf].second;
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

		MaxHP = (*equipmentInfo)[num - 1][2];
		MaxMP = (*equipmentInfo)[num - 1][3];
		Atc = (*equipmentInfo)[num - 1][4];
		Def = (*equipmentInfo)[num - 1][5];
		MAtc = (*equipmentInfo)[num - 1][6];
		MDef = (*equipmentInfo)[num - 1][7];
		Spd = (*equipmentInfo)[num - 1][8];
		Hit = (*equipmentInfo)[num - 1][9];
		Escape = (*equipmentInfo)[num - 1][10];
		Luck = (*equipmentInfo)[num - 1][11];

		if (equipmentKind <= 2) {
			Element = (*equipmentInfo)[num - 1][12];
			FireDef = (*equipmentInfo)[num - 1][13];
			WoodDef = (*equipmentInfo)[num - 1][14];
			WaterDef = (*equipmentInfo)[num - 1][15];
			LightDef = (*equipmentInfo)[num - 1][16];
			DarkDef = (*equipmentInfo)[num - 1][17];
		}
		else {
			FireDef = (*equipmentInfo)[num - 1][12];
			WoodDef = (*equipmentInfo)[num - 1][13];
			WaterDef = (*equipmentInfo)[num - 1][14];
			LightDef = (*equipmentInfo)[num - 1][15];
			DarkDef = (*equipmentInfo)[num - 1][16];

		}

		MaxHP *= (1.0 + 0.1*Level);
		MaxMP *= (1.0 + 0.1*Level);
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
		HP = MaxHP;
		MP = MaxMP;

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
		Status[15] += MaxHP;
		Status[16] += MaxMP;

		if (i == 0) {
			skillNum[0] = (*equipmentInfo)[num - 1][19];
			skillNum[1] = (*equipmentInfo)[num - 1][20];
		}
		else {
			skillNum[i+1] = (*equipmentInfo)[num - 1][18];
		}

		


		delete equipmentInfo;
		delete equipManager;
		equipmentInfo = NULL;
		equipManager = NULL;

	}

	HP = Status[0];
	MP = Status[1];
	Atc = Status[2];
	Def = Status[3];
	MAtc = Status[4];
	MDef = Status[5];
	Spd = Status[6];
	Hit = Status[7];
	Escape = Status[8];
	Luck = Status[9];
	FireDef = Status[10];
	WoodDef = Status[11];
	WaterDef = Status[12];
	LightDef = Status[13];
	DarkDef = Status[14];
	MaxHP = Status[15];
	MaxMP== Status[16];

	equipmentKind = mySaveData->wearEquipmentLocate[0][0];

	skillInfo = new CSV("zero/ZeroData/Skill.csv");
	for (int i = 0; i < 6; i++) {
		skill[i].ene = false;

		skill[i].num = skillNum[i];
		skill[i].neme = (*skillInfo)[skillNum[i] - 1][1];
		skill[i].MP = (*skillInfo)[skillNum[i] - 1][2];
		skill[i].element = (*skillInfo)[skillNum[i] - 1][3];
		skill[i].PMode = (*skillInfo)[skillNum[i] - 1][4];
		skill[i].times = (*skillInfo)[skillNum[i] - 1][5];
		skill[i].classifyNum = (*skillInfo)[skillNum[i] - 1][6];
		for (int j = 0; j < 3; j++) {

			skill[i].target[j] = (*skillInfo)[skillNum[i] - 1][7+j*4];
			skill[i].classify[j] = (*skillInfo)[skillNum[i] - 1][8+j*4];
			skill[i].content[j] = (*skillInfo)[skillNum[i] - 1][9+j*4];
			skill[i].power[j] = (*skillInfo)[skillNum[i] - 1][10+j*4];
		}

		skill[i].experience = (*skillInfo)[skillNum[i] - 1][19];
	}


	normalAtack.ene = false;
	normalDefence.ene = false;

	if (equipmentKind <= 1) {
		normalAtack.num = Element + 1;
		normalAtack.neme = (*skillInfo)[normalAtack.num - 1][1];
		normalAtack.MP = (*skillInfo)[normalAtack.num - 1][2];
		normalAtack.element = (*skillInfo)[normalAtack.num - 1][3];
		normalAtack.PMode = (*skillInfo)[normalAtack.num - 1][4];
		normalAtack.times = (*skillInfo)[normalAtack.num - 1][5];
		normalAtack.classifyNum = (*skillInfo)[normalAtack.num - 1][6];
		for (int j = 0; j < 3; j++) {

			normalAtack.target[j] = (*skillInfo)[normalAtack.num - 1][7 + j * 4];
			normalAtack.classify[j] = (*skillInfo)[normalAtack.num - 1][8 + j * 4];
			normalAtack.content[j] = (*skillInfo)[normalAtack.num - 1][9 + j * 4];
			normalAtack.power[j] = (*skillInfo)[normalAtack.num - 1][10 + j * 4];
		}

		normalAtack.experience = (*skillInfo)[normalAtack.num - 1][19];

	}
	else {
		normalAtack.num = Element + 7;
		normalAtack.neme = (*skillInfo)[normalAtack.num - 1][1];
		normalAtack.MP = (*skillInfo)[normalAtack.num - 1][2];
		normalAtack.element = (*skillInfo)[normalAtack.num - 1][3];
		normalAtack.PMode = (*skillInfo)[normalAtack.num - 1][4];
		normalAtack.times = (*skillInfo)[normalAtack.num - 1][5];
		normalAtack.classifyNum = (*skillInfo)[normalAtack.num - 1][6];
		for (int j = 0; j < 3; j++) {

			normalAtack.target[j] = (*skillInfo)[normalAtack.num - 1][7 + j * 4];
			normalAtack.classify[j] = (*skillInfo)[normalAtack.num - 1][8 + j * 4];
			normalAtack.content[j] = (*skillInfo)[normalAtack.num - 1][9 + j * 4];
			normalAtack.power[j] = (*skillInfo)[normalAtack.num - 1][10 + j * 4];
		}

		normalAtack.experience = (*skillInfo)[normalAtack.num - 1][19];

	}

	normalDefence.num = 13;
	normalDefence.neme = (*skillInfo)[normalDefence.num - 1][1];
	normalDefence.MP = (*skillInfo)[normalDefence.num - 1][2];
	normalDefence.element = (*skillInfo)[normalDefence.num - 1][3];
	normalDefence.PMode = (*skillInfo)[normalDefence.num - 1][4];
	normalDefence.times = (*skillInfo)[normalDefence.num - 1][5];
	normalDefence.classifyNum = (*skillInfo)[normalDefence.num - 1][6];
	for (int j = 0; j < 3; j++) {

		normalDefence.target[j] = (*skillInfo)[normalDefence.num - 1][7 + j * 4];
		normalDefence.classify[j] = (*skillInfo)[normalDefence.num - 1][8 + j * 4];
		normalDefence.content[j] = (*skillInfo)[normalDefence.num - 1][9 + j * 4];
		normalDefence.power[j] = (*skillInfo)[normalDefence.num - 1][10 + j * 4];
	}

	normalDefence.experience = (*skillInfo)[normalDefence.num - 1][19];

	delete skillInfo;
	skillInfo = NULL;

}

CJiki::~CJiki()
{
}

void CJiki::Draw(int x, int y)
{
	DrawFormatString(x, y, BLACK, "%s", name.c_str());
	charGraph.Draw(x, y + 18);
	DrawSmallHPBar(x + 36, y + 18, false);
	DrawSmallMPBar(x + 36, y + 18 + 23, false);
	if (doku) {
		DrawFormatString(x, y + 64, RED, "毒");
	}
	if (mahi) {
		DrawFormatString(x + 22, y + 64, RED, "麻痺");
	}
	if (housin) {
		DrawFormatString(x + 66, y + 64, RED, "放心");
	}
	if (huchi) {
		DrawFormatString(x + 110, y + 64, RED, "不治");
	}

}

CHaniwa::CHaniwa(CMySaveData * mySD,int kind)
{
	mySaveData = mySD;
	this->kind = kind;
	Level = mySaveData->haniwaLevel[kind - 1];

	haniwaInfo = new CSV("zero/ZeroData/Haniwa.csv");
	float bufFlo;
	int bufI;
	stringstream bufSS;
	bufSS << "zero/hani";
	bufSS << this->kind;
	bufSS << ".png";

	charGraph = bufSS.str().c_str();

	name = (*haniwaInfo)[kind - 1][1];

	for (int i = 0; i < 15; i++) {
		bufI = (*haniwaInfo)[kind - 1][2 + i];
		bufFlo = (*haniwaInfo)[kind - 1][17 + i];
		switch (i)
		{
		case 0:
			HP = bufI + bufFlo*Level;
			MaxHP = bufI + bufFlo*Level;
			break;
		case 1:
			MP = bufI + bufFlo*Level;
			MaxMP = bufI + bufFlo*Level;
			break;
		case 2:
			Atc = bufI + bufFlo*Level;
			break;
		case 3:
			Def = bufI + bufFlo*Level;
			break;
		case 4:
			MAtc = bufI + bufFlo*Level;
			break;
		case 5:
			MDef = bufI + bufFlo*Level;
			break;
		case 6:
			Spd = bufI + bufFlo*Level;
			break;
		case 7:
			Hit = bufI + bufFlo*Level;
			break;
		case 8:
			Escape = bufI + bufFlo*Level;
			break;
		case 9:
			Luck = bufI + bufFlo*Level;
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

	Status[0] = HP;
	Status[1] = MP;
	Status[2] = Atc;
	Status[3] = Def;
	Status[4] = MAtc;
	Status[5] = MDef;
	Status[6] = Spd;
	Status[7] = Hit;
	Status[8] = Escape;
	Status[9] = Luck;
	Status[10] = FireDef;
	Status[11] = WoodDef;
	Status[12] = WaterDef;
	Status[13] = LightDef;
	Status[14] = DarkDef;
	Status[15] = MaxHP;
	Status[16] = MaxMP;

	for (int i = 0; i < 4; i++) {
		skillNum[i] = (this->kind - 1) * 4 + i + 1;
	}

	delete haniwaInfo;
	haniwaInfo = NULL;

	haniwaSkillInfo = new CSV("zero/ZeroData/HaniwaSkill.csv");
	for (int i = 0; i < 4; i++) {

		skill[i].ene = false;

		skill[i].num = skillNum[i];
		skill[i].neme = (*haniwaSkillInfo)[skillNum[i] - 1][1];
		if (Level < 30) {
			skill[i].MP = (*haniwaSkillInfo)[skillNum[i] - 1][2];
		}
		else if (Level < 50) {
			skill[i].MP = (*haniwaSkillInfo)[skillNum[i] - 1][3];
		}
		else if (Level < 70) {
			skill[i].MP = (*haniwaSkillInfo)[skillNum[i] - 1][4];
		}
		else {
			skill[i].MP = (*haniwaSkillInfo)[skillNum[i] - 1][5];
		}

		skill[i].element = (*haniwaSkillInfo)[skillNum[i] - 1][6];
		skill[i].times = (*haniwaSkillInfo)[skillNum[i] - 1][7];
		skill[i].classifyNum = (*haniwaSkillInfo)[skillNum[i] - 1][7];

		for (int j = 0; j < 3; j++) {

			skill[i].target[j] = (*haniwaSkillInfo)[skillNum[i] - 1][8 + j * 7];
			skill[i].classify[j] = (*haniwaSkillInfo)[skillNum[i] - 1][9 + j * 7];
			skill[i].content[j] = (*haniwaSkillInfo)[skillNum[i] - 1][10 + j * 7];
			
			if (Level < 30) {
				skill[i].power[j] = (*haniwaSkillInfo)[skillNum[i] - 1][11 + j * 7];
			}
			else if (Level < 50) {
				skill[i].power[j] = (*haniwaSkillInfo)[skillNum[i] - 1][12 + j * 7];
			}
			else if (Level < 70) {
				skill[i].power[j] = (*haniwaSkillInfo)[skillNum[i] - 1][13 + j * 7];
			}
			else {
				skill[i].power[j] = (*haniwaSkillInfo)[skillNum[i] - 1][14 + j * 7];
			}
						
		}

		skill[i].experience = (*haniwaSkillInfo)[skillNum[i] - 1][29];

	}
	delete haniwaSkillInfo;
	haniwaSkillInfo = NULL;


	skillInfo = new CSV("zero/ZeroData/Skill.csv");
	if (3 <= kind && kind <= 7) {
		normalAtack.num = kind - 1;
	}
	else if(kind==2)
	{
		normalAtack.num = 7;
	}
	else {
		normalAtack.num = 1;
	}

	normalAtack.ene = false;
	normalDefence.ene = false;
	
	normalAtack.neme = (*skillInfo)[normalAtack.num - 1][1];
	normalAtack.MP = (*skillInfo)[normalAtack.num - 1][2];
	normalAtack.element = (*skillInfo)[normalAtack.num - 1][3];
	normalAtack.times = (*skillInfo)[normalAtack.num - 1][5];
	normalAtack.classifyNum = (*skillInfo)[normalAtack.num - 1][6];
	for (int j = 0; j < 3; j++) {

		normalAtack.target[j] = (*skillInfo)[normalAtack.num - 1][7 + j * 4];
		normalAtack.classify[j] = (*skillInfo)[normalAtack.num - 1][8 + j * 4];
		normalAtack.content[j] = (*skillInfo)[normalAtack.num - 1][9 + j * 4];
		normalAtack.power[j] = (*skillInfo)[normalAtack.num - 1][10 + j * 4];
	}

	normalAtack.experience = (*skillInfo)[normalAtack.num - 1][19];




	normalDefence.num = 13;
	normalDefence.neme = (*skillInfo)[normalDefence.num - 1][1];
	normalDefence.MP = (*skillInfo)[normalDefence.num - 1][2];
	normalDefence.element = (*skillInfo)[normalDefence.num - 1][3];
	normalDefence.times = (*skillInfo)[normalDefence.num - 1][5];
	normalDefence.classifyNum = (*skillInfo)[normalDefence.num - 1][6];
	for (int j = 0; j < 3; j++) {

		normalDefence.target[j] = (*skillInfo)[normalDefence.num - 1][7 + j * 4];
		normalDefence.classify[j] = (*skillInfo)[normalDefence.num - 1][8 + j * 4];
		normalDefence.content[j] = (*skillInfo)[normalDefence.num - 1][9 + j * 4];
		normalDefence.power[j] = (*skillInfo)[normalDefence.num - 1][10 + j * 4];
	}

	normalDefence.experience = (*skillInfo)[normalDefence.num - 1][19];

	delete skillInfo;
	skillInfo = NULL;

}

CHaniwa::~CHaniwa()
{
}

void CHaniwa::Draw(int x, int y)
{
	DrawFormatString(x, y, BLACK, "%s", name.c_str());
	charGraph.Draw(x , y + 18);
	DrawSmallHPBar(x + 36, y + 18, false);
	DrawSmallMPBar(x+ 36, y + 18 + 23, false);
	if (doku) {
		DrawFormatString(x, y + 64, RED, "毒");
	}
	if (mahi) {
		DrawFormatString(x + 22, y + 64, RED, "麻痺");
	}
	if (housin) {
		DrawFormatString(x + 66, y + 64, RED, "放心");
	}
	if (huchi) {
		DrawFormatString(x + 110, y + 64, RED, "不治");
	}
}

CEnemy::CEnemy(CMySaveData * mySD, int kind)
{

	mySaveData = mySD;
	this->kind = kind;


	enemyInfo = new CSV("zero/ZeroData/Enemy.csv");
	float bufFlo;
	int bufI;
	string bufS;


	name = (*enemyInfo)[kind-1][1];
	bufS = (*enemyInfo)[kind - 1][2];
	charGraph = bufS.c_str();

	for (int i = 0; i < 15; i++) {
		
		bufI = (*enemyInfo)[kind-1][3 + i];
		switch (i)
		{
		case 0:
			HP = bufI ;
			MaxHP = bufI ;
			break;
		case 1:
			Atc = bufI;
			break;
		case 2:
			Def = bufI;
			break;
		case 3:
			MAtc = bufI;
			break;
		case 4:
			MDef = bufI;
			break;
		case 5:
			Spd = bufI;
			break;
		case 6:
			Hit = bufI;
			break;
		case 7:
			Escape = bufI ;
			break;
		case 8:
			Luck = bufI ;
			break;
		case 9:
			FireDef = bufI ;
			break;
		case 10:
			WoodDef = bufI ;
			break;
		case 11:
			WaterDef = bufI ;
			break;
		case 12:
			LightDef = bufI ;
			break;
		case 13:
			DarkDef = bufI ;
			break;



		default:
			break;
		}
	}

	Status[0] = HP;
	Status[1] = MP;
	Status[2] = Atc;
	Status[3] = Def;
	Status[4] = MAtc;
	Status[5] = MDef;
	Status[6] = Spd;
	Status[7] = Hit;
	Status[8] = Escape;
	Status[9] = Luck;
	Status[10] = FireDef;
	Status[11] = WoodDef;
	Status[12] = WaterDef;
	Status[13] = LightDef;
	Status[14] = DarkDef;
	Status[15] = MaxHP;
	Status[16] = MaxMP;

	for (int i = 0; i < 5; i++) {
		skillNum[i]= (*enemyInfo)[kind - 1][17+i];
	}
	for (int i = 0; i < 4; i++) {
		Item[i][0] = (*enemyInfo)[kind - 1][22 + i * 2];
		Item[i][1] = (*enemyInfo)[kind - 1][23 + i * 2];

	}
	delete enemyInfo;
	enemyInfo = NULL;

	skillInfo = new CSV("zero/ZeroData/Skill.csv");
	for (int i = 0; i < 5; i++) {
		skill[i].ene = true;

		skill[i].num = skillNum[i];
		if (skillNum[i] > 0) {
			skill[i].neme = (*skillInfo)[skillNum[i] - 1][1];
			skill[i].MP = (*skillInfo)[skillNum[i] - 1][2];
			skill[i].element = (*skillInfo)[skillNum[i] - 1][3];
			skill[i].PMode = (*skillInfo)[skillNum[i] - 1][4];
			skill[i].times = (*skillInfo)[skillNum[i] - 1][5];
			skill[i].classifyNum = (*skillInfo)[skillNum[i] - 1][6];
			for (int j = 0; j < 3; j++) {

				skill[i].target[j] = (*skillInfo)[skillNum[i] - 1][7 + j * 4];
				skill[i].classify[j] = (*skillInfo)[skillNum[i] - 1][8 + j * 4];
				skill[i].content[j] = (*skillInfo)[skillNum[i] - 1][9 + j * 4];
				skill[i].power[j] = (*skillInfo)[skillNum[i] - 1][10 + j * 4];
			}

			skill[i].experience = (*skillInfo)[skillNum[i] - 1][19];
		}
	}

	delete skillInfo;
	skillInfo = NULL;

	tenmetsu = 121;

}

CEnemy::~CEnemy()
{
}

void CEnemy::Draw(int x, int y, bool nameZurasi)
{
	this->x = x;
	this->y = y;

	if (live == true) {
		if (tenmetsu > 90 || tenmetsu % 30 <= 15) {
			charGraph.Draw(x, y);
		}
		if (tenmetsu < 110) {
			tenmetsu++;
		}

		DrawSmallHPBar(x, y - 24, true);

		if (nameZurasi == false) {
			DrawFormatString(x, y - 44, BLACK, name.c_str());
			
		}
		else
		{
			DrawFormatString(x, y - 64, BLACK, name.c_str());
		}

		if (doku) {
			DrawFormatString(x-6, y - 84, RED, "毒");
		}
		if (mahi) {
			DrawFormatString(x + 14, y - 84, RED, "麻痺");
		}
		if (housin) {
			DrawFormatString(x + 54, y - 84, RED, "放心");
		}
		if (huchi) {
			DrawFormatString(x + 94, y - 84, RED, "不治");
		}


	}

}
