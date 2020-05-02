#include "../Objects/game_manager.h"
#include "../Utils/parser.h"
#include "../Utils/room_factory.h"
#include <stdlib.h>


using namespace advcpp;

typedef std::tr1::shared_ptr<Room> SPRoom;
int main (int argc, char const* argv[])
{
	Parser pars("map.txt");
	if (argc == 2)
	{
		GameManager manager(pars, atoi(argv[1]));
		manager.Start();

	}
	else
	{
		GameManager manager(pars);
		manager.Start();
	}
	return 0;
}

