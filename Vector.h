#ifndef WOLFENSTEIN3D_VECTOR_H
#define WOLFENSTEIN3D_VECTOR_H

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

#endif