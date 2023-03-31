
//### 日志打印的CPP文件
//logger.cpp
#include "logger.h"

Logger::Logger(LogLevel _logLevel)
	:level_(_logLevel),
	lastPrinted_(0)
{
}

Logger& Logger::operator<<(std::ostream& (*pf)(std::ostream&))	//pf是参数和输出都是标准库的输出流的函数指针
{ 
	std::cout << pf;
	lastPrinted_ = 0;
	return *this;	//(*this)是返回该对象，这样方便操作符重载函数链式输出
}

void Logger::printLog()
{
	// 获取当前时间
	time_t now = time(nullptr);
	struct tm* timeinfo = localtime(&now);	//localtime输入是一个指针参数，所以需要&获取now的地址
	char buffer[80];
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
	
	if (lastPrinted_ == 0)
	{
		std::cout << "[" << buffer << "]";
		switch (level_)
		{
		case LogLevel::INFO:
			std::cout << "[INFO]: ";
			break;
		case LogLevel::WARNING:
			std::cout << "[WARNING]: ";
			break;
		case LogLevel::ERROR:
			std::cout << "[ERROR]: ";
			break;
		}
	}
}

Logger LOG_INFO(LogLevel::INFO);  //LOG_INFO这里是Logger类的对象，先进行初始化
Logger LOG_WARNING(LogLevel::WARNING);
Logger LOG_ERROR(LogLevel::ERROR);



