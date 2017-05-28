#pragma once

/**
*	@file	Scene.h
*	@brief	�F�X�l�ߍ��݂������@���Ȃ͂��Ă���@����͂��Ă��Ȃ��@cpp�͔����ȏ�V�[���؂�ւ����ʂ���
*	@author	Photon
*/

#include "../Utility/Graph.h"
#include "Object\Transform.h"
#include "Object\Object.h"
#include "../Utility/UniquePtr.h"
#include "../Utility/safe_vector.h"
#include <string>
#include <list>
#include <queue>
#include <map>
#include <typeinfo>
#include <functional>

namespace suken {
	/**
	*	@brief�@�����\���́@�C�ɂ��Ȃ��Ă�����
	*/
	struct DrawMode {
		unsigned char blendMode, param;
		unsigned char red, green, blue;
		DrawMode(unsigned char blendMode, unsigned char param, unsigned char red, unsigned char green, unsigned char blue);
	};

	/**
	*	@brief�@�����\���́@�t���b�v�A�j���[�V�����́@Flip::�`�@�̂悤�Ɏw�肷���
	*/
	struct Flip {
		enum Type {
			CROSS_FADE,
			FADE_OUT_IN,
			SLIDE_UP,
			SLIDE_DOWN,
			SLIDE_RIGHT,
			SLIDE_LEFT,
			SCALEDOWN_ROTATION_RIGHT,
			SCALEDOWN_ROTATION_LEFT,
			PUSH_UP,
			PUSH_DOWN,
			PUSH_RIGHT,
			PUSH_LEFT,
			ROTATION_RIGHT,
			ROTATION_LEFT,
			ROTATION_UP,
			ROTATION_DOWN,
			DOOR_DEPTH_VERTICAL,
			DOOR_COME_VERTICAL,
			DOOR_DEPTH_HORIZONTAL,
			DOOR_COME_HORIZONTAL,
			CROSS_SLIDE_HORIZONTAL,
			DEFAULT
		};
	private:
		enum {
			maxCount = 256
		};

		Flip(Type type = DEFAULT,const char* ruleGraph = "", const char* ruleGraph2 = "", unsigned char speed = 10,unsigned char gradate = 1);

		void SetDrawMode(DrawMode* drawMode);

		bool Draw(Graph now, Graph next, DrawMode* dNow, DrawMode* dNext);

		bool DrawAppear(Graph screen,DrawMode* mode);

		bool DrawDisappear(Graph screen, DrawMode* mode);

		Type type;
		Graph graph, graph2;
		unsigned char gradate;
		unsigned char speed;
		unsigned char cnt;//count�̎��B�g�p�������L���O��ʂɓ���̂ŁA�O�����ϐ��ɓa������

		friend class CGame;
		friend class CScene;
		friend struct SystemSetting;
	};

	/**
	*	@brief�@�V�[���N���X����@FlipScene�ɂ͂���̌p���N���X����ꂽ�炢����@�q�V�[����ǉ��ł����
	*/
	class CScene {
	public:
		/**
		*	@brief�@����̃R���X�g���N�^
		*/
		CScene();

		/**
		*	@brief�@�ŏ�����q�V�[�������������Ƃ��Ɏg��
		*/
		CScene(CScene* scene);

		/**
		*	@brief�@�ŏ�����q�V�[�������������Ƃ��Ɏg���@���[���摜�g�p�g�����V�W����
		*/
		CScene(CScene* scene, const char* ruleGraph, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief�@�ŏ�����q�V�[�������������Ƃ��Ɏg���@���[���摜��g�p�g�����V�W����
		*/
		CScene(CScene* scene, const char* ruleGraph, const char* ruleGraph2, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief�@�ŏ�����q�V�[�������������Ƃ��Ɏg���@Flip.�`�Ŏw�肷����
		*/
		CScene(CScene* scene, Flip::Type flipType, unsigned char speed = 10);

		/**
		*	@brief�@�f�X�g���N�^
		*/
		virtual ~CScene();

		/**
		*	@brief�@�q�V�[���؂�ւ�
		*/
		void FlipScene(CScene* scene);

		/**
		*	@brief�@�q�V�[���؂�ւ��@���[���摜�g�p�g�����V�W����
		*/
		void FlipScene(CScene* scene, const char* ruleGraph, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief�@�q�V�[���؂�ւ��@���[���摜��g�p�g�����V�W����
		*/
		void FlipScene(CScene* scene, const char* ruleGraph, const char* ruleGraph2, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief�@�q�V�[���؂�ւ��@Flip.�`�Ŏw�肷����
		*/
		void FlipScene(CScene* scene, Flip::Type flipType, unsigned char speed = 10);

		/**
		*	@brief�@�q�V�[���폜
		*/
		void RemoveScene();

		/**
		*	@brief�@�q�V�[���폜�@���[���摜�g�p�g�����V�W����
		*/
		void RemoveScene(const char* ruleGraph, unsigned char speed = 10, unsigned char gradate = 1);

		/**
		*	@brief�@�q�V�[���폜�@Flip.�`�Ŏw�肷����
		*/
		void RemoveScene(Flip::Type flipType, unsigned char speed = 10);

		/**
		*	@brief�@�N���X��p�̃}�l�[�W���[�̎g�p�錾
		*/
		template<typename Object>
		void UseManager() {
			if (managerKey.count(typeid(Object).raw_name()) > 0)return;
			managerKey.insert(std::map<std::string, const char>::value_type(std::string(typeid(Object).raw_name()),manager().size()));
			manager().push_back(new CManager<Object>());
		}

		/**
		*	@brief�@�N���X��p�̃}�l�[�W���[�̎g�p�錾 �R���X�g���N�^�g�p�o�[�W����
		*/
		template<typename Object>
		void UseManager(CManager<Object>* ptr) {
			if (managerKey.count(typeid(Object).raw_name()) > 0)return;
			managerKey.insert(std::map<std::string, const char>::value_type(std::string(typeid(Object).raw_name()), manager().size()));
			manager().push_back(ptr);
		}

		/**
		*	@brief�@���ʂɃI�u�W�F�N�g�ǉ�
		*/
		void AddObject(CObject* object);

		/**
		*	@brief�@�N���X��p�̃}�l�[�W���[�ɃI�u�W�F�N�g�ǉ��@���݂��Ȃ��Ȃ�false�@�g�p�錾���܂��傤
		*/
		template<class Object>
		bool AddObjectToManager(Object* object) {
			auto it = managerKey.find(typeid(Object).raw_name());
			if (it == managerKey.end())return false;
			object->SetScene(this);
			(static_cast<CManager<Object>*>(manager()[it->second]))->AddObject(object);
			return true;
		}

		/**
		*	@brief�@�N���X��p�̃}�l�[�W���[�擾�@���݂��Ȃ��Ȃ�nullptr Algorithm�g�������Ȃ炢��Ȃ��@���ꉻ���ꂽ�}�l�[�W���[����
		*/
		template<class Object>
		CManager<Object>* GetManager() {
			auto it = managerKey.find(typeid(Object).raw_name());
			if (it == managerKey.end())return nullptr;
			return static_cast<CManager<Object>*>(manager()[it->second]);//�R�[�h�����Ԉ���Ă��Ȃ�������A�m���ɃL���X�g�ł��A���z�p���ł͂Ȃ��̂ŁA���Ȃ�
		}

		/**
		*	@brief�@�X�N���[���l�w��@�X�N���[���͎蓮�ł��@�V�[�����Ƃɋ��L�Ǘ��ł��邩��A�\�����낤
		*/
		void SetScrol(float x = 0, float y = 0);

		/**
		*	@brief�@�X�N���[���l�擾�@�X�N���[���͎蓮�ł��@�V�[�����Ƃɋ��L�Ǘ��ł��邩��A�\�����낤
		*/
		Twin<float> GetScrol();

		/**
		*	@brief�@�X�N���[���l�擾�@�X�N���[���͎蓮�ł��@�V�[�����Ƃɋ��L�Ǘ��ł��邩��A�\�����낤
		*/
		float GetScrolX();

		/**
		*	@brief�@�X�N���[���l�擾�@�X�N���[���͎蓮�ł��@�V�[�����Ƃɋ��L�Ǘ��ł��邩��A�\�����낤
		*/
		float GetScrolY();

		/**
		*	@brief�@�V�[���̃u�����h���[�h��ݒ�@�ڂ�����DxLib��SetDrawBlendMode�̃��t�@�����X���Q��
		*/
		void SetBlendMode(unsigned char blendMode = DX_BLENDMODE_NOBLEND,unsigned char param = 255);

		/**
		*	@brief�@�V�[���̕`��P�x��ݒ�@�ڂ�����DxLib��SetDrawBright�̃��t�@�����X���Q��
		*/
		void SetBright(unsigned char red,unsigned char green,unsigned char blue);

		/**
		*	@brief�@�`�惂�[�h���擾�@nullptr�ɒ���
		*/
		DrawMode* GetDrawMode();

		/**
		*	@brief	�w�i�摜�ݒ�@�g���Ȃ�ǂ���
		*/
		void SetBackGround(const char* fileName);

		/**
		*	@brief	�f�o�b�O�E�C���h�E�ɕ�����o�́@�g�����t���[������
		*/
		void DebugPrint(const char* name, const char* string);

		/**
		*	@brief	�f�o�b�O�E�C���h�E�Ƀt���O�o�́@�g�����t���[������
		*/
		void DebugPrintFlag(const char* name, bool flag);

		/**
		*	@brief	�f�o�b�O�E�C���h�E������s�ł���֐��@�@Start�Ŋ֐����ƂɈ�x�g��
		*/
		void DebugRegistFunc(const char* name, std::function<void()> func);

		/**
		*	@brief	�f�o�b�O�E�C���h�E������s�ł���֐��@�@Start�Ŋ֐����ƂɈ�x�g��
		*/
		void DebugRegistFuncInt(const char* name, std::function<void(int)> func);

		/**
		*	@brief	�f�o�b�O�E�C���h�E������s�ł���֐��@�@Start�Ŋ֐����ƂɈ�x�g��
		*/
		void DebugRegistFuncDouble(const char* name, std::function<void(double)> func);

		/**
		*	@brief	�f�o�b�O�E�C���h�E�ɕϐ��o�́@Start�ŕϐ����ƂɈ�x�g���@�V�[�����ɏ����Ȃ�Remove�g��
		*/
		void DebugRegist(const char* name, unsigned char* value);

		/**
		*	@brief	�f�o�b�O�E�C���h�E�ɕϐ��o�́@Start�ŕϐ����ƂɈ�x�g���@�V�[�����ɏ����Ȃ�Remove�g��
		*/
		void DebugRegist(const char* name, int* value);

		/**
		*	@brief	�f�o�b�O�E�C���h�E�ɕϐ��o�́@Start�ŕϐ����ƂɈ�x�g���@�V�[�����ɏ����Ȃ�Remove�g��
		*/
		void DebugRegist(const char* name, unsigned int* value);

		/**
		*	@brief	�f�o�b�O�E�C���h�E�ɕϐ��o�́@Start�ŕϐ����ƂɈ�x�g���@�V�[�����ɏ����Ȃ�Remove�g��
		*/
		void DebugRegist(const char* name, float* value);

		/**
		*	@brief	�f�o�b�O�E�C���h�E�ɕϐ��o�́@Start�ŕϐ����ƂɈ�x�g���@�V�[�����ɏ����Ȃ�Remove�g��
		*/
		void DebugRegist(const char* name, double* value);

		/**
		*	@brief	�f�o�b�O�E�C���h�E�ɕϐ��o�́@Start�ŕϐ����ƂɈ�x�g���@�V�[�����ɏ����Ȃ�Remove�g��
		*/
		void DebugRegist(const char* name, bool* value);

		/**
		*	@brief	���I�m�ۂ����ϐ��A�I�u�W�F�N�g�̕ϐ��͏������Ɏg��
		*/
		void DebugRemove(unsigned char* value);

		/**
		*	@brief	���I�m�ۂ����ϐ��A�I�u�W�F�N�g�̕ϐ��͏������Ɏg��
		*/
		void DebugRemove(int* value);

		/**
		*	@brief	���I�m�ۂ����ϐ��A�I�u�W�F�N�g�̕ϐ��͏������Ɏg��
		*/
		void DebugRemove(unsigned int* value);

		/**
		*	@brief	���I�m�ۂ����ϐ��A�I�u�W�F�N�g�̕ϐ��͏������Ɏg��
		*/
		void DebugRemove(float* value);

		/**
		*	@brief	���I�m�ۂ����ϐ��A�I�u�W�F�N�g�̕ϐ��͏������Ɏg��
		*/
		void DebugRemove(double* value);

		/**
		*	@brief	���I�m�ۂ����ϐ��A�I�u�W�F�N�g�̕ϐ��͏������Ɏg��
		*/
		void DebugRemove(bool* value);

	private:
		CScene(bool fake);

		/**
		*	@brief�@FlipScene���Ɏ��s�����B�������p�@���z�֐��@
		*/
		virtual void Start();

		void Update();

		/**
		*	@brief�@���t���[�����s�@���z�֐�
		*/
		virtual void Loop();

		void Graphic();

		/**
		*	@brief�@���t���[�����s�@�`��p�@���z�֐�
		*/
		virtual void Draw();

		/**
		*	@brief�@���t���[���̍Ō�Ɏ��s�@�I�u�W�F�N�g�̍폜����
		*/
		void LoopEnd();

		/**
		*	@brief�@�V�[�����㏑�����ꂽ�Ƃ��Ɏ��s�B�㏈���p�@���z�֐�
		*/
		virtual void End();

		void Regist();

		void SetDrawMode(CScene* obj);

		void SetDrawBlendMode(CScene* obj);

		void SetDrawBright(CScene* obj);

		UniquePtr<CScene> now, next;
		Graph screen, nextScreen, backGround;
		Twin<float> scrol;
		Flip* flip;
		DrawMode* mode;
		unsigned char flag;

		CManager<CObject> object;
		safe_vector<CManagerBase> manager;//�폜���N���Ȃ��̂�vector
		std::map<std::string, const char> managerKey;//������v����̂�map

#ifdef DEBUG 
		std::list<std::pair<std::string, std::string>> debugStr;
		std::list<std::pair<std::string, bool>> debugFlag;
		std::list<std::pair<std::string, unsigned char*>> debugUchar;
		std::list<std::pair<std::string, int*>> debugInt;
		std::list<std::pair<std::string, unsigned int*>> debugUint;
		std::list<std::pair<std::string, float*>> debugFloat;
		std::list<std::pair<std::string, double*>> debugDouble;
		std::list<std::pair<std::string, bool*>> debugBool;
		std::list<std::pair<std::string, std::function<void()>>> debugFuncVoid;
		std::list<std::pair<std::string, std::function<void(int)>>> debugFuncInt;
		std::list<std::pair<std::string, std::function<void(double)>>> debugFuncDouble;
#endif 


		/**
		*	@brief�@������I�[�o�[���C�h����l�͎􂢎E����܂��@�Ǝ��̃V�[���؂�ւ����ʂ���肽���l�́A�R�[�h�����S�ɗ������������ŃI�[�o�[���C�h����΂����Ǝv���܂��@�o�O���Ă��ӔC�͎��܂���
		*/
		virtual bool FlipTransition();

		enum {
			isFliping = 1 << 0,
			isNextFlip = 1 << 1
		};

		friend class CGame;
		friend class CSystem;
		friend class CDebug;
	};
}