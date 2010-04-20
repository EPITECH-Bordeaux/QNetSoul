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

#ifndef CONTACTSWRITER_H
#define CONTACTSWRITER_H

#include <QXmlStreamWriter>
#include "ContactWidget.h"

class	ContactsWriter : public QXmlStreamWriter
{
public:
  ContactsWriter(const QList<ContactWidget*>);
  ~ContactsWriter(void);

  bool	writeFile(QIODevice*);

private:
  void	writeContact(const ContactWidget*);
  const QList<ContactWidget*>	_contactList;
};

#endif // CONTACTSWRITER_H
