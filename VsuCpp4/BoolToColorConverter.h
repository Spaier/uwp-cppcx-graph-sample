#pragma once

namespace VsuCpp4
{
	using namespace Windows::UI::Xaml::Interop;
	using namespace Windows::UI::Xaml::Data;
	using namespace Platform;
	public ref class BoolToColorConverter sealed : IValueConverter
	{
	public:
		BoolToColorConverter();

		// Inherited via IValueConverter
		virtual Platform::Object ^ Convert(Object ^value, TypeName targetType, Object ^parameter, String ^language);
		virtual Platform::Object ^ ConvertBack(Object ^value, TypeName targetType, Object ^parameter, String ^language);
	};
}

