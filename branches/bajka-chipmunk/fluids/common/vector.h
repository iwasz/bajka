// ** NOTES **
// Vector code CANNOT be inlined in header file because of dependencies
//    across vector classes (error generated: "Use of undeclared class..")
// 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include <math.h>

#ifndef VECTOR_DEF
#define VECTOR_DEF

	// Vector3DF Declarations

	#define VNAME		3DF
	#define VTYPE		float

	class Vector3DF {
	public:
		VTYPE x, y, z;
	
		// Constructors/Destructors
		inline Vector3DF();
		inline ~Vector3DF();
		inline Vector3DF (const VTYPE xa, const VTYPE ya, const VTYPE za);
		inline Vector3DF (const Vector3DF &op);

		// Set Functions
		inline Vector3DF &Set (const double xa, const double ya, const double za);
		
		// Member Functions
		inline Vector3DF &operator= (const int op);
		inline Vector3DF &operator= (const double op);
		inline Vector3DF &operator= (const Vector3DF &op);

		inline Vector3DF &operator+= (const int op);
		inline Vector3DF &operator+= (const double op);
		inline Vector3DF &operator+= (const Vector3DF &op);

		inline Vector3DF &operator-= (const int op);
		inline Vector3DF &operator-= (const double op);
		inline Vector3DF &operator-= (const Vector3DF &op);
	
		inline Vector3DF &operator*= (const int op);
		inline Vector3DF &operator*= (const double op);
		inline Vector3DF &operator*= (const Vector3DF &op);
//		Vector3DF &operator*= (const Matrix4F &op);
//		Vector3DF &operator*= (const MatrixF &op);				// see vector.cpp

		inline Vector3DF &operator/= (const int op);
		inline Vector3DF &operator/= (const double op);
		inline Vector3DF &operator/= (const Vector3DF &op);

		inline Vector3DF &Cross (const Vector3DF &v);	
		
		inline double Dot(const Vector3DF &v);

		inline double Dist (const Vector3DF &v);

		inline double DistSq (const Vector3DF &v);
		
		inline Vector3DF &Normalize (void);
		inline double Length (void);

		inline VTYPE &X();
		inline VTYPE &Y();
		inline VTYPE &Z();
		inline VTYPE W();
		inline const VTYPE &X() const;
		inline const VTYPE &Y() const;
		inline const VTYPE &Z() const;
		inline const VTYPE W() const;
		inline VTYPE *Data ();
	};
	

	// Constructors/Destructors
	inline Vector3DF::Vector3DF() {x=0; y=0; z=0;}
	inline Vector3DF::~Vector3DF() {}
	inline Vector3DF::Vector3DF (const VTYPE xa, const VTYPE ya, const VTYPE za) {x=xa; y=ya; z=za;}
	inline Vector3DF::Vector3DF (const Vector3DF &op) {x=(VTYPE) op.x; y=(VTYPE) op.y; z=(VTYPE) op.z;}

	// Set Functions
	inline Vector3DF &Vector3DF::Set (const double xa, const double ya, const double za)
	{
	        x = (float) xa; y = (float) ya; z = (float) za;
	        return *this;
	}

	// Member Functions
	inline Vector3DF &Vector3DF::operator= (const int op) {x= (VTYPE) op; y= (VTYPE) op; z= (VTYPE) op; return *this;}
	inline Vector3DF &Vector3DF::operator= (const double op) {x= (VTYPE) op; y= (VTYPE) op; z= (VTYPE) op; return *this;}
	inline Vector3DF &Vector3DF::operator= (const Vector3DF &op) {x=(VTYPE) op.x; y=(VTYPE) op.y; z=(VTYPE) op.z; return *this;}

	inline Vector3DF &Vector3DF::operator+= (const int op) {x+= (VTYPE) op; y+= (VTYPE) op; z+= (VTYPE) op; return *this;}
	inline Vector3DF &Vector3DF::operator+= (const double op) {x+= (VTYPE) op; y+= (VTYPE) op; z+= (VTYPE) op; return *this;}
	inline Vector3DF &Vector3DF::operator+= (const Vector3DF &op) {x+=(VTYPE) op.x; y+=(VTYPE) op.y; z+=(VTYPE) op.z; return *this;}

	inline Vector3DF &Vector3DF::operator-= (const int op) {x-= (VTYPE) op; y-= (VTYPE) op; z-= (VTYPE) op; return *this;}
	inline Vector3DF &Vector3DF::operator-= (const double op) {x-= (VTYPE) op; y-= (VTYPE) op; z-= (VTYPE) op; return *this;}
	inline Vector3DF &Vector3DF::operator-= (const Vector3DF &op) {x-=(VTYPE) op.x; y-=(VTYPE) op.y; z-=(VTYPE) op.z; return *this;}

	inline Vector3DF &Vector3DF::operator*= (const int op) {x*= (VTYPE) op; y*= (VTYPE) op; z*= (VTYPE) op; return *this;}
	inline Vector3DF &Vector3DF::operator*= (const double op) {x*= (VTYPE) op; y*= (VTYPE) op; z*= (VTYPE) op; return *this;}
	inline Vector3DF &Vector3DF::operator*= (const Vector3DF &op) {x*=(VTYPE) op.x; y*=(VTYPE) op.y; z*=(VTYPE) op.z; return *this;}

	inline Vector3DF &Vector3DF::operator/= (const int op) {x/= (VTYPE) op; y/= (VTYPE) op; z/= (VTYPE) op; return *this;}
	inline Vector3DF &Vector3DF::operator/= (const double op) {x/= (VTYPE) op; y/= (VTYPE) op; z/= (VTYPE) op; return *this;}
	inline Vector3DF &Vector3DF::operator/= (const Vector3DF &op) {x/=(VTYPE) op.x; y/=(VTYPE) op.y; z/=(VTYPE) op.z; return *this;}

	inline Vector3DF &Vector3DF::Cross (const Vector3DF &v) {double ax = x, ay = y, az = z; x = (VTYPE) (ay * (double) v.z - az * (double) v.y); y = (VTYPE) (-ax * (double) v.z + az * (double) v.x); z = (VTYPE) (ax * (double) v.y - ay * (double) v.x); return *this;}

	inline double Vector3DF::Dot(const Vector3DF &v)                        {double dot; dot = (double) x*v.x + (double) y*v.y + (double) z*v.z; return dot;}

	inline double Vector3DF::Dist (const Vector3DF &v)              { double distsq = DistSq (v); if (distsq!=0) return sqrt(distsq); return 0.0;}
	inline double Vector3DF::DistSq (const Vector3DF &v)            { double a,b,c; a = (double) x - (double) v.x; b = (double) y - (double) v.y; c = (double) z - (double) v.z; return (a*a + b*b + c*c);}

	inline Vector3DF &Vector3DF::Normalize (void) {
	        double n = (double) x*x + (double) y*y + (double) z*z;
	        if (n!=0.0) {
	                n = sqrt(n);
	                x /= (float) n; y /= (float) n; z /= (float) n;
	        }
	        return *this;
	}
	inline double Vector3DF::Length (void) { double n; n = (double) x*x + (double) y*y + (double) z*z; if (n != 0.0) return sqrt(n); return 0.0; }

	inline VTYPE &Vector3DF::X()                            {return x;}
	inline VTYPE &Vector3DF::Y()                            {return y;}
	inline VTYPE &Vector3DF::Z()                            {return z;}
	inline VTYPE Vector3DF::W()                                     {return 0;}
	inline const VTYPE &Vector3DF::X() const        {return x;}
	inline const VTYPE &Vector3DF::Y() const        {return y;}
	inline const VTYPE &Vector3DF::Z() const        {return z;}
	inline const VTYPE Vector3DF::W() const         {return 0;}
	inline VTYPE *Vector3DF::Data ()                        {return &x;}

	#undef VTYPE
	#undef VNAME

#endif

