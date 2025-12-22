#pragma once

#include <QWidget>

enum ButtonType
{
	MIN_BUTTON = 0,
	MIN_MAX_BUTTON,
	ONLY_CLOSE_BUTTON,
};

class TitleBar  : public QWidget
{
	Q_OBJECT

public:
	TitleBar(QWidget *parent = nullptr);
	~TitleBar();


	void setTitleIcon(const QString& filePath);									// 设置标题栏图标
	void setTitleContent(const QString& titleContent);							// 设置标题栏内容
	void setTitleWidth(int width);												// 标题栏宽度
	void setButtonType(ButtonType buttonType);									// 标题栏按钮类型

	void saveRestoreInfo(const QPoint& point, const QSize& size);				// 保存窗口最大化前,窗口的位置 + 大小
	void getRestoreInfo(QPoint& point, QSize& size);							// 获取保存的 窗口最大化前,窗口的位置 + 大小


private:
	void paintEvent(QPaintEvent* event);										// 绘图事件
	void mouseDoubleClickEvent(QMouseEvent* event);								// 鼠标双击事件
	void mousePressEvent(QMouseEvent* event);									// 鼠标按下事件
	void mouseMoveEvent(QMouseEvent* event);									// 鼠标移动事件
	void mouseReleaseEvent(QMouseEvent* event);									// 鼠标松开事件 , 就是 鼠标释放事件

	void initControl();															// 初始化控件
	void initConnections();														// 初始化信号与槽的连接
	void loadStyleSheet(const QString& sheetName);								// 加载样式表

signals:
	void signalButtonMinClicked();												// 最小化按钮点击信号
	void signalButtonMaxClicked();												// 最大化按钮点击信号
	void signalButtonCloseClicked();											// 关闭按钮点击信号
	void signalButtonRestoreClicked();											// 还原按钮点击信号

};

