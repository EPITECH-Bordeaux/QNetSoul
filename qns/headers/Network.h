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

#ifndef NETWORK_H
#define NETWORK_H

#include <QTimer>
#include <QTcpSocket>
#include <QStringList>

class   QNetsoul;
class   OptionsWidget;

class   Network : public QObject
{
  Q_OBJECT

    public:
  Network(QObject* parent);
  virtual ~Network(void) { this->_socket.close(); }

  void  setOptions(OptionsWidget* options) { this->_options = options; }
  QAbstractSocket::SocketState state(void) const
    { return this->_socket.state(); }
  void  sendMessage(const char* msg) { this->_socket.write(msg); }
  void  sendMessage(const QByteArray& msg) { this->_socket.write(msg); }

  void  connect(const QString& host, quint16);
  void  disconnect(void);
  void  resolveLocation(QString& oldLocation) const;

  void  refreshContact(const QString& contact);
  void  refreshContacts(const QStringList& contacts);
  void  transmitTypingStatus(const QString&, const QString&, const bool);
  void  transmitMsg(const QString&, const QString& loc, const QString& msg);
  void  monitorContact(const QString& contact);
  void  monitorContacts(const QStringList& contacts);

  public slots:
  void  sendStatus(const int& status);

 signals:
  void  handShaking(int step, QStringList);
  void  msg(const QStringList&, const QString&);
  void  state(const QStringList&);
  void  who(const QStringList&);
  void  typingStatus(const int id, bool typing);

  private slots:
  void  handleSocketState(const QAbstractSocket::SocketState& state);
  void  handleSocketError(const QAbstractSocket::SocketError& error);
  void  processPackets(void);

 private:
  void  parseLines(void);
  void  interpretLine(const QString& line);

 private:
  QNetsoul*      _ns;
  OptionsWidget* _options;
  QString        _rbuffer;
  QTcpSocket     _socket;
  int            _handShakingStep;
  QString        _host;
  quint16        _port;
  int            _retries;
  QTimer         _reconnectionTimer;
};

#endif // NETWORK_H
