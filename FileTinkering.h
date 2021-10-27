#ifndef FILE_TINKERING
#define FILE_TINKERING
//ask what is the naming convention here
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <list>
#include <windows.h>

using std::list;
using std::vector;
using std::string;

class FileTinkering
{
public:
	FileTinkering(string path, string extension); 
	~FileTinkering();
	//Provide a new root and it will make you a folder structure from your file name, everything ensuing a '_' 
	//will be a folder
	void fileNameToFolderStructure(string newRoot);
	//static void moveFile(string, string);
	//Careful returns a vector of pointers, not greatest design I know 
    vector<string*> getPathsFromDirectory(string, string extension);
private:
	vector<string*> endPaths;
	vector<string*> paths;
	string ext;
	//strips the path to only a filename
	string removeFoldersFromPath(const string& a);
	//Split string with a char
	vector<string> splitString(const string&, char, char);
	vector<string> splitString(const string&, char);
	//fills in / between the strings
	string pathFromVector(const vector<string>&);
	//Checks if the folder already has a file with the same name 
	bool checkIfDirectoryContains(const string directory, const string& fileName, const string extension);
	//adds a number between the extension and the name 
	string addNumberBetweenNameAndExt(const string& name, const string& ext, const int& i);
	//Moves file to new location
	void moveFile(const string& path, const string& endPath);
	LPWSTR convertToLPWSTR(const string&);
	void clearVectorContents(vector <string*>& a);
	//if a number is found at the end or '-' we delete
	//This is in order to avoid gaps in numbering and numbers on numbers
	void deleteIncrementationsFromName(string& fileName, const string& ext);
	
};
#endif //FILE_TINKERING