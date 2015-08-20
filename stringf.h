// stringf.h
// Chris Bowers

/**
 *	Defines a function to create a string from a format string + arguments.
 *  Format string uses %% to signify an argument.
 *	Arguments can be any type with a defined operator<<.
 *	Alternatively you can specialize the template to use something other than operator<<
 *	such as Json::Value::toStyledString().
 */

#ifndef __STRINGF_H__
#define __STRINGF_H__

#include <string>
#include <sstream>

void format_print(std::ostream& os, const std::string& str) { os << str; }

template<typename T, typename... Args>
void format_print(std::ostream& os, const std::string& format, const T& arg, const Args&... args){
	for (unsigned int i = 0; i < format.size(); ++i){
		if (format[i] != '%'){
			os << format[i];
		}
		else if (format[i + 1] != '%'){
			os << format[i];
		}
		else{
			os << arg;
			format_print(os, format.substr(i + 2), args...);
			break;
		}
	}
}

template<typename... Args>
std::string stringf(const std::string& format, const Args&... args){
	std::stringstream ss;
	format_print(ss, format, args...);
	return ss.str();
}

#endif
