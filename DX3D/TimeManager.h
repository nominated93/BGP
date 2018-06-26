#pragma once

#define g_pTimeManager TimeManager::GetInstance()

class TimeManager
{
	SINGLETON(TimeManager)
private:
	DWORD prevTime;
	DWORD deltaTime;
	float sumTime;
	int frameCnt;
	int fps;

public:
	void Update();
	float GetDeltaTime() { return deltaTime / 1000.f; }
	float GetEllapsedTime(){ return deltaTime / 1000.f; }
	int GetFPS() { return fps; }
};

