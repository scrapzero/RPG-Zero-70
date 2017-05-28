#pragma once

#include "../../Manager.h"
#include "../../Utility/UniquePtr.h"
#include <queue>
#include <list>

#define OBJECT_CHARM(ObjectName) friend class CScene; friend class CManager< ObjectName >;friend struct Algorithm;

namespace suken {
	class CObject;

	/**
	*	@brief	�I�u�W�F�N�g�}�l�[�W���[���ꌳ�I�Ɉ������߂̃N���X�ł��B
	*/
	class CManagerBase {
	public:
		/**
		*	�R���X�g���N�^
		*/
		CManagerBase() {}

		/**
		*	@brief	�f�X�g���N�^
		*/
		virtual ~CManagerBase() {}
	private:
		/**
		*	@brief �I�u�W�F�N�g�̓o�^���s��
		*/
		virtual void Regist() {}

		/**
		*	@brief �V�[�����q�V�[�����������Ă��Ȃ��Ƃ��ɁA���t���[���Ă΂��
		*/
		virtual void Loop() {}

		/**
		*	@brief ���t���[���Ă΂��
		*/
		virtual void Draw() {}

		/**
		*	@brief ������GetDeleteFlag()���āA�폜����邩�m���߂�
		*/
		virtual void LoopEnd() {}

		virtual int GetSize() { return 0; }

		friend class CScene;
		friend class CDebug;
		friend struct Algorithm;
	};

	/**
	*	@brief	CObject���p�������N���X��o�^���邱�Ƃ��ł��A�����Ĉ������Ƃ��ł��܂��@Algorithm�֐���p����ƁA�}�l�[�W���[�ɓ����Ă���I�u�W�F�N�g�ɑ΂��āA���삷�邱�Ƃ��ł��܂�
	*	����ׂ��@�\���ʂ����Ȃ�A���ꉻ���āA�������Ƃ������܂��B
	*/
	template<class Object>
	class CManager :public CManagerBase {
	public:
		CManager() {}

		virtual ~CManager() {}
	private:
		void AddObject(Object* object) {
			m_queue.push(object);
		}

		void Regist() {
			while (!m_queue.empty()) {
				Object* o = m_queue.front();
				m_queue.pop();
				o->Start();
				m_object.push_back(nullptr);
				m_object.back().Reset(o);
			}
		}

		void Loop() {
			for (auto i = m_object.begin(); i != m_object.end(); ++i) {
				(*i)->Loop();
			}
		}

		void Draw() {
			for (auto i = m_object.begin(); i != m_object.end(); ++i) {
				(*i)->Draw();
			}
		}

		void LoopEnd() {
			for (auto i = m_object.begin(); i != m_object.end();) {
				if ((*i)->GetDeleteFlag()) {
					(*i)->End();
					i = m_object.erase(i);
				}
				else {
					++i;
				}
			}
		}

		int GetSize() {
			return m_object.size();
		}

		std::queue<Object*> m_queue;
		std::list<UniquePtr<Object>> m_object;

		friend class CScene;
		friend class CDebug;
		friend struct Algorithm;
	};

	/**
	*	@brief�@���ׂẴI�u�W�F�N�g�̐e�ł�
	*/
	class CObject {
	public:
		/**
		*	@brief�@�R���X�g���N�^
		*/
		CObject();

		/**
		*	@brief�@�f�X�g���N�^
		*/
		virtual ~CObject();
	protected:

		/**
		*	@brief�@�I�u�W�F�N�g����������V�[���̃|�C���^�����
		*/
		CScene *const GetScene();

		/**
		*	@brief ������@Loop()���Ŏg���Ă�������
		*/
		void Delete();

		/**
		*	@brief ������钼�O���ǂ����A�m�F
		*/
		bool GetDeleteFlag();
	private:

		/**
		*	@brief�@�ŏ��ɌĂ΂��@���z�N���X
		*/
		virtual void Start();

		/**
		*	@brief�@�q�V�[�������ĂȂ����ɌĂ΂��@���z�N���X
		*/
		virtual void Loop();

		/**
		*	@brief�@�`�悷�鎞�ɌĂ΂��@���z�N���X
		*/
		virtual void Draw();

		/**
		*	@brief�@�I���̎��ɌĂ΂��@���z�N���X
		*/
		virtual void End();

		CScene* scene;

		bool deleteFlag;

		void SetScene(CScene* ptr);

		friend class CScene; 
		template <class> friend class CManager; 
		friend struct Algorithm;
	};
}