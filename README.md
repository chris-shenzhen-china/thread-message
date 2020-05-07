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
