#include "pch.h"
#include "BoolToColorConverter.h"

using namespace VsuCpp4;
using namespace Platform;
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Media;

BoolToColorConverter::BoolToColorConverter() { }

Object ^ BoolToColorConverter::Convert(Object ^value, TypeName targetType, Object ^parameter, String ^language)
{
	if (value->Equals(true))
	{
		return ref new SolidColorBrush(Colors::Violet);
	}
	else
	{
		return ref new SolidColorBrush(Colors::Red);
	}
}

Object ^ BoolToColorConverter::ConvertBack(Object ^value, TypeName targetType, Object ^parameter, String ^language)
{
	throw ref new Platform::NotImplementedException();
}
