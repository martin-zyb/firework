#include "cmd.h"

#include "uni.h"

#include <spdlog\spdlog.h>

void Cmd::Init()
{
	spdlog::set_pattern("[%T] %^%l: %v%$");
}

void Cmd::run()
{
	// Something will print in Console when the program running
	spdlog::info("Example information in running");
	uni::__sleep(3000);
}

void Cmd::off()
{
	// Something will print in Console when the program closing
	spdlog::info("Example information in closing");
	uni::__sleep(3000);
}
