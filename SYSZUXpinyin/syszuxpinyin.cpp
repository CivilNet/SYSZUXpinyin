/***************************************************************************
**
**  <SYSZUXpinyin 1.0 , a chinese input method based on Qt for Embedded linux>
**  Copyright (C) <2010> <Gemfield> <gemfield@civilnet.cn>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License version 3 as published
**  by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
**  If you have questions regarding the use of this file, please contact
**  Gemfield at gemfield@civilnet.cn or post your questions at
**  http://civilnet.cn/syszux/bbs
**
****************************************************************************/

#include <QtGui>
#include "syszuxpinyin.h"
#include "syszuxim.h"
QString syszux_lower_letter[52]={"1","2","3","4","5","6","7","8","9","0","-","=","backspace","q","w","e","r","t","y","u","i",
                            "o","p","[","]","\\","a","s","d","f","g","h","j","k","l",";","\'","enter","z","x","c","v",
                            "b","n","m",",",".","/","shift"," "};
QString syszux_upper_letter[52]={"!","@","#","$","%","^","&&","*","(",")","_","+","backspace","Q","W","E","R","T","Y","U","I",
                            "O","P","{","}","|","A","S","D","F","G","H","J","K","L",":","\"","enter","Z","X","C","V",
                            "B","N","M","<",">","?","SHIFT"," "};
SyszuxPinyin::SyszuxPinyin(QWSInputMethod* im) :QDialog(0,Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint),button_group(new QButtonGroup(this)),input_method(0),lower_upper(0),page_count(0)
{
    int ret=0;
    setupUi(this);
    //resize(800,480);
    initGb();
    pinyin_file.setFileName(":/syszux/syszuxpinyin");

    if( !pinyin_file.open(QIODevice::ReadOnly) )
        QMessageBox::warning(0,tr("syszuxpinyin"),tr("can't load"));

    regExp.setCaseSensitivity(Qt::CaseSensitive);
    regExp.setPattern(QString("([a-z]+)"));

    while(!pinyin_file.atEnd())
    {
        QByteArray data = pinyin_file.readLine();
        ret = regExp.indexIn(QString(data.data()),0,QRegExp::CaretAtZero);
        pinyin_map.insert(regExp.cap(1),data.left(ret));
    }
    connect(this,SIGNAL(sendPinyin(QString)),im,SLOT(confirmString(QString)));
}
SyszuxPinyin::~SyszuxPinyin()
{
}
void SyszuxPinyin::initGb()
{
    QPushButton *pushButton=new QPushButton(this);
    pushButton->hide();
    pushButton=pushButton_hanzi_left;
    for(int i=1;i<67;i++)
    {
        button_vector.push_back(pushButton);
        button_group->addButton(pushButton,i);
        pushButton=qobject_cast<QPushButton *>(pushButton->nextInFocusChain());
    }
    connect(button_group,SIGNAL(buttonClicked(int)),SLOT(buttonClickResponse(int)));
}
void SyszuxPinyin::buttonClickResponse(int gemfield)
{
    if(gemfield==1)
    {
        selectHanziPre();
        return;
    }
    else if(gemfield==10)
    {
        selectHanziNext();
        return;
    }
    else if(gemfield<10)
    {
        lineEdit_window->insert(button_vector.at(gemfield-1)->text());
        lineEdit_pinyin->clear();
        clearString();
        return;
    }
    else if(gemfield==23)
    {
        deleteString();
        return;
    }
    else if(gemfield==59)
    {
         changeLowerUpper();
         return;
    }

    else if(gemfield>10 && gemfield<=60)
    {
        if(lower_upper)
            event=new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier,syszux_upper_letter[gemfield-11]);
        else
            event=new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier,syszux_lower_letter[gemfield-11]);
    }
    else if(gemfield==61)
    {
        changeInputMethod();
        return;
    }
    else if(gemfield==62)
    {
        affirmString();
        return;
    }
    else if(gemfield>62)
    {
        switch(gemfield)
        {
        case 63:
            event=new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
            break;
        case 64:
            event=new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
            break;
        case 65:
            event=new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
            break;
        case 66:
            event=new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
            break;
        }
    }
    if(input_method)
    {
        lineEdit_pinyin->setFocus();
        QApplication::sendEvent(focusWidget(),event);
        matching(lineEdit_pinyin->text());
    }
    else
    {
        lineEdit_window->setFocus();
        QApplication::sendEvent(focusWidget(),event);
    }
}
void SyszuxPinyin::matching(QString gemfield)
{
    pinyin_list = pinyin_map.values(gemfield);
    changePage(0);
    page_count=0;
}

void SyszuxPinyin::changePage(int index)
{
    int count = pinyin_list.size();
    int i=index*8,j=0;
    while(++j != 9 )
        button_vector.at(j)->setText(tr(pinyin_list.value(count-(++i)).toAscii()));
    if(index==0)
        pushButton_hanzi_left->setEnabled(false);
    else
        pushButton_hanzi_left->setEnabled(true);
    if(pinyin_list.size()>(index*8+8))
        pushButton_hanzi_right->setEnabled(true);
    else
        pushButton_hanzi_right->setEnabled(false);
}

void SyszuxPinyin::selectHanziPre()
{
    changePage(--page_count);
}

void SyszuxPinyin::selectHanziNext()
{
    changePage(++page_count);
}
void SyszuxPinyin::clearString()
{
    int i=0;
    while(++i!=9)
        button_vector.at(i)->setText("");
}
void SyszuxPinyin::changeInputMethod()
{
    if(pushButton_shift->text()=="SHIFT")
        return;
   lineEdit_pinyin->clear();
   if(pushButton_is_hanzi->text()=="Eng")
       input_method=1,pushButton_is_hanzi->setText("CH");
   else
       input_method=0,pushButton_is_hanzi->setText("Eng");
}
void SyszuxPinyin::changeLowerUpper()
{
    if(pushButton_shift->text()=="shift")
    {
        lower_upper=1,pushButton_shift->setText("SHIFT");
        input_method=0,pushButton_is_hanzi->setText("Eng");
        int i=9;
        while(++i!=59)
            button_vector.at(i)->setText(syszux_upper_letter[i-10]);
    }
    else
    {
        lower_upper=0,pushButton_shift->setText("shift");
        int i=9;
        while(++i!=59)
            button_vector.at(i)->setText(syszux_lower_letter[i-10]);
    }
}
void SyszuxPinyin::deleteString()
{
    event=new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    if(input_method)
    {
        lineEdit_pinyin->text().isEmpty()?lineEdit_window->setFocus():lineEdit_pinyin->setFocus();
        QApplication::sendEvent(focusWidget(),event);
        matching(lineEdit_pinyin->text());
    }
    else
    {
        lineEdit_window->setFocus();
        QApplication::sendEvent(focusWidget(),event);
    }
}
void SyszuxPinyin::affirmString()
{
    emit sendPinyin(lineEdit_window->text());
    this->hide();
}




