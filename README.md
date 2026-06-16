# TCP 服务端

基于 **Qt 6** 的简易 TCP 服务端 Demo，使用 `QTcpServer` + `QTcpSocket` 实现。

## 功能

- 启动 / 关闭服务器（默认监听 `0.0.0.0:8080`）
- 接收新客户端连接，并在日志区显示客户端 IP 与端口
- 接收客户端发来的数据
- 向客户端发送自定义内容
- 清空日志显示

## 项目结构

```
TCPService/
├── CMakeLists.txt   # CMake 构建脚本
├── main.cpp         # 程序入口
├── widget.h         # 主窗口类声明
├── widget.cpp       # 主窗口实现（核心 TCP 逻辑）
└── widget.ui        # Qt Designer 界面文件
```

## 编译与运行

### 依赖

- Qt 6.5 或更高（需要 `Core` / `Widgets` / `Network` 模块）
- CMake 3.19+
- 支持 C++17 的编译器

### 构建

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 运行

构建完成后可直接运行生成的可执行文件 `TCPService`（Windows 下为 `TCPService.exe`）。

## 使用说明

1. 在「主机 IP 地址」与「端口地址」输入框中填入信息（端口目前实际固定为 `8080`）
2. 点击 **打开服务器** 按钮，状态变绿表示已启动
3. 客户端连接后，日志区会显示连接信息与收发内容
4. 在底部输入发送内容，点击 **发送数据** 即可向客户端发送
