#include "pch.h"
#include "BoolToColorConverter.h"

using namespace VsuCpp4;

BoolToColorConverter::BoolToColorConverter()
{

}

Platform::Object ^ BoolToColorConverter::Convert(Platform::Object ^value, TypeName targetType, Platform::Object ^parameter, Platform::String ^language)
{
	if (value->Equals(true))
	{
		return ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Violet);
	}
	else
	{
		return ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Red);
	}
}

Platform::Object ^ BoolToColorConverter::ConvertBack(Platform::Object ^value, TypeName targetType, Platform::Object ^parameter, Platform::String ^language)
{
	throw ref new Platform::NotImplementedException();
}
