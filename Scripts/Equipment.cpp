#include "Equipment.h"
#include <algorithm>

bool KeyOK();
bool KeyCancel();
bool KeyRight();
bool KeyLeft();
bool KeyUp();
bool KeyDown();


CEquipmentManager::CEquipmentManager(CMySaveData* CSD, int equipKind) : equipmentInfo("")
{
	intint kariIntInt;
	lookLocate = 0;
	lookPage = 0;
	savedata = CSD;
	equipmentAmount = CSD->GetEquipmentAmountSaveData();
	for (int i = 0;i<equipmentAmount;i++) {

		equipmentKind = CSD->GetHaveEquipmentKindLevelSaveData(i, 0);
		kariIntInt.first = CSD->GetHaveEquipmentKindLevelSaveData(i,1);
		kariIntInt.second = CSD->GetHaveEquipmentKindLevelSaveData(i,2);
		
		haveEquipmentNumLevel[equipmentKind].push_back(kariIntInt);

	}


	equipmentKind = equipKind;

	for (int i = 0; i < 5; i++) {
		wearWeaponLocate[i][0] = CSD->GetWearEquipmentLocateSaveData(i, 0);
		wearWeaponLocate[i][1] = CSD->GetWearEquipmentLocateSaveData(i, 1);
	}
	
	bufWearNumLevel[0] = 0;
	bufWearNumLevel[1] = 0;

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

	equipmentWindow = new CEquipmentWindow(equipmentKind,haveEquipmentNumLevel[equipmentKind][0].first, haveEquipmentNumLevel[equipmentKind][0].second);
	Window = "zero/TextWindow4.png";
	Arrow = "zero/Arrow.png";

}

CEquipmentManager::~CEquipmentManager() {
	int buf=0;
	equipmentAmount = 0;
	for (int i = 0; i < 7; i++) {
		equipmentAmount += haveEquipmentNumLevel[i].size();
	}

	savedata->SetEquipmentAmount(equipmentAmount);
	for (int i = 0; i < 7; i++) {
		savedata->SetWearEquipmentLocate(equipmentKind, wearWeaponLocate[i][0], wearWeaponLocate[i][1]);
	}
	
	for (int i = 0; i < 7; i++) {
		
		for (int j = 0; j<haveEquipmentNumLevel[i].size(); j++) {
			savedata->SetHaveEquipmentNumLevel(buf, i, haveEquipmentNumLevel[i][j].first, haveEquipmentNumLevel[i][j].second);
				buf++;
		}
	}
	savedata->WriteSaveData();

	delete equipmentWindow;
	equipmentWindow = NULL;
}

void CEquipmentManager::Draw()
{



}


void CEquipmentManager::LoopWindow() {

	if (KeyRight()) {
		if (lookLocate % 2 == 1 && haveEquipmentNumLevel[equipmentKind].size() > (lookPage + 1) * 20) {
			lookPage++;
			if (haveEquipmentNumLevel[equipmentKind].size() <= lookPage * 20 + lookLocate - 1) {
				lookLocate = 0;
			}
			else {
				lookLocate--;
			}
		}
		else if (lookLocate % 2 == 0 && haveEquipmentNumLevel[equipmentKind].size()>lookPage * 20 + lookLocate + 1) {
			lookLocate++;
		}
		equipmentWindow->ChangeKind(haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].first, haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].second);
	}

	if (KeyLeft()) {
		if (lookLocate % 2 == 0 && 0 <= lookPage - 1) {
			lookPage--;
			lookLocate++;
		}
		else if (lookLocate % 2 == 1) {
			lookLocate--;
		}
		equipmentWindow->ChangeKind(haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].first, haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].second);
	}

	if (KeyUp()&&lookLocate>=2) {
		lookLocate -= 2;
		equipmentWindow->ChangeKind(haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].first, haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].second);
	}

	if (KeyDown()) {
		if (lookLocate<=17&&haveEquipmentNumLevel[equipmentKind].size()>lookPage * 20 + lookLocate + 2) {
			lookLocate += 2;
		}
		else if (lookLocate <= 17&&haveEquipmentNumLevel[equipmentKind].size()>lookPage * 20 + lookLocate + 1) {
			lookLocate++;
		}
		equipmentWindow->ChangeKind(haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].first, haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].second);

	}

	if (Input.GetKeyEnter(Input.key.X)) {

		if (equipmentKind <= 2) {

			if (wearWeaponLocate[0][0] == equipmentKind) {
				bufWearNumLevel[0] = haveEquipmentNumLevel[equipmentKind][wearWeaponLocate[0][1]].first;
				bufWearNumLevel[1] = haveEquipmentNumLevel[equipmentKind][wearWeaponLocate[0][1]].second;
				std::sort(haveEquipmentNumLevel[equipmentKind].begin(), haveEquipmentNumLevel[equipmentKind].end());
				equipmentWindow->ChangeKind(haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].first, haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].second);
				for (int i = 0; i < haveEquipmentNumLevel[equipmentKind].size(); i++) {
					if (haveEquipmentNumLevel[equipmentKind][i].first == bufWearNumLevel[0] && haveEquipmentNumLevel[equipmentKind][i].second == bufWearNumLevel[1]) {
						wearWeaponLocate[0][1] = i;
					}
				}

			}
		}

		else {
			bufWearNumLevel[0] = haveEquipmentNumLevel[equipmentKind][wearWeaponLocate[equipmentKind - 2][1]].first;
			bufWearNumLevel[1] = haveEquipmentNumLevel[equipmentKind][wearWeaponLocate[equipmentKind - 2][1]].second;
			std::sort(haveEquipmentNumLevel[equipmentKind].begin(), haveEquipmentNumLevel[equipmentKind].end());
			equipmentWindow->ChangeKind(haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].first, haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].second);
			for (int i = 0; i < haveEquipmentNumLevel[equipmentKind].size(); i++) {
				if (haveEquipmentNumLevel[equipmentKind][i].first == bufWearNumLevel[0] && haveEquipmentNumLevel[equipmentKind][i].second == bufWearNumLevel[1]) {
					wearWeaponLocate[0][1] = i;
				}
			}

		}

	}

	if (Input.GetKeyEnter(Input.key.C)) {
	
		if (equipmentKind <= 2) {

			if (wearWeaponLocate[0][0] == equipmentKind) {
				bufWearNumLevel[0] = haveEquipmentNumLevel[equipmentKind][wearWeaponLocate[0][1]].first;
				bufWearNumLevel[1] = haveEquipmentNumLevel[equipmentKind][wearWeaponLocate[0][1]].second;
				std::sort(haveEquipmentNumLevel[equipmentKind].begin(), haveEquipmentNumLevel[equipmentKind].end());
				std::reverse(haveEquipmentNumLevel[equipmentKind].begin(), haveEquipmentNumLevel[equipmentKind].end());
				equipmentWindow->ChangeKind(haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].first, haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].second);
				for (int i = 0; i < haveEquipmentNumLevel[equipmentKind].size(); i++) {
					if (haveEquipmentNumLevel[equipmentKind][i].first == bufWearNumLevel[0] && haveEquipmentNumLevel[equipmentKind][i].second == bufWearNumLevel[1]) {
						wearWeaponLocate[0][1] = i;
					}
				}

			}
		}

		else {
			bufWearNumLevel[0] = haveEquipmentNumLevel[equipmentKind][wearWeaponLocate[equipmentKind - 2][1]].first;
			bufWearNumLevel[1] = haveEquipmentNumLevel[equipmentKind][wearWeaponLocate[equipmentKind - 2][1]].second;
			std::sort(haveEquipmentNumLevel[equipmentKind].begin(), haveEquipmentNumLevel[equipmentKind].end());
			std::reverse(haveEquipmentNumLevel[equipmentKind].begin(), haveEquipmentNumLevel[equipmentKind].end());
			equipmentWindow->ChangeKind(haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].first, haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].second);
			for (int i = 0; i < haveEquipmentNumLevel[equipmentKind].size(); i++) {
				if (haveEquipmentNumLevel[equipmentKind][i].first == bufWearNumLevel[0] && haveEquipmentNumLevel[equipmentKind][i].second == bufWearNumLevel[1]) {
					wearWeaponLocate[0][1] = i;
				}
			}

		}

	
	}

}

