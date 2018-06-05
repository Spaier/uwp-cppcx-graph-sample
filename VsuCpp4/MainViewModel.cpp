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
	SaveAsCommand = ref new RelayCommand(
		ref new ExecuteDelegate(this, &MainViewModel::OnSaveAs),
		nullptr
	);
}

void MainViewModel::OnSaveAs(Platform::Object^ parameter)
{
	using namespace Windows::Storage;
	auto picker = ref new Pickers::FileSavePicker();
	auto extensions = ref new Platform::Collections::Vector<Platform::String^>();
	extensions->Append(".vsu");
	picker->SuggestedStartLocation = Pickers::PickerLocationId::DocumentsLibrary;
	picker->SuggestedFileName = "graph";
	picker->FileTypeChoices->Insert("App File", extensions);
	auto pick_task = create_task(picker->PickSaveFileAsync());
	pick_task.then([&](StorageFile^ file)
	{
		if (file != nullptr)
		{
			Windows::Storage::CachedFileManager::DeferUpdates(file);
			wstringstream stream;
			for (auto&& vertice : vertices)
			{
				stream << wstring(vertice->Value->Data()) << " " << vertice->X << " " << vertice->Y;
				for (auto&& edge : edges)
				{
					if (edge->Vertice1 == vertice)
					{
						stream << " " << edge->Vertice2->Value->Data() << " " << edge->Vertice2->X << " " << edge->Vertice2->Y;
					}
				}
				stream << endl;
			}
			Platform::String^ text = ref new Platform::String(stream.str().c_str());
			auto write_task = create_task(Windows::Storage::FileIO::WriteTextAsync(file, text));
			write_task.wait();
			auto update_task = create_task(Windows::Storage::CachedFileManager::CompleteUpdatesAsync(file));
			update_task.wait();
		}
	});
}