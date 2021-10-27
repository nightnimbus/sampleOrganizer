#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "FileTinkering.h"
//#include "SamplePack.h"
/*
*Program that can move files into new directory structures based on keywords in the file name.
*@Author Victor Maillé a.k.a. Nimbus Fall 2021
*/
using std::cout;
using std::endl;
using std::string;
using std::filesystem::directory_iterator;
//can you have random .h and .cpp files and still run?

int main() {
	string fileName = "Sample-Manager-Settings.txt";
	vector<string> settings;
	std::ifstream file(fileName);
	if (file.is_open()) {
		string line;
		while (getline(file, line))
		{
			settings.push_back(line);
		}
		file.close();
	}
	if (settings.size() == 3) {
		string path = settings.at(0);
		string newRoot = settings.at(1);
		string extension = settings.at(2);
		//string path = "C:/Users/nimbus/Music/plugins temp";
		//string newRoot = "C:/Users/nimbus/Music/plugins temp/FOLDERTEST";
		//string extension = ".wav";
		FileTinkering* test = new FileTinkering(path, extension);
		test->fileNameToFolderStructure(newRoot);
	}
	else {
		cout<<"Don't have what is required in Sample-Manager-Settings.txt, need in this order on 3 seperate lines: Original Path, Destination Path(don't add the filename), extension(\".wav\").";
	}
}