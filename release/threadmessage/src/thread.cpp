/*********************************************************************
Copyright ? 2016- , relax Tech. Co., Ltd.
FileName:    thread.cpp
Author:      chrislee
Date :       2020-01-28
Description: c++11 thread and message queue
Others:        
Function List: 
History:
       <Author>        <time>        <version>    <desc>
       chrislee     2020-01-28      1.00        Create this module
*********************************************************************/


#include "../include/thread.h"

namespace threadmessage
{

CThread::CThread()
{
    queue_ = new queue<CMessage *>();
    state_ = THREAD_STATE_IDLE;
}

CThread::~CThread()
{
    delete(queue_);
}

//启动线程
int CThread::start()
{
    if (state_ == THREAD_STATE_RUNNING) 
        return -1;

    state_ = THREAD_STATE_RUNNING;
    thread_ = new std::thread(threadFun, this);
    thread_->detach();  //此线程开始独立运行

    return 0;
}

void* CThread::threadFun(void *arg)
{
    CThread *ptr = (CThread *)arg;

    //线程消息主循环run, 正常一直运行
    ptr->run();

    //线程结束运行, 摧毁
    delete ptr;
    return NULL;
}

void CThread::run()
{
    //线程主循环
    while (THREAD_STATE_RUNNING == state_)
    {
        //阻塞读队列中的消息
        CMessage *message = readMessage();
        if (message->msgType_ == MSG_THREAD_END)
        {
            message->done();
            break;
        }

        //应用层处理消息
        handleMessage(message);
        message->done();		//处理完消息进行善后处理
    }

    state_ = THREAD_STATE_END;  //

    // clear message queue, free memory
    std::lock_guard<std::mutex> lock(messageMutex_);
    while (!queue_->empty())
    {
        CMessage *message = queue_->front();
        queue_->pop();
        message->done();
    }

	delete thread_;
}

//应用层调用向线程队列中发送消息
void CThread::sendMessage(CMessage *message)
{
    std::unique_lock<std::mutex> lock(messageMutex_);

    if (THREAD_STATE_RUNNING == state_)
    {
        queue_->push(message);
		messageCond_.notify_one();
    }
}

CMessage *CThread::readMessage()
{
    std::unique_lock<std::mutex> lock(messageMutex_);

    //队列为空, 用条件锁阻塞等待
    CMessage *message = NULL;
    while (queue_->empty())
    {
        messageCond_.wait(lock);
    }

    //取出队列头部的数据返回给应用层处理
    message = queue_->front();
    queue_->pop();
    return message;
}
}
