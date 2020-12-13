#ifndef WOLFENSTEIN3D_VECTOR_H
#define WOLFENSTEIN3D_VECTOR_H

class Vector{

	public:
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
		~Vector();
};

#endif