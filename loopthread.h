#ifndef LOOPTHREAD_H
#define LOOPTHREAD_H

#include <QThread>
#include "config.h"

class LoopThread : public QThread
{
public:
    LoopThread(): count(0) {}
    virtual void run();
    void setConfig(Config* config) {m_config = config;}
signals:

public slots:
private:
    Config* m_config;
    int count;
};

#endif // LOOPTHREAD_H
