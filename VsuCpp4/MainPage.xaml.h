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
	using namespace Windows::UI::Xaml::Input;
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class MainPage sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
	{
	private:
		Windows::Foundation::Collections::IObservableVector<Vertice^>^ vertices;
		Windows::Foundation::Collections::IObservableVector<Edge^>^ edges;
		Vertice^ newEdgeVertice1;
		Vertice^ newEdgeVertice2;
	protected:
		virtual void NotifyPropertyChanged(Platform::String^ propertyName);
	public:
		virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;
		property Windows::Foundation::Collections::IObservableVector<Vertice^>^ Vertices {
			Windows::Foundation::Collections::IObservableVector<Vertice^>^ get();
		}
		property Windows::Foundation::Collections::IObservableVector<Edge^>^ Edges {
			Windows::Foundation::Collections::IObservableVector<Edge^>^ get();
		}
		property double NewVerticeX;
		property double NewVerticeY;
		property Platform::String^ NewVerticeValue;
		property Vertice^ NewEdgeVertice1
		{
			Vertice^ get();
			void set(Vertice^ value);
		}
		property Vertice^ NewEdgeVertice2
		{
			Vertice^ get();
			void set(Vertice^ value);
		}
		property ICommand^ AddEdgeCommand;
		MainPage();
	private:
		bool CanAddEdge(Platform::Object^ parameter);
		void OnAddEdge(Platform::Object^ parameter);
		void OnNew(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnOpen(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnSave(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnSaveAs(Platform::Object^ voi, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnAddVertice(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClear(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnRemoveVertice(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnRemoveEdge(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnTextToDouble(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxTextChangingEventArgs^ args);
	};
}
