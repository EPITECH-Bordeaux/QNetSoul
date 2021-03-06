/*
  Copyright 2010 Dally Richard
  This file is part of QNetSoul.
  QNetSoul is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  QNetSoul is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with QNetSoul.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QUrl>
#include <QMimeData>
#include <QClipboard>
#include <QMessageBox>
#include <QApplication>
#include <QNetworkProxy>
#include <QNetworkRequest>
#include "Pastebin.h"

Pastebin::Pastebin(void)
{
  connect(&this->_manager, SIGNAL(finished(QNetworkReply*)),
          SLOT(replyFinished(QNetworkReply*)));
}

Pastebin::~Pastebin(void)
{
}

void    Pastebin::pastebinIt(void)
{
  const QClipboard* clipboard = QApplication::clipboard();

  //#ifdef Q_WS_X11
  //const QMimeData* mimeData = clipboard->mimeData(QClipboard::Selection);
  //#else
  const QMimeData* mimeData = clipboard->mimeData();
  //#endif

  QMessageBox mbox(QMessageBox::Question, "QNetSoul",
                   tr("Are you sure to past this ?"),
                   QMessageBox::Ok | QMessageBox::Cancel);

  if (mimeData == 0)
    {
      QMessageBox::information(NULL, "QNetSoul Pastebin",
                               tr("Clipboard is empty"));
      return;
    }
  if (mimeData->hasText())
    {
      QString post_content(mimeData->text());
      mbox.setDetailedText(post_content);
      int ret = mbox.exec();
      if (ret == QMessageBox::Cancel)
        return;

      post_content.prepend("paste_private=1&paste_code=");
      this->_manager.post
        (QNetworkRequest(QUrl("http://pastebin.com/api_public.php")),
         post_content.toAscii());
    }
  else
    {
      QMessageBox::information(NULL, "QNetSoul Pastebin",
                               tr("Clipboard has no text"));
    }
}

void    Pastebin::replyFinished(QNetworkReply* reply)
{
  if (reply->error() == QNetworkReply::NoError)
    {
      QByteArray array = reply->readAll();
      QString url = QString("<a href='%1'>%1</a>").arg(array.data());
      QMessageBox::information(NULL, "PasteBin", url);
    }
#ifndef QT_NO_DEBUG
  else
    {
      qDebug() << "[Pastebin::replyFinished]"
               << "Reply error:" << reply->errorString();
    }
#endif
  reply->deleteLater();
}