void CEquipmentManager::DrawWindow() 
{
	int myLoop=0;
	std::string equipName="";

	Window(0, 7);
	Arrow(20 +345 * (lookLocate % 2),30+(lookLocate / 2) * 30 );

	for (int i = lookPage*20; i < haveEquipmentNumLevel[equipmentKind].size();i++) {
		equipName = equipmentInfo[haveEquipmentNumLevel[equipmentKind][i].first-1][1];
		DrawFormatString(45+ 345 * (i % 2), 32 + ((i%20)/2) * 30,BLACK,"%s",equipName.c_str());
		myLoop++;
		if(myLoop>=20){
			break;
		}
	}

	DrawFormatString(40, 340, BLACK, "ページ　%d/%d  X:番号順に並べる　C:番号逆順に並べる", lookPage+1, (haveEquipmentNumLevel[equipmentKind].size() - 1) / 20 +1);

	equipmentWindow->Draw();

}

void CEquipmentManager::PushEquipment(int equipKind, int equipNum,int equipLevel)
{

	if (haveEquipmentNumLevel[equipKind].size() < 50) {
		intint kariIntInt;
		kariIntInt.first = equipNum;
		kariIntInt.second = equipLevel;
		if (haveEquipmentNumLevel[equipKind].size() < maxHaving) {
			haveEquipmentNumLevel[equipKind].push_back(kariIntInt);
		}
	}
}

int CEquipmentManager::SellEquipment(){

	int getMoney;
	int buf = haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].first - 1;
	int buff = haveEquipmentNumLevel[equipmentKind][lookLocate + lookPage * 20].second;
	int bufff = 0;

	if (equipmentKind <= 2) {
		bufff = 0;
	}
	else {
		bufff = equipmentKind - 2;
	}

	if (wearWeaponLocate[bufff][0]!= equipmentKind || wearWeaponLocate[bufff][1] != (lookPage * 20 + lookLocate)) {
		if(haveEquipmentNumLevel[equipmentKind].size()>=2){

			if (equipmentKind == wearWeaponLocate[equipmentKind][0]) {
				if (wearWeaponLocate[bufff][1]>(lookPage * 20 + lookLocate)) {
					wearWeaponLocate[bufff][1]--;
				}
			}

			if (equipmentKind <= 2) {
				getMoney = equipmentInfo[buf][31];
				getMoney *= (1 + buff/10);
			}
			else {
				getMoney = equipmentInfo[buf][24];
				getMoney *= (1 + buff / 10);
			}

			haveEquipmentNumLevel[equipmentKind].erase(haveEquipmentNumLevel[equipmentKind].begin() + (lookPage * 20 + lookLocate));
			
			if (haveEquipmentNumLevel[equipmentKind].size() == (lookPage * 20 + lookLocate)-1) {
				if (lookLocate == 0) {
					lookPage--;
					lookLocate = 19;
				}
				else {
					lookLocate--;
				}
			}

		}

		return getMoney;
	}
	return 0;
}

int CEquipmentManager::GetSize(int equipKind)
{
	return haveEquipmentNumLevel[equipKind].size();
}
