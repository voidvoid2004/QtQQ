#pragma once

#include <QPixmap>
#include <QSize>
#include <QProxystyle>

class CustomProxyStyle : public QProxyStyle
{
public:
	CustomProxyStyle(QObject* parent)
	{
		setParent(parent);
	}

	virtual void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const
	{
		if (PE_CustomBase == element)
		{
			return;
		}
		else
		{
			QProxyStyle::drawPrimitive(element, option, painter, widget);
		}
	}
};


class CommonUtils
{
public:
	CommonUtils();
public:
	static QPixmap getRoundImage(const QPixmap& src, QPixmap& mask, QSize maskSize = QSize(0, 0));		// 获取图片资源
	static void loadStyleSheet(QWidget* widget, const QString& sheetName);								// 加载皮肤
	static void setDefaultSkinColor(const QColor& color);												// 默认的颜色
	static QColor getDefaultSkinColor();																// 获取颜色
};

