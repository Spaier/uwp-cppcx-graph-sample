#include "pch.h"
#include "MainViewModel.h"

using namespace VsuCpp4;
using namespace VsuCpp4::Mvvm;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace std;

// Constructors

MainViewModel::MainViewModel()
{
	auto edges_vector = ref new Platform::Collections::Vector<Edge^>();
	edges_vector->VectorChanged += ref new VectorChangedEventHandler<Edge^>(this, &MainViewModel::OnEdgeVectorChanged);
	edges = edges_vector;
	auto vertices_vector = ref new Platform::Collections::Vector<Vertice^>();
	vertices_vector->VectorChanged += ref new VectorChangedEventHandler<Vertice^>(this, &MainViewModel::OnVerticeVectorChanged);
	vertices = vertices_vector;
	AddVerticeCommand = ref new RelayCommand(
		ref new ExecuteDelegate(this, &MainViewModel::OnAddVertice),
		nullptr
	);
	AddEdgeCommand = ref new RelayCommand(
		ref new ExecuteDelegate(this, &MainViewModel::OnAddEdge),
		ref new CanExecuteDelegate(this, &MainViewModel::CanAddEdge)
	);
	RemoveVerticeCommand = ref new RelayCommand(
		ref new ExecuteDelegate(this, &MainViewModel::OnRemoveVertice),
		ref new CanExecuteDelegate(this, &MainViewModel::CanRemoveVertice)
	);
	RemoveEdgeCommand = ref new RelayCommand(
		ref new ExecuteDelegate(this, &MainViewModel::OnRemoveEdge),
		ref new CanExecuteDelegate(this, &MainViewModel::CanRemoveEdge)
	);
	ClearCommand = ref new RelayCommand(
		ref new ExecuteDelegate(this, &MainViewModel::OnClear),
		nullptr
	);
	OpenCommand = ref new RelayCommand(
		ref new ExecuteDelegate(this, &MainViewModel::OnOpen),
		nullptr
	);
	SaveCommand = ref new RelayCommand(
		ref new ExecuteDelegate(this, &MainViewModel::OnSave),
		ref new CanExecuteDelegate(this, &MainViewModel::CanSave)
	);
	SaveAsCommand = ref new RelayCommand(
		ref new ExecuteDelegate(this, &MainViewModel::OnSaveAs),
		nullptr
	);
}
