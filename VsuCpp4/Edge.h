#pragma once

#include "Vertice.h"

namespace VsuCpp4
{
	public ref class Edge sealed
	{
	public:
		property Vertice^ Vertice1;
		property Vertice^ Vertice2;
		property double Weight;
		property bool IsMst;
		property Platform::String^ Value 
		{
			Platform::String^ get();
		}
		Edge(Vertice^ vertice1, Vertice^ vertice2, double weight);
	};
}

