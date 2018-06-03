#include "pch.h"
#include "Edge.h"

using namespace VsuCpp4;

Platform::String^ Edge::Value::get()
{
	return Vertice1->Value + Vertice2->Value;
}

Edge::Edge(Vertice^ vertice1, Vertice^ vertice2)
{
	Vertice1 = vertice1;
	Vertice2 = vertice2;
}
