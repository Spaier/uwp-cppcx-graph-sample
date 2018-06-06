#pragma once

namespace VsuCpp4
{
	using namespace Platform;
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
		property String^ Value;
		property double X;
		property double Y;
		Vertice(double x, double y, String^ value, unsigned long long id) : id(id)
		{
			X = x;
			Y = y;
			Value = value;
		}
	};
}
