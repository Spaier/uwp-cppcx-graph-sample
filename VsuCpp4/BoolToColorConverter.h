#pragma once

namespace VsuCpp4
{
	using namespace Windows::UI::Xaml::Interop;
	public ref class BoolToColorConverter sealed : Windows::UI::Xaml::Data::IValueConverter
	{
	public:
		BoolToColorConverter();

		// Inherited via IValueConverter
		virtual Platform::Object ^ Convert(Platform::Object ^value, TypeName targetType, Platform::Object ^parameter, Platform::String ^language);
		virtual Platform::Object ^ ConvertBack(Platform::Object ^value, TypeName targetType, Platform::Object ^parameter, Platform::String ^language);
	};
}

