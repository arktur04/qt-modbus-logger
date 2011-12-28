//#define QT_NO_DEBUG_OUTPUT

#include <QtCore>
#include <iostream>
#include <QtXml>
#include <QtDebug>

#include "config.h"
#include "querysender.h"
//#include "abstractnetworkclient.h"
#include "tcpclient.h"
//#include "vartypes.h"
#include "vars.h"
#include "loopthread.h"

using namespace std;

#define tr QObject::tr
#define STR(s) ((outcodec->fromUnicode(s)).constData())

//const char * configName = "C:/Users/V/Desktop/QtWebClient/das-build-desktop-Qt_4_7_3_for_Desktop_-_MinGW_4_4__Qt_SDK_________/debug/config.xml";//"config.xml";

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTextCodec *incodec = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForTr(incodec);

    #ifdef Q_WS_WIN
    QTextCodec *outcodec = QTextCodec::codecForName("CP866");
    QTextCodec::setCodecForLocale(outcodec);
    #endif

    //createGlobalVarList();
    //createTypeDescriptor();

    Config config("config.xml");//(configName);

    cout << STR(config.hostAddress().toString())
         << endl;

    foreach(QByteArray ba, *config.pQueryList())
        cout << STR(ba.toHex())
             << endl;

    cout << "--------------------"
         << endl;
    //-----------------------------
    LoopThread loopThread;
    loopThread.setConfig(&config);
    loopThread.start();

    string s;
    while(s != "q")
    {
        cin >> s;
    };
    loopThread.terminate();
    app.exit();

    //deleteGlobalVarList();
}
