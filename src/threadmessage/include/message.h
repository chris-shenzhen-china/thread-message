﻿/*********************************************************************
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


#pragma once

#include <string> //c++数据类型定义


namespace threadmessage
{

#define MSG_THREAD_END 0xffddeecc       //结束线程消息

//线程间消息格式封装
class CMessage 
{
public:
	CMessage(uint16_t recvId, uint16_t senderId, int msgType, int32_t param1, int32_t param2, int32_t param3, uint8_t* handle);
	virtual ~CMessage();

public:
	//自定义数据的设置
	void setData(uint8_t* data, int length);

    //释放消息
    void done();

public:
    uint16_t      senderId_;       //发送模块id
    uint16_t      recvId_;         //接收模块id

    int           msgType_;        //message id

    //需要额外的信息可以自定义消息内容放入data中
    int             length_;         //data length
    uint8_t*        data_;           //data content, alloc by user free by ~CMessage()

    //预留三个参数,有的简单的消息直接重用即可
    int32_t       param1_;
    int32_t       param2_;
    int64_t       param3_;        //唯一一个long long 参数
    uint8_t*      handle_;        //指针: 用于传输句柄

};

}
