#pragma once

namespace VsuCpp4::Mvvm
{
	public delegate void ExecuteDelegate(Platform::Object^ parameter);
	public delegate bool CanExecuteDelegate(Platform::Object^ parameter);

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class RelayCommand sealed : public Windows::UI::Xaml::Input::ICommand
	{
	public:
		virtual event Windows::Foundation::EventHandler<Platform::Object^>^ CanExecuteChanged;

		RelayCommand();
		RelayCommand(ExecuteDelegate^ execute, CanExecuteDelegate^ canExecute);

		virtual void Execute(Platform::Object^ parameter);
		virtual bool CanExecute(Platform::Object^ parameter);
		void RaiseCanExecuteChanged();
	private:
		ExecuteDelegate^ executeDelegate;
		CanExecuteDelegate^ canExecuteDelegate;
	};
}
