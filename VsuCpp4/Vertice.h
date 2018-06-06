#pragma once

namespace VsuCpp4
{
	public ref class Vertice sealed
	{
	private:
		unsigned long long id;
	public:
		property unsigned long long Id
		{
			unsigned long long get()
			{
				return id;
			}
		}
		property Platform::String^ Value;
		property double X;
		property double Y;
		Vertice(double x, double y, Platform::String^ value, unsigned long long id) : id(id)
		{
			X = x;
			Y = y;
			Value = value;
		}
	};
}
