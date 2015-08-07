// Project
#include "GameBar.h"
#include "ISE.h"
#include "qfile.h"
#include "qtextstream.h"

#define WIDTH 225
ISEBegin

GameBar::GameBar()
  : QToolBar()
{
	setFixedWidth(WIDTH);
	setMovable(false);
	QToolButton *button = gameButton();;
	button->setText("Shannon");
	button->setIcon(QIcon(QPixmap(ISE::imagesPath("user.png")).scaled(150,170)));
	connect(button,SIGNAL(clicked()), this, SLOT(showOverlay()));
	button = gameButton();;

	button->setText("Hebrews");
	button->setIcon(QIcon(QPixmap(ISE::imagesPath("Section.png")).scaled(150,170)));

	addSeparator();
	QLabel *spacer = new QLabel();
	spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	addWidget(spacer);
	button = new QToolButton();
	button->setFixedSize(200,300);
	button->setIcon(QIcon(QPixmap(ISE::imagesPath("john.png")).scaled(200,300)));
	button->setIconSize(QSize(200,300));
	setFont(QFont("calibri",20));
	setIconSize(QSize(200,300));
	addWidget(button);
		button = new QToolButton();
	button->setFixedSize(200,300);
	button->setIcon(QIcon(QPixmap(ISE::imagesPath("sack.png")).scaled(150,170)));
	button->setIconSize(QSize(200,300));
	setFont(QFont("calibri",16));
	setIconSize(QSize(200,300));
	addWidget(button);
}


GameBar::~GameBar()
{

}

QToolButton* GameBar::gameButton()
{
	QToolButton *button = new QToolButton(this);
	button->setFixedSize(WIDTH,WIDTH);
	button->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
	addWidget(button);
	return button;

}
void GameBar::showOverlay()
{
	QGraphicsRectItem *item = ISE::Instance()->viewer->overlay;
	item->setVisible(!item->isVisible());
}
ISEEnd