using System.Runtime.InteropServices;

namespace Calculator.UI;

public static partial class NativeMethods
{
    private const string LibName = "CalculatorCore";

    [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern double add(double a, double b);

    [DllImport(LibName, CallingConvention = CallingConvention.Cdecl)]
    public static extern double calculate([MarshalAs(UnmanagedType.LPStr)] string expression, out int errorCode);
}
