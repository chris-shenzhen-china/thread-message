/*********************************************************************
Copyright ? 2016- , relax Tech. Co., Ltd.
FileName:    message.h
Author:      chrislee
Date :       2020-01-28
Description: 线程消息队列发送接收测试
           1. 启动定时器 每3秒向线程的消息队列发送消息；
           2. MsgReceiver继承与CThread,实现handleMessage函数处理收到的消息
Others:        
Function List: 
History:
       <Author>        <time>        <version>    <desc>
       chrislee     2020-01-28      1.00        Create this module
       any question mail to: sz_lidong@qq.com
*********************************************************************/

#pragma once

//for thread message
#include "../../release/threadmessage/include/thread.h"
#include "../../release/threadmessage/include/message.h"

//for timer
#include "../../release/timer/timer.h"

//for log output
#include "../log4z/log4z.h"


#include <queue>
#include <mutex>
#include <condition_variable> //c++11
#include <string>
#include <fstream>

using namespace std;

using namespace threadmessage;          //thread message


typedef enum {
    MODULE_ID_IDLE,

    MODULE_RECEIVER,            //消息接收模块
    MODULE_SENDER,              //消息发送模块
    

    MODULE_BUTT
}MODULE_ID_E;


typedef enum {
    MSG_ID_IDLE,

    MSG_TIMER_3S,               //3S定时消息
    MSG_TIMER_10S,              //消息发送模块

    MSG_OTHER_TEST,             //测试消息

    MSG_ID_BUTT
}MESSAGE_ID_E;



//集成消息线程: 默认支持一个待消息队列的线程
//TCP server: 需要实现tcp server的接口

class MsgReceiver : public CThread
{

public:

    virtual ~MsgReceiver();

    int start();                                    //启动文件上传线程
    void stop();

    static MsgReceiver *sharedInstance();            //单实例共享给其他模块调用

private:

	MsgReceiver();                                   //不写到public, 避免应用层用new操作
	MsgReceiver(const MsgReceiver&);
	MsgReceiver& operator=(const MsgReceiver&);

    void selfMsgHandler(CMessage* pMsg);
    void senderMsgHandler(CMessage* pMsg);

private:
    

    //定时器
    CTimer m_timer;                                //定时3s消息模拟

private:
    void initTickTimer();
public:
    //implement for CThread
    virtual void handleMessage(CMessage *message);                     //各模块自己实现此函数进行消息处理
    virtual void stopThread();


    void timerMsgTriger();                  //3s定时器模拟消息发送

};


