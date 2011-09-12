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

#ifndef WICDAPPLET_HEADER
#define WICDAPPLET_HEADER

#include "dbushandler.h"
#include "networkplotter.h"
#include "networkview.h"
#include "infosdialog.h"
#include "ui_wicdappletConfig.h"

#include <KIcon>

#include <Plasma/PopupApplet>
#include <Plasma/Svg>
#include <Plasma/Label>
#include <Plasma/ToolButton>

class QSizeF;

// Define our plasma Applet
class WicdApplet : public Plasma::PopupApplet
{
    Q_OBJECT
public:
    // Basic Create/Destroy
    WicdApplet(QObject *parent, const QVariantList &args);
    ~WicdApplet();

    // The paintInterface procedure paints the applet to the desktop
    void paintInterface(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        const QRect& contentsRect);
    void init();

    QList<QAction*> contextualActions();

public slots:
    void configChanged();
    void toolTipAboutToShow();
    void toolTipHidden();

protected:
    void popupEvent(bool show);
    void createConfigurationInterface(KConfigDialog *parent);

protected slots:
    void configAccepted();

private slots:
    void updateStatus(Status status);
    void handleConnectionResult(const QString& result);
    void launchProfileManager();
    void forceUpdateStatus();
    void freeze();
    void unfreeze();
    void cancelConnect() const;
    void showPreferences();
    void createAdhocDialog();
    void findHiddenDialog();
    void connectionInfoRequested();

private:
    void setupActions();
    void setWirelessIcon(int quality);
    void loadNetworks();
    void showPlotter(bool show);
    void notify(const QString& event, const QString& message);
    InfosDialog* infosDialog();

    // Configuration dialog
    Ui::WicdAppletConfig ui;
    bool m_showSignalStrength;
    bool m_autoScan;
    bool m_showPlotter;

    Plasma::Svg *m_theme;
    QString m_icon;
    Status m_status;
    QString m_message;
    QGraphicsWidget *m_appletDialog;
    QGraphicsLinearLayout * m_dialoglayout;
    NetworkPlotter *m_plotter;
    NetworkView *m_networkView;
    QHash<QString, QString> m_messageTable;
    Plasma::Label *m_messageBox;
    Plasma::ToolButton *m_abortButton;
    InfosDialog* m_infosDialog;
};

// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(wicd-kde, WicdApplet)
#endif
