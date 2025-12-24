#pragma once

#include <QWidget>
#include "ui_UserLogin.h"
#include "BasicWindow.h"

class UserLogin : public BasicWindow
{
	Q_OBJECT

public:
	UserLogin(QWidget *parent = nullptr);
	~UserLogin();

private slots:
	void onLoginBtnClicked();

private:
	void initControl();

private:
	Ui::UserLogin ui;
};

