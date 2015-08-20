// stringf.h
// Chris Bowers

/**
 *	Defines a function to create a string from a format string + arguments.
 *  Format string uses %% to signify an argument.
 *	Arguments can be any type with a defined operator<<.
 */

#ifndef __STRINGF_H__
#define __STRINGF_H__

#include <string>
#include <sstream>

static std::stringstream ss;

std::string stringf(const std::string& str) { return str; }

template<typename T, typename... Args>
std::string stringf(const std::string& format, T arg, Args... args){
	std::string outstring = "";
	for (unsigned int i = 0; i < format.size(); ++i){
		if (format[i] != '%'){
			outstring += format[i];
		}
		else if (format[i + 1] != '%'){
			outstring += format[i];
		}
		else{
			ss << arg;
			outstring += ss.str();
			ss.str("");
			outstring += stringf(format.substr(i + 2), args...);
			break;
		}
	}
	return outstring;
}

#endif
