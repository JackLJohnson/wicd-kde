/****************************************************************************
 *  Copyright (c) 2011 Anthony Vital <anthony.vital@gmail.com>              *
 *                                                                          *
 *  This file is part of Wicd Client KDE.                                   *
 *                                                                          *
 *  Wicd Client KDE is free software: you can redistribute it and/or modify *
 *  it under the terms of the GNU General Public License as published by    *
 *  the Free Software Foundation, either version 3 of the License, or       *
 *  (at your option) any later version.                                     *
 *                                                                          *
 *  Wicd Client KDE is distributed in the hope that it will be useful,      *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *  GNU General Public License for more details.                            *
 *                                                                          *
 *  You should have received a copy of the GNU General Public License       *
 *  along with Wicd Client KDE.  If not, see <http://www.gnu.org/licenses/>.*
 ****************************************************************************/

#include "wicdengine.h"
#include "wicdservice.h"

WicdEngine::WicdEngine(QObject* parent, const QVariantList& args)
    : Plasma::DataEngine(parent)
{
    Q_UNUSED(args)

    setMinimumPollingInterval(1000);

    connect(DBusHandler::instance(), SIGNAL(statusChange(Status)), this, SLOT(updateStatus(Status)));
}

void WicdEngine::init()
{
    //force first status update
    m_state = 10;
    updateStatus(DBusHandler::instance()->status());
}

Plasma::Service *WicdEngine::serviceForSource(const QString &source)
{
    Q_UNUSED(source)
    return new WicdService(this, DBusHandler::instance());
}

QStringList WicdEngine::sources() const
{
    QStringList sources;
    sources<<"networks";
    sources<<"status";
    return sources;
}

bool WicdEngine::sourceRequestEvent(const QString &source)
{
    if (source == "networks") {
        updateSourceEvent(source);
        return true;
    }
    if (source == "status") {
        updateSourceEvent(source);
        return true;
    }
    return false;
}

bool WicdEngine::updateSourceEvent(const QString &source)
{
    if (source == "networks") {
        //reset
        setData(source, DataEngine::Data());
        //populate new data
        QMap<int, NetworkInfos> list = DBusHandler::instance()->networksList();
        QMap<int, NetworkInfos>::const_iterator it = list.constBegin();
        while (it != list.constEnd()) {
            setData(source, QString::number(it.key()), it.value());
            ++it;
        }
        return true;
    }
    if (source == "status") {
        setData(source, "state", m_state);
        setData(source, "info", m_info);
        setData(source, "message", m_message);
        setData(source, "interface", m_interface);
        return true;
    }
    return false;
}

void WicdEngine::updateStatus(Status status)
{
    m_state = status.State;
    m_info = status.Infos;
    m_interface = DBusHandler::instance()->callDaemon("GetCurrentInterface").toString();
    if (status.State == WicdState::CONNECTING) {
        bool wired = (status.Infos.at(0)=="wired");
        if (wired) {
            m_message = DBusHandler::instance()->callWired("CheckWiredConnectingMessage").toString();
        } else {
            m_message = DBusHandler::instance()->callWireless("CheckWirelessConnectingMessage").toString();
        }
        QTimer::singleShot(500, this, SLOT(forceUpdateStatus()));
    }
    updateSourceEvent("status");
}

void WicdEngine::forceUpdateStatus()
{
    updateStatus(DBusHandler::instance()->status());
}

#include "wicdengine.moc"
