#pragma once

#include "WhatCubes/Components/Pre.h"

class MathUtils
{
public:
	/**
	 * @brief 
	 * @param A 
	 * @param Min 
	 * @param Max 
	 * @return 
	 */
	static Double Clamp(Double A, Double Min, Double Max);
	/**
	 * @brief 
	 * @param A 
	 * @return 
	 */
	static Double Square(Double A);
	/**
	 * @brief 
	 * @param A 
	 * @return 
	 */
	static Double Cube(Double A);
	/**
	 * @brief 
	 * @param X 
	 * @param Y 
	 * @return 
	 */
	static Double Hypot(Double X, Double Y);
	/**
	 * @brief 
	 * @param X 
	 * @param Y 
	 * @param Z 
	 * @return 
	 */
	static Double Hypot(Double X, Double Y, Double Z);
	/**
	 * @brief 
	 * @param A 
	 * @return 
	 */
	static Double Floor(Double A);
	/**
	 * @brief 
	 * @param A 
	 * @return 
	 */
	static Double Ceil(Double A);
	/**
	 * @brief 
	 * @param A 
	 * @param B 
	 * @return 
	 */
	static Double FloorMod(Long A, Long B);

	class Coord
	{
	public:
		Coord(CoordInt X, CoordInt Y, CoordInt Z) : X{X}, Y{Y}, Z{Z} {}
		CoordInt GetX() const
		{
			return X;
		}
		CoordInt GetY() const
		{
			return Y;
		}
		CoordInt GetZ() const
		{
			return Z;
		}
	private:
		CoordInt X, Y, Z;
	};
};
