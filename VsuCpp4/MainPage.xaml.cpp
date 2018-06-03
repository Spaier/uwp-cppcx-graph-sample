//
// MainPage.xaml.cpp
// Implementation of the MainPage class
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <string>

using namespace VsuCpp4;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace std;

Windows::Foundation::Collections::IObservableVector<Vertice^>^ MainPage::Vertices::get()
{
	return vertices;
}

Windows::Foundation::Collections::IObservableVector<Edge^>^ MainPage::Edges::get()
{
	return edges;
}

MainPage::MainPage()
{
	InitializeComponent();
	vertices = ref new Platform::Collections::Vector<Vertice^>();
	edges = ref new Platform::Collections::Vector<Edge^>();
}

void VsuCpp4::MainPage::OnNew(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}

void VsuCpp4::MainPage::OnOpen(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}

void VsuCpp4::MainPage::OnSave(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}

void VsuCpp4::MainPage::OnSaveAs(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}

void VsuCpp4::MainPage::OnAddEdge(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//edges->Append(ref new Edge());
}

void VsuCpp4::MainPage::OnAddVertice(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto new_vertice = ref new Vertice(NewVerticeX, NewVerticeY, NewVerticeValue);
	vertices->Append(new_vertice);
}

void VsuCpp4::MainPage::OnClear(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	vertices->Clear();
}

void VsuCpp4::MainPage::OnRemoveEdge(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}

void VsuCpp4::MainPage::OnRemoveVertice(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}

void VsuCpp4::MainPage::OnTextToDouble(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxTextChangingEventArgs^ args)
{
	if (!sender->Text->IsEmpty())
	{
		wstringstream stream(sender->Text->Data());
		double value;
		stream >> value;
		if (!stream.eof() || stream.fail())
		{
			sender->Text = L"0";
		}
	}
}
