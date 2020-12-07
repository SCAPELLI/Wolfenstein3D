

class Vector{

	public:
		double x;
		double y;
		Vector(double x, double y);
		Vector operator+(const Vector& v);
		Vector operator*(double z);
		Vector scale();
		~Vector();
}