#ifndef WOLFENSTEIN3D_CGAME_H
#define WOLFENSTEIN3D_CGAME_H

#include "GameScreen.h"
#include "CPlayer.h"
#include "Renderable.h"
#include "Wall.h"
#include <map>
#include "SoundManager.h"
#include "EnemyPlayer.h"
#include "BagOfSprites.h"
/* Juego de cliente*/
class PositionEvent;
class GameOverEvent;
class KillEvent;
class ShootingEvent;
class TurnEvent;
class OpenDoorEvent;
class SpawnEvent;
class DoorOpenedEvent;
class ChangeWeaponEvent;
class DespawnEvent;
class CreateMapEvent;
class SpawnNotMovableEvent;
class ScoreChangeEvent;
class AmmoChangeEvent;
class HealthChangeEvent;
class PickUpKeyEvent;

class CGame{
	CPlayer activePlayer;
	GameScreen screen;
	std::vector<std::vector<int>> map;
	std::map<int, Renderable> renderables;
	std::map<int, EnemyPlayer*> players;
    SoundManager soundQueue;
    BagOfSprites sprites;
    bool& isPlaying;
public:

    std::map<std::string, std::vector<int>> highscores;
	    CGame(double x, double y, double fov, std::vector<std::vector<int>> map, int playerId, bool& isPlaying);
		void draw();
		void rotate(double degrees);
		void advanceTime();
		void playSounds();
		void processEvent(ShootingEvent& event);
        void processEvent(TurnEvent& event);
        void processEvent(PickUpKeyEvent& event);
        void processEvent(GameOverEvent& event);
		void processEvent(KillEvent& event);
		void processEvent(PositionEvent& event);
        void processEvent(ChangeWeaponEvent& event);
		void processEvent(SpawnEvent& event);
		void processEvent(SpawnNotMovableEvent& event);
		void processEvent(DespawnEvent& event);
        void processEvent(DoorOpenedEvent& event);
        void processEvent(CreateMapEvent& event);
        void processEvent(AmmoChangeEvent& event);
        void processEvent(ScoreChangeEvent& event);
        void processEvent(HealthChangeEvent& event);
        void spawnEnemy(int playerId, Vector spawnPoint);

		~CGame();
};

#endif