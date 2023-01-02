#include <graphics.h>
#include <ctime>
#include <string>
#include <cstdlib>
#include <mmsystem.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <windows.h>

#pragma comment(lib,"winmm.lib")

#define NUM 13
#define PI 3.14159265358979323846

class Firework
{
	private:

		struct Jet
		{
			int x, y;
			int hx, hy;
			int height;
			bool shoot;
			DWORD t1, t2, dt;
			IMAGE img[2];
			byte n : 1;
		};

		struct Fire
		{
			int r;
			int maxr;
			int x, y;
			int cen_x, cen_y;
			int width, height;
			int xy[240][240];
			bool show;
			bool draw;
			DWORD t1, t2, dt;
		};

		public:
			Jet jet[NUM];

			Fire fire[NUM];

			void Init(int i); 
			void Load(); 
			void ChoiseRelu(DWORD& t1); 
			void Shoot();
			void ShowFire(DWORD* pmem);
};