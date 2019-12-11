#include "Engine.h"
#include "ItemBuilder.h"

int main(int argc, char** argv)
{
	auto& engine = Engine::Instance();

	ItemBuilder itemBuilder;


	for (int i = 0; i < 10; i++)
	{
		Armor* armor = itemBuilder.GetRandomArmor(50);

		std::cout << "Name: " << armor->Name() << std::endl;
		std::cout << "Str: " << armor->Strength() << std::endl;
		std::cout << "Agi: " << armor->Agility() << std::endl;
		std::cout << "Int: " << armor->Intellect() << std::endl;
		std::cout << "Spr: " << armor->Spirit() << std::endl;
		std::cout << "Sta: " << armor->Stamina() << std::endl;
		std::cout << "Def: " << armor->Defense() << std::endl;
		std::cout << "Res: " << armor->Resistance() << std::endl;

		delete armor;

		std::cin.ignore();
	}
	
	//engine.Run();

	return 0;
}