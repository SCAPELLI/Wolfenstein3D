class Player: public Renderable{
	public:
		Player();
		bool isOnSight(Map& map, Vector& origin);
		void drawFrom(Vector& origin);
		~Player();
};
