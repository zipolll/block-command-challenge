# Block Command Challenge

一个使用 C++ 与 SFML 编写的指令编程闯关游戏。玩家需要组合有限的机器指令处理输入方块，让输出结果满足每一关的目标。

## 功能

- SFML 图形化选关界面，显示关卡的锁定与通关状态
- 四个逐步解锁的指令编程关卡
- 支持键盘输入指令，也支持从 `inputorder.txt` 按行读取
- 提供 `inbox`、`outbox`、`add`、`sub`、`copyto`、`copyfrom`、`jump` 和 `jumpifzero` 八种指令
- 执行前检查指令名称、参数、内存位置和跳转范围
- 在控制台显示输入区、输出区、临时存储区、当前指令和执行结果
- 使用本地文件记录通关进度

## 项目结构

```text
.
├── README.md
├── code
│   ├── main(OJtest).cpp          # 独立的联机评测/逻辑测试版本
│   ├── sfml/SFML-2.6.2
│   │   ├── include/              # SFML 头文件
│   │   ├── lib/                  # 项目所需的 x64 导入库
│   │   ├── bin/                  # 项目所需的 x64 运行时 DLL
│   │   └── license.md            # SFML 的 zlib/png 许可证
│   └── src
│       ├── 大作业.sln            # Visual Studio 解决方案
│       ├── 大作业.vcxproj        # C++ 项目配置
│       ├── main.cpp              # 主循环、关卡调度与进度保存
│       ├── 选关.cpp              # SFML 选关界面
│       ├── level.cpp             # 四个关卡的规则与数据
│       ├── 8function.cpp         # 八种机器指令的实现
│       ├── operation.cpp         # 指令执行与流程控制
│       ├── 静态指令检查.cpp      # 指令语法和参数检查
│       ├── input.cpp             # 键盘/文件输入
│       ├── 界面.cpp              # 控制台状态渲染
│       ├── declaration.h         # 公共声明
│       ├── inputorder.txt        # 文件输入示例
│       └── 各关通关方法.txt      # 示例解法
└── .gitignore
```

原始课程报告、提交说明、参考资料和约 2.5 GB 的演示视频没有纳入 Git 仓库；它们不参与构建，并可能包含个人信息。

## 构建与运行

### 环境

- Windows 10/11
- Visual Studio 2022 或更新版本
- 安装“使用 C++ 的桌面开发”工作负载
- x64 构建平台

### 步骤

1. 使用 Visual Studio 打开 `code/src/大作业.sln`。
2. 在工具栏选择 `Debug | x64` 或 `Release | x64`。
3. 选择“生成解决方案”，然后运行项目。

SFML 已以仓库相对路径配置，无需额外设置全局安装路径。构建完成后，项目会自动把对应的 SFML DLL 复制到可执行文件目录。

## 游玩方式

进入关卡后可以选择两种指令输入方式：

- 键盘：先输入指令总数，再逐行输入指令。
- 文件：编辑 `code/src/inputorder.txt`，每行写一条指令，不需要填写指令总数。

带参数的指令使用空格分隔，例如：

```text
inbox
copyto 0
inbox
sub 0
outbox
```

`levelpass.txt` 会在运行时生成，用于保存本机通关状态，且不会提交到 Git。

## 说明

- 当前随项目提供的是 x64 SFML 二进制，因此解决方案仅保留 x64 配置。
- SFML 以其自带的 zlib/png 许可证分发，详见 `code/sfml/SFML-2.6.2/license.md`。
- 项目自身暂未声明开源许可证。
