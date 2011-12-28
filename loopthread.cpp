#include "loopthread.h"
#include <QThread>
#include "config.h"
#include "tcpclient.h"
#include "querysender.h"
#include <QDebug>

void LoopThread::run()
{
    TcpClient networkClient;
    //-----------------------------
    QuerySender querySender(m_config->pQueryList());
    querySender.setNetworkClient(&networkClient);

    qDebug() << "Starting" << endl;
    querySender.run();

    qDebug() << count++;
    exec();
}
