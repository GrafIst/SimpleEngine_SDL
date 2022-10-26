#pragma once
class Timer
{
public:
	Timer() = default;
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;

	unsigned int computeDeltaTime();

	//wait if the game run faster than the decided FPS
	void delayTime();

private:
	const static unsigned int FPS = 60;
	const static unsigned int FRAME_DELAY = 1000 / FPS;
	const unsigned int MAX_DT = 50;

	unsigned int frameStart {0};

	unsigned int lastFrame {0};

	unsigned int frameTime {0};
};

