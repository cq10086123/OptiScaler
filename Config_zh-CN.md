# 配置说明
本文档尽可能详细地解释 `OptiScaler.ini` 和 游戏内菜单 (打开菜单的快捷键是 **INSERT**) 中的设置。

![in-game menu](images/menu043.png)

> 🇨🇳 简体中文版。英文原版见 [Config.md](Config.md)。

### Upscalers (放大算法)
OptiScaler 支持 DirectX 11、DirectX 12 和 Vulkan API, 提供多种放大算法后端。可以在 `OptiScaler.ini` 文件的 `[Upscalers]` 部分选择使用哪个放大算法。

```ini
[Upscalers]
; Select upscaler for Dx11 games
; fsr22 (native dx11), xess (with dx12), fsr21_12 (dx11 with dx12) or fsr22_12 (dx11 with dx12)
; Default (auto) is fsr22
Dx11Upscaler=auto

; Select upscaler for Dx12 games
; xess, fsr21 or fsr22
; Default (auto) is xess
Dx12Upscaler=auto

; Select upscaler for Vulkan games
; fsr21 or fsr22
; Default (auto) is fsr21
VulkanUpscaler=auto
```

* `fsr21` 表示 FSR 2.1.2
* `fsr22` 表示 FSR 2.2.1
* `xess` 表示 XeSS

*对于 DirectX11, `fsr21_12`、`fsr22_12` 和 `xess` 会使用一个 DirectX12 后台设备来调用仅限 DirectX12 的放大算法。此方法有 10%-15% 的性能损耗, 但提供更多放大算法选择。另外, FSR 2.2.1 的原生 DirectX11 实现是从 Unity 渲染器回移的, 自身有一些问题, 其中部分已被 OptiScaler 规避。*

也可以在游戏内菜单的 `Upscalers` (放大算法) 部分选择放大算法。

![upscalers](images/Upscalers.png)

### Pseudo SuperSampling (伪超级采样)
从 OptiScaler 0.4 开始, `[Upscalers]` 部分新增了伪超级采样选项。

```ini
[Upscalers]
; Enable pseudo-supersampling option for Dx12 and Dx11 with Dx12 backends
; true or false - Default (auto) is false
SuperSamplingEnabled=auto

; Pseudo-supersampling ratio
; 0.0 - 5.0 - Default (auto) is 2.5
SuperSamplingMultiplier=auto
```

解释一下: 通常当你的游戏以 1080p 运行且 DLSS 预设选择 `Quality` (质量) 时, 会渲染一张 720p 图像, 连同其他必要的输入信息一起发送给放大算法, 输出 1080p 图像。

启用伪超级采样后, 会用 `SuperSamplingMultiplier` 计算放大算法的目标渲染尺寸。对于 720p, 默认倍数 (2.5) 下就是 1800p。于是放大算法会把图像放大到 1800p 而不是 1080p, 然后 OptiScaler 再把输出图像降采样到 1080p。

![pseudo superSampling](images/pss.png)

由于放大目标分辨率更高, 相比直接放大会有性能损失。但主观上它能在较高性能水平下产生接近 DLAA 质量的图像。

可以在游戏内菜单中修改, 效果实时可见。

![pss config](images/pss_config.png)

### Dx11withDx12 Sync Settings (Dx11wDx12 同步设置)
对于 DirectX11 的 `fsr21_12`、`fsr22_12` 和 `xess` 放大算法选项, OptiScaler 使用一个 DirectX12 后台设备来调用这些仅限 DirectX12 的放大算法。这是一个非常小众的功能, 在不稳定的 GPU 驱动上 (尤其是 Intel) 可能引起问题。为缓解并防止崩溃或画面问题, 可以使用这些选项。

```ini
[Dx11withDx12]
; Syncing methods for Dx11 with Dx12
;
; Valid values are;
;	0 - No syncing                                  (fastest, most prone to errors)
;	1 - Fence
;	2 - Fences + Flush
;	3 - Fences + Event
;	4 - Fences + Flush + Event
;	5 - Query Only

; Default (auto) is 1
TextureSyncMethod=auto

; Default (auto) is 5
CopyBackSyncMethod=auto

; Start output copy back sync after or before Dx12 execution
; true or false - Default (auto) is true
SyncAfterDx12=auto

; Delay some operations during creation of D11wDx12 features to increase compatibility
; true or false - Default (auto) is false
UseDelayedInit=auto
```

