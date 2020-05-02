FLAGS = -g -ansi -pedantic -Werror -Wall
OBJS = room.o room_factory.o maze.o look.o hero_position.o character.o hero.o game_manager.o command_manager.o command_factory.o comunication.o NetworkHandler.o treasure.o monster.o create_hero.o left.o right.o quit.o quiting.o walk.o shout.o shouting.o talking.o talk.o take.o attack.o back.o help.o heal.o open.o close.o passage.o parser.o tokenizer.o insert_name.o default_action.o room_info.o passageobjfactory.o unlock.o lock.o rage.o raging.o



MazeApp: libGame.a main.o
	g++ $(FLAGS) -o MazeApp main.o libGame.a
	
main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

libGame.a: $(OBJS)
	ar rsc libGame.a $(OBJS)
	
	
NetworkHandler.o: ../Utils/NetworkHandler.cpp ../Utils/NetworkHandler.h
	g++ -c -g ../Utils/NetworkHandler.cpp	#not compile with flags

create_hero.o: ../Commands/create_hero.cpp ../Commands/create_hero.h
	g++ -c $(FLAGS) ../Commands/create_hero.cpp
	
comunication.o: ../Utils/comunication.cpp ../Utils/comunication.h
	g++ -c $(FLAGS) ../Utils/comunication.cpp
	
passageobjfactory.o: ../Utils/passageobjfactory.cpp ../Utils/passageobjfactory.h ../Objects/passage.h ../Objects/passageobj.h
	g++ -c $(FLAGS) ../Utils/passageobjfactory.cpp

passage.o: ../Objects/passage.cpp ../Objects/passage.h
	g++ -c $(FLAGS) ../Objects/passage.cpp
	
room_factory.o: ../Utils/room_factory.cpp ../Utils/room_factory.h
	g++ -c $(FLAGS) ../Utils/room_factory.cpp

room_info.o: ../Objects/room_info.cpp ../Objects/room_info.h
	g++ -c $(FLAGS) ../Objects/room_info.cpp

hero_position.o: ../Objects/hero_position.cpp ../Objects/hero_position.h
	g++ -c $(FLAGS) ../Objects/hero_position.cpp

hero.o: ../Objects/hero.cpp ../Objects/hero.h
	g++ -c $(FLAGS) -std=c++11 ../Objects/hero.cpp

character.o: ../Objects/character.cpp ../Objects/character.h
	g++ -c $(FLAGS) ../Objects/character.cpp -std=c++11
	
monster.o: ../Objects/monster.cpp ../Objects/monster.h
	g++ -c $(FLAGS) ../Objects/monster.cpp

treasure.o: ../Objects/treasure.cpp ../Objects/treasure.h
	g++ -c $(FLAGS) -std=c++11 ../Objects/treasure.cpp

game_manager.o: ../Objects/game_manager.cpp ../Objects/game_manager.h
	g++ -c $(FLAGS) ../Objects/game_manager.cpp

#Commands

command_manager.o: ../Commands/command_manager.cpp ../Commands/command_manager.h
	g++ -c $(FLAGS) ../Commands/command_manager.cpp

command_factory.o: ../Utils/command_factory.cpp ../Utils/command_factory.h
	g++ -c $(FLAGS) ../Utils/command_factory.cpp

parser.o: ../Utils/parser.cpp ../Utils/parser.h
	g++ -c $(FLAGS) ../Utils/parser.cpp
	
tokenizer.o: ../Utils/tokenizer.cpp ../Utils/tokenizer.h
	g++ -c $(FLAGS) ../Utils/tokenizer.cpp

close.o: ../Commands/close.cpp ../Commands/close.h
	g++ -c $(FLAGS) ../Commands/close.cpp

open.o: ../Commands/open.cpp ../Commands/open.h
	g++ -c $(FLAGS) ../Commands/open.cpp

walk.o: ../Commands/walk.cpp ../Commands/walk.h
	g++ -c $(FLAGS) ../Commands/walk.cpp

back.o: ../Commands/back.cpp ../Commands/back.h
	g++ -c $(FLAGS) ../Commands/back.cpp
	
quit.o: ../Commands/quit.cpp ../Commands/quit.h
	g++ -c $(FLAGS) ../Commands/quit.cpp
	
quiting.o: ../Commands/quiting.cpp ../Commands/quiting.h
	g++ -c $(FLAGS) ../Commands/quiting.cpp
	
left.o: ../Commands/left.cpp ../Commands/left.h
	g++ -c $(FLAGS) ../Commands/left.cpp

right.o: ../Commands/right.cpp ../Commands/right.h
	g++ -c $(FLAGS) ../Commands/right.cpp
	
take.o: ../Commands/take.cpp ../Commands/take.h
	g++ -c $(FLAGS) ../Commands/take.cpp

room.o: ../Objects/room.cpp ../Objects/room.h
	g++ -c $(FLAGS) ../Objects/room.cpp

maze.o: ../Objects/maze.cpp ../Objects/maze.h
	g++ -c $(FLAGS) ../Objects/maze.cpp

look.o: ../Commands/look.cpp ../Commands/look.h
	g++ -c $(FLAGS) ../Commands/look.cpp

attack.o: ../Commands/attack.cpp ../Commands/attack.h
	g++ -c $(FLAGS) ../Commands/attack.cpp

lock.o: ../Commands/lock.cpp ../Commands/lock.h
	g++ -c $(FLAGS) ../Commands/lock.cpp

help.o: ../Commands/help.cpp ../Commands/help.h
	g++ -c $(FLAGS) ../Commands/help.cpp

heal.o: ../Commands/heal.cpp ../Commands/heal.h
	g++ -c $(FLAGS) -std=c++11 ../Commands/heal.cpp

unlock.o: ../Commands/unlock.cpp ../Commands/unlock.h
	g++ -c $(FLAGS) ../Commands/unlock.cpp
	
shout.o: ../Commands/shout.cpp ../Commands/shout.h
	g++ -c $(FLAGS) ../Commands/shout.cpp
	
shouting.o: ../Commands/shouting.cpp ../Commands/shouting.h
	g++ -c $(FLAGS) ../Commands/shouting.cpp
	
talking.o: ../Commands/talking.cpp ../Commands/talking.h
	g++ -c $(FLAGS) ../Commands/talking.cpp

raging.o: ../Commands/raging.cpp ../Commands/raging.h
	g++ -c $(FLAGS) ../Commands/raging.cpp

rage.o: ../Commands/rage.cpp ../Commands/rage.h
	g++ -c $(FLAGS) ../Commands/rage.cpp
	
talk.o: ../Commands/talk.cpp ../Commands/talk.h
	g++ -c $(FLAGS) ../Commands/talk.cpp
	
insert_name.o: ../Commands/insert_name.cpp ../Commands/insert_name.h
	g++ -c $(FLAGS) ../Commands/insert_name.cpp

default_action.o: ../Commands/default_action.cpp ../Commands/default_action.h
	g++ -c $(FLAGS) ../Commands/default_action.cpp
	
	
clean: 
	rm -f *.o *~ MazeApp libGame.a
	

