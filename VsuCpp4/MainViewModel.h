#pragma once

#include "Edge.h"
#include "Vertice.h"
#include "RelayCommand.h"

namespace VsuCpp4
{
	using namespace Windows::Foundation::Collections;
	using namespace Windows::UI::Xaml::Input;
	using namespace VsuCpp4::Mvvm;
	using namespace Platform;
	using namespace Platform::Collections;
	using namespace concurrency;
	using namespace std;

	template <typename T> static void RaiseCanExecuteChanged(ICommand^ instance)
	{
		auto command = dynamic_cast<T^>(instance);
		command->RaiseCanExecuteChanged();
	}

	public ref class EdgeInfo sealed
	{
	public:
		EdgeInfo() { }
		EdgeInfo(unsigned long long id, double weight)
		{
			Id = id;
			Weight = weight;
		}
		property unsigned long long Id;
		property double Weight;
	};

	[Windows::UI::Xaml::Data::Bindable]
	public ref class MainViewModel sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
	{
	private:
		// Fields
		unsigned long long max_vertice_id;
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
			auto vm_edge_vec = dynamic_cast<Vector<Edge^>^>(edges);
			vector<Edge^> edge_vec(begin(vm_edge_vec), end(vm_edge_vec));
			sort(begin(edge_vec), end(edge_vec), [](Edge^ e1, Edge^ e2)
			{
				return e1->Weight < e2->Weight;
			});
			vector<Vertice^> vertice_ver;
			for (auto& edge : edge_vec)
			{
				if (vertice_ver.size() == vertices->Size)
				{
					edge->IsMst = false;
				}
				else
				{
					auto is_v1_missing = find(begin(vertice_ver), end(vertice_ver), edge->Vertice1) == end(vertice_ver);
					auto is_v2_missing = find(begin(vertice_ver), end(vertice_ver), edge->Vertice2) == end(vertice_ver);
					if (!is_v1_missing && !is_v2_missing)
					{
						edge->IsMst = false;
					}
					else
					{
						if (is_v1_missing) { vertice_ver.push_back(edge->Vertice1); }
						if (is_v2_missing) { vertice_ver.push_back(edge->Vertice2); }
						edge->IsMst = true;
					}
				}
			}
			Edges->Clear();
			for (auto& item : edge_vec)
			{
				Edges->Append(item);
			}
		}
		// Events
		void OnEdgeVectorChanged(IObservableVector<Edge^>^sender, IVectorChangedEventArgs ^event)
		{
			RaiseCanExecuteChanged<RelayCommand>(RemoveEdgeCommand);
		}
		void OnVerticeVectorChanged(IObservableVector<Vertice^>^sender, IVectorChangedEventArgs ^event)
		{
			RaiseCanExecuteChanged<RelayCommand>(RemoveVerticeCommand);
		}
		// Command Implementations
		void OnAddVertice(Object^ parameter)
		{
			auto new_vertice = ref new Vertice(NewVerticeX, NewVerticeY, NewVerticeValue, max_vertice_id++);
			vertices->Append(new_vertice);
		}
		bool CanAddEdge(Object^ parameter)
		{
			return NewEdgeVertice1 != nullptr && NewEdgeVertice2 != nullptr && NewEdgeVertice1 != NewEdgeVertice2;
		}
		void OnAddEdge(Object^ parameter)
		{
			auto new_edge = ref new Edge(NewEdgeVertice1, NewEdgeVertice2, NewEdgeWeight);
			edges->Append(new_edge);
			OnMst();
		}
		bool CanRemoveVertice(Object^ parameter)
		{
			return VerticeToRemove != nullptr;
		}
		void OnRemoveVertice(Object^ parameter)
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
			OnMst();
		}
		bool CanRemoveEdge(Object^ parameter)
		{
			return EdgeToRemove != nullptr;
		}
		void OnRemoveEdge(Object^ parameter)
		{
			RemoveEdge(EdgeToRemove);
		}
		void RemoveEdge(Edge^ edge)
		{
			unsigned int n;
			edges->IndexOf(edge, &n);
			edges->RemoveAt(n);
			OnMst();
		}
		void OnClear(Object^ parameter)
		{
			Clear();
		}
		void Clear()
		{
			edges->Clear();
			vertices->Clear();
			max_vertice_id = 0;
		}
		void OnOpen(Object^ parameter)
		{
			create_task(LoadGraphAsync());
		}
		void OnSaveAs(Object^ parameter)
		{
			create_task(SaveGraphAsync());
		}
		task<void> SaveGraphAsync();
		task<void> LoadGraphAsync();
		// INotifyPropertyChanged
		template <typename T> void Set(T const& field, T const& value, String^ propertyName)
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
		virtual void NotifyPropertyChanged(String^ propertyName)
		{
			PropertyChanged(this, ref new Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
		}
	};
}
