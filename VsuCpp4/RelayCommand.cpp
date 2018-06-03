#include "pch.h"
#include "RelayCommand.h"

using namespace VsuCpp4::Mvvm;

RelayCommand::RelayCommand() { }

RelayCommand::RelayCommand(ExecuteDelegate^ execute, CanExecuteDelegate^ canExecute)
	: executeDelegate(execute), canExecuteDelegate(canExecute) { }

void VsuCpp4::Mvvm::RelayCommand::Execute(Platform::Object ^ parameter)
{
	assert(executeDelegate != nullptr);
	if (nullptr != executeDelegate) {
		executeDelegate(parameter);
	}
}

bool VsuCpp4::Mvvm::RelayCommand::CanExecute(Platform::Object ^ parameter)
{
	return canExecuteDelegate == nullptr ? true : canExecuteDelegate(parameter);
}

void VsuCpp4::Mvvm::RelayCommand::RaiseCanExecuteChanged()
{
	CanExecuteChanged(this, nullptr);
}
