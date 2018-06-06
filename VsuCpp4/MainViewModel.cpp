#include "pch.h"
#include "MainViewModel.h"

using namespace Platform;
using namespace Platform::Collections;
using namespace VsuCpp4;
using namespace VsuCpp4::Mvvm;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace std;
using namespace concurrency;

// Constructors

MainViewModel::MainViewModel()
{
	auto edges_vector = ref new Vector<Edge^>();
	edges_vector->VectorChanged += ref new VectorChangedEventHandler<Edge^>(this, &MainViewModel::OnEdgeVectorChanged);
	edges = edges_vector;
	auto vertices_vector = ref new Vector<Vertice^>();
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
	SaveAsCommand = ref new RelayCommand(
		ref new ExecuteDelegate(this, &MainViewModel::OnSaveAs),
		nullptr
	);
	max_vertice_id = 0;
}

task<void> MainViewModel::SaveGraphAsync()
{
	auto picker = ref new FileSavePicker();
	auto extensions = ref new Vector<String^>();
	extensions->Append(".vsu");
	picker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;
	picker->SuggestedFileName = "graph";
	picker->FileTypeChoices->Insert("App File", extensions);
	auto file = co_await picker->PickSaveFileAsync();
	if (file == nullptr) return;
	CachedFileManager::DeferUpdates(file);
	wstringstream stream;
	for (auto&& vertice : vertices)
	{
		stream << vertice->Id << wstring(vertice->Value->Data()) << " " << vertice->X << " " << vertice->Y;
		for (auto&& edge : edges)
		{
			if (edge->Vertice1 == vertice)
			{
				stream << " " << edge->Vertice2->Id;
			}
		}
		stream << endl;
	}
	String^ text = ref new String(stream.str().c_str());
	co_await FileIO::WriteTextAsync(file, text);
	auto update_status = co_await CachedFileManager::CompleteUpdatesAsync(file);
}

task<void> MainViewModel::LoadGraphAsync()
{
	auto picker = ref new FileOpenPicker();
	picker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;
	picker->FileTypeFilter->Append(".vsu");
	auto file = co_await picker->PickSingleFileAsync();
	if (file == nullptr) return;
	auto lines = co_await FileIO::ReadLinesAsync(file);
	for (auto&& line : lines)
	{
		wstringstream stream(line->Data());
		unsigned long long vertice_id;
		wstring vertice_value;
		double vertice_x;
		double vertice_y;
		stream >> vertice_id >> vertice_value >> vertice_x >> vertice_y;
		auto vertice = ref new Vertice(vertice_x, vertice_y, ref new String(vertice_value.c_str()), vertice_id);
	}
}