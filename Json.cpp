// Json.cpp
// Chris Bowers

/**
 *	This implements a JSON parser - see Json.h
 */

#include "Json.h"

using namespace Json;

InvalidType::InvalidType(std::string real, std::string attempt) : real_t{ real }, attempt_t{ attempt } {}

const char* InvalidType::what() const{
	return ("Invalid Type: Attempted to extract " + attempt_t + " from " + real_t + "\n").c_str();
}

Array::~Array(){
	for (auto& item : arr){
		delete item;
		item = nullptr;
	}
}

Object::~Object(){
	for (auto& pair : obj){
		delete pair.second;
		pair.second = nullptr;
	}
}

std::string Array::to_string(){
	std::string outstring{ "[ " };
	for (auto& item : arr){
		outstring += (item->to_string() + ", ");
	}
	outstring[outstring.size() - 2] = ' ';
	outstring[outstring.size() - 1] = ']';
	return outstring;
}

std::string Object::to_string(){
	std::string outstring{ "{\n" };
	for (auto& pair : obj){
		outstring += ('"' + pair.first + "\" : " + pair.second->to_string() + ",\n");
	}
	outstring[outstring.size() - 2] = '\n';
	outstring[outstring.size() - 1] = '}';
	return outstring;
}

std::string String::to_string() { return str; }

std::string Number::to_string() { return std::to_string(value); }

std::string Null::to_string() { return "null"; }

std::string Boolean::to_string() { return b ? "true" : "false"; }

void Object::populate(std::istream& input){
	assert(input.get() == '{');
	while (true){
		while (isspace(input.peek()))
			input.ignore();
		if (input.peek() == '}'){
			input.ignore();
			break;
		}
		else if (input.peek() == ',')
			input.ignore();
		while (isspace(input.peek()))
			input.ignore();

		// first get the string part
		assert(input.get() == '"');
		std::string key = "";
		while (true){
			char currentChar = input.get();
			if (currentChar == '"')
				break;
			else if (currentChar == '\\'){
				if (input.peek() == '"'){
					input.ignore();
					key += "\"";
				}
				else if (input.peek() == '\\'){
					input.ignore();
					key += "\\";
				}
				else if (input.peek() == '/'){
					input.ignore();
					key += "\\/";
				}
				else if (input.peek() == 'b'){
					input.ignore();
					key += "\b";
				}
				else if (input.peek() == 'f'){
					input.ignore();
					key += "\f";
				}
				else if (input.peek() == 'n'){
					input.ignore();
					key += "\n";
				}
				else if (input.peek() == 'r'){
					input.ignore();
					key += "\r";
				}
				else if (input.peek() == 't'){
					input.ignore();
					key += "\t";
				}
			}
			else {
				key += currentChar;
			}
		}
		while (isspace(input.peek()))
			input.ignore();
		assert(input.get() == ':');

		// then get the value
		while (isspace(input.peek()))
			input.ignore();
		Value* newItem = nullptr;
		if (input.peek() == '{')
			newItem = new Object;
		else if (input.peek() == '[')
			newItem = new Array;
		else if (input.peek() == '"')
			newItem = new String;
		else if (input.peek() == 'f' || input.peek() == 't')
			newItem = new Boolean;
		else if (input.peek() == 'n')
			newItem = new Null;
		else
			newItem = new Number;
		newItem->populate(input);
		obj[key] = newItem;
		while (isspace(input.peek()))
			input.ignore();
	}
	while (isspace(input.peek()))
		input.ignore();
}

void Array::populate(std::istream& input){
	assert(input.get() == '[');
	while (true){
		while (isspace(input.peek()))
			input.ignore();
		if (input.peek() == ']'){
			input.ignore();
			break;
		}
		else if (input.peek() == ',')
			input.ignore();
		while (isspace(input.peek()))
			input.ignore();
		Value* newItem = nullptr;
		if (input.peek() == '{')
			newItem = new Object;
		else if (input.peek() == '[')
			newItem = new Array;
		else if (input.peek() == '"')
			newItem = new String;
		else if (input.peek() == 'f' || input.peek() == 't')
			newItem = new Boolean;
		else if (input.peek() == 'n')
			newItem = new Null;
		else
			newItem = new Number;
		newItem->populate(input);
		arr.push_back(newItem);
	}
	while (isspace(input.peek()))
		input.ignore();
}

void String::populate(std::istream& input){
	assert(input.get() == '"');
	str = "";
	while (true){
		char currentChar = input.get();
		if (currentChar == '"')
			break;
		else if (currentChar == '\\'){
			if (input.peek() == '"'){
				input.ignore();
				str += "\"";
			}
			else if (input.peek() == '\\'){
				input.ignore();
				str += "\\";
			}
			else if (input.peek() == '/'){
				input.ignore();
				str += "\\/";
			}
			else if (input.peek() == 'b'){
				input.ignore();
				str += "\b";
			}
			else if (input.peek() == 'f'){
				input.ignore();
				str += "\f";
			}
			else if (input.peek() == 'n'){
				input.ignore();
				str += "\n";
			}
			else if (input.peek() == 'r'){
				input.ignore();
				str += "\r";
			}
			else if (input.peek() == 't'){
				input.ignore();
				str += "\t";
			}
		}
		else {
			str += currentChar;
		}
	}
	while (isspace(input.peek()))
		input.ignore();
}

void Boolean::populate(std::istream& input){
	if (input.peek() == 't'){
		assert(input.get() == 't');
		assert(input.get() == 'r');
		assert(input.get() == 'u');
		assert(input.get() == 'e');
		b = true;
	}
	else {
		assert(input.get() == 'f');
		assert(input.get() == 'a');
		assert(input.get() == 'l');
		assert(input.get() == 's');
		assert(input.get() == 'e');
		b = false;
	}
	while (isspace(input.peek()))
		input.ignore();
}

void Null::populate(std::istream& input){
	assert(input.get() == 'n');
	assert(input.get() == 'u');
	assert(input.get() == 'l');
	assert(input.get() == 'l');
	while (isspace(input.peek()))
		input.ignore();
}

void Number::populate(std::istream& input){
	input >> value;
	while (isspace(input.peek()))
		input.ignore();
}

Value* parse(std::string filepath){
	std::ifstream infile{ filepath };
	Value* topItem = nullptr;
	while (isspace(infile.peek()))
		infile.ignore();
	if (infile.eof())
		return new Null;
	else if (infile.peek() == '{')
		topItem = new Object;
	else if (infile.peek() == '[')
		topItem = new Array;
	else if (infile.peek() == '"')
		topItem = new String;
	else if (infile.peek() == 'f' || infile.peek() == 't')
		topItem = new Boolean;
	else if (infile.peek() == 'n')
		topItem = new Null;
	else
		topItem = new Number;
	topItem->populate(infile);
	return topItem;
}
