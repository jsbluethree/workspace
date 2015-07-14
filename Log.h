// Log.h
// Chris Bowers

/**
 *	Defines a logger for debugging and other purposes. It is a class with only static members and methods.
 */
 
#ifndef __LOG_H__
#define __LOG_H__


#include <iostream>
#include <string>

enum class LogLevel{
	NOT_SET,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};

struct Log{
	static void set_level(LogLevel lvl);
	static LogLevel get_level();
	
	static bool debug(const std::string& msg);
	static bool info(const std::string& msg);
	static bool warning(const std::string& msg);
	static bool error(const std::string& msg);
	static bool critical(const std::string& msg);
	static bool log(LogLevel lvl, const std::string& msg);
	
private:
	static LogLevel level;
};

#endif // __LOG_H__
