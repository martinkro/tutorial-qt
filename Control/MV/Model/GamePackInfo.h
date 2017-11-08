#ifndef MODEL_GAME_PACK_INFO_H
#define MODEL_GAME_PACK_INFO_H

#include <QString>
#include <QDateTime>

class GamePackInfo {
	enum SIGNATURE_STATUS {
		SIGNATURE_STATUS_UNKNOWN = 0, // 状态未知 ---
		SIGNATURE_STATUS_NOT = 1,     // 未签名
		SIGNATURE_STATUS_DONE = 2,    // 已签名
	};

	enum OPERATE_STATUS {
		OPERATE_STATUS_UNKNOWN = 0,     // 上传、加固、下载失败 无操作
		OPERATE_STATUS_DOWNLOAD = 1,    // 显示下载按钮
		OPERATE_STATUS_DOWNLOADING = 2, // 下载中... 
		OPERATE_STATUS_VIEW = 3,        // 显示查看按钮
		OPERATE_STATUS_CANCEL = 4,      // 显示取消按钮
	};

	enum PACK_STATUS {
		PACK_STATUS_UNKNOWN = 0,           // 未知
		PACK_STATUS_START = 1,             // 待加固
		PACK_STATUS_UPLOADING = 2,         // 上传中
		PACK_STATUS_UPLOAD_FAIL = 3,       // 上传失败
		PACK_STATUS_UPLOAD_SUCCESS = 4,    // 上传成功
		PACK_STATUS_PACKING = 5,           // 加固中
		PACK_STATUS_PACK_FAIL = 6,         // 加固失败
		PACK_STATUS_PACK_SUCCESS = 7,      // 加固成功
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