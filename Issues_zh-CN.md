# 已知问题
> 🇨🇳 简体中文版。英文原版见 [Issues.md](Issues.md)。

## 游戏内菜单

如果打不开游戏内菜单:
1. 请确认你已在游戏选项中启用了 DLSS、XeSS 或 FSR
2. 如果使用传统安装方式, 请尝试在游戏进行中 (3D 渲染运行时) 打开菜单
3. 如果在使用 RTSS (MSI Afterburner、CapFrameX), 请启用 RTSS 的这个设置并尝试更新 RTSS。
  ![image](https://github.com/optiscaler/OptiScaler/assets/35529761/8afb24ac-662a-40ae-a97c-837369e03fc7)

* 某些游戏不释放鼠标控制权, 键盘和游戏柄控制在这些情况下仍然有效。
* 在某些系统和游戏的组合下, 打开旧版游戏内菜单可能导致游戏崩溃或画面损坏 (尤其在 Unreal Engine 5 游戏中)。

![Banishers](/images/banishers.png)<br>*《Banishers: 新伊甸之灵》*

* 更改设置大多经过测试, 但仍可能导致崩溃 (尤其是切换后端或重新初始化后端时)。
* 在使用 Unity Engine 的游戏中, 旧版游戏内菜单会上下颠倒。

![barrel roll](/images/upsidedown.png)<br>*《森林之子》*

## DirectX 11 搭配 DirectX 12 放大算法
此实现使用一个后台 DirectX12 设备来调用仅限 DirectX12 的放大算法。该方法有 10%-15% 的性能损耗, 但提供更多放大算法选择。

## 曝光纹理
有时游戏的曝光纹理格式无法被放大算法识别。大多数情况下表现为颜色被压缩 (暗部尤为明显)。

![exposure](/images/exposure.png)<br>*《古墓丽影: 暗影》*

大多数情况下, 在 `OptiScaler.ini` 中启用 `AutoExposure=true`, 或在游戏内菜单的 `Init Parameters` 中选择 `Auto Exposure` 应可修复此问题。

## 资源屏障
Unreal Engine 的 DLSS 插件以错误的状态发送 DLSS 资源是已知问题。通常 OptiScaler 会从 NVSDK 读取引擎信息, 自动为 Unreal Engine 游戏启用必要的修复, 但有些游戏不能正确上报引擎信息。此问题通常表现为屏幕底部的彩色区域。

![christmas lights](/images/christmas.png)<br>*《深岩银河》*

解决方法: 在 `OptiScaler.ini` 中设置 `ColorResourceBarrier=4`, 或在游戏内菜单的 `Resource Barriers (Dx12)` 中将 `Color` 选为 `RENDER_TARGET`。

## XeSS 黑屏/花屏或崩溃
有用户反馈使用 XeSS 放大算法后端时, 结果是带 UI 的黑屏/花屏或崩溃 (例如《银河护卫队》)。某些情况下, 下载最新版 [DirectX Shader Compiler](https://github.com/microsoft/DirectXShaderCompiler/releases) 并把 `bin\x64\` 中的 `dxcompiler.dll`、`dxil.dll` 放到游戏 exe 旁边解决了此问题。

## Minecraft RTX
XeSS 1.1 与 Minecraft RTX 的兼容性最好。但也有反馈显示通过[各种启动器](https://github.com/MCMrARM/mc-w10-version-launcher/releases) 也可以使用 1.2 及以上版本。

## Linux 上的着色器编译错误
如果你在 Linux 上使用 OptiScaler, 且 `RCAS`、`Reactive Mask Bias` 或 `Output Scaling` 有问题, 日志中大概率会出现这条消息:
```
CompileShader error compiling shader : <anonymous>:83:26: E5005: Function "rcp" is not defined.
```
解决方法: 使用菜单中的 `Precompiled Shaders` (预编译着色器) 选项, 或用 `WineTricks`/`ProtonTricks` 安装 `d3dcompiler_47`。OptiScaler 的这些功能使用自定义着色器, 依赖该编译器文件在运行时编译着色器。

## 性能问题
* 总体上 XeSS 对 GPU 的负担比 FSR 大, 因此在 Intel Arc 显卡上性能也偏低属于正常现象。
* 由于伪装 Nvidia 显卡以启用 DLSS, 某些游戏会走 Nvidia 优化的代码路径, 这可能使其他 GPU 的性能下降。

## 显示分辨率运动向量
有时游戏会错误地设置 `DisplayResolution` 初始化标志, 导致运动模糊过重。设置或重置 `DisplayResolution` 有助于解决此问题。

![mv wrong](/images/mv_wrong.png)<br>*《深岩银河》*

## 画面损坏和崩溃
如上所述, 伪装 Nvidia 显卡可能使游戏走特殊代码路径, 从而引起画面损坏。可能的情况下请禁用伪装, 在这些情况下改用 FSR 或 XeSS 输入。

![talos principle 2](/images/talos.png)<br>*《塔罗斯的法则 2》*

* 以及崩溃问题, 尤其在启用光线追踪时。
