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

#include "infodialog.h"

#include <QLabel>
#include <QFormLayout>

#include <KLocalizedString>

#include <Plasma/Theme>

InfoDialog::InfoDialog(Status status, QWidget *parent)
    : Plasma::Dialog(parent, Qt::Popup)
{
    setAttribute(Qt::WA_DeleteOnClose);
    QFormLayout *layout = new QFormLayout(this);
    layout->setLabelAlignment(Qt::AlignLeft);
    setLayout(layout);

    if (status.State == WicdState::CONNECTING) {
        layout->addRow(i18n("State:"), new QLabel(i18n("Connecting")));
    }
    else if (status.State == WicdState::WIRED) {
        layout->addRow(i18n("Connection type:"), new QLabel(i18nc("Connection type", "Wired")));
        layout->addRow(i18n("IP:"), new QLabel(status.Info.at(0)));
    }
    else if (status.State == WicdState::WIRELESS) {
        layout->addRow(i18n("Connection type:"), new QLabel(i18nc("Connection type", "Wireless")));
        layout->addRow(i18n("ESSID:"), new QLabel(status.Info.at(1)));
        layout->addRow(i18n("Speed:"), new QLabel(status.Info.at(4)));
        layout->addRow(i18n("IP:"), new QLabel(status.Info.at(0)));

        QString quality = status.Info.at(2);
        QString unit('%');
        if (quality.toInt() <= -10)
            unit = " dBm";
        layout->addRow(i18n("Signal strength:"), new QLabel(quality + unit));
    }
    else {
        layout->addRow(i18n("State:"), new QLabel(i18n("Disconnected")));
    }

    connect(Plasma::Theme::defaultTheme(), SIGNAL(themeChanged()), SLOT(updateColors()));
    updateColors();
}

InfoDialog::~InfoDialog()
{
}

void InfoDialog::updateColors()
{
    QPalette pal = palette();
    pal.setColor(QPalette::WindowText, Plasma::Theme::defaultTheme()->color(Plasma::Theme::TextColor));
    setPalette(pal);
}
