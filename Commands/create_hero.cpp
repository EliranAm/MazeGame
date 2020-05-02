#include "create_hero.h"

#include "../Objects/hero.h"
#include "../Objects/room.h"
#include <tr1/memory>
#include <string>

#define COLOR_BOLD	"\x1b[01m"
#define COLOR_CYAN	"\x1b[36m"
#define COLOR_RESET	"\x1b[0m"


namespace advcpp
{

const std::string CreateHero::Execute(size_t _heroID, Maze &_maze)
{
	if (_maze.IsUserExist(_heroID)) 
	{
		//in case the user already exist
		return "ERROR!";
	}
	
	std::tr1::shared_ptr<Hero> newHero(new Hero(_heroID));
	_maze.InsertNewHero(newHero);
	std::string retVal = "Please, Enter your name.\n";
	return ShowEntranceScreen() + retVal;
}

const std::string CreateHero::ShowEntranceScreen() const
{
	return std::string (COLOR_BOLD "" COLOR_CYAN
	"\t\t\t\t                              .-') _   _ .-') _       \n"
	"\t\t\t\t                             ( OO ) ) ( (  OO) )      \n"
	"\t\t\t\t      ,------.   ,-.-')  ,--./ ,--,'   \\     .'_     \n"
	"\t\t\t\t   ('-| _.---'   |  |OO) |   \\ |  |\\   ,`'--..._)   \n"
	"\t\t\t\t   (OO|(_\\       |  |  \\ |    \\|  | )  |  |  \\  ' \n"
	"\t\t\t\t   /  |  '--.    |  |(_/ |  .     |/   |  |   ' |     \n"
	"\t\t\t\t   \\_)|  .--'   ,|  |_.' |  |\\    |    |  |   / :   \n"
	"\t\t\t\t     \\|  |_)   (_|  |    |  | \\   |    |  '--'  /   \n"
	"\t\t\t\t      `--'       `--'    `--'  `--'    `-------'      \n\n\n\n"

	"\t\t                          ('-.       .-')      .-')                 ('-.\n"   
	"\t\t                         ( OO ).-.  ( OO ).   ( OO ).             _(  OO)   \n"
	"\t\t             ,--.        / . --. / (_)---\\_) (_)---\\_)   ,-.-')  (,------.  \n"
	"\t\t             |  |.-')    | \\-.  \\  /    _ |  /    _ |    |  |OO)  |  .---'  \n"
	"\t\t             |  | OO ) .-'-'  |  | \\  :` `.  \\  :` `.    |  |  \\  |  |      \n"
	"\t\t             |  |`-' |  \\| |_.'  |  '..`''.)  '..`''.)   |  |(_/ (|  '--.   \n"
	"\t\t            (|  '---.'   |  .-.  | .-._)   \\ .-._)   \\  ,|  |_.'  |  .--'   \n"
	"\t\t             |      |    |  | |  | \\       / \\       / (_|  |     |  `---.  \n"
	"\t\t             `------'    `--' `--'  `-----'   `-----'    `--'     `------'  \n\n\n\n" COLOR_RESET);
}


/*
	std::string str(""COLOR_BOLD
	"                           .-') _   _ .-') _                       ('-.       .-')      .-')                 ('-.\n"   
	"                          ( OO ) ) ( (  OO) )                     ( OO ).-.  ( OO ).   ( OO ).             _(  OO)   \n"
	"   ,------.   ,-.-')  ,--./ ,--,'   \\     .'_         ,--.        / . --. / (_)---\\_) (_)---\\_)   ,-.-')  (,------.  \n"
	"('-| _.---'   |  |OO) |   \\ |  |\\   ,`'--..._)        |  |.-')    | \\-.  \\  /    _ |  /    _ |    |  |OO)  |  .---'  \n"
	"(OO|(_\\       |  |  \\ |    \\|  | )  |  |  \\  '        |  | OO ) .-'-'  |  | \\  :` `.  \\  :` `.    |  |  \\  |  |      \n"
	"/  |  '--.    |  |(_/ |  .     |/   |  |   ' |        |  |`-' |  \\| |_.'  |  '..`''.)  '..`''.)   |  |(_/ (|  '--.   \n"
	"\\_)|  .--'   ,|  |_.' |  |\\    |    |  |   / :       (|  '---.'   |  .-.  | .-._)   \\ .-._)   \\  ,|  |_.'  |  .--'   \n"
	"  \\|  |_)   (_|  |    |  | \\   |    |  '--'  /        |      |    |  | |  | \\       / \\       / (_|  |     |  `---.  \n	"
	"   `--'       `--'    `--'  `--'    `-------'         `------'    `--' `--'  `-----'   `-----'    `--'     `------'  \n\n\n\n");
*/


}	//namespace advcpp
