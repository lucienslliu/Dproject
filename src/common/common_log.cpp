#include "stdcommon.h"
#include "common_log.h"

#include <fstream>


Log::Log()
{
}

Log::~Log()
{
	std::ofstream out;
	out.open(m_strFileName.c_str(), std::ios_base::out | std::ios_base::trunc);
	out << m_stream;
	out.close();
}

void Log::Init(const std::string& file)
{
	m_strFileName = file;
}

void Log::Print(const std::string& str)
{
	m_stream += str;
	m_stream += "\n";
}
