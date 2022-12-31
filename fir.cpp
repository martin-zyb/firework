#include "fir.h"

void Firework::Init(int i)
{
	int r[NUM] = { 120,120,155,123,130,147,138,138,130,135,140,132,155 };
	int x[NUM] = { 120,120,110,117,110,93,102,102,110,105,100,108,110 };
	int y[NUM] = { 120,120,85,118,120,103,105,110,110,120,120,104,85 };
	fire[i].width = 240;
	fire[i].height = 240;
	fire[i].cen_x = x[i];
	fire[i].cen_y = y[i];
	fire[i].maxr = r[i];
	fire[i].show = false;
	fire[i].dt = 5;
	fire[i].t1 = timeGetTime();
	fire[i].r = 0;

	jet[i].t1 = timeGetTime();
	jet[i].dt = rand() % 10;
	jet[i].n = 0;
	jet[i].shoot = false;
}

void Firework::Load()
{
	IMAGE flowerImg, fimg;
	loadimage(&flowerImg, "IMAGE", "flower");
	for (int i = 0; i < NUM; i++)
	{
		SetWorkingImage(&flowerImg);
		getimage(&fimg, i * 240, 0, 240, 240);
		SetWorkingImage(&fimg);
		for (int m = 0; m < 240; m++)
		{
			for (int n = 0; n < 240; n++)
			{
				fire[i].xy[m][n] = getpixel(m, n);
			}
		}
	}
	IMAGE shootImg;
	loadimage(&shootImg, "IMAGE", "shoot");
	for (int i = 0; i < NUM; i++)
	{
		int n = rand() % 5;
		SetWorkingImage(&shootImg);
		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], (n + 5) * 20, 0, 20, 50);
	}
	SetWorkingImage(NULL);
}

void Firework::ChoiseRelu(DWORD& t1)
{
	DWORD t2 = timeGetTime();
	if (t2 - t1 > 100)
	{
		int n = rand() % NUM;
		if (jet[n].shoot == false && fire[n].show == false)
		{
			jet[n].x = rand() % 1180;
			jet[n].y = rand() % 100 + 600;
			jet[n].hx = jet[n].x;
			jet[n].hy = rand() % 400;
			jet[n].height = jet[n].y - jet[n].hy;
			jet[n].shoot = true;
			putimage(jet[n].x, jet[n].y, &jet[n].img[jet[n].n], SRCINVERT);
		}
		t1 = t2;
	}
}

void Firework::Shoot()
{
	for (int i = 0; i < NUM; i++)
	{
		jet[i].t2 = timeGetTime();
		if (jet[i].t2 - jet[i].t1 > jet[i].dt && jet[i].shoot == true)
		{
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			if (jet[i].y >= jet[i].hy)
			{
				jet[i].y -= 5;
				jet[i].n++;
			}
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
			if (jet[i].y - jet[i].hy * 4 < jet[i].height)
			{
				jet[i].dt = rand() % 4 + 10;
			}
			if (jet[i].y <= jet[i].hy)
			{
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
				fire[i].x = jet[i].x;
				fire[i].y = jet[i].hy;
				fire[i].show = true;
				jet[i].shoot = false;
			}
			jet[i].t1 = jet[i].t2;
		}
	}
}

void Firework::ShowFire(DWORD* pmem)
{ 
	int  drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 65, 65 };
	for (int i = 0; i < NUM; i++)
	{
		fire[i].t2 = timeGetTime();

		if (fire[i].t2 - fire[i].t1 > fire[i].dt && fire[i].show == true)
		{
			if (fire[i].r < fire[i].maxr)
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;
			}
			if (fire[i].r >= fire[i].maxr - 1)
			{
				fire[i].draw = false;
				Init(i);
			}
			fire[i].t1 = fire[i].t2;
		}
		if (fire[i].draw)
		{
			for (double a = 0; a <= 6.28; a += 0.01)
			{
				int x1 = (int)(fire[i].cen_x + fire[i].r * cos(a));
				int y1 = (int)(fire[i].cen_y + fire[i].r * sin(a));
				if (x1 > 0 && x1 < fire[i].width && y1>0 && y1 < fire[i].height)
				{
					int b = fire[i].xy[x1][y1] & 0xff;   //blue
					int g = (fire[i].xy[x1][y1] >> 8) & 0xff;   //green
					int r = fire[i].xy[x1][y1] >> 16;   //red
					int xx = (int)(fire[i].x + fire[i].r * cos(a));
					int yy = (int)(fire[i].y - fire[i].r * sin(a));
					//
					if (r > 0x20 && g > 0x20 && b > 0x20 && xx < 1200 && xx>0 && yy > 0 && yy < 600)
					{
						pmem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);
					}
				}
			}
			fire[i].draw = false;
		}
	}
}