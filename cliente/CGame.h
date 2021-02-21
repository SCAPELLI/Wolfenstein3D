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

class CGame{
	CPlayer activePlayer;
	GameScreen screen;
	std::vector<std::vector<int>> map;
	std::map<int, Renderable> renderables;
	std::map<int, EnemyPlayer*> players;
    SoundManager soundQueue;
    BagOfSprites sprites;

	public:
		CGame(double x, double y, double fov, std::vector<std::vector<int>> map);
		void draw();
		void rotate(double degrees);
		void advanceTime();
		void playSounds();
		void processEvent(ShootingEvent& event);
        void processEvent(TurnEvent& event);
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
		~CGame();
};

#endif