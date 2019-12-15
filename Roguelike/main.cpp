#include "Engine.h"

int main(int argc, char** argv)
{
	auto& engine = Engine::Instance();

	engine.Run();

	return 0;
}