#include "Character.h"
#include "MyScene.h"
#include "math.h"

bool KeyOK();
bool KeyCancel();
bool KeyRight();
bool KeyLeft();
bool KeyUp();
bool KeyDown();

CEffect1::CEffect1()
{
	Effect[0] = "zero/BattleEffect1.png";

}

CEffect1::~CEffect1()
{

}

void CEffect1::PushEffect(CCharacterBase * fromChar, CCharacterBase * toChar)
{
	SEffect bufSEf;
	bufSEf.x = fromChar->x;
	bufSEf.y = fromChar->y;
	if (fromChar->y <= 270) {
		bufSEf.x += 25;
	}
	else
	{
		bufSEf.x += 10;
	}
	bufSEf.vx = (toChar->x - fromChar->x) / effectTime1;
	bufSEf.vy = (toChar->y - fromChar->y) / effectTime1;
	if (toChar->y <= 270) {
		bufSEf.vx += 0.400;
	}
	else {
		bufSEf.vx += 0.100;
	}
	bufSEf.drawTime = 0;
	vSEffect.push_back(bufSEf);

}

void CEffect1::DrawEffect()
{
	for (int i = 0; i < vSEffect.size(); i++) {
		vSEffect[i].x += vSEffect[i].vx;
		vSEffect[i].y += vSEffect[i].vy;
		vSEffect[i].y -= cos(DX_PI * vSEffect[i].drawTime / effectTime1)*3;
		vSEffect[i].drawTime++;
		if (vSEffect[i].drawTime > effectTime1) {
			vSEffect.erase(vSEffect.begin());
			i--;
		}
		else {
			DxLib::SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			Effect[0].DrawRota(vSEffect[i].x, vSEffect[i].y, vSEffect[i].y/300, 0);
			DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}

	}


}


CCharacterBase::CCharacterBase()
{
	live = true;
	HPBar = "zero/HPBar.png";
	MPBar = "zero/MPBar.png";
	smallHPBar = "zero/SmallHPBar.png";
	smallMPBar = "zero/SmallMPBar.png";
	Window[0]= "zero/ItemSelectWindow3.png";

	for (int i = 0; i < 8; i++) {
		statusHenka[i] = 0;
	}

	for (int i = 0; i < 10; i++) {
		skill[i].targetNum = 100;
	}

	doku = false;
	mahi = false;
	housin = false;
	huchi = false;
	hirumi = false;
	damageDisplayTime = 121;
	displayDamage = 0;
	cureDisplayTime = 121;
	displayCure = 0;
	damageMPDisplayTime = 121;
	displayDamageMP = 0;
	cureMPDisplayTime = 121;
	displayCureMP = 0;
	statusChangeDisplayTime=121;
	displayStatusChange =0;

	damageCut[0] = 0;
	damageCut[1] = 0;


	for (int i = 0; i < 10; i++)
	{
		skill[i].useChar = this;
		skill[i].Point = -1;
		skill[i].cardNum = -1;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			dropItem[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		jikiSkillCard[i] = NULL;
	}


	normalAtack.useChar = this;
	normalDefence.useChar = this;

}

CCharacterBase::~CCharacterBase()
{
}

void CCharacterBase::Reset()
{
	doku = false;
	mahi = false;
	housin = false;
	huchi = false;
	hirumi = false;
	damageDisplayTime = 121;
	displayDamage = 0;
	cureDisplayTime = 121;
	displayCure = 0;
	damageMPDisplayTime = 121;
	displayDamageMP = 0;
	cureMPDisplayTime = 121;
	displayCureMP = 0;
	statusChangeDisplayTime = 121;
	displayStatusChange = 0;
	tenmetsu = 121;

	damageCut[0] = 0;
	damageCut[1] = 0;


	for (int i = 0; i < 8; i++) {
		statusHenka[i] = 0;
	}


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

	tenmetsu = effectTime1*-1;
	damageDisplayTime = effectTime1*-1;
	displayDamage = amount;
}

void CCharacterBase::GiveCureHP(int amount, CTextWindow * textWindow)
{
	int bufI = 0;
	bufI = Status[0];
	Status[0] += amount;
	if (Status[0] > MaxHP) {
		Status[0] = MaxHP;
	}

	cureDisplayTime = effectTime1*-1;
	displayCure = Status[0]-bufI;
}

void CCharacterBase::GiveDamgeMP(int amount, CTextWindow * textWindow)
{
	Status[1] -= amount;
	if (Status[1] < 0) {
		Status[1] = 0;
	}

	damageMPDisplayTime = effectTime1*-1;
	displayDamageMP = amount;

}


void CCharacterBase::GiveCureMP(int amount, CTextWindow * textWindow)
{
	int bufI = 0;
	bufI = Status[1];
	Status[1] += amount;
	if (Status[1] > MaxMP) {
		Status[1] = MaxMP;
	}

	cureMPDisplayTime = effectTime1*-1;
	displayCureMP = Status[1] - bufI;
}

void CCharacterBase::GiveButuriDamge(CCharacterBase *atackChar, Skill *atackSkill,int skillNum ,CTextWindow *textWindow, bool *hazureta)
{
	int damage=0;
	int bufI = 0;
	int buffI = 1;
	stringstream bufSS;
	string bufS;
	bufI = (float)Status[8] * 250/ atackChar->Status[7] /25;
	if (atackChar->statusHenka[5] > 0) {
		bufI *= (float)(10 - statusHenka[5]) / 10;
	}
	if (atackChar->statusHenka[5] < 0) {
		bufI *= (float)(10 - statusHenka[5] * 2) / 10;
	}
	if (statusHenka[6] > 0) {
		bufI *= (float)(10 + statusHenka[6] * 2) / 10;
	}
	if (statusHenka[6] < 0) {
		bufI *= (float)(10 + statusHenka[6]) / 10;
	}
	bufI+=1;

	if (bufI < GetRand(255) && *hazureta == false) {

		effect1.PushEffect(atackChar, this);

		damage = (float)atackSkill->power[skillNum] * atackChar->Atc * atackChar->Atc / Def / 100;
		if (atackSkill->content[skillNum] == 1) {
			damage = (float)atackSkill->power[skillNum] * atackChar->MAtc * atackChar->Atc / Def / 100;
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

		if (atackSkill->element > 0) {
			damage /= 200;
		}

		bufI = atackChar->Luck;

		if (atackChar->statusHenka[7] > 0) {
			bufI *= (float)(10 + statusHenka[7] * 4) / 10;
			//bufI /= 10;
		}
		if (atackChar->statusHenka[7] < 0) {
			bufI *= (float)(10 + statusHenka[7] / 10) / 10;
			//bufI /= 10;
		}

		if (atackSkill->content[skillNum] == 3) {
			buffI = 7;
		}
		if ((float)GetRand(250) < (float)buffI *(10 + bufI) / 2) {
			damage *= 2.5;
			textWindow->PushText("クリティカルヒット！");
		}


		

		if (atackChar->statusHenka[0] > 0) {
			damage *= (float)(10 + atackChar->statusHenka[0] * 2) / 10;
			//damage /= 10;
		}
		if (atackChar->statusHenka[0] < 0) {
			damage *= (float)(10 + atackChar->statusHenka[0]) / 10;
			//damage /= 10;
		}

		if (statusHenka[1] < 0) {
			damage *= (float)(10 - statusHenka[1] * 2) / 10;
			//damage /= 10;
		}
		if (statusHenka[1] > 0) {
			damage *= (float)(10 - statusHenka[1]) / 10;
			//damage /= 10;
		}
		

		damage *= (float)(GetRand(15) + 100)/100;
		damage *= (float)(100 - damageCut[0])/100;

		if (atackSkill->PMode == 0) {
			damage *= (float)(20+atackSkill->Point)/20;
			//damage /= 20;
		}

		if (damage <= 0) {
			damage = 1;
		}

		//damage /= 100;
		//damage /= 100;
		

		bufSS << name.c_str();
		bufSS<< "に";
		bufSS << damage;
		bufSS << "ダメージ与えた。";
		textWindow->PushText(bufSS.str().c_str());
		GiveDamge(damage, textWindow);

		if (atackSkill->content[skillNum] == 4) {
			atackChar->GiveCureHP((float)damage*0.12 + 1,textWindow);
			bufS = atackChar->name.c_str();
			bufS += "はHPを回復した。";
			textWindow->PushText(bufS.c_str());
		}

		if (atackSkill->content[skillNum] == 5) {
			atackChar->GiveCureMP((float)damage*0.06 + 1, textWindow);
			bufS = atackChar->name.c_str();
			bufS += "はMP回復した。";
			textWindow->PushText(bufS.c_str());
		}


	}
	else {
		bufS += "攻撃が外れた。";
		textWindow->PushText(bufS.c_str());
		*hazureta = true;

	}

}

void CCharacterBase::GiveMahouDamge(CCharacterBase * atackChar, Skill * atackSkill, int skillNum, CTextWindow * textWindow, bool *hazureta)
{
	int damage = 0;
	int bufI = 0;
	int buffI = 1;
	stringstream bufSS;
	string bufS;
	bufI = (float)Status[8] * 250 / atackChar->Status[7] / 25;
	if (atackChar->statusHenka[5] > 0) {
		bufI *= (float)(10 - statusHenka[5]) / 10;
	}
	if (atackChar->statusHenka[5] < 0) {
		bufI *= (float)(10 - statusHenka[5] * 2) / 10;
	}
	if (statusHenka[6] > 0) {
		bufI *= (float)(10 + statusHenka[6] * 2) / 10;
	}
	if (statusHenka[6] < 0) {
		bufI *= (float)(10 + statusHenka[6]) / 10;
	}
	bufI += 1;


	if (bufI < GetRand(255) && *hazureta==false) {
		effect1.PushEffect(atackChar, this);

		damage = (float)atackSkill->power[skillNum] * atackChar->MAtc * atackChar->MAtc / MDef / 100;
		if (atackSkill->content[skillNum] == 1) {
			damage = (float)atackSkill->power[skillNum] * atackChar->Atc * atackChar->MAtc / MDef / 100;
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

		if (atackSkill->element > 0) {
			damage /= 200;
		}

		bufI = atackChar->Luck;

		if (atackChar->statusHenka[7] > 0) {
			bufI *= (float)(10 + statusHenka[7] * 4) / 10;
			//bufI / 10;
		}
		if (atackChar->statusHenka[7] < 0) {
			bufI *= (float)(10 + statusHenka[7]) / 10;
			//bufI /= 10;
		}

		if (atackSkill->content[skillNum] == 3) {
			buffI = 7;
		}

		if ((float)GetRand(250) < (float)buffI * (10 + bufI) / 2) {
			damage *= 2.5;
			textWindow->PushText("クリティカルヒット！");
		}



		if (atackChar->statusHenka[2] > 0) {
			damage *= (float)(10 + atackChar->statusHenka[2] * 2) / 10;
			//damage /= 10;
		}
		if (atackChar->statusHenka[2] < 0) {
			damage *= (float)(10 + atackChar->statusHenka[2] / 10);
			//damage /= 10;
		}

		if (statusHenka[3] < 0) {
			damage *= (float)(10 - statusHenka[3] * 2) / 10;
			//damage /= 10;
		}
		if (statusHenka[3] > 0) {
			damage *= (float)(10 - statusHenka[3]) / 10;
			//damage /= 10;
		}


		damage *= (float)(GetRand(15) + 100)/100;
		damage *= (float)(100 - damageCut[1])/100;

		if (atackSkill->PMode == 0) {
			damage *= (20+atackSkill->Point);
			damage /= 20;
		}

		//damage /= 100;
		//damage /= 100;


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
			atackChar->GiveCureHP((float)damage*0.12 + 1, textWindow);
			bufS = atackChar->name.c_str();
			bufS += "はHPを回復した。";
			textWindow->PushText(bufS.c_str());
		}

		if (atackSkill->content[skillNum] == 5) {
			atackChar->GiveCureMP((float)damage*0.06 + 1, textWindow);
			bufS = atackChar->name.c_str();
			bufS += "はMPを回復した。";
			textWindow->PushText(bufS.c_str());
		}

	}
	else {
		bufS += "攻撃が外れた。";
		textWindow->PushText(bufS.c_str());
		*hazureta = true;
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

	if (atackSkill->content[skillNum] <= 1 && huchi) {
		bufS = name.c_str();
		bufS += "は不治状態のためHPは回復しない。";
		textWindow->PushText(bufS.c_str());
	}
	else {
		effect1.PushEffect(atackSkill->useChar, this);

		switch (atackSkill->content[skillNum])
		{
		case 0:
			bufI = Status[0];
			GiveCureHP(MaxHP*atackSkill->power[skillNum] / 100, textWindow);
			bufSS << "HPが";
			bufSS << (Status[0] - bufI);
			bufSS << "回復した。";
			break;
		case 1:
			bufI = Status[0];
			GiveCureHP(atackSkill->power[skillNum], textWindow);
			bufSS << "HPが";
			bufSS << (Status[0] - bufI);
			bufSS << "回復した。";
			break;
		case 2:
			bufI = Status[1];
			GiveCureMP(MaxMP*atackSkill->power[skillNum] / 100, textWindow);
			bufSS << "MPが";
			bufSS << (Status[1] - bufI);
			bufSS << "回復した。";
			break;
		case 3:
			bufI = Status[1];
			GiveCureMP(atackSkill->power[skillNum], textWindow);
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
			bufS = name.c_str();
			if (live == false) {
				bufS += "が復活した。";
				Status[0] = MaxHP *atackSkill->power[skillNum] / 100;
			}
			else
			{
				bufS += "は倒れていないので復活の効果がなかった。";
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


}


void CCharacterBase::statusChange(Skill *atackSkill, int skillNum, CTextWindow *textWindow)
{
	int kind = atackSkill->content[skillNum];
	int amount = atackSkill->power[skillNum];
	int bufI = statusHenka[kind];
	int buffI = 0;
	char koreijou = 0;
	stringstream bufSS;



	if (kind <= 7) {
		if (statusHenka[kind] >= 5) {
			koreijou = 1;
		}

		if (statusHenka[kind] <= -5) {
			koreijou=2;
		}

		statusHenka[kind] += amount;
		if (statusHenka[kind] >= 5) {
			statusHenka[kind] = 5;
		}

		if (statusHenka[kind] <= -5) {
			statusHenka[kind] = -5;
		}

		buffI = statusHenka[kind] - bufI;
		bufSS << name.c_str();
		bufSS << "の";

		switch (kind)
		{
		case 0: bufSS << "物攻"; break;
		case 1: bufSS << "物防"; break;
		case 2: bufSS << "魔攻"; break;
		case 3: bufSS << "魔防"; break;
		case 4: bufSS << "速さ"; break;
		case 5: bufSS << "命中"; break;
		case 6: bufSS << "回避"; break;
		case 7: bufSS << "運"; break;
		default:
			break;
		}
		if (koreijou == 1) {
			bufSS << "はこれ以上上がらない。";
		}
		else if (koreijou == 2) {
			bufSS << "はこれ以上下がらない。";
		}
		else if (buffI > 0) {
			statusChangeDisplayTime = 0;
			displayStatusChange = bufI;
			bufSS << "が";
			bufSS << buffI;
			bufSS << "上がった。";

			displayStatusChange = buffI;
			statusChangeDisplayTime = 0;
		}
		else if (buffI < 0)
		{
			displayStatusChange = bufI;
			buffI *= -1;
			statusChangeDisplayTime = 0;
			bufSS << "が";
			bufSS << buffI;
			bufSS << "下がった。";
			buffI *= -1;
			displayStatusChange = buffI;
			statusChangeDisplayTime = 0;
		}
		else {
			bufSS << "が変化しなった。";
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

			bufSS << "のプラスのステータス変化が0になった。";
		}
		if (kind == 17) {
			bufSS << "のマイナスのステータス変化効果が0になった。";
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
			displayStatusChange=amount;
			statusChangeDisplayTime = 0;
			for (int i = 0; i < 8; i++) {
				statusHenka[i] += amount;
				if (statusHenka[i] >= 5) {
					statusHenka[i] = 5;
				}
			}
		}

		if (kind == 20) {
			bufSS << "の全てのステータスが";
			bufSS << amount *-1;
			bufSS << "下がった。（-5が最小）";
			displayStatusChange = amount*-1;
			statusChangeDisplayTime = 0;
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
			huchi = true;
			break;
		default:
			break;
		}

	}
	else {
		switch (atackSkill->content[skillNum])
		{
		case 0:bufS += "は毒状態にならなかった。";  break;
		case 1:bufS += "は麻痺状態にならなかった。";  break;
		case 2:bufS += "は放心状態にならなかった。";  break;
		case 3:bufS += "は不治状態になならなかった。";  break;
		case 4:bufS += "はひるまなかった。";  break;
		case 5:
			bufS += "は毒、麻痺、放心、不治状態にならなかった。";
			break;
		default:
			break;
		}
	}


	textWindow->PushText(bufS.c_str());

}

void CCharacterBase::Tokusyu(CCharacterBase * atackChar, Skill * atackSkill, int skillNum, CTextWindow * textWindow)
{

	int bufI = 0;
	int bufSyahhuru[4] = { -1,-1,-1,-1 };
	bool syahhuruOK = false;
	string bufS = name.c_str();
	bufS += "の";
	stringstream bufSS;
	bufSS << name.c_str();
	bufSS << "の";

	switch (atackSkill->content[skillNum])
	{
	case 0:
		if (atackSkill->cardNum >= 0) {
			if (atackSkill->power[skillNum] >= 4) {
				for (int i = 0; i < 4; i++) {
					bufSyahhuru[i] = i;
				}
			}
			else {
				for (int i = 0; i < atackSkill->power[skillNum]; i++) {
					for (int j = 0; j < 300; j++) {
						syahhuruOK = true;
						bufSyahhuru[i] = GetRand(3);
						for (int k = 0; k < i; k++) {
							if (bufSyahhuru[k] == bufSyahhuru[i]) {
								syahhuruOK = false;
							}
						}
						if (atackSkill->cardNum == bufSyahhuru[i]) {
							syahhuruOK = false;
						}
						if (syahhuruOK) {
							break;
						}

						if (j == 299) {
							for (int l = 0; l < 4; l++) {
								syahhuruOK = true;
								bufSyahhuru[i] = l;

								for (int k = 0; k < i; k++) {
									if (bufSyahhuru[k] == bufSyahhuru[i]) {
										syahhuruOK = false;
									}
								}
								if (atackSkill->cardNum == bufSyahhuru[i]) {
									syahhuruOK = false;
								}
								if (syahhuruOK) {
									break;
								}

							}
						}
						//
					}
				}
			}

		}
		else {
			if (atackSkill->power[skillNum] >= 4) {
				for (int i = 0; i < 4; i++) {
					bufSyahhuru[i] = i;
				}
			}
			else {
				for (int i = 0; i < atackSkill->power[skillNum]; i++) {
					for (int j = 0; j < 300; j++) {
						syahhuruOK = true;
						bufSyahhuru[i] = GetRand(3);
						for (int k = 0; k < i; k++) {
							if (bufSyahhuru[k] == bufSyahhuru[i]) {
								syahhuruOK = false;
							}
						}
						if (syahhuruOK) {
							break;
						}
						if (j == 299) {
							for (int l = 0; l < 4; l++) {
								syahhuruOK = true;
								bufSyahhuru[i] = l;

								for (int k = 0; k < i; k++) {
									if (bufSyahhuru[k] == bufSyahhuru[i]) {
										syahhuruOK = false;
									}
								}

								if (syahhuruOK) {
									break;
								}

							}
						}
						//
					}
				}
			}

		}

		for (int i = 0; i < atackSkill->power[skillNum]; i++) {
			if (i > 3) {
				break;
			}
			SkillSpeadRand();
			*jikiSkillCard[bufSyahhuru[i]] = skill[GetRand(5)];
			jikiSkillCard[bufSyahhuru[i]]->Point = GetRand(9) + 1;
			jikiSkillCard[bufSyahhuru[i]]->cardNum = bufSyahhuru[i];

		}
		bufSS << "スキルカードを";
		bufSS << atackSkill->power[skillNum];
		bufSS << "枚シャッフルした。";
		textWindow->PushText(bufSS.str().c_str());

		break;
	case 1:
		for (int i = 0; i < 4; i++) {
			jikiSkillCard[i]->Point += atackSkill->power[skillNum];
			if (jikiSkillCard[i]->Point > 10) {
				jikiSkillCard[i]->Point = 10;
			}
			if (jikiSkillCard[i]->Point < 1) {
				jikiSkillCard[i]->Point = 1;
			}
		}
		bufSS << "スキルカードのポイントが";
		if (atackSkill->power[skillNum] >= 0) {
			bufSS << atackSkill->power[skillNum];
			bufSS << "上昇した。(最大は10)";
		}
		else {
			bufSS << atackSkill->power[skillNum]*-1;
			bufSS << "減少した。(最小は1)";
		}
		textWindow->PushText(bufSS.str().c_str());

		break;
	case 2:

		break;
	case 3:
		bufI = MaxHP*atackSkill->power[skillNum] / 100;
		GiveDamge(MaxHP*atackSkill->power[skillNum] / 100 , textWindow);
		bufSS << "HPが";
		bufSS << bufI;
		bufSS << "減少した。";
		textWindow->PushText(bufSS.str().c_str());
		break;
	case 4:
		bufI = atackSkill->power[skillNum];
		GiveDamge(atackSkill->power[skillNum] , textWindow);
		bufSS << "HPが";
		bufSS << bufI;
		bufSS << "減少した。";
		textWindow->PushText(bufSS.str().c_str());
		break;
	case 5:
		bufI = MaxMP*atackSkill->power[skillNum] / 100;
		GiveDamgeMP(MaxMP*atackSkill->power[skillNum] / 100 , textWindow);
		bufSS << "MPが";
		bufSS << bufI;
		bufSS << "減少した。";
		textWindow->PushText(bufSS.str().c_str());
		break;
	case 6:
		bufI = atackSkill->power[skillNum];
		GiveDamgeMP(atackSkill->power[skillNum], textWindow);
		bufSS << "MPが";
		bufSS << bufI;
		bufSS << "減少した。";
		textWindow->PushText(bufSS.str().c_str());
		break;
	case 7:
		bufS = "このターン";
		bufS += name.c_str();
		bufS += "への物理ダメージが減っている。";
		textWindow->PushText(bufS.c_str());
		break;
	case 8:
		bufS = "このターン";
		bufS += name.c_str();
		bufS += "への魔法ダメージが減っている。";
		textWindow->PushText(bufS.c_str());
		break;
	case 9:
		bufS = "このターン";
		bufS += name.c_str();
		bufS += "へのダメージが減っている。";
		textWindow->PushText(bufS.c_str());
		break;
	}


}

void CCharacterBase::DethJudge(CTextWindow *textWindow)
{
	string bufS =name.c_str();
	bufS += "は倒れた。";

	if (Status[0] <= 0) {
		Status[0] = 0;
		live = false;
		textWindow->PushText(bufS.c_str());
		Reset();
	}


}

Skill CCharacterBase::returnSkill()
{
	int bufI = GetRand(9);
	int buffI=0;
	
	if (bigBoss == false) {
		if (bufI < 4) {
			buffI = 0;
		}
		else if(bufI<6)
		{
			buffI = 1;
		}
		else if (bufI<8)
		{
			buffI = 2;
		}
		else if (bufI<9)
		{
			buffI = 3;
		}
		else
		{
			buffI = 4;
		}
	}

	skill[buffI].speed = (float)Spd*(1 - GetRand(20)*0.01);
	if (statusHenka[4] > 0) {
		skill[buffI].speed *= (float)(10 + statusHenka[4] * 2) / 10;
	}
	if (statusHenka[4] < 0) {
		skill[buffI].speed *= (float)(10 - statusHenka[4]) / 10;
	}
	return skill[buffI];

}

void CCharacterBase::SkillSpeadRand()
{
	for (int i = 0; i < 10; i++) {
		skill[i].speed = (float)Spd*(1 - GetRand(20)*0.01);
		if (statusHenka[4] > 0) {
			skill[i].speed *= (float)(10 + statusHenka[4] * 2) / 10;
		}
		if (statusHenka[4] < 0) {
			skill[i].speed *= (float)(10 + statusHenka[4]) / 10;
		}
	}
		
		normalAtack.speed = (float)Spd*(1 - GetRand(20)*0.01);
		if (statusHenka[4] > 0) {
			normalAtack.speed *= (float)(10 + statusHenka[4] * 2) / 10;
		}
		if (statusHenka[4] < 0) {
			normalAtack.speed *= (float)(10 + statusHenka[4]) / 10;
		}
		normalDefence.speed = (float)Spd*(1 - GetRand(20)*0.01);
		if (statusHenka[4] > 0) {
			normalDefence.speed *= (float)(10 + statusHenka[4] * 2) / 10;
		}
		if (statusHenka[4] < 0) {
			normalDefence.speed *= (float)(10 + statusHenka[4]) / 10;
		}

}

void CCharacterBase::skillHatudou(CCharacterBase *atackChar, Skill *atackSkill, int skillNum, CTextWindow *textWindow, bool *oneMore, bool *hazureta)
{
	*oneMore = false;
	string bufS;

	if (atackSkill->useChar->live) {

		if (atackSkill->hajime) {
			atackSkill->hajime = false;
			bufS = atackChar->name.c_str();
			bufS += "の";
			bufS += atackSkill->neme.c_str();
			textWindow->PushText(bufS.c_str());
		}
		else {

			if (live && *hazureta == false) {
				effect1.PushEffect(atackChar, this);
				switch (atackSkill->classify[skillNum])
				{
				case 0:
					GiveButuriDamge(atackChar, atackSkill, skillNum, textWindow, hazureta);
					break;
				case 1:
					GiveMahouDamge(atackChar, atackSkill, skillNum, textWindow, hazureta);
					break;
				case 2:
					Cure(atackSkill, skillNum, textWindow);
					break;
				case 3:
					JoutaiIjou(atackSkill, skillNum, textWindow);
					break;
				case 4:
					statusChange(atackSkill, skillNum, textWindow);
					break;
				case 5:
					Tokusyu(atackChar, atackSkill, skillNum, textWindow);
					break;

				default:
					break;
				}
			}
			else if (atackSkill->classify[skillNum] == 2 && atackSkill->content[skillNum] == 10 && *hazureta == false) {
				Cure(atackSkill, skillNum, textWindow);
				effect1.PushEffect(atackChar, this);
			}
			else
			{
				*oneMore = true;
			}

		}
	}
	else {
		*oneMore=true;
		atackSkill->hajime = false;
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
	if (damageDisplayTime == 0 || cureDisplayTime == 0) {
		drawHP = Status[0];
	}
	if (damageDisplayTime >= 120 && cureDisplayTime >= 120) {
		drawHP = Status[0];
	}

	int bufI = 82 * drawHP / Status[15];
	//if (onlyLive == false ) {
		smallHPBar.Draw(x, y);
		if (drawHP <= MaxHP*0.2) {

			DrawBox(x + 34, y + 4, x + 34 + bufI, y + 16, RED_B, true);
		}
		else if (drawHP <= MaxHP*0.5) {

			DrawBox(x + 34, y + 4, x + 34 + bufI, y + 16, YELLOW_B, true);
		}
		else {
			DrawBox(x + 34, y + 4, x + 34 + bufI, y + 16, GREEN_B, true);
		}
	//}

}

void CCharacterBase::DrawSmallMPBar(int x, int y, bool onlyLive)
{
	if (damageDisplayTime == 0 || cureDisplayTime == 0) {
		drawMP = Status[1];
	}
	if (damageDisplayTime >= 120 && cureDisplayTime >= 120) {
		drawMP = Status[1];
	}

	int bufI = 82 * drawMP / Status[16];
	if (onlyLive == false || live == true) {
		smallMPBar.Draw(x, y);
		DrawBox(x + 34, y + 4, x + 34 + bufI, y + 16, BLUE_B, true);
	}

}

void CCharacterBase::DrawDamageAndCure()
{
	int bufI= damageDisplayTime / 2;
	if (bufI > 40) {
		bufI = 40;
	}
	if (damageDisplayTime <= 120) {
		damageDisplayTime++;
		if (damageDisplayTime >= 0) {
			DrawFormatString(x + 15, y - 15 - bufI, RED, "%d", displayDamage*-1);
		}

	}

	bufI = cureDisplayTime / 2;
	if (bufI > 40) {
		bufI = 40;
	}
	if (cureDisplayTime <= 120) {
		cureDisplayTime++;

		if (cureDisplayTime >= 0) {
			DrawFormatString(x + 15, y - 15 - bufI, GREEN_B, "+%d", displayCure);
		}
	}


	bufI = damageMPDisplayTime / 2;

	if (bufI > 40) {
		bufI = 40;

	}
	if (damageMPDisplayTime <= 120) {
		damageMPDisplayTime++;

		if (damageMPDisplayTime >= 0) {
			DrawFormatString(x + 15, y - 15 - bufI, RED, "%d", displayDamageMP*-1);
		}
	}

	bufI = cureMPDisplayTime / 2;

	if (bufI > 40) {
		bufI = 40;

	}
	if (cureMPDisplayTime <= 120 ) {
		cureMPDisplayTime++;

		if (cureMPDisplayTime >= 0) {
			DrawFormatString(x + 15, y - 15 - bufI, BLUE_B, "+%d", displayCureMP);
		}

	}

	bufI = statusChangeDisplayTime / 2;

	if (bufI > 40) {
		bufI = 40;

	}
	if (statusChangeDisplayTime <= 120 && statusChangeDisplayTime>=0) {
		statusChangeDisplayTime++;

		
		if (displayStatusChange > 0) {
			DrawFormatString(x + 30, y - 15 - bufI, ORANGE, "↑%d", displayStatusChange);
		}
		else if (displayStatusChange < 0) {
			DrawFormatString(x + 30, y - 15 - bufI, BLUE_S, "↓%d", displayStatusChange);
		}

	}

	effect1.DrawEffect();

}

void CCharacterBase::DrawStatusHenkaWindow(int x, int y)
{
	string bufS = "";

	Window[0].DrawExtend(x, y, x + 136, y + 120);
	for (int i = 0; i < 8;i++) {
		switch (i)
		{
		case 0:bufS = "物攻"; break;
		case 1:bufS = "物防"; break;
		case 2:bufS = "魔攻"; break;
		case 3:bufS = "魔防"; break;
		case 4:bufS = "速"; break;
		case 5:bufS = "命中"; break;
		case 6:bufS = "回避"; break;
		case 7:bufS = "運"; break;

		default:
			break;
		}

		if (statusHenka[i] > 0) {
			DrawFormatString(x +3 + (i%2)*70, y + 5 + (i/2) * 25, ORANGE, "%s+%d", bufS.c_str(), statusHenka[i]);
		}
		else if (statusHenka[i] < 0) {
			DrawFormatString(x + 3 + (i % 2) * 70, y + 5 + (i / 2) * 25, BLUE_S, "%s%d", bufS.c_str(), statusHenka[i]);
		}
		else {
			DrawFormatString(x + 3 + (i % 2) * 70, y + 5 + (i / 2) * 25, BLACK, "%s±%d", bufS.c_str(), statusHenka[i]);
		}
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
	MaxMP= Status[16];

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


	drawHP = MaxHP;
	drawMP = MaxMP;


}

CJiki::~CJiki()
{
}

void CJiki::Draw(int x, int y)
{
	this->x = x;
	this->y = y;

	DrawFormatString(x+35, y, BLACK, "%s", name.c_str());
	if (tenmetsu > 60 || tenmetsu % 30 <= 15 || tenmetsu<0) {
		charGraph.Draw(x, y);
	}
	if (tenmetsu < 110) {
		tenmetsu++;
	}

	DrawSmallHPBar(x , y + 35, false);
	DrawFormatString(x + 124, y + 37, BLACKNESS, "%d / %d", drawHP, Status[15]);
	DrawSmallMPBar(x , y + 35 + 23, false);
	DrawFormatString(x + 124, y + 37 + 23, BLACKNESS, "%d / %d", drawMP, Status[16]);

	if (doku) {
		DrawFormatString(x, y + 81, RED, "毒");
	}
	if (mahi) {
		DrawFormatString(x + 22, y + 81, RED, "麻痺");
	}
	if (housin) {
		DrawFormatString(x + 66, y + 81, RED, "放心");
	}
	if (huchi) {
		DrawFormatString(x + 110, y + 81, RED, "不治");
	}
	if (hirumi) {
		DrawFormatString(x + 144, y + 81, RED, "ひるみ");
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
		skill[i].classifyNum = (*haniwaSkillInfo)[skillNum[i] - 1][8];

		for (int j = 0; j < 3; j++) {

			skill[i].target[j] = (*haniwaSkillInfo)[skillNum[i] - 1][9 + j * 7];
			skill[i].classify[j] = (*haniwaSkillInfo)[skillNum[i] - 1][10 + j * 7];
			skill[i].content[j] = (*haniwaSkillInfo)[skillNum[i] - 1][11 + j * 7];
			
			if (Level < 30) {
				skill[i].power[j] = (*haniwaSkillInfo)[skillNum[i] - 1][12 + j * 7];
			}
			else if (Level < 50) {
				skill[i].power[j] = (*haniwaSkillInfo)[skillNum[i] - 1][13 + j * 7];
			}
			else if (Level < 70) {
				skill[i].power[j] = (*haniwaSkillInfo)[skillNum[i] - 1][14 + j * 7];
			}
			else {
				skill[i].power[j] = (*haniwaSkillInfo)[skillNum[i] - 1][15 + j * 7];
			}
						
		}

		skill[i].experience = (*haniwaSkillInfo)[skillNum[i] - 1][30];

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


	drawHP = MaxHP;
	drawMP = MaxMP;


}

CHaniwa::~CHaniwa()
{
}

void CHaniwa::Draw(int x, int y)
{
	this->x = x;
	this->y = y;

	DrawFormatString(x + 35 , y, BLACK, "%s", name.c_str());
	if (tenmetsu > 60 || tenmetsu % 30 <= 15 || tenmetsu<0) {
		charGraph.Draw(x, y);
	}
	if (tenmetsu < 110) {
		tenmetsu++;
	}
	DrawSmallHPBar(x , y + 35, false);
	DrawFormatString(x + 124, y +37, BLACKNESS, "%d / %d",drawHP,MaxHP);
	DrawSmallMPBar(x, y + 35 + 23, false);
	DrawFormatString(x + 124, y + 37 + 23, BLACKNESS, "%d / %d", drawMP, MaxMP);

	if (doku) {
		DrawFormatString(x, y + 81, RED, "毒");
	}
	if (mahi) {
		DrawFormatString(x + 22, y + 81, RED, "麻痺");
	}
	if (housin) {
		DrawFormatString(x + 66, y + 81, RED, "放心");
	}
	if (huchi) {
		DrawFormatString(x + 110, y + 81, RED, "不治");
	}
	if (hirumi) {
		DrawFormatString(x + 144, y + 81, RED, "ひるみ");
	}
}

CEnemy::CEnemy(CMySaveData * mySD, int kind, bool bigBoss)
{

	mySaveData = mySD;
	this->kind = kind;
	this->bigBoss = bigBoss;

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
	
	for (int i = 0; i < 3; i++) {

		bufI = GetRand(19);
		if (bufI < 8) {
			dropItem[i][0] = (*enemyInfo)[kind - 1][22 + 0 * 2];
			dropItem[i][1] = (*enemyInfo)[kind - 1][23 + 0 * 2];
		}
		else if (bufI < 14) {
			dropItem[i][0] = (*enemyInfo)[kind - 1][22 + 1 * 2];
			dropItem[i][1] = (*enemyInfo)[kind - 1][23 + 1 * 2];
		}
		else if (bufI < 18) {
			dropItem[i][0] = (*enemyInfo)[kind - 1][22 + 2 * 2];
			dropItem[i][1] = (*enemyInfo)[kind - 1][23 + 2 * 2];
		}
		else {
			dropItem[i][0] = (*enemyInfo)[kind - 1][22 + 3 * 2];
			dropItem[i][1] = (*enemyInfo)[kind - 1][23 + 3 * 2];
		}
	}

	delete enemyInfo;
	enemyInfo = NULL;

	for (int i = 0; i < 3; i++) {
		switch (dropItem[i][0]) {
		case 0:
			itemInfo = new CSV("zero/ZeroData/Sorce.csv");
			break;
		case 1:
			itemInfo = new CSV("zero/ZeroData/Tool.csv");
			break;
		case 2:
			itemInfo = new CSV("zero/ZeroData/Food.csv");
			break;

		}

		dropItemName[i] = (*itemInfo)[dropItem[i][1] - 1][1];

		delete itemInfo;
		itemInfo = NULL;
	}


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


	drawHP = MaxHP;
	drawMP = MaxMP;


}

CEnemy::~CEnemy()
{
}

void CEnemy::Draw(int x, int y, bool nameZurasi)
{
	this->x = x;
	this->y = y;

	if (live == true || damageDisplayTime<=0 ||cureDisplayTime<=0 || damageMPDisplayTime<=0 || cureMPDisplayTime<=0) {
		if (tenmetsu > 90 || tenmetsu % 30 <= 15 || tenmetsu<0) {
			charGraph.Draw(x, y);
		}
		if (tenmetsu < 110) {
			tenmetsu++;
		}

		DrawSmallHPBar(x, y - 24, true);

		if (nameZurasi == false) {
			DrawFormatString(x-5, y - 44, BLACK, name.c_str());
			
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
		if (hirumi) {
			DrawFormatString(x -6, y -105 , RED, "ひるみ");
		}


	}

}

