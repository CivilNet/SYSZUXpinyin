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

#ifndef SYSZUXPINYIN_H
#define SYSZUXPINYIN_H
#include <QFile>
#include <QWSInputMethod>
#include "ui_syszuxpinyin.h"

class SyszuxPinyin : public QDialog ,public Ui::Dialog
{
    Q_OBJECT
public:
    SyszuxPinyin(QWSInputMethod* im);
    ~SyszuxPinyin();
    void changePage(int index);
    void matching(QString gemfield);
    void initGb();
    void selectHanziPre();
    void selectHanziNext();
    void changeInputMethod();
    void changeLowerUpper();
    void clearString();
    void affirmString();
    void deleteString();
public slots:
    void buttonClickResponse(int gemfield);
signals:
    void sendPinyin(QString gemfield);
private:
    QFile pinyin_file;
    QKeyEvent *event;
    QRegExp regExp;
    QButtonGroup *button_group;
    QMultiMap<QString,QString> pinyin_map;
    QList<QString> pinyin_list;
    QVector<QPushButton*> button_vector;
    int input_method,lower_upper,page_count;
};

#endif

