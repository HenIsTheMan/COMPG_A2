#pragma once
#include <windows.h>

class StopWatch{
	double LIToSecs(LARGE_INTEGER&);
	LARGE_INTEGER frequency, prevTime, currTime;
	UINT wTimerRes;
public:
	StopWatch();
	~StopWatch();
	double getElapsedTime(); //Get time in seconds since the last call to this function
	void startTimer(), waitUntil(long long);
};