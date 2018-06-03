//
// MainPage.xaml.cpp
// Implementation of the MainPage class
//

#include "pch.h"
#include "MainPage.xaml.h"

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

Windows::Foundation::Collections::IObservableVector<Vertice^>^ MainPage::Vertices::get()
{
	return vertices;
}

MainPage::MainPage()
{
	InitializeComponent();
	vertices = ref new Platform::Collections::Vector<Vertice^>();
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

}

void VsuCpp4::MainPage::OnAddVertice(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	vertices->Append(ref new Vertice(NewVerticeX, NewVerticeY, NewVerticeValue));
}

void VsuCpp4::MainPage::OnClear(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	vertices->Clear();
}

void VsuCpp4::MainPage::OnRemoveVertice(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}

void VsuCpp4::MainPage::OnRemoveEdge(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}
