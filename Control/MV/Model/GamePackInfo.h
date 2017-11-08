#ifndef MODEL_GAME_PACK_INFO_H
#define MODEL_GAME_PACK_INFO_H

#include <QString>
#include <QDateTime>

class GamePackInfo {
	enum SIGNATURE_STATUS {
		SIGNATURE_STATUS_UNKNOWN = 0, // ״̬δ֪ ---
		SIGNATURE_STATUS_NOT = 1,     // δǩ��
		SIGNATURE_STATUS_DONE = 2,    // ��ǩ��
	};

	enum OPERATE_STATUS {
		OPERATE_STATUS_UNKNOWN = 0,     // �ϴ����ӹ̡�����ʧ�� �޲���
		OPERATE_STATUS_DOWNLOAD = 1,    // ��ʾ���ذ�ť
		OPERATE_STATUS_DOWNLOADING = 2, // ������... 
		OPERATE_STATUS_VIEW = 3,        // ��ʾ�鿴��ť
		OPERATE_STATUS_CANCEL = 4,      // ��ʾȡ����ť
	};

	enum PACK_STATUS {
		PACK_STATUS_UNKNOWN = 0,           // δ֪
		PACK_STATUS_START = 1,             // ���ӹ�
		PACK_STATUS_UPLOADING = 2,         // �ϴ���
		PACK_STATUS_UPLOAD_FAIL = 3,       // �ϴ�ʧ��
		PACK_STATUS_UPLOAD_SUCCESS = 4,    // �ϴ��ɹ�
		PACK_STATUS_PACKING = 5,           // �ӹ���
		PACK_STATUS_PACK_FAIL = 6,         // �ӹ�ʧ��
		PACK_STATUS_PACK_SUCCESS = 7,      // �ӹ̳ɹ�
	};

	typedef struct {
		PACK_STATUS status;
		int progress;
		QString desc;
	}PACK_STATUS_INFO;

	typedef struct {
		SIGNATURE_STATUS status;
		int progress;
		QString desc;

	}SIGNATURE_STATUS_INFO;

	typedef struct {
		OPERATE_STATUS status;
		int progress;
		QString desc;
	}OPERATE_STATUS_INFO;

private:
	QString appName;
	QString appVersion;
	qint64 appSize;
	QDateTime commitTime;
	QString user;
	PACK_STATUS_INFO statusPack;
	SIGNATURE_STATUS_INFO statusSignature;
	OPERATE_STATUS_INFO statusOperate;

	
};


#endif