#pragma once
#include <string>
#include <fstream>
#include "Debug.h"
#include <iterator>

class TextAsset {

private:
	std::string text_;

	TextAsset(std::string _text = "");

public:
	std::string GetString() { return text_; }

	static TextAsset LoadFile(std::string _file);

};

inline TextAsset::TextAsset(std::string _text) {
	text_ = _text;
}

inline TextAsset TextAsset::LoadFile(std::string _file) {
	TextAsset textAsset;

	std::ifstream file;
	file.open(_file);
	if(!file.is_open()) { 
		Debug::print("TextAsset::LoadFile - Failed to open file: " + _file);
		return textAsset;
	}

	std::string fileText;
	while(!file.eof()) {
		std::string line;
		std::getline(file, line);
		fileText.append(line + "\n");
	}

	textAsset = TextAsset(fileText);
	return textAsset;
}

