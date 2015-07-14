// Log.cpp
// Chris Bowers

/**
 *	This implements a debug logger - see Log.h
 */
 
#include "Log.h"

LogLevel Log::level = LogLevel::NOT_SET;

void Log::set_level(LogLevel lvl) { level = lvl; }

LogLevel Log::get_level() { return level; }

bool Log::debug(const std::string& msg) { return log(LogLevel::DEBUG, "DEBUG: " + msg); }

bool Log::info(const std::string& msg) { return log(LogLevel::INFO, "INFO: " + msg); }

bool Log::warning(const std::string& msg) { return log(LogLevel::WARNING, "WARNING: " + msg); }

bool Log::error(const std::string& msg) { return log(LogLevel::ERROR, "ERROR: " + msg); }

bool Log::critical(const std::string& msg) { return log(LogLevel::CRITICAL, "CRITICAL: " + msg); }

bool Log::log(LogLevel lvl, const std::string& msg){
	if (lvl < level) return false;
	std::cerr << msg << std::endl << std::endl;
	return true;
}
