// Project
#include "GameOptions.h"
#include "ISE.h"
#include "qguiapplication.h"
#include "qdialog.h"
#include "Bible.h"
ISEBegin
	GameOptions* GameOptions::instance = 0;
GameOptions::GameOptions(QWidget *parent)
: QDialog(parent)
{
	QHBoxLayout *layout = new QHBoxLayout(this);
	stack = new QStackedWidget(this);
	layout->addWidget(stack);

	stack->addWidget(new LoginScreen(this));
	stack->addWidget(new ProfileScreen(this));
	searchScreen = new SearchScreen(this);
	searchScreen->hide();
}
GameOptions::~GameOptions()
{

}


GameOptions* GameOptions::Instance()
{
	if(!instance)
		instance = new GameOptions(ISE::Instance()->window);
	return instance;
}

void GameOptions::setCurrentIndex(int index)
{ 
  stack->setCurrentIndex(index);
  if(index >= stack->count())
    emit finished();
}

void ProfileScreen::submit()
{
	bool submitable = true;;
	for(int i = 0; i < layout->rowCount(); i++)
	{
		QLayoutItem *item = layout->itemAt(i,QFormLayout::ItemRole::FieldRole);
		QLineEdit *edit = dynamic_cast<QLineEdit*>(item->widget());
		if(!edit)
			continue;
		if(edit->text().isEmpty())
		{
			layout->itemAt(i,QFormLayout::ItemRole::LabelRole)->widget()->setStyleSheet("color:red;");
			submitable = false;
		}
		else
			layout->itemAt(i,QFormLayout::ItemRole::LabelRole)->widget()->setStyleSheet("");

	}
	if(submitable)
	{
		stack->hide();
		stack->close();
		stack->searchScreen->show();
	}
}

ProfileScreen::ProfileScreen(GameOptions *widget)
{
    stack = widget;
    //New profile
	layout = new QFormLayout(this);
	layout->addRow("Account Name", new QLineEdit());
	layout->addRow("First Name", new QLineEdit());
	layout->addRow("Last Name", new QLineEdit());
	layout->addRow("Email Address", new QLineEdit());
	layout->addRow("Password", new QLineEdit());
	layout->addRow("Confirm Password", new QLineEdit());
    QPushButton *button = new QPushButton("Submit");
	connect(button, SIGNAL(clicked()), this, SLOT(submit()));
    button->setStyleSheet("font: 30px");
	layout->addWidget(button);
	layout->setRowWrapPolicy(QFormLayout::WrapAllRows);
  };
void SearchScreen::loadBox(QComboBox* box)
{
	if(box->objectName().contains("Book"))
		foreach(Book *book, Bible::Instance()->data.values())
		box->addItem(book->name);
	if(box->objectName().contains("Chapter"))
		foreach(StructureType *chapter, Bible::Instance()->data.value(currentBook)->data.values())
		{
			box->addItem(chapter->name);
			qDebug() << chapter->name;
	}
	if(box->objectName().contains("Verse"))
		foreach(Verse *verse, Bible::Instance()->findVerses(currentBook,currentChapter,""))
		box->addItem(verse->number);
}
SearchScreen::SearchScreen(GameOptions *widget)
  {
	  setPixmap(ISE::imagesPath("scroll.png"));
	  GameOptions *options = widget;
	  QDialog *dialog = new QDialog(widget);
	  layout = new QFormLayout(dialog);
	  QComboBox *box = new QComboBox(widget);
	  box->setObjectName("Book");
	  layout->addRow("Book", box);
	  loadBox(box);

	  box = new QComboBox(widget);
	  box->setObjectName("Chapter");
	  layout->addRow("Starting Chapter", box);

	  box = new QComboBox(widget);
	  box->setObjectName("Chapter");
	  layout->addRow("Ending Chapter", box);

	  box = new QComboBox(widget);
	  box->setObjectName("Verse");
	  layout->addRow("Starting Verse", box);

	  box = new QComboBox(widget);
	  box->setObjectName("Verse");
	  layout->addRow("Ending Verse", box);
	  //QPushButton *submit = new QPushButton("Submit",widget);
	  //layout->add(submit);
	QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(this);
	proxy->setOpacity(.8);
	proxy->setWidget(dialog);
	proxy->moveBy(-1200,-300);

    result = new QTextEdit();
	result->resize(boundingRect().width() - 400, boundingRect().height() - 400);
	proxy = new QGraphicsProxyWidget(this);
	proxy->setWidget(result);
		proxy->setOpacity(.5);
	proxy->moveBy(200,200);

	updateComboBoxes();
  };

void SearchScreen::updateComboBoxes()
{
	for(int i = 0; i < layout->rowCount(); i++)
	{
		QLayoutItem *item = layout->itemAt(i,QFormLayout::ItemRole::FieldRole);
		if(!item)
			continue;
		QComboBox *combo = dynamic_cast<QComboBox*>(item->widget());
		if(!combo)
			continue;
		combo->setInsertPolicy(QComboBox::InsertPolicy::InsertAtBottom);
		if(!combo->count())
			combo->setEnabled(false);
		combo->setCurrentIndex(-1);
		connect(combo, SIGNAL(currentIndexChanged(int)),
			this, SLOT(currentIndexChanged(int)));

	}
}

void SearchScreen::currentIndexChanged(int index)
{
	QComboBox *comboBox = dynamic_cast<QComboBox*>(QObject::sender());
	if(!comboBox)
		return;
	if(comboBox->currentText().isEmpty())
		return;
	QString name = comboBox->objectName();
	QString type;
	if(name.contains("Book"))
	{
		currentBook = comboBox->currentText();
		type = "Chapter";
	}
	if(name.contains("Chapter"))
	{
		currentChapter = comboBox->currentText();
		type = "Verse";
	}
	if(type.isEmpty())
		return;
	for(int i = 0; i < layout->rowCount(); i ++)
	{
		QLayoutItem *item = layout->itemAt(i,QFormLayout::ItemRole::FieldRole);
		if(!item)
			continue;
		QComboBox* box = dynamic_cast<QComboBox*>(item->widget());
		if(box->objectName().contains(type))
		{
			loadBox(box);
			box->setCurrentIndex(-1);
			box->setEnabled(true);
		}
	}
	findText();
}

void SearchScreen::findText()
{
	QString book, chapter, verse;
	for(int i = 0; i < layout->rowCount(); i ++)
	{
		QLayoutItem *item = layout->itemAt(i,QFormLayout::FieldRole);
		if(!item)
			continue;
		QComboBox* box = dynamic_cast<QComboBox*>(item->widget());
		if(box->objectName().contains("Book"))
		{
			book = box->currentText();
		}
		if(box->objectName().contains("Chapter"))
		{
			chapter+= box->currentText();
		}
		if(box->objectName().contains("Verse"))
		{
			 verse+= box->currentText();
		}
	}

	result->setPlainText(Bible::Instance()->findText(book,chapter,verse));
}
ISEEnd