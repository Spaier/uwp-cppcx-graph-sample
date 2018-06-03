#include "pch.h"
#include "Vertice.h"

using namespace VsuCpp4;

Vertice::Vertice(double x, double y, Platform::String^ value)
{
	X = x;
	Y = y;
	Value = value;
}
