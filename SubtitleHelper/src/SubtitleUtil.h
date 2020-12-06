#ifndef _SUBTITLE_UTIL_H_
#define _SUBTITLE_UTIL_H_

#include <string>
#include <chrono>
#include <sstream>
#include "FileWrite.h"

class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	std::chrono::milliseconds elpasedMilliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(clock_t::now() - m_beg);
	}
};

class SubtitleUtil
{
public:
	explicit SubtitleUtil(const std::string &fileName)
		:m_File(fileName)
		,m_count(1)
		,m_bIsStart(true)
	{
	}

	void start()
	{
		m_timer.reset();
	}

	void record()
	{
		std::chrono::milliseconds currentTime = m_timer.elpasedMilliseconds();
		if (m_bIsStart)
		{
			m_File.Write(m_count++);
			m_File.Write("\n");
			std::string str = format_duration(currentTime);
			m_File.Write(str);
			m_File.Write(" --> ");
			m_bIsStart = !m_bIsStart;

			std::cout << "Start Time : " << str << '\n';
		}
		else
		{
			std::string str = format_duration(currentTime);
			m_File.Write(str);
			m_File.Write("\n\n\n");
			m_bIsStart = !m_bIsStart;

			std::cout << "End Time : " << str << '\n';
		}
	}
private:
	std::string format_duration(std::chrono::milliseconds ms)
	{
		using namespace std::chrono;
		std::chrono::seconds secs = duration_cast<seconds>(ms);
		ms -= duration_cast<milliseconds>(secs);

		std::chrono::minutes mins = duration_cast<minutes>(secs);
		secs -= duration_cast<seconds>(mins);
		
		std::chrono::hours hour = duration_cast<hours>(mins);
		mins -= duration_cast<minutes>(hour);

		std::stringstream ss;
		ss << hour.count() << ":" << mins.count() << ":" << secs.count() << "," << ms.count();
		return ss.str();
	}

private:
	Timer																m_timer;
	FileWrite															m_File;
	int																	m_count;
	bool																m_bIsStart;

};
#endif	//_SUBTITLE_UTIL_H_