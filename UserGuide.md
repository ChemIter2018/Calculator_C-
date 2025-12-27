# 项目结构与编译指南

## 1. 项目文件结构 (Tree Structure)

```text
Calculator_C#/
├── UserGuide.md             # 用户指南与编译发布说明
└── src/
    ├── Calculator.Core/      # C++ 核心逻辑层 (后端)
    │   ├── CMakeLists.txt     # CMake 编译配置文件，定义如何生成动态库
    │   ├── CalculatorCore.cpp  # 计算逻辑的具体 C++ 实现
    │   ├── CalculatorCore.h    # C++ 接口定义，用于与 C# 通信
    │   └── build/             # C++ 编译生成目录，包含生成的 .dylib 库
    └── Calculator.UI/        # Avalonia C# UI 层 (前端界面)
        ├── App.axaml          # 全局应用定义、资源和样式
        ├── Program.cs         # 程序的启动入口
        ├── Calculator.UI.csproj # C# 项目工程文件，管理依赖和编译选项
        ├── Models/            # 数据模型类
        ├── ViewModels/        # 业务逻辑处理 (MVVM 模式)
        ├── Views/             # UI 布局文件 (.axaml)，定义界面样子
        ├── ViewLocator.cs     # 视图定位器，用于将 ViewModel 自动匹配并映射到对应的 View
        ├── NativeMethods.cs   # 核心桥接文件，通过 P/Invoke (DllImport) 调用 C++ 动态库
        ├── Assets/            # 静态资源文件 (如图标)
        └── app.manifest       # 应用清单文件 (Windows 兼容性等配置)
```

---

## 2. 编译发布命令
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