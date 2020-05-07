[1.中文说明](#chinese) [2.English](#English)

<span id="Chinese">1.中文说明</span>
### 多线程和消息队列
基于标准C++的thread，mutex，queue，condition_variable等技术的消息队列和多线程。目标是可以在windows，linux，android jni，macos等操作系统环境中跨平台使用，不用再为每个操作系统写一套代码。服务器端软件一般是模块化设计，功能模块之间比不可少的需要消息通信，thread-message或许就是你在寻找的解决方案。

### 测试工程说明
+ 提供vs2019下可编译运行通过的测试代码
+ 使用定时器模拟向MsgReceiver线程发送消息
+ MsgReceiver收到消息后打印输出，模拟消息处理
+ 未尽事宜请小心使用

### 使用方法
+ 消息接收方集成CThread类，如上实例中MsgReceiver
+ CThread::start()启动消息接收线程
+ CThread::sendMessage发送消息给应用线程，如实例中MsgReceiver线程
+ 实现virtual 函数handleMessage()接收消息，详见实例： MsgReceiver::handleMessage
+ 实现virtual 函数stopThread()可动态停止线程

### 其他说明
+ 测试工程中使用了YaweiZhang <yawei.zhang@foxmail.com>的log4z用于debug信息输出

<span id="English">2.English</span>
### Multithreading and message queue
Message queue and multithreading based on standard C ++ thread, mutex, queue, condition_variable and other technologies. The goal is that it can be run cross-platform in operating system environments such as windows, linux, android jni, macos, etc., without writing a set of codes for each operating system. Server-side software is generally of a modular design, and message communication is indispensable between functional modules. Thread-message may be the solution you are looking for.

### test project description
+ can be run in vs2019
+ timer send msg to thread MsgReceiver
+ MsgReceiver receive the msg and output debug info
+ please use it carefully

### usage
+ MsgReceiver extend CThread
+ CThread::Start() the message receive thread
+ CThread::SendMessage send the message to thread MsgReceiver
+ Implement the virtual function handleMessage () to receive messages. For details, see the example: MsgReceiver :: handleMessage
+ Implement the virtual function stopThread () to stop the thread dynamically

### other
The log4z of YaweiZhang yawei.zhang@foxmail.com was used in the test project for debug information output
