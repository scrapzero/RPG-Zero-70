#include "Suken.h"
#include "MyScene.h"


/**
*	@file	Main.cpp
*	@brief	初期設定をしたり、Game.Init()を書いたり、機能追加の設定をするところです
*	@author	-
*/

SystemSetting suken::Config() {
	SystemSetting setting; //設定用構造体　System.Awake()に渡すためのもの

	/////////////＜＜ここよりした初期設定につき、自由に触ってよし＞＞//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	setting.WindowSyle = 0;						//　0:普通のウインドウ、1:タイトルバーなし、縁あり、2:タイトルバー、縁なし。
	setting.isWindow = true;					//	フルスクリーンにするかどうかのフラグ　trueなら解像度は640*480に変更される
	setting.WindowText = "SukenlibObjective";	//　左上のウインドウテキスト
	setting.iconID = 101;						//	基本弄らなくていいよ
	setting.SetWindowSize(704, 576);			//	画面サイズ設定 横22マス　縦18マス
	setting.targetFps = 60.0f;					//	目標fps設定
	setting.startLoadingMinTime = 400;			//	最初の最短ローディング時間
	setting.startGraphPath = "SukenLibAsset/LOGO/LOGO.png";	//最初のロード中に表示する画像
	setting.SetLoadingGraph("SukenLibAsset/LOGO/loading.png", 408, 64, 10, 392, 536);	//ロード中に表示するアニメーション　引数(ファイル名、pixel幅、pixel高さ、画像切り替え時間、表示座標)
//	setting.SetLoadingGraph();
	setting.isLaunchar = false;

	setting.debugWindowWidth = 500;
	setting.debugWindowHeight = 640;

	setting.InitScene(new CSTitle(), Flip::SCALEDOWN_ROTATION_RIGHT, 7);

	////////////＜＜初期設定ここまで＞＞/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return setting;//触らないでください
}

//初期化用。ほぼ初期シーン設定用
void suken::Awake() {
	Game.DebugRegistFunc("GoTitle", [] {
		Game.FlipScene(new CSTitle);
	});


}

//デバッグ用　シーンよりも先に実行される
void suken::DebugLoopEnter() {

}

//おなじくデバッグ用　シーンの後に実行される
void suken::DebugLoopExit() {

}



bool KeyOK() {
	return (Input.GetKeyEnter(Input.key.RETURN) || Input.GetKeyEnter(Input.key.Z));
}

bool KeyCancel() {
	return (Input.GetKeyEnter(Input.key.BACK) || Input.GetKeyEnter(Input.key.X));
}

bool KeyRight() {
	return (Input.GetKeyEnter(Input.key.RIGHT) );
}

bool KeyLeft() {
	return (Input.GetKeyEnter(Input.key.LEFT));
}

bool KeyUp() {
	return (Input.GetKeyEnter(Input.key.UP));
}

bool KeyDown() {
	return (Input.GetKeyEnter(Input.key.DOWN));
}