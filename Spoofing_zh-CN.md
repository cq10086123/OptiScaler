# GPU 伪装 (Spoofing)
> 🇨🇳 简体中文版。英文原版见 [Spoofing.md](Spoofing.md)。

除第一代 DLSS2 游戏外, 其他游戏都有某种形式的 NVidia 验证来启用 DLSS 选项。为了绕过这些检查, Mod 作者们开发了一些工具。

## Windows
### Nvapi
伪装 Nvapi 调用可以使用 FakeNvapi。某些游戏 (如《古墓丽影: 暗影》等) 启用 DLSS 支持需要它。

另外, 最新版本作为**一大额外福利**, FakeNvapi 还增加了对 AMD AntiLag 2 和 LatencyFlex 的支持, 可以在支持 Nvidia Reflex 的游戏上降低输入延迟。

##### 用法
只需把 `nvapi64.dll` 放在 OptiScaler 旁边, 并在 `OptiScaler.ini` 中设置 `OverrideNvapiDll=true`。仅在 OptiScaler 以非 nvngx 方式 (不是 `nvngx.dll`) 运行时有效。

不借助 OptiScaler 单独使用:
需要把 `nvapi64.dll` 放到 `%WINDIR%\System32`, 但**请注意!**
* 如果你是 Nvidia 用户, **先备份原始文件**, Mod 使用完毕后恢复。
* 请勿在联机游戏中使用此 Mod, 可能引起反作弊问题或封号。

##### 链接
[FakeNvapi](https://github.com/FakeMichau/fakenvapi/releases)

### DXGI
OptiScaler 内置 DXGI 伪装选项, 以非 nvngx 方式 (不是 `nvngx.dll`) 运行时默认启用。

#### d3d12-proxy
另一种方案是用 d3d12-proxy 伪装 DXGI 适配器检查。该 Mod 会把你的显卡报告为 RTX 4090。
##### 用法
把 dxgi.dll 放到游戏可执行文件旁边即可。
##### 链接
[d3d12-proxy](https://github.com/cdozdil/d3d12-proxy/releases)

### Vulkan
OptiScaler 以非 nvngx 方式 (不是 `nvngx.dll`) 运行时内置 Vulkan 伪装选项。
Vulkan 伪装默认禁用, 需要时在 `OptiScaler.ini` 中启用。
```ini
; Enables Nvidia GPU spoofing for Vulkan
; true or false - Default (auto) is false
Vulkan=auto

; Enables Nvidia extension spoofing for Vulkan
; true or false - Default (auto) is false
VulkanExtensionSpoofing=auto
```

#### vulkan-spoofer
另一种方案是用 vulkan-spoofer 伪装 `GetPhysicalDeviceProperties` 检查。该 Mod 会把你的显卡报告为 RTX 4090。
兼容性时好时坏, 在《无人深空》上可用 (最新的 streamline 补丁后不可用), 但在《毁灭战士: 永恒》上无效。
##### 用法
把 version.dll 放到游戏可执行文件旁边即可。
##### 链接
[vulkan-spoofer](https://github.com/cdozdil/vulkan-spoofer/releases)

## Linux
在 Linux 上可以使用 Wine 和 DXVK 内置的伪装机制。

### DirectX 与 Vulkan
DXGI 和 Vulkan 伪装: 在游戏可执行文件旁边创建一个内容为如下内容的 `dxvk.conf` 文件, 或直接从[这里](https://raw.githubusercontent.com/cdozdil/CyberXeSS/imgui-intergration/dxvk.conf)下载。
```ini
dxgi.customVendorId = 10de
dxgi.hideAmdGpu = True
dxgi.hideNvidiaGpu = False
dxgi.customDeviceId = 2684
dxgi.customDeviceDesc = "NVIDIA GeForce RTX 4090"
```

### NVAPI
Proton 下伪装 NVAPI: 设置环境变量 `PROTON_FORCE_NVAPI=1`

## Goghor 的 DLSS Unlocker
Goghor 为大量游戏制作了 DLSS Unlocker mod, 可以在他的 [Nexus](https://www.nexusmods.com/spidermanmilesmorales/users/12564231?tab=user+files&BH=0) 个人主页找到。
例如据我所知, 在《毁灭战士: 永恒》上启用 DLSS 目前只有他的 mod 这一条路。
