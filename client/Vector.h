#ifndef WOLFENSTEIN3D_VECTOR_H
#define WOLFENSTEIN3D_VECTOR_H
/* Vector con métodos para manejar ángulos y distancias*/
class Vector{

	public:
        Vector();
		double x;
		double y;
		Vector(double x, double y);
		Vector rotate(double degrees);
		Vector operator+(const Vector& v);
		double distance(const Vector& v);
		void operator+=(const Vector& v);
		Vector operator-(const Vector&v);
		double size();
		double angle();
		double angle(const Vector& v);
		Vector operator*(double z);
		Vector scale();
        Vector operator/(double z);
        double operator*(Vector const &v);
    ~Vector();
};

#endif