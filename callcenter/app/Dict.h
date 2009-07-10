#ifndef __DICT_H__
#define __DICT_H__

#include <string>
#include <list>
#include <map>

class Dict {
public:
	typedef std::list<std::string> FileNameList;

	Dict();
	FileNameList GetFileList(const std::string &str);
	void Init();


private:
	std::map<std::string, std::string> file_name_map;
};

#endif
