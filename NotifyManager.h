#pragma once

#include <QObject>
#include "CommonUtils.h"

class NotifyManager  : public QObject
{
	Q_OBJECT

public:
	NotifyManager();
	~NotifyManager();
signals:
	void signalSkinChanged(const QColor& color);

public:
	static NotifyManager* getInstance();

	void notifyOtherWindowChangeSkin(const QColor& color);

private:
	static NotifyManager* instance;
};

