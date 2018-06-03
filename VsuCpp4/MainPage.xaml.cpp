//
// MainPage.xaml.cpp
// Implementation of the MainPage class
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "RelayCommand.h"

using namespace VsuCpp4;
using namespace VsuCpp4::Mvvm;

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

template <typename T> static void RaiseCanExecuteChanged(Windows::UI::Xaml::Input::ICommand^ instance)
{
	auto command = dynamic_cast<T^>(instance);
	command->RaiseCanExecuteChanged();
}

void MainPage::NotifyPropertyChanged(String^ propertyName)
{
	PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
}

Windows::Foundation::Collections::IObservableVector<Vertice^>^ MainPage::Vertices::get() { return vertices; }

Windows::Foundation::Collections::IObservableVector<Edge^>^ MainPage::Edges::get() { return edges; }

Vertice^ MainPage::NewEdgeVertice1::get() { return newEdgeVertice1; }

void MainPage::NewEdgeVertice1::set(Vertice^ value)
{
	newEdgeVertice1 = value;
	NotifyPropertyChanged(L"NewEdgeVertice1");
	RaiseCanExecuteChanged<RelayCommand>(AddEdgeCommand);
}

Vertice^ MainPage::NewEdgeVertice2::get() { return newEdgeVertice2; }

void MainPage::NewEdgeVertice2::set(Vertice^ value)
{
	newEdgeVertice2 = value;
	NotifyPropertyChanged(L"NewEdgeVertice2");
	RaiseCanExecuteChanged<RelayCommand>(AddEdgeCommand);
}

MainPage::MainPage()
{
	InitializeComponent();
	vertices = ref new Platform::Collections::Vector<Vertice^>();
	edges = ref new Platform::Collections::Vector<Edge^>();
	AddEdgeCommand = ref new RelayCommand(
		ref new ExecuteDelegate(this, &MainPage::OnAddEdge),
		ref new CanExecuteDelegate(this, &MainPage::CanAddEdge)
	);
}

void MainPage::OnAddEdge(Platform::Object^ parameter)
{
	vertices->Append(dynamic_cast<Vertice^>(parameter));
}

bool MainPage::CanAddEdge(Platform::Object^ parameter)
{
	return NewEdgeVertice1 != nullptr && NewEdgeVertice2 != nullptr && NewEdgeVertice1 != NewEdgeVertice2;
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

void MainPage::OnTextToDouble(Windows::UI::Xaml::Controls::TextBox^ sender, Windows::UI::Xaml::Controls::TextBoxTextChangingEventArgs^ args)
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
