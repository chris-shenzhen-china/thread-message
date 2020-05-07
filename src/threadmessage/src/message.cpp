/*********************************************************************
Copyright ? 2016- , relax Tech. Co., Ltd.
FileName:    message.cpp
Author:      chrislee
Date :       2020-01-28
Description: message wrapper
Others:        
Function List: 
History:
       <Author>        <time>        <version>    <desc>
       chrislee     2020-01-28      1.00        Create this module
*********************************************************************/




#include "../include/message.h"


using namespace threadmessage;

CMessage::CMessage(uint16_t recvId, uint16_t senderId, int msgType, int32_t param1, int32_t param2, int32_t param3, uint8_t* handle)
{
    recvId_     = recvId;
    senderId_   = senderId;
    msgType_    = msgType;
    param1_     = param1;
    param2_     = param2;
    param3_     = param3;
    handle_     = handle;
    data_       = 0;
}

CMessage::~CMessage()
{
    //释放消息数据内存
    if (data_ != 0)
    {
        delete[] data_;
    }
}

void CMessage::done()
{
	delete this;
}

void CMessage::setData(uint8_t* data, int length)
{
    if (length <= 0)
    {
        return;
    }

    length_ = length;
    data_ = data;
}
