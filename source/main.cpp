#include "fir.h"
#include "cmd.h"
#include "text.h"
#include "uni.h"

int main(void)
{
	Cmd* cmd = new Cmd;
	Text* text = new Text;
	Firework* firework = new Firework;

	cmd->Init();
	cmd->run();

	srand((unsigned)time(0));
	initgraph(1200, 600);

	uni::__sleep(750);

	DWORD t1 = timeGetTime();
	DWORD* pmem = GetImageBuffer();
	DWORD st1 = timeGetTime();

	text->show();

	for (int i = 0; i < NUM; i++)
	{
		firework->Init(i);
	}

	firework->Load();

	BeginBatchDraw();
	while (!GetAsyncKeyState(0x1B))
	{
		for (int clr = 0; clr < 1000; clr++)
		{
			for (int j = 0; j < 2; j++)
			{
				int px1 = rand() % 1200;
				int py1 = rand() % 600;
				if (py1 < 790)
				{
					pmem[py1 * 1200 + px1] = pmem[py1 * 1200 + px1 + 1] = BLACK;
				}
			}
		}
		firework->ChoiseRelu(t1);
		firework->Shoot();
		firework->ShowFire(pmem);
		FlushBatchDraw();
	}
	delete text;
	delete firework;
	closegraph();
	cmd->off();
	delete cmd;
	return 0;
}