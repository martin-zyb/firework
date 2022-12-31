#include "text.h"
#include <graphics.h>

void Text::show()
{
	settextcolor(YELLOW);
	settextstyle(40, 0, "Î¢ÈíÑÅºÚ");

	outtextxy(400, 150, "Say Something......");
}