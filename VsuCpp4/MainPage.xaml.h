//
// MainPage.xaml.h
// Declaration of the MainPage class
//

#pragma once

#include "MainPage.g.h"
#include "Vertice.h"

namespace VsuCpp4
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class MainPage sealed
	{
	private:
		Windows::Foundation::Collections::IObservableVector<Vertice^>^ vertices;
	public:
		property Windows::Foundation::Collections::IObservableVector<Vertice^>^ Vertices {
			Windows::Foundation::Collections::IObservableVector<Vertice^>^ get();
		}
		property double NewVerticeX;
		property double NewVerticeY;
		property Platform::String^ NewVerticeValue;
		MainPage();
	private:
		void OnNew(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnOpen(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnSave(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnSaveAs(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnAddVertice(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnAddEdge(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClear(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnRemoveVertice(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnRemoveEdge(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
