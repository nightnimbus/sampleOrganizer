#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include "FileTinkering.h"
#include <new>
#include <windows.h>
#include <ctype.h>
//#include "SamplePack.h"

using std::list;
using std::cout;
using std::vector;
using std::endl;
using std::string;
using std::filesystem::directory_iterator;
using std::filesystem::create_directories;
using std::isdigit;

//Gets the file paths containing a specific extension
vector<string*> FileTinkering::getPathsFromDirectory(string startPath, string extension)
{	
	vector<string*> paths;
	//need an error message here
	for (const auto& file : directory_iterator(startPath))
	{
		string path_string{ file.path().string() };
		if (path_string.find(extension) != string::npos) {
			paths.push_back(new string(path_string));
			
		}
		
	}
	
	return paths;
}
string FileTinkering::removeFoldersFromPath(const string& a)
{
	vector<string> splitString;
	splitString = this->splitString(a, '\\', '/');
	cout << "\n" << splitString.back() << endl;
	return splitString.back();
}
vector<string> FileTinkering::splitString(const string& a, char b, char c)
{
	vector<string> splitString;
	string temp = "";
	for (size_t i = 0; i < a.length(); ++i) {
		if (a[i] == b|| a[i] == c) {
			splitString.push_back(temp);
			temp = "";
		}
		else {
			temp.push_back(a[i]);
		}

	}
	splitString.push_back(temp);
	return splitString;
}

vector<string> FileTinkering::splitString(const string& a, char b)
{
	vector<string> splitString;
	string temp = "";
	for (size_t i = 0; i < a.length(); ++i) {

		if (a[i] == b) {
			splitString.push_back(temp);
			temp = "";
		}
		else {
			temp.push_back(a[i]);
		}

	}
	splitString.push_back(temp);
	return splitString;
}
//Last index is assumed to be a file name so ignored
//Example output "folder1/folder2\\" end is to show that we are at the leaf of the structure
string FileTinkering::pathFromVector(const vector<string>& a)
{
	string path;
	path.append("\\");
	if (a.size() < 2 ) {
		return path;
	}
	for (auto& b : a) {
		//not my best loop implementation I know
		if (b != a.back() && b != a.at(a.size() - 2)) {
			path.append(b);
			path.append("\\");
		}
		else if (b == a.at(a.size() - 2)) {
			path.append(b);
			path.append("\\");
		}
	}
	return path;
}
void FileTinkering::moveFile(const string& path, const string& endPath)
{	
	LPWSTR start = convertToLPWSTR(path);
	LPWSTR end = convertToLPWSTR(endPath);
	BOOL fileT = MoveFile(start, end);
	if (fileT == FALSE) {
		cout << "Move failed" << GetLastError()<<endl;
	}
}

LPWSTR FileTinkering::convertToLPWSTR(const string& a) {

	vector<char> writable(a.begin(), a.end());
	writable.push_back('\0');
	size_t size = strlen(&writable[0]) + 1;
	wchar_t* writableName = new wchar_t[size];
	size_t outSize;
	mbstowcs_s(&outSize, writableName, size, &writable[0], size - 1);
	return writableName;
}
FileTinkering::FileTinkering(string path, string extension)
{
	this->paths = this->getPathsFromDirectory(path, extension);
	this->ext = extension;
}
void FileTinkering::fileNameToFolderStructure(string newRoot) {
	//cout << *this->paths.at(0) << endl;
	for (const auto& path : this->paths) {
		//bool created;
		bool duplicate;
		string fileName;
		string& endPath = *(new string(*path));
		
		fileName = removeFoldersFromPath(*path);
		//do you have to make sure to delete this at the end? Is this a pointer technically 
		vector<string> pathParts = splitString(fileName, '_');
		endPath = newRoot;
		endPath += pathFromVector(pathParts);
		//created = create_directories(endPath);
		create_directories(endPath);
		//if (created) {
		//Sends the folders, filename, ext.
		deleteIncrementationsFromName(fileName, ext);
		string tempFileName = fileName.c_str();
		int i = 0;
		do {
			i++;
			duplicate = checkIfDirectoryContains(endPath, tempFileName, this->ext);
			if (duplicate) {
				tempFileName = addNumberBetweenNameAndExt(fileName, this->ext, i);
			}
		} while (duplicate);
		fileName = tempFileName;
		endPath += fileName;
		moveFile(*path, endPath);
		this->endPaths.push_back(new string(*path));
		
		//}
		//else {
		//	cout << "Coudn't create directories" << GetLastError() << endl;
		//}
		
	}
}

bool FileTinkering::checkIfDirectoryContains(const string directory, const string& fileName, const string extension) {
	bool found = false;
	vector<string*> paths = getPathsFromDirectory(directory, extension);
	
	if(paths.size() != 0){
		vector<string*>::iterator it;
		
	for (it = paths.begin(); it != paths.end(); it++) {
		found = (*(*it)).find(fileName) != string::npos ? true: false;
		if (found) {
			it = paths.begin() + (paths.size() - 1);
		}
	}
	clearVectorContents(paths);
	}
	return found; //!!!!!!!!!
}

string FileTinkering::addNumberBetweenNameAndExt(const string& name, const string& ext, const int& i)
{	
	string a = name.c_str();
	string extra = "-" + std::to_string(i);
	a.insert(a.size() - ext.size(), extra);
	return a;
}

//Free function to delete vectors;
void FileTinkering::clearVectorContents(vector <string*>& a)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		delete a[i];
	}
	a.clear();
}

void FileTinkering::deleteIncrementationsFromName(string& fileName, const string& ext)
{
	cout << (fileName.length() - (ext.length() + 1));
	for (int i = (fileName.length() - (ext.length() + 1)); i > -1; --i) {
		if (isdigit(fileName.at(i)) || fileName.at(i)== '-') {
			fileName.erase(i, 1);
		}
		else {
			i = 0;
		}
	}
}
