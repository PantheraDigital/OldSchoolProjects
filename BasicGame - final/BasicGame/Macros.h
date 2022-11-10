#pragma once

#include <string>
#include <iostream>
#include <fstream>

//controls if VERBOSE_LOG will do anything
#define ENABLE_VERBOSE_LOG

#ifdef ENABLE_VERBOSE_LOG
	//print location of call with message
	//saves to Verbose file
	#define VERBOSE_LOG(message)		\
		std::string m = "FILE <";		\
		m += (std::string)__FILE__;		\
		m += ">  Line <";				\
		m += std::to_string(__LINE__);	\
		m += ">  Message <";			\
		m += message;					\
		m += ">\n";						\
		std::fstream fileStream;		\
		fileStream.open("..\\Verbose.sys", std::ios_base::out | std::ios_base::app);	\
		fileStream << m;				\
		fileStream.close();				\
		std::cout << m << std::endl;
#else
	#define VERBOSE_LOG(message)
#endif // ENABLE_VERBOSE_LOG

