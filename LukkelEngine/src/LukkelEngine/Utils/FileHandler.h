#include "LukkelEngine/Core/Base.h"
#include <fstream>

namespace LukkelEngine::Utils::File {

	bool readFile(std::string file, std::string& fileContents, bool addLineTerminator) {
		std::ifstream f(file);
		std::string currentLine;
		std::string allFileContent;

		if (f.is_open()) {
			while (getline(f, currentLine)) {
				if (addLineTerminator) {
					currentLine += "\n";
				}
				allFileContent += currentLine;
			}
			f.close();
			fileContents = allFileContent;
			return true;
		}
		else {
			return false;
		}
	}

	long getLastModificationTime(std::string file) {
		struct stat fileInfo;
		stat(file.c_str(), &fileInfo);
		return fileInfo.st_mtime;
	}

}