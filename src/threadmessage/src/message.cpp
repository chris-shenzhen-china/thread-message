/*********************************************************************
MIT License

Copyright (c) 2020 chrislee

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

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
