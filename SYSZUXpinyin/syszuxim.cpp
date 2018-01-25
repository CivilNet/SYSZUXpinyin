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

#include "syszuxim.h"
#include "syszuxpinyin.h"

SyszuxIM::SyszuxIM()
{
        syszuxpinyin = new SyszuxPinyin(this);
        syszuxpinyin->resize(800,480);
}
SyszuxIM::~SyszuxIM()
{
    syszuxpinyin->deleteLater();
}

void SyszuxIM::confirmString(QString gemfield)
{
        sendCommitString(gemfield);
}

void SyszuxIM::updateHandler(int type)
{
        switch(type)
        {
        case QWSInputMethod::FocusIn:
            syszuxpinyin->show();
            break;
        case QWSInputMethod::FocusOut:
            syszuxpinyin->hide();
            break;
        default:
            break;
        }
}


