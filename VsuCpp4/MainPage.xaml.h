//
// MainPage.xaml.h
// Declaration of the MainPage class
//

#pragma once

#include "MainPage.g.h"
#include "Vertice.h"
#include "Edge.h"

namespace VsuCpp4
{
	using namespace Windows::UI::Xaml::Controls;
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class MainPage sealed
	{
	public:
		property MainViewModel^ ViewModel;
		MainPage();
	private:
		void OnTextToDouble(TextBox^ sender, TextBoxTextChangingEventArgs^ args);
	};
}
