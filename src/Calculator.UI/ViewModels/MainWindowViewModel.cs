using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using System;

namespace Calculator.UI.ViewModels;

public partial class MainWindowViewModel : ViewModelBase
{
    [ObservableProperty]
    private string _displayText = "";

    [ObservableProperty]
    private string _resultText = "0";

    [RelayCommand]
    private void AddCharacter(string character)
    {
        DisplayText += character;
    }

    [RelayCommand]
    private void Clear()
    {
        DisplayText = "";
        ResultText = "0";
    }

    [RelayCommand]
    private void Backspace()
    {
        if (DisplayText.Length > 0)
        {
            DisplayText = DisplayText.Substring(0, DisplayText.Length - 1);
        }
    }

    [RelayCommand]
    private void ExecuteCalculate()
    {
        if (string.IsNullOrWhiteSpace(DisplayText)) return;

        try
        {
            int errorCode;
            double result = NativeMethods.calculate(DisplayText, out errorCode);
            if (errorCode == 0)
            {
                ResultText = result.ToString();
            }
            else
            {
                ResultText = "Error";
            }
        }
        catch (Exception ex)
        {
            ResultText = "Error";
        }
    }
}