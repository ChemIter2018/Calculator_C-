``` bash
dotnet publish -c Release -r osx-arm64 --self-contained true -p:PublishSingleFile=true
chmod +x bin/Release/net10.0/osx-arm64/publish/Calculator.UI
```

如果你使用了我之前建议的 dotnet publish 命令，你只需要拷贝 publish 目录下的所有内容。

具体取决于你执行的命令：

1. 如果你使用了“单文件”发布命令：
如果你运行的是： dotnet publish -c Release -r osx-arm64 --self-contained true -p:PublishSingleFile=true

你只需要拷贝以下文件：

Calculator.UI (这是主执行程序，它已经包含了 .NET 运行时和大部分 DLL)
CalculatorCore.dylib (这是你的 C++ 核心库，通常 .NET 不会自动将其压缩进单文件，它会放置在可执行程序旁边)
2. 如果你使用了“非单文件”发布（普通发布）：
如果你运行的是： dotnet publish -c Release -r osx-arm64 --self-contained true

你需要拷贝 publish/ 文件夹内的全部内容。这里面会包含：

Calculator.UI (启动器)
大量的 System.*.dll 和 Avalonia.*.dll
CalculatorCore.dylib
libhostfxr.dylib 等运行时库