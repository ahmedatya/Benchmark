#ifndef ATYA_TIC_TOC_
#define ATYA_TIC_TOC_

#include <iostream>
#include <stack>
#include <time.h>
#include <sys/time.h>
#include <string.h>

class TicToc
{
	struct timeval start;
	struct timeval end;
	std::stack<struct timeval> q;

public:

	TicToc()
	{
		//Init
		gettimeofday(&start,NULL);
		gettimeofday(&end,NULL);
	}

	/**
	* Return Current Date and Time in a string
	*/
	const std::string GetDateTime()
	{
	    time_t rawtime;
	    struct tm * timeinfo;
	    char buffer[80];
	    time (&rawtime);
	    timeinfo = localtime(&rawtime);
	    strftime(buffer,80,"%d-%m-%Y_%I:%M:%S",timeinfo);
	    std::string str(buffer);
		return str;
	}

	/**
	* Save a start time
	*/
	void tic()
	{
		gettimeofday(&start,NULL);
		q.push(start);
	}

	/**
	* Calculate the duration from the start time in microseconds
	*/
	const double toc()
	{
		if(q.empty()) return 0;

		gettimeofday(&end,NULL);
		start = q.top();
		q.pop();

		double RTT = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
		return RTT;
	}

};

#endif //ATYA_TIC_TOC_
