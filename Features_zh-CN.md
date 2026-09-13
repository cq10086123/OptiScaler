## 特性 (Features)
> 🇨🇳 简体中文版。英文原版见 [Features.md](Features.md)。

* 支持多种放大算法后端 (XeSS、FSR 2.1.2、FSR 2.2.1、FSR 3.1 和 DLSS)
* v0.7.0 及以上版本提供实验性帧生成支持 (基于 FSR 的 OptiFG)
* 支持 DLSS 3.7 及以上 (查看[安装说明](#install-as-non-nvngx))
* Nvidia 显卡上支持 DLSS-D (光追重建), 支持修改预设并使用 OptiScaler 增强功能
* 可以即时修改 DLSS/DLSS-D 预设
* 支持 XeSS v1.3.x 的 Ultra Performance 和 NativeAA 模式 (**不使用 XeSS 1.3.x 默认的缩放比例, 而是旧的比例**)
* [游戏内菜单](https://github.com/optiscaler/OptiScaler/blob/master/Config.md), 可即时调校和保存设置 (快捷键为 **INSERT**)
* 与 [DLSS Enabler](https://www.nexusmods.com/site/mods/757) 完全集成, 支持 DLSS-FG
* **RCAS** 锐化, 配合 **MAS** (运动自适应锐化), 适用于所有 Dx12 和 Dx11 放大算法
* Dx12 和 Dx11 后端的 **输出缩放 (Output Scaling)** 选项 (0.5x 到 3.0x)
* 支持 DXGI 伪装 (以 `dxgi.dll` 方式运行时) 伪装成 Nvidia 显卡 (带 XeSS 检测, 可在 Intel Arc 显卡上启用 XMX)
* 支持 Vulkan 伪装 (需要在 `nvngi.ini` 中启用) 伪装成 Nvidia 显卡 (《毁灭战士: 永恒》上无效)
* 支持加载指定的 `nvapi64.dll` 文件 (以非 nvngx 模式运行时)
* 支持加载指定的 `nvngx_dlss.dll` 文件 (以非 nvngx 模式运行时)
* 支持覆盖缩放比例
* 支持覆盖 DRS 范围
* 自动修复 Unreal Engine + AMD 显卡的[彩色灯光](https://github.com/optiscaler/OptiScaler/blob/master/Config.md#resource-barriers-dx12-only)问题
* 自动修复[缺失曝光纹理](https://github.com/optiscaler/OptiScaler/blob/master/Config.md#init-flags)信息的问题
* 可以修改游戏的 [Mipmap LOD Bias](https://github.com/optiscaler/OptiScaler/blob/master/Config.md#mipmap-lod-bias-override-dx12-only) 值
* 支持 [Fakenvapi](https://github.com/FakeMichau/fakenvapi) 集成, 可 hook Reflex 并注入 Anti-Lag 2 或 LatencyFlex (LFX)
* 支持 Nukem 的 FSR FG mod [dlssg-to-fsr3](https://github.com/Nukem9/dlssg-to-fsr3) (v0.7.7 起)

**为了绕过 DLSS 3.7 的签名检查要求, OptiScaler 使用了 [DLSS Enabler](https://www.nexusmods.com/site/mods/757?tab=description) 作者 **Artur** 开发的方法。**
