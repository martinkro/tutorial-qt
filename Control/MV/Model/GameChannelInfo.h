#ifndef MODEL_GAME_CHANNEL_INFO_H
#define MODEL_GAME_CHANNEL_INFO_H

#include <QString>

class GameChannelInfo {
public:
	enum CHANNEL_STATUS {
		CHANNEL_STATUS_UNKNOWN = 0,   // δ֪
		CHANNEL_STATUS_START = 1,     // ������
		CHANNEL_STATUS_FAIL = 2,      // ����ʧ��
		CHANNEL_STATUS_SUCCESS = 3,   // ����ɹ�
		CHANNEL_STATUS_HANDLING = 4,  // ������...
	};

	enum CHANNEL_OPERATE_STATUS {
		CHANNEL_OPERATE_STATUS_UNKNOWN = 0, // 
		CHANNEL_OPERATE_STATUS_VIEW_DIR = 1, // �鿴Ŀ¼
	};
private:
	QString filename;
	QString packageName;
	QString appVersion;
	qreal appSize;
	CHANNEL_STATUS statusChannel;
	CHANNEL_OPERATE_STATUS statusOperate;

};

#endif