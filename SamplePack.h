#ifndef SAMPLE_PACK
#define SAMPLE_PACK
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <list>

using std::list;
using std::cout;
using std::vector;
using std::endl;
using std::string;

class SamplePack : FileTinkering 
{
public:
	string makeFullFuturePaths();
private:
	bool isUncut(string);
	string uncutDirectoryPath;
	friend class Definitions;
};
#endif //SAMPLE_PACK