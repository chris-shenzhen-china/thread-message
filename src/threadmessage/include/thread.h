/*********************************************************************
Copyright ? 2016- , relax Tech. Co., Ltd.
FileName:    thread.h
Author:      chrislee
Date :       2020-01-28
Description: c11 thread and message
Others:        
Function List: 
History:
       <Author>        <time>        <version>    <desc>
       chrislee     2020-01-28      1.00        Create this module
       any question mail to: sz_lidong@qq.com
*********************************************************************/


#pragma once

#include <thread>
#include <queue>
#include <condition_variable>

#include "message.h"

using namespace std;

namespace threadmessage
{

typedef enum {
    THREAD_STATE_IDLE,      //初始状态
    THREAD_STATE_RUNNING,   //线程已经运行, 只启动一次
    THREAD_STATE_END        //线程已经结束
}THREAD_STATE_E;

class CThread {
private:
    THREAD_STATE_E              state_;             //线程运行状态
    std::thread*                thread_;            //c11 线程
    queue<CMessage *>*          queue_;             //C11 队列, 非线程安全, 用于线程消息队列,构造函数创建, 析构函数中摧毁
    std::mutex                  messageMutex_;      //消息队列互斥信号量
    std::condition_variable     messageCond_;       //c11线程队列条件锁

private:
    static void* threadFun(void *arg);
    CMessage *readMessage();

	void run();		//应用层不用实现此函数

public:
    //类的公共变量

public:
    CThread();
    virtual ~CThread();
    /*
     * WARN: 如果new CThread后，已经调用start被启动，千万不要调用delete释放对象, 请调用stop方法，线程停止后，会自动释放对象。
     * */
    int start();                                                //启动线程
    virtual void stopThread() = 0;                              //停止线程, =0 虚函数,派生类需要实现此函数

    void sendMessage(CMessage *message);                         //消息发送模块调用, 发送消息
    virtual void handleMessage(CMessage *message) = 0;     //各模块自己实现此函数进行消息处理
};

}

