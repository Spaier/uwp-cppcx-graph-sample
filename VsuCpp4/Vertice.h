#pragma once

namespace VsuCpp4
{
	public ref class Vertice sealed
	{
	public:
		property Platform::String^ Value;
		property double X;
		property double Y;
		Vertice(double x, double y, Platform::String^ value);
	};
}
