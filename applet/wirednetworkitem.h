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

#ifndef WIREDNETWORKITEM_H
#define WIREDNETWORKITEM_H

#include "profilewidget.h"
#include "networkitem.h"

class WiredNetworkItem : public NetworkItem
{
    Q_OBJECT

public:
    WiredNetworkItem(NetworkInfo info, QGraphicsWidget *parent);

protected:
    QGraphicsWidget *moreWidget();

private slots:
    void profileUpdated(QString profile);

private:
    ProfileWidget *m_profileWidget;
};

#endif // WIREDNETWORKITEM_H
