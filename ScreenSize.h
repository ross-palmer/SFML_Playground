#pragma once

class ScreenSize
{
public:
	static int height()
	{
		return s_height;
	}

	static int width()
	{
		return s_width;
	}

private:
	static int s_width;

	static int s_height;
};
