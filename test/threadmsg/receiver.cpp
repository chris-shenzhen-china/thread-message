/*********************************************************************
Copyright ? 2016- , relax Tech. Co., Ltd.
FileName:    message.h
Author:      chrislee
Date :       2020-01-28
Description: message struct header
Others:        
Function List: 
History:
       <Author>        <time>        <version>    <desc>
       chrislee     2020-01-28      1.00        Create this module
       any question mail to: sz_lidong@qq.com
*********************************************************************/



#include "receiver.h"


// must C11_SUPPORT
#include <thread>         //多线程
#include <chrono>         // std::chrono::seconds 定时器
#include <map>
#include <utility>          //pair make_pair


//全局单实例和互斥
static MsgReceiver *g_receiverInstance = NULL;
static std::mutex g_receiverMutex;

void sendTickMsg(void)
{
	MsgReceiver* instance = MsgReceiver::sharedInstance();
	if(instance)
		instance->timerMsgTriger();
}


MsgReceiver::MsgReceiver()
{
    initTickTimer();
}

MsgReceiver::~MsgReceiver()
{
}

MsgReceiver::MsgReceiver(const MsgReceiver&)
{

}

MsgReceiver& MsgReceiver::operator=(const MsgReceiver&)
{
	return *this;
}

//单实例共享,第一次调用时创建
MsgReceiver* MsgReceiver::sharedInstance()
{
    if (g_receiverInstance == NULL)
    {
        g_receiverMutex.lock();
        if (g_receiverInstance == NULL)
        {
            g_receiverInstance = new MsgReceiver();
        }
        g_receiverMutex.unlock();
    }

    return g_receiverInstance;
}

void MsgReceiver::initTickTimer()
{
    //周期性执行定时任务
    m_timer.startTimer(3000, std::bind(&sendTickMsg)); //3s timer
}


int MsgReceiver::start()
{
	CThread::start(); //启动基类的线程
	LOGI("MsgReceiver--> msgreceiver thread running......");
    return 0;
}

void MsgReceiver::handleMessage(CMessage *message)     //各模块自己实现此函数进行消息处理
{
    if(message->recvId_ != MODULE_RECEIVER)
    {
        LOGI("MsgReceiver--> receive error msg for module: " << message->recvId_);
        return ;
    }

    switch (message->senderId_)
    {
        case MODULE_SENDER:
            senderMsgHandler(message);
            break;

        case MODULE_RECEIVER:
            selfMsgHandler(message);
            break;

        default:
            break;
    }
}


/* 处理 xxx 模块发来的消息包 */
void MsgReceiver::senderMsgHandler( CMessage *pMsg )
{
    /* 自定义的消息结构是放在消息包的 data_ 字段中的 */
    switch(pMsg->msgType_)
    {
    case MSG_OTHER_TEST:
        break;
        default:
            LOGI("MsgReceiver--> receive unknown msg: " << pMsg->msgType_);
    }
}


/* 处理主控模块发来的消息包 */
void MsgReceiver::selfMsgHandler(CMessage *pMsg )
{
    static int count = 0;
    /* 自定义的消息结构是放在消息包的 data_ 字段中的 */
    switch(pMsg->msgType_)
    {
        case MSG_TIMER_3S:        //定时打印信息
            count++;
            LOGI("MsgReceiver--> receive 3s timer msg: " << pMsg->msgType_ << ": message count: "<< count);
            break;

        default:
            LOGI("MsgReceiver--> receive unknown msg: " << pMsg->msgType_);
    }

    return;
}


void MsgReceiver::stop()
{
}

void MsgReceiver::stopThread()
{
    CMessage* msg = new CMessage(MODULE_RECEIVER, MODULE_RECEIVER, 1123, 0, 0, 0, 0);
    sendMessage(msg);
}

void MsgReceiver::timerMsgTriger()
{
	CMessage* msg = new CMessage(MODULE_RECEIVER, MODULE_RECEIVER, MSG_TIMER_3S, 0, 0, 0, 0);
	sendMessage(msg);
}

