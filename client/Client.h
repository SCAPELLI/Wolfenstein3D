#include "WorldMap.h"
#include "client/include/Renderable.h"
#include <vector>
/* Clase que corre cliente*/
class Client: public Thread{
	GameScreen screen;

	public:
		Client();
		void operator()();
		void run();
		~Client();
}