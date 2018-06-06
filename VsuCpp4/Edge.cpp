#include "pch.h"
#include "Edge.h"

using namespace VsuCpp4;
using namespace Platform;

String^ Edge::Value::get()
{
	return Vertice1->Value + L" " + Vertice2->Value + L" " + Weight.ToString();
}

Edge::Edge(Vertice^ vertice1, Vertice^ vertice2, double weight)
{
	Vertice1 = vertice1;
	Vertice2 = vertice2;
	Weight = weight;
	IsMst = false;
}
