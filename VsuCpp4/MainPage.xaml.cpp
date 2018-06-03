//
// MainPage.xaml.cpp
// Implementation of the MainPage class
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Windows::UI::Xaml::Controls;
using namespace VsuCpp4;
using namespace std;

MainPage::MainPage()
{
	InitializeComponent();
	ViewModel = ref new MainViewModel();
}

void MainPage::OnTextToDouble(TextBox^ sender, TextBoxTextChangingEventArgs^ args)
{
	if (sender->Text != nullptr && !sender->Text->IsEmpty())
	{
		wstringstream stream(sender->Text->Data());
		double value;
		stream >> value;
		if (stream.eof() && !stream.fail()) return;
	}
	sender->Text = L"0";
}
