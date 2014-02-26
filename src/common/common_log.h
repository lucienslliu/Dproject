#pragma once

#include <string>
#include <sstream>

class Log
{
public:
	Log();
	~Log();

	static Log& Instance()
	{
		static Log log;
		return log;
	}

	void Init(const std::string& file);

	void Print(const std::string& str);

private:
	
	std::string m_strFileName;

	std::string m_stream;

};