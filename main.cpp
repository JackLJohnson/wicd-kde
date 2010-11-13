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

#include <KUniqueApplication>
#include <KCmdLineArgs>
#include <KAboutData>

#include "mainwindow.h"

class MyApp : public KUniqueApplication
{
public:
    MyApp() : KUniqueApplication() { KGlobal::ref(); }
    ~MyApp() {}

    int newInstance() { return 0; }
};

int main(int argc, char *argv[])
{

    KAboutData aboutData( "wicd-kde", 0, ki18n("Wicd Client KDE"),
                          QByteArray("0.2.1"),
                          ki18n("Wicd client for KDE"),
                          KAboutData::License_GPL_V3,
                          ki18n("(c) 2010 Anthony Vital"));
    aboutData.addAuthor(ki18n("Anthony Vital"), ki18n("Author"), "anthony.vital@gmail.com");
    aboutData.addCredit(ki18n("Dario Freddi"), ki18n("Contributor and original KCM author"), "drf@kde.org", "http://drfav.wordpress.com");
    aboutData.addCredit(ki18n("Brieuc Roblin"), ki18n("Contributor"), "brieuc.roblin@gmail.com");
    aboutData.addCredit(ki18n("Yoann Laissus"), ki18n("Contributor"), "yoann.laissus@gmail.com");
    aboutData.addCredit(ki18n("Gianluca Boiano"), ki18n("Translator"), "morf3089@gmail.com");
    aboutData.addCredit(ki18n("Jekyll Wu"), ki18n("Translator"), "adaptee@gmail.com");
    aboutData.addCredit(ki18n("Carlos López"), ki18n("Translator"), "musikolo at hotmail dot com");
    aboutData.addCredit(ki18n("Attila Szabo"), ki18n("Translator"), "a.szabo38@gmail.com");
    aboutData.addCredit(ki18n("Márcio Moraes"), ki18n("Translator"), "marciopanto@gmail.com");
    aboutData.addCredit(ki18n("Pavel Fric"), ki18n("Translator"), "pavelfric@seznam.cz");
    aboutData.setBugAddress("anthony.vital@gmail.com");
    aboutData.setProgramIconName("network-wireless");

    KCmdLineArgs::init(argc, argv, &aboutData);

    if (!KUniqueApplication::start()) {
        return 0;
    }

    MyApp app;

    MainWindow *window = new MainWindow();
    window->setObjectName("wicdclientkde");

    return app.exec();
}
