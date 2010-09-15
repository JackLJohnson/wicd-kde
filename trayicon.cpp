/****************************************************************************
 *  Copyright (c) 2010 Anthony Vital <anthony.vital@gmail.com>              *
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

#include "trayicon.h"
#include <KMenu>
#include <KIcon>
#include <KAboutApplicationDialog>
#include <KCmdLineArgs>
#include <KAboutData>
#include <KLocalizedString>

TrayIcon::TrayIcon( QObject *parent )
    : KStatusNotifierItem( parent )
{
    setObjectName("wicdclientkde.statusnotifieritem");
    setStatus(KStatusNotifierItem::Active);
    setCategory(KStatusNotifierItem::Communications);
    setIcon("network-disconnect");
    setToolTipTitle("Wicd");
    KAboutApplicationDialog *aboutDialog = new KAboutApplicationDialog(KCmdLineArgs::aboutData());
    contextMenu()->addAction(KIcon("help-about"), i18n("About"), aboutDialog, SLOT(show()));
}

void TrayIcon::setIcon(const QString &name)
{
    if (name != iconName()) {
        setIconByName(name);
        setToolTipIconByName(name);
    }
}
