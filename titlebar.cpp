#include "titlebar.h"
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QFile>
#include <QPainter>
#include <QPainterPath>
#include "basicwindow.h"



#define BUTTON_WIDTH 27		// 按钮宽度
#define BUTTON_HEIGHT 27	// 按钮高度
#define TITLE_HEIGHT 27		// 标题栏高度

TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
	, m_isPressed(false)
	, m_buttonType(MIN_MAX_BUTTON)
{
	initControl();
	initConnections();
	loadStyleSheet("Title");
}

TitleBar::~TitleBar()
{}

void TitleBar::setTitleIcon(const QString & filePath)
{
	QPixmap titleIcon(filePath);
	m_pIcon->setFixedSize(titleIcon.size());
	m_pIcon->setPixmap(titleIcon);
}

void TitleBar::setTitleContent(const QString& titleContent)
{
	m_pTitleContent->setText(titleContent);
	m_titleContent = titleContent;
}

void TitleBar::setTitleWidth(int width)
{
	setFixedWidth(width);
}

void TitleBar::setButtonType(ButtonType buttonType)
{
	m_buttonType = buttonType;

	switch (buttonType)
	{
	case MIN_BUTTON:
	{
		m_pButtonMax->setVisible(false);
		m_pButtonRestore->setVisible(false);
	}
		break;
	case MIN_MAX_BUTTON:
	{
		m_pButtonRestore->setVisible(false);
	}
		break;
	case ONLY_CLOSE_BUTTON:
	{
		m_pButtonMin->setVisible(false);
		m_pButtonMax->setVisible(false);
		m_pButtonRestore->setVisible(false);
	}
		break;
	default:
		break;
	}
}

void TitleBar::saveRestoreInfo(const QPoint& point, const QSize& size)
{
	m_restorePoint = point;
	m_restoreSize = size;
}

void TitleBar::getRestoreInfo(QPoint& point, QSize& size)
{
	point = m_restorePoint;
	size = m_restoreSize;
}

void TitleBar::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRoundedRect(QRect(0, 0, width(), height()), 3, 3);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	if (width() != parentWidget()->width())
	{
		setFixedWidth(parentWidget()->width());
	}

	QWidget::paintEvent(event);

}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	if(m_buttonType == MIN_MAX_BUTTON)
	{
		if(m_pButtonMax->isVisible())
		{
			onButtonMaxClicked();
		}
		else
		{
			onButtonRestoreClicked();
		}
	}
}

void TitleBar::mousePressEvent(QMouseEvent* event)
{
	if (m_buttonType == MIN_MAX_BUTTON)
	{
		if (m_pButtonMax->isVisible())
		{
			m_isPressed = true;
			m_startMovePos = event->globalPosition().toPoint();
		}
	}
	else
	{
		m_isPressed = true;
		m_startMovePos = event->globalPosition().toPoint();
	}
	return QWidget::mousePressEvent(event);
}

void TitleBar::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isPressed)
	{
		QPoint movePoint = event->globalPosition().toPoint() - m_startMovePos;
		QPoint widgetPos = this->parentWidget()->pos();
		m_startMovePos = event->globalPosition().toPoint();
		parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
	}

	return QWidget::mouseMoveEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent* event)
{
	m_isPressed = false;
	return QWidget::mouseReleaseEvent(event);
}

void TitleBar::initControl()
{
	m_pIcon = new QLabel(this);
	m_pTitleContent = new QLabel(this);
	m_pButtonMin = new QPushButton(this);
	m_pButtonMax = new QPushButton(this);
	m_pButtonClose = new QPushButton(this);
	m_pButtonRestore = new QPushButton(this);

	// 设置按钮大小
	m_pButtonMin->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pButtonMax->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pButtonClose->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_pButtonRestore->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

	// 设置对象名 
	m_pTitleContent->setObjectName("TitleContent");
	m_pButtonMin->setObjectName("ButtonMin");
	m_pButtonMax->setObjectName("ButtonMax");
	m_pButtonClose->setObjectName("ButtonClose");
	m_pButtonRestore->setObjectName("ButtonRestore");

	//设置布局
	QHBoxLayout* myLayout = new QHBoxLayout(this);
	myLayout->addWidget(m_pIcon);
	myLayout->addWidget(m_pTitleContent);
	myLayout->addWidget(m_pButtonMin);
	myLayout->addWidget(m_pButtonRestore);
	myLayout->addWidget(m_pButtonMax);
	myLayout->addWidget(m_pButtonClose);

	myLayout->setContentsMargins(5, 0, 0, 0);
	myLayout->setSpacing(0);			// 控件间距为0

	m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setFixedHeight(TITLE_HEIGHT);
	setWindowFlags(Qt::FramelessWindowHint);
}

void TitleBar::initConnections()
{
	connect(m_pButtonMin, &QPushButton::clicked, this, &TitleBar::onButtonMinClicked);
	connect(m_pButtonMax, &QPushButton::clicked, this, &TitleBar::onButtonMaxClicked);
	connect(m_pButtonClose, &QPushButton::clicked, this, &TitleBar::onButtonCloseClicked);
	connect(m_pButtonRestore, &QPushButton::clicked, this, &TitleBar::onButtonRestoreClicked);
}

void TitleBar::loadStyleSheet(const QString& sheetName)
{
	QFile file(":/Resources/QSS/" + sheetName + ".css");
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1String(file.readAll());
		setStyleSheet(styleSheet);
	}

	file.close();
}

void TitleBar::onButtonMinClicked()
{
	emit signalButtonMinClicked();
}

void TitleBar::onButtonMaxClicked()
{
	m_pButtonRestore->setVisible(true);
	m_pButtonMax->setVisible(false);
	emit signalButtonMaxClicked();
}
void TitleBar::onButtonCloseClicked()
{
	emit signalButtonCloseClicked();
}
void TitleBar::onButtonRestoreClicked()
{
	m_pButtonRestore->setVisible(false);
	m_pButtonMax->setVisible(true);
	emit signalButtonRestoreClicked(); 
}
