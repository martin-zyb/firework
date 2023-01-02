#include "text.h"

#include "uni.h"

#include <graphics.h>

void Text::show()
{
	settextcolor(YELLOW);
	settextstyle(40, 0, "Î¢ÈíÑÅºÚ");

	outtextxy(390, 200, "Write Something here");

	uni::__sleep(3000);
}