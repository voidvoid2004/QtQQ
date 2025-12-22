#pragma once

#include <QDialog>
#include "titlebar.h"

class BasicWindow  : public QDialog
{
	Q_OBJECT

public:
	BasicWindow(QWidget *parent = nullptr);
	virtual ~BasicWindow();

public:
	void loadStyleSheet(const QString& sheetName);			//加载样式表
	QPixmap getRoundImage(const QPixmap& src, QPixmap& mask, QSize maskSize = QSize(0, 0));  //获取圆头像

private:
	void initBackGroundColor();

protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

protected:
	void initTitleBar(ButtonType buttonType = MIN_BUTTON);
	void setTitleBarTitle(const QString& title, const QString& icon = "");

public slots:
	void onShowClose(bool);
	void onShowMin(bool);
	void onShowHide(bool);
	void onShowNormal(bool);
	void onShowQuit(bool);
	void onSignalSkinChange(const QColor& color);

	void onButtonMinClicked();
	void onButtonMaxClicked();
	void onButtonRestoreClicked();
	void onButtonCloseClicked();

protected:
	QPoint m_mousePoint;					//鼠标位置
	bool m_mousePressed;					//鼠标是否按下
	QColor m_colorBackGround;				//背景色
	QString m_styleName;					//样式文件名称
	TitleBar* m_titleBar;					//标题栏
};

