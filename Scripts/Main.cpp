#include "Suken.h"
#include "MyScene.h"


/**
*	@file	Main.cpp
*	@brief	�����ݒ��������AGame.Init()����������A�@�\�ǉ��̐ݒ������Ƃ���ł�
*	@author	-
*/

SystemSetting suken::Config() {
	SystemSetting setting; //�ݒ�p�\���́@System.Awake()�ɓn�����߂̂���

	/////////////����������肵�������ݒ�ɂ��A���R�ɐG���Ă悵����//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	setting.WindowSyle = 0;						//�@0:���ʂ̃E�C���h�E�A1:�^�C�g���o�[�Ȃ��A������A2:�^�C�g���o�[�A���Ȃ��B
	setting.isWindow = true;					//	�t���X�N���[���ɂ��邩�ǂ����̃t���O�@true�Ȃ�𑜓x��640*480�ɕύX�����
	setting.WindowText = "SukenlibObjective";	//�@����̃E�C���h�E�e�L�X�g
	setting.iconID = 101;						//	��{�M��Ȃ��Ă�����
	setting.SetWindowSize(704, 576);			//	��ʃT�C�Y�ݒ� ��22�}�X�@�c18�}�X
	setting.targetFps = 60.0f;					//	�ڕWfps�ݒ�
	setting.startLoadingMinTime = 400;			//	�ŏ��̍ŒZ���[�f�B���O����
	setting.startGraphPath = "SukenLibAsset/LOGO/LOGO.png";	//�ŏ��̃��[�h���ɕ\������摜
	setting.SetLoadingGraph("SukenLibAsset/LOGO/loading.png", 408, 64, 10, 392, 536);	//���[�h���ɕ\������A�j���[�V�����@����(�t�@�C�����Apixel���Apixel�����A�摜�؂�ւ����ԁA�\�����W)
//	setting.SetLoadingGraph();
	setting.isLaunchar = false;

	setting.debugWindowWidth = 500;
	setting.debugWindowHeight = 640;

	setting.InitScene(new CSTitle(), Flip::SCALEDOWN_ROTATION_RIGHT, 7);

	////////////���������ݒ肱���܂Ł���/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return setting;//�G��Ȃ��ł�������
}

//�������p�B�قڏ����V�[���ݒ�p
void suken::Awake() {
	Game.DebugRegistFunc("GoTitle", [] {
		Game.FlipScene(new CSTitle);
	});


}

//�f�o�b�O�p�@�V�[��������Ɏ��s�����
void suken::DebugLoopEnter() {

}

//���Ȃ����f�o�b�O�p�@�V�[���̌�Ɏ��s�����
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