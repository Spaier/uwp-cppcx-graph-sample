# Graph C++/CX UWP Application

## Tips

Always check field's value in setter to prevent stack overflow.

```cpp
	if (value != newEdgeVertice1) {
		newEdgeVertice1 = value;
		NotifyPropertyChanged(L"NewEdgeVertice1");
		RaiseCanExecuteChanged<RelayCommand>(AddEdgeCommand);
	}
```

`DisplayMemberPath` doesn't work with `x:Bind` or `Binding`.
Use `ItemTemplate` instead.