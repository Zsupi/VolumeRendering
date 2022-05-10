#pragma once
#include <string>
#include <fstream>
#include <iostream>

namespace File {
	inline std::string readFile(const char* filePath) {
		std::string content;
		std::ifstream fileStream(filePath, std::ios::in);

		if (!fileStream.is_open()) {
			std::cerr << "could not read file: " << filePath << std::endl;
			throw "File does not exist!";
		}
		std::string line = "";
		while (!fileStream.eof()) {
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();
		return content;
	}

}

//todo Logger
//RayTracing