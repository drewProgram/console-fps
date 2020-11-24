#include <iostream>
using namespace std;

#include <Windows.h>

int nScreenWidth = 120;
int nScreenHeight = 40;

float fPlayerX = 0.0f;
float fPlayerY = 0.0f;
float fPlayerA = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

float fFOV = 3.14159 / 4.0;
float fDepth = 16.0;

int main()
{
	// create screen buffer
	wchar_t* screen = new wchar_t[nScreenHeight * nScreenWidth];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0,
		NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	wstring map;

	map += L"###############";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"#.............#";
	map += L"###############";

	// game loop
	while (1)
	{
		for (int x = 0; x < nScreenWidth; x++)
		{
			//for each column, calculate the projected ray angle into world space
			float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth * fFOV);

			float fDistanceToWall = 0;
			bool bHitWall = false;

			float fEyeX = sinf(fRayAngle); // unit vector for ray in player space
			float fEyeY = cosf(fRayAngle);

			while (!bHitWall && fDistanceToWall < fDepth)
			{
				fDistanceToWall += 0.1f;

				int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
				int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

				// test if ray is out of bounds
				if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight) 
				{

				}
			}
		}

		// when to stop writing
		screen[nScreenHeight * nScreenWidth - 1] = '\0';
		// handle, buffer, how many bytes, coordinates (always write at top left)
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
	}

	return 0;
}
