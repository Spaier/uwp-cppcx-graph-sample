#pragma once

#include "Edge.h"
#include "Vertice.h"
#include "RelayCommand.h"

namespace VsuCpp4
{
	using namespace Windows::Foundation::Collections;
	using namespace VsuCpp4::Mvvm;
	using namespace concurrency;
	using namespace std;

	template <typename T> static void RaiseCanExecuteChanged(Windows::UI::Xaml::Input::ICommand^ instance)
	{
		auto command = dynamic_cast<T^>(instance);
		command->RaiseCanExecuteChanged();
	}

	[Windows::UI::Xaml::Data::Bindable]
	public ref class MainViewModel sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
	{
	private:
		// Fields
		IObservableVector<Edge^>^ edges;
		IObservableVector<Vertice^>^ vertices;
		Vertice^ newEdgeVertice1;
		Vertice^ newEdgeVertice2;
		Vertice^ verticeToRemove;
		Edge^ edgeToRemove;
	public:
		// Properties
		property IObservableVector<Vertice^>^ Vertices {
			IObservableVector<Vertice^>^ get() { return vertices; }
		}
		property IObservableVector<Edge^>^ Edges {
			IObservableVector<Edge^>^ get() { return edges; }
		}
		property double NewVerticeX;
		property double NewVerticeY;
		property Platform::String^ NewVerticeValue;
		property double NewEdgeWeight;
		property Vertice^ NewEdgeVertice1
		{
			Vertice^ get() { return newEdgeVertice1; }
			void set(Vertice^ value)
			{
				if (value != newEdgeVertice1) {
					newEdgeVertice1 = value;
					NotifyPropertyChanged(L"NewEdgeVertice1");
					RaiseCanExecuteChanged<RelayCommand>(AddEdgeCommand);
				}
			}
		}
		property Vertice^ NewEdgeVertice2
		{
			Vertice^ get() { return newEdgeVertice2; }
			void set(Vertice^ value)
			{
				if (value != newEdgeVertice2) {
					newEdgeVertice2 = value;
					NotifyPropertyChanged(L"NewEdgeVertice2");
					RaiseCanExecuteChanged<RelayCommand>(AddEdgeCommand);
				}
			}
		}
		property Vertice^ VerticeToRemove
		{
			Vertice^ get() { return verticeToRemove; }
			void set(Vertice^ value)
			{
				if (value != verticeToRemove) {
					verticeToRemove = value;
					NotifyPropertyChanged(L"VerticeToRemove");
					RaiseCanExecuteChanged<RelayCommand>(RemoveVerticeCommand);
				}
			}
		}
		property Edge^ EdgeToRemove
		{
			Edge^ get() { return edgeToRemove; }
			void set(Edge^ value)
			{
				if (value != edgeToRemove) {
					edgeToRemove = value;
					NotifyPropertyChanged(L"EdgeToRemove");
					RaiseCanExecuteChanged<RelayCommand>(RemoveEdgeCommand);
				}
			}
		}
		// Commands
		property Windows::UI::Xaml::Input::ICommand^ AddVerticeCommand;
		property Windows::UI::Xaml::Input::ICommand^ AddEdgeCommand;
		property Windows::UI::Xaml::Input::ICommand^ RemoveVerticeCommand;
		property Windows::UI::Xaml::Input::ICommand^ RemoveEdgeCommand;
		property Windows::UI::Xaml::Input::ICommand^ ClearCommand;
		property Windows::UI::Xaml::Input::ICommand^ OpenCommand;
		property Windows::UI::Xaml::Input::ICommand^ SaveAsCommand;
		// Constructors
		MainViewModel();
	private:
		void OnMst()
		{
			auto vm_edge_vec = dynamic_cast<Platform::Collections::Vector<Edge^>^>(edges);
			auto edge_vec = ref new Platform::Collections::Vector<Edge^>(begin(vm_edge_vec), end(vm_edge_vec));
			sort(begin(edge_vec), end(edge_vec), [](Edge^ e1, Edge^ e2)
			{
				return e1->Weight < e2->Weight;
			});
			auto vertice_ver = ref new Platform::Collections::Vector<Vertice^>();
			for (unsigned int i = 0; i < edge_vec->Size; i++)
			{
				auto edge = edge_vec->GetAt(i);
				if (vertice_ver->Size == vertices->Size)
				{
					edge->IsMst = false;
				}
				else
				{
					unsigned int e1, e2;
					vertice_ver->IndexOf(edge->Vertice1, &e1);
					vertice_ver->IndexOf(edge->Vertice2, &e2);
					if (e1 != 0 && e2 != 0)
					{
						edge->IsMst = false;
					}
					else
					{
						if (e1 == 0) { vertice_ver->Append(edge->Vertice1); }
						if (e2 == 0) { vertice_ver->Append(edge->Vertice2); }
						edge->IsMst = true;
					}
				}
			}
		}
		// Events
		void OnEdgeVectorChanged(IObservableVector<Edge^>^sender, IVectorChangedEventArgs ^event)
		{
			RaiseCanExecuteChanged<RelayCommand>(RemoveEdgeCommand);
			OnMst();
		}
		void OnVerticeVectorChanged(IObservableVector<Vertice^>^sender, IVectorChangedEventArgs ^event)
		{
			RaiseCanExecuteChanged<RelayCommand>(RemoveVerticeCommand);
		}
		// Command Implementations
		void OnAddVertice(Platform::Object^ parameter)
		{
			auto new_vertice = ref new Vertice(NewVerticeX, NewVerticeY, NewVerticeValue);
			vertices->Append(new_vertice);
		}
		bool CanAddEdge(Platform::Object^ parameter)
		{
			return NewEdgeVertice1 != nullptr && NewEdgeVertice2 != nullptr && NewEdgeVertice1 != NewEdgeVertice2;
		}
		void OnAddEdge(Platform::Object^ parameter)
		{
			auto new_edge = ref new Edge(NewEdgeVertice1, NewEdgeVertice2, NewEdgeWeight);
			edges->Append(new_edge);
		}
		bool CanRemoveVertice(Platform::Object^ parameter)
		{
			return VerticeToRemove != nullptr;
		}
		void OnRemoveVertice(Platform::Object^ parameter)
		{
			for (unsigned int i = 0; i < edges->Size;)
			{
				if (edges->GetAt(i)->Vertice1 == VerticeToRemove || edges->GetAt(i)->Vertice2 == VerticeToRemove)
				{
					edges->RemoveAt(i);
				}
				else
				{
					i++;
				}
			}
			unsigned int n;
			vertices->IndexOf(VerticeToRemove, &n);
			vertices->RemoveAt(n);
		}
		bool CanRemoveEdge(Platform::Object^ parameter)
		{
			return EdgeToRemove != nullptr;
		}
		void OnRemoveEdge(Platform::Object^ parameter)
		{
			RemoveEdge(EdgeToRemove);
		}
		void RemoveEdge(Edge^ edge)
		{
			unsigned int n;
			edges->IndexOf(edge, &n);
			edges->RemoveAt(n);
		}
		void OnClear(Platform::Object^ parameter)
		{
			edges->Clear();
			vertices->Clear();
		}
		void OnOpen(Platform::Object^ parameter)
		{
			using namespace Windows::Storage;
			auto picker = ref new Pickers::FileOpenPicker();
			picker->SuggestedStartLocation = Pickers::PickerLocationId::DocumentsLibrary;
			picker->FileTypeFilter->Append(".vsu");
			auto pick_task = create_task(picker->PickSingleFileAsync());
			pick_task.then([&](StorageFile^ file)
			{
				if (file != nullptr)
				{
					auto read_task = create_task(FileIO::ReadLinesAsync(file));
					read_task.then([&](IVector<Platform::String^>^ lines)
					{
						for (auto&& line : lines)
						{
							wstring wline(line->Data());
							// Add Vertices
						}
						for (auto&& line : lines)
						{
							wstring wline(line->Data());
							// Add Edges
						}
					});
				}
			});
		}
		void OnSaveAs(Platform::Object^ parameter);
		// INotifyPropertyChanged
		template <typename T> void Set(T const& field, T const& value, Platform::String^ propertyName)
		{
			if (field != value)
			{
				field = value;
				NotifyPropertyChanged(propertyName);
			}
		}
	public:
		virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;
	protected:
		virtual void NotifyPropertyChanged(Platform::String^ propertyName)
		{
			PropertyChanged(this, ref new Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
		}
	};
}