下图展示了 Dx11wDx12 放大流程。黄色圆圈是同步点 (或可能的同步点)。`SyncAfterDx12` 决定第二次同步发生的时间。

![dx11 with dx12 flow](images/Dx11wDx12.png)

`No syncing` (不同步) : 顾名思义
`Fence` : 使用共享 `Fence` (信号 & 等待) 同步。这些操作发生在 GPU 上, 相当快。
`Fence + Event` : 使用共享 `Fence` (信号 & 事件) 同步。`Event` 在 CPU 上等待, 更慢。
`Flush` : 信号共享 `Fence` 之后, 对 Dx11 DeviceContext 执行 `Flush`。
`Query Only` : 使用 Dx11 `Query` 同步, 一般比 `Event` 快, 但比 `Fence` 慢。

使用 `Event` 同步输出时, `SyncAfterDx12=false` 通常性能更好。

**这些设置与游戏和硬件相关。默认值兼顾性能与画面稳定, 追求高性能时可能需要针对每个游戏调整。**

可以在游戏内菜单中修改, 效果实时可见 (`UseDelayedInit` 除外)。

![dx11 sync setings](images/dx11wdx12menu.png)

### XeSS Settings (XeSS 设置)

```ini
[XeSS]
; Building pipeline for XeSS before init
; true or false - Default (auto) is true
BuildPipelines=auto

;Select XeSS network model
; 0 = KPSS
; 1 = Splat
; 2 = Model 3
; 3 = Model 4
; 4 = Model 5
; 5 = Model 6
;
; Default (auto) is 0
NetworkModel=auto

[CAS]
; Enables CAS sharpening for XeSS
; true or false - Default (auto) is false
Enabled=auto

; Color space conversion for input and output
; Possible values are at the end of the file - Default (auto) is 0
ColorSpaceConversion=auto
```

`BuildPipelines` 参数允许在创建上下文时预先构建 XeSS 管线, 以避免之后的卡顿。

`NetworkModel` 用于选择 XeSS 放大使用的网络模型。**(目前对放大后的图像没有可见效果)**

#### CAS
XeSS 的最终图像相比其他放大算法通常偏软, 且没有锐化选项可以弥补。因此 OptiScaler 允许你对最终图像使用 AMD 的 CAS 锐化滤镜, 以平衡放大图像的偏软观感。不过 CAS 并不完美, 在某些游戏中会引起一些问题, 如辉光 (bloom) 效果消失、画面色调偏移, 甚至黑屏无画面。

![cas](images/cas.png)

1. 辉光被移除
2. 色调改变

`ColorSpaceConversion` 用于修复色彩空间转换问题, 但**绝大多数**情况下默认设置都能正常工作。

可以在游戏内菜单中修改, 效果实时可见。

![xess](images/xess.png)

`Dump` 选项用于调试, 会把 XeSS 的输入输出参数和纹理转储到游戏文件夹。

### FSR Settings (FSR 设置)

```ini
[FSR]
; 0.0 to 180.0 - Default (auto) is 60.0
VerticalFov=auto

; If vertical fov is not defined will be used to calculate vertical fov
; 0.0 to 180.0 - Default (auto) is off
HorizontalFov=auto
```

为了改善画质, 可以用这些设置把游戏实际的垂直或水平 FOV 匹配出来。默认是 60° 垂直 FOV, 大多数情况下工作正常。

可以在游戏内菜单中修改, 效果实时可见。

![fsr](images/fsr.png)

### Sharpness (锐度)
DLSS 曾经有锐化选项, 后来被移除了。因此有些游戏有锐度滑块, 有些没有。通过此选项可以禁用或启用最终图像的锐化。FSR 自带锐化, 而 XeSS 需要启用 CAS 选项。

```ini
[Sharpness]
; Override DLSS sharpness paramater with fixed shapness value
; true or false - Default (auto) is false
OverrideSharpness=auto

; Strength of sharpening,
; value range between 0.0 and 1.0 - Default (auto) is 0.3
Sharpness=auto
```

可以在游戏内菜单中修改, 效果实时可见。

![sharpness](images/sharpness.png)

### Upscaling Ratios (放大比例)
OptiScaler 提供了多个覆盖和锁定放大比例的选项。

#### Upscale Ratio Override (放大比例覆盖)
`UpscaleRatioOverride` 允许为所有画质预设选择同一个放大比例。

```ini
[UpscaleRatio]
; Set this to true to enable the internal resolution override
; true or false - Default (auto) is false
UpscaleRatioOverrideEnabled=auto

; Set this to true to enable limiting DRS max resolution to overriden ratio
; true or false - Default (auto) is false
DrsMaxOverrideEnabled=auto

; Set the forced upscale ratio value
; Default (auto) is 1.3
UpscaleRatioOverrideValue=auto
```

可以在游戏内菜单中修改并保存, 但通常要重启或改变分辨率后才会生效。

![us ratio](images/us_ratio.png)

#### Quality Ratio Override (画质比例覆盖)
`QualityRatioOverride` 允许为每个画质预设覆盖放大比例。

```ini
[QualityOverrides]
; Set this to true to enable custom quality mode overrides
; true or false - Default (auto) is false
QualityRatioOverrideEnabled=auto

; Set custom upscaling ratio for each quality mode
;
; Default (auto) values:
; Ultra Quality         : 1.3
; Quality               : 1.5
; Balanced              : 1.7
; Performance           : 2.0
; Ultra Performance     : 3.0
QualityRatioUltraQuality=auto
QualityRatioQuality=auto
QualityRatioBalanced=auto
QualityRatioPerformance=auto
QualityRatioUltraPerformance=auto
```

**如果两种覆盖都启用, `UpscaleRatioOverride` 优先于 `QualityRatioOverride`。**

启用 `DrsMaxOverrideEnabled` 后, 对支持 DRS 的游戏, 最高内部渲染分辨率会被限制为默认渲染分辨率而不是显示分辨率。启用后实际上等效于禁用 DRS。可与 `QualityRatioOverride` 和 `UpscaleRatioOverride` 同时使用。

这些可以在游戏内菜单中修改并保存, 但通常要重启或改变分辨率后才会生效。

![quality ratio](images/q_ratio.png)

### Init Flags (初始化标志)
这些设置允许覆盖 DLSS 初始化标志以修复一些问题。

```ini
[Depth]
; Force add INVERTED_DEPTH to init flags
; true or false - Default (auto) is DLSS value
DepthInverted=auto

[Color]
; Force add ENABLE_AUTOEXPOSURE to init flags
; Some Unreal Engine games needs this, fixes colors specially in dark areas
; true or false - Default (auto) is  DLSS value
AutoExposure=auto

; Force add HDR_INPUT_COLOR to init flags
; true or false - Default (auto) is  DLSS value
HDR=auto

[MotionVectors]
; Force add JITTERED_MV flag to init flags
; true or false - Default (auto) is  DLSS value
JitterCancellation=auto

; Force add HIGH_RES_MV flag to init flags
; true or false - Default (auto) is  DLSS value
DisplayResolution=auto

[Hotfix]
; Force remove RESPONSIVE_PIXEL_MASK from init flags
; true or false - Default (auto) is true
DisableReactiveMask=auto
```

启用 `AutoExposure` 有助于修复颜色过暗或发白的问题。

![exposure](/images/exposure.png)

有反馈称启用 `HDR` 有助于解决某些游戏中的紫色偏色。

启用 `DisableReactiveMask` 可以在某些游戏中帮助 FSR 后端, 但通常它引发的问题比解决的更多, 因此默认禁用。

某些游戏可能错误地设置运动向量尺寸标志, 导致镜头移动时运动模糊过重。在这些情况下, 启用或禁用 `DisplayResolution` 可能有帮助。

![wrong mv flag](/images/mv_wrong.png)

这些可以在游戏内菜单中修改, 效果实时可见。

![init flags](images/init_flags.png)

### Resource Barriers (资源屏障, 仅 Dx12)
某些游戏 (尤其是 Unreal Engine) 会以错误的状态把输入资源发送给 DLSS, 导致画面问题 (尤其在 AMD 硬件上)。通常 OptiScaler 会尝试检测引擎类型来缓解这些问题, 但有时游戏不会正确上报这些信息。要修复这些问题, 以下 ini 参数会派上用场。

![early christmas](images/christmas.png)

**在这里设置错误的资源状态可能导致崩溃!**

```ini
[Hotfix]
; Color texture resource state to fix for rainbow colors on AMD cards (for mostly UE games)
; For UE engine games on AMD, set it to D3D12_RESOURCE_STATE_RENDER_TARGET (4)
; Default (auto) is state correction disabled
ColorResourceBarrier=auto

; MotionVector texture resource state, from this to D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE (for mostly debugging)
; Default (auto) is state correction disabled
MotionVectorResourceBarrier=auto

; Depth texture resource state, from this D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE (for mostly debugging)
; Default (auto) is state correction disabled
DepthResourceBarrier=auto

; Color mask texture resource state, from this D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE (for mostly debugging)
; Default (auto) is state correction disabled
ColorMaskResourceBarrier=auto

; Exposure texture resource state, from this D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE (for mostly debugging)
; Default (auto) is state correction disabled
ExposureResourceBarrier=auto

; Output texture resource state, from this D3D12_RESOURCE_STATE_UNORDERED_ACCESS (for mostly debugging)
; Default (auto) is state correction disabled
OutputResourceBarrier=auto
```

这些可以在游戏内菜单中修改, 效果实时可见。

![resource barriers](images/rb.png)

### Mipmap LOD Bias Override (Mipmap LOD 偏移覆盖, 仅 Dx12)
为了获得更清晰的纹理, 可以用此设置覆盖 `MipmapLodBias`。-15 最锐利, +15 最模糊。

```ini
[Hotfix]
; Override mipmap lod bias for textures
; -15.0 - 15.0 - Default (auto) is disabled
MipmapBiasOverride=auto
```

**调整 MipmapLODBias 会影响性能!**

可以在游戏内菜单中修改, 需要改变分辨率后才会生效。

![mipmap lod bias](images/mipmap.png)

### Restore Root Certificates (恢复根签名, 仅 Dx12)
这个热修复基于原版 CyberFSR2 的恢复 ComputeRootSignature 逻辑, 我也加入了恢复 ComputeRootSignature 的选项。我没有发现需要这些选项的游戏。

```ini
[Hotfix]
; Restore last used compute signature after upscaling
; true or false - Default (auto) is false
RestoreComputeSignature=auto

; Restore last used graphics signature after upscaling
; true or false - Default (auto) is false
RestoreGraphicSignature=auto
```

这些可以在游戏内菜单中修改, 效果实时可见。

![root certificate](images/cs.png)

### Logging (日志)
```ini
[Log]
; Logging
; true or false- Default (auto) is true
LoggingEnabled=auto

; Log file, if undefined log_xess_xxxx.log file in current folder
;LogFile=./CyberXess.log

; Verbosity level of file logs
; 0 = Trace / 1 = Debug / 2 = Info / 3 = Warning / 4 = Error
; Default (auto) is 2 = Info
LogLevel=auto

; Log to console (Log level is always 2 (Info) for performance reasons)
; true or false - Default (auto) is false
LogToConsole=auto

; Log to file
; true or false - Default (auto) is false
LogToFile=auto

; Log to NVNGX API
; true or false - Default (auto) is false
LogToNGX=auto

; Open console window for logs
; true or false - Default (auto) is false
OpenConsole=auto
```

这些可以在游戏内菜单中修改, 效果实时可见。

![logging](images/logging.png)

### Menu (菜单)
```ini
[Menu]
; In-game ImGui menu scale
; 1.0 to 2.0 - Default (auto) is 1.0
Scale=auto
```

这些可以在游戏内菜单中修改, 效果实时可见。

![menu scale](images/ui_scale.png)
