// Json.h

#ifndef __JSON_H__
#define __JSON_H__

#include <cassert>
#include <exception>
#include <fstream>
#include <string>
#include <map>
#include <vector>

namespace Json{
	struct InvalidType : std::exception{
		std::string real_t;
		std::string attempt_t;
		InvalidType(std::string real, std::string attempt);
		const char* what() const;
	};

	struct Value{
		virtual ~Value() {}
		virtual std::string to_string() = 0;
		virtual void populate(std::istream& input) = 0;
		virtual std::vector<Value*>& array() = 0;
		virtual std::map<std::string, Value*>& object() = 0;
		virtual std::string string() = 0;
		virtual bool boolean() = 0;
		virtual bool null() = 0;
		virtual double number() = 0;
	};

	struct Array : Value{
		~Array();
		std::string to_string();
		void populate(std::istream& input);
		std::vector<Value*>& array() { return arr; }
		std::map<std::string, Value*>& object() { throw InvalidType("Array", "Object"); }
		std::string string() { throw InvalidType("Array", "String"); }
		bool boolean() { throw InvalidType("Array", "Boolean"); }
		bool null() { throw InvalidType("Array", "Null"); }
		double number() { throw InvalidType("Array", "Number"); }

	private:
		std::vector<Value*> arr;
	};

	struct Object : Value{
		~Object();
		std::string to_string();
		void populate(std::istream& input);
		std::vector<Value*>& array() { throw InvalidType("Object", "Array"); }
		std::map<std::string, Value*>& object() { return obj; }
		std::string string() { throw InvalidType("Object", "String"); }
		bool boolean() { throw InvalidType("Object", "Boolean"); }
		bool null() { throw InvalidType("Object", "Null"); }
		double number() { throw InvalidType("Object", "Number"); }

	private:
		std::map<std::string, Value*> obj;
	};

	struct String : Value{
		std::string to_string();
		void populate(std::istream& input);
		std::vector<Value*>& array() { throw InvalidType("String", "Array"); }
		std::map<std::string, Value*>& object() { throw InvalidType("String", "Object"); }
		std::string string() { return str; }
		bool boolean() { throw InvalidType("String", "Boolean"); }
		bool null() { throw InvalidType("String", "Null"); }
		double number() { throw InvalidType("String", "Number"); }

	private:
		std::string str;
	};

	struct Boolean : Value{
		std::string to_string();
		void populate(std::istream& input);
		std::vector<Value*>& array() { throw InvalidType("Boolean", "Array"); }
		std::map<std::string, Value*>& object() { throw InvalidType("Boolean", "Object"); }
		std::string string() { throw InvalidType("Boolean", "String"); }
		bool boolean() { return b; }
		bool null() { throw InvalidType("Boolean", "Null"); }
		double number() { throw InvalidType("Boolean", "Number"); }

	private:
		bool b;
	};

	struct Null : Value{
		std::string to_string();
		void populate(std::istream& input);
		std::vector<Value*>& array() { throw InvalidType("Null", "Array"); }
		std::map<std::string, Value*>& object() { throw InvalidType("Null", "Object"); }
		std::string string() { throw InvalidType("Null", "String"); }
		bool boolean() { throw InvalidType("Null", "Boolean"); }
		bool null() { return false; }
		double number() { throw InvalidType("Null", "Number"); }
	};

	struct Number : Value{
		std::string to_string();
		void populate(std::istream& input);
		std::vector<Value*>& array() { throw InvalidType("Number", "Array"); }
		std::map<std::string, Value*>& object() { throw InvalidType("Number", "Object"); }
		std::string string() { throw InvalidType("Number", "String"); }
		bool boolean() { throw InvalidType("Number", "Boolean"); }
		bool null() { throw InvalidType("Number", "Null"); }
		double number() { return value; }

	private:
		double value;
	};

	Value* parse(std::string filepath);
}

#endif