
#include "main.h"

using namespace std;

int main(int argc, char **argv)
{

    //初始化日志输出
    initLog4z("./");

    //启动消息接收线程
	MsgReceiver *msgreceiver = MsgReceiver::sharedInstance();
	msgreceiver->start();


	while (1) {
		;
	}

	system("pause");
	return 0;
}

void initLog4z(const char* logpath)
{
    zsummer::log4z::ILog4zManager::getInstance()->setLoggerMonthdir(LOG4Z_MAIN_LOGGER_ID, true);
    zsummer::log4z::ILog4zManager::getInstance()->setLoggerDisplay(LOG4Z_MAIN_LOGGER_ID,false);
    zsummer::log4z::ILog4zManager::getInstance()->setLoggerLevel(LOG4Z_MAIN_LOGGER_ID,LOG_LEVEL_INFO);
    zsummer::log4z::ILog4zManager::getInstance()->setLoggerLimitsize(LOG4Z_MAIN_LOGGER_ID,100);
    if (logpath)
    {
        zsummer::log4z::ILog4zManager::getInstance()->setLoggerPath(LOG4Z_MAIN_LOGGER_ID,logpath);
    }
    zsummer::log4z::ILog4zManager::getInstance()->start();
}


