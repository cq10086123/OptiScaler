<div align="center">

  ![Logo](https://github.com/user-attachments/assets/c7dad5da-0b29-4710-8a57-b58e4e407abd)

</div>
<hr />
<br />
<div align="center">
  <a href="https://github.com/sponsors/cdozdil?frequency=one-time"><img src="images/gh-sponsor-red.png" /></a>
  <a href="https://buymeacoffee.com/nitec"><img src="images/bmac.png" /></a>
</div>
<br />

> 🇨🇳 本文档为简体中文版。英文原版见 [README.md](README.md)。
> 配置文件中文注释版见 [OptiScaler_zh.ini](OptiScaler_zh.ini)；其他中文文档: [Config](Config_zh-CN.md) · [Features](Features_zh-CN.md) · [Issues](Issues_zh-CN.md) · [Spoofing](Spoofing_zh-CN.md)

## 目录

**1.** [**简介**](#简介)
**2.** [**工作原理**](#工作原理)
**3.** [**支持的 API 和放大算法**](#支持的-api-和放大算法)
**4.** [**安装**](#安装)
**5.** [**已知问题**](#已知问题)
**6.** [**编译与致谢**](#编译与致谢)
**7.** [**Wiki**](https://github.com/optiscaler/OptiScaler/wiki)

<br />
<div align="center">
  <a href="https://discord.gg/wEyd9w4hG5"><img src="https://img.shields.io/badge/OptiScaler-blue?style=for-the-badge&logo=discord&logoColor=white&logoSize=auto&color=5865F2" alt="Discord invite"></a>
  <a href="https://github.com/optiscaler/OptiScaler/releases/latest"><img src="https://img.shields.io/badge/Download-Stable-green?style=for-the-badge&logo=github&logoSize=auto" alt="Stable release"></a>
  <a href="https://github.com/optiscaler/OptiScaler/releases/tag/nightly"><img src="https://img.shields.io/badge/Download-Nightly-purple?style=for-the-badge&logo=github&logoSize=auto" alt="Nightly release"></a>
  <a href="https://github.com/optiscaler/OptiScaler/wiki"><img src="https://img.shields.io/badge/Documentation-blue?style=for-the-badge&logo=gitbook&logoColor=white&logoSize=auto" alt="Wiki"></a>
</div>

## 简介

**OptiScaler** 是一个可以在游戏已经支持 DLSS2+ / FSR2+ / XeSS ($`^1`$) 的前提下**替换放大算法 (upscaler)** 的工具, 同时可以管理上述游戏的***帧生成 (Frame Generation)*** _(通过替换现有 FG 选项, 或在 DX12 游戏中通过实验性的 ***OptiFG*** 启用)_。它还为所有用户 (包括使用 DLSS 的 Nvidia 显卡用户) 提供了丰富的自定义选项。

> [!CAUTION]
> * 我们已获悉一些**假冒网站**冒充 OptiScaler 团队, 在此特别强调: 我们**没有官方网站!**
> * 我们**没有官方的管理器应用**, 下载或使用此类应用时请小心! 也请不要让我们为不属于我们的东西提供支持!
> * **正规渠道**只有: 本 Github 仓库、我们的 Discord 服务器, 以及 Nitec 的 NexusMods 页面。
> * OptiScaler **完全免费**, 任何收费要求都是诈骗!

> [!TIP]
> _例如, 如果某游戏只有 DLSS, OptiScaler 可以把 DLSS 替换为 XeSS 或 FSR 3.1 (对只有 FSR2 的游戏如《The Outer Worlds: Spacer's Choice》也有效, 但需要手动提供 nvngx_dlss.dll)。_

**OptiScaler 的主要特性:**
- 让 (时域) 放大算法支持的游戏可以使用 XeSS、FSR2、FSR3、**FSR4**$`^2`$ _(官方仅支持 RDNA4 和 RDNA3 dGPU)_ 和 DLSS
- 提供大量调校与增强选项, 让用户精细调整放大体验 (RCAS & MAS、输出缩放、DLSS 预设、比例 & DRS 覆盖等)
- v0.7.0+ 起新增***实验性 DX12***帧生成支持, 并附带可能的 HUDfix 方案 ([**OptiFG**](#optifg--hudfix-实验性-hud-残影修复))
- 支持 [**Fakenvapi**](#安装) 集成 - 可 hook 并注入 Reflex 的 _Anti-Lag 2_ (仅 RDNA1+)、_LatencyFlex_ (LFX) 或 _XeLL_ - _0.9 起已内置_
- v0.7.7 起新增对 **Nukem** 的 FSR3-FG mod [**dlssg-to-fsr3**](#安装) 的支持, 仅支持***原生 DLSS-FG***游戏 - _0.9 起已内置_
- v0.7.8 起新增 **ASI 插件加载**支持 (默认_禁用_ (INI 中 `LoadAsiPlugins=`), 从可自定义的文件夹加载, 默认 `plugins`)
- 新项目 - [**OptiPatcher**](https://github.com/optiscaler/OptiPatcher) - 一个 OptiScaler 的 ASI 插件, 可在***受支持的游戏***中无需伪装 (spoofing) 就启用 DLSS 和 DLSSG 输入。
- v0.7.8 起, OptiScaler 会自动应用某些游戏补丁, 以获得更好的开箱即用体验
- v0.9.0 起, 拆分了 FG 输入 (Inputs) 和输出 (Outputs), 新增 XeFG 和 FSR4-FG 支持, 并内置了 Fakenvapi 和 Nukem 的 FSR3-FG mod
- 完整特性列表见 [Features](Features.md) (中文: [Features_zh-CN.md](Features_zh-CN.md))

> [!IMPORTANT]
> _**请务必查看 [Wiki 兼容性列表](https://github.com/optiscaler/OptiScaler/wiki) 了解已知游戏问题及解决方法。**_
> 另外也请查看文末的 [***OptiScaler 已知问题***](#已知问题), 特别是关于 **RTSS** 兼容性的部分。
> 另有一份社区测试的 [***FSR4 兼容性列表***](https://github.com/optiscaler/OptiScaler/wiki/FSR4-Compatibility-List)。
> ***[3]*** 对于**未内置**的项目, 请查看 [安装](#安装)。

> [!NOTE]
> ### 放大算法相关说明
> <details>
>  <summary><b>点击展开 [1]、[2]</b></summary>
>
> **[1]** 对于 **Unreal Engine** 游戏, 只有 UE XeSS -> Opti XeSS/FSR4 可行
>
> *关于 **XeSS** 输入: 由于 **Unreal Engine 插件**不提供深度信息, 替换游戏内 XeSS 会破坏其他放大算法 (例如 XeSS-only 游戏《Redout 2》), 但你仍可以对 XeSS 应用 RCAS 锐化来减少模糊。*
>
> *关于 **FSR 输入**: FSR 3.1 是第一个拥有完全标准化、面向未来 API 的版本, 应该能完全支持。由于 FSR2 和 FSR3 支持自定义接口, 游戏支持情况取决于开发者的实现。Unreal Engine 游戏的 FSR 输入可能需要进行 [ini 调整](https://github.com/optiscaler/OptiScaler/wiki/Unreal-Engine-Tweaks)。*
>
> **[2]** *关于 **FSR4**, 请查看 [FSR4 兼容性列表](https://github.com/optiscaler/OptiScaler/wiki/FSR4-Compatibility-List) 了解已支持的游戏和通用信息。*
>
> </details>

## 官方 Discord 服务器: [OptiScaler](https://discord.gg/wEyd9w4hG5)

*本项目基于 [PotatoOfDoom](https://github.com/PotatoOfDoom) 的优秀作品 [CyberFSR2](https://github.com/PotatoOfDoom/CyberFSR2) 开发。*

## 工作原理
* OptiScaler 作为中间件运行: 拦截游戏对放大算法的调用 (***输入 Inputs***) 并重定向到所选的放大后端 (***输出 Output***), 从而允许用一种技术替换另一种技术。 **输入 -> OptiScaler -> 输出**
* _直白一点说: **输入 (Input)** 是游戏设置里使用的放大算法, **输出 (Output)** 是 OptiScaler 覆盖层 (Overlay) 里选择的那个。_
* _FG 选项同样拆分为 **FG 输入 (FG Input)** 和 **FG 输出 (FG Output)**。_

> [!NOTE]
> * 按 **`Insert`** 键应可打开游戏内 OptiScaler **覆盖层菜单 (Overlay)**, 包含所有选项 (快捷键可在 INI 文件的 `ShortcutKey=` 中修改, 或在覆盖层的 **Keybinds (快捷键)** 中修改)。
> * 按 **`Page Up`** 会在左上角显示性能统计覆盖层, 按 **`Page Down`** 可切换不同显示模式 (快捷键可在覆盖层中自定义)。
> * 如果按了几次 Insert 后覆盖层立刻消失, 可以试试 **`Alt + Insert`** (针对非 QWERTY 键盘布局的[已知解决方法](https://github.com/optiscaler/OptiScaler/issues/484))。

![inputs_and_outputs](https://github.com/user-attachments/assets/7ff37fd7-515f-488d-99ff-faa586e206fc)

## 支持哪些 API 和放大算法?
目前 **OptiScaler** 可用于 DirectX 11、DirectX 12 和 Vulkan, 但每个 API 支持的放大算法集合不同。
[**OptiFG**](#optifg--hudfix-实验性-hud-残影修复) 目前**仅支持 DX12**, 详见专门段落。

#### DirectX 12
- XeSS (默认)
- FSR 2.1.2, 2.2.1
- FSR 3.X (以及 FSR 2.3.X)
- FSR 4.X (通过 FSR 3.X/4 实现, _官方仅支持 RDNA4 和 RDNA3 dGPU_)
- DLSS

#### DirectX 11
- FSR 2.2.1 (默认, 原生 DX11)
- FSR 3.1.2 (非官方的原生 DX11 移植)
- DLSS (原生 DX11)
- XeSS 2.X (原生 DX11, _仅限 Intel ARC_)
- XeSS、FSR 2.1.2、2.2.1、FSR 3.X w/Dx12 (_通过 D3D11on12_)$`^1`$
- FSR 4.X (通过 FSR 3.X/4 w/Dx12 互操作, _官方仅支持 RDNA4 和 RDNA3 dGPU_)

> [!NOTE]
> <details>
>  <summary><b>展开 [1]</b></summary>
>
> _**[1]** 这些实现使用一个后台 DirectX12 设备来调用仅限 DX12 的放大算法。此方法有大约 10% 的性能损耗, 但提供更多放大算法选择。另外 FSR 2.2.1 的原生 DX11 实现是从 Unity 渲染器回移的, 自身有一些问题, 其中部分已被 OptiScaler 修复。_
> </details>

#### Vulkan
- FSR 4.X (通过 FSR 3.X/4 w/Dx12 互操作, _官方仅支持 RDNA4 和 RDNA3 dGPU_)
- FSR2 2.1.2 (默认), 2.2.1
- FSR3 3.1 (以及 FSR2 2.3.2)
- DLSS
- XeSS 2.x

#### OptiFG + HUDfix (实验性 HUD 残影修复)
**OptiFG** 在 **v0.7** 中加入, **仅支持 DX12**。
它是一种**实验性**手段, 为没有原生帧生成的游戏添加 FG; 也可以在原生 FG 不工作时作为最后手段使用。
* 目前支持 FSR3-FG (需要 HUDfix 以避免 HUD 残影)、XeFG 和 FSR4-FG (ML 模型会处理 HUD, 是否需要 HUDfix 视情况而定)。

关于 OptiFG 的更多信息和使用方法, 请查看 Wiki 页面 - [OptiFG](https://github.com/optiscaler/OptiScaler/wiki/OptiFG)。

## 安装
> [!CAUTION]
> _**警告**: **请勿在联机游戏中使用本 mod。** 可能触发反作弊软件导致封号!_

> [!IMPORTANT]
> **安装步骤请查看 [**Wiki**](https://github.com/optiscaler/OptiScaler/wiki)**

## 配置
配置参数和说明请查看 [Config_zh-CN.md](Config_zh-CN.md) (英文: [Config.md](Config.md))。如果你的显卡不是 Nvidia, 请查看 [GPU 伪装 (Spoofing) 选项](Spoofing.md)

## 已知问题

> [!NOTE]
> **已知问题列表请查看 [**Wiki**](https://github.com/optiscaler/OptiScaler/wiki)**。
>
> 也值得查看 [兼容性列表](https://github.com/optiscaler/OptiScaler/wiki/Compatibility-List) 了解可能的游戏问题及其解决方法。

## 编译与致谢

### 要求
* Visual Studio 2022

### 步骤
* 克隆本仓库 (**包括所有子模块 submodules**)。
* 用 Visual Studio 2022 打开 OptiScaler.sln。
* 构建项目

## 致谢
* @PotatoOfDoom 的 CyberFSR2
* @Artur 的 DLSS Enabler, 以及帮助我正确实现 NVNGX api
* @LukeFZ 和 @Nukem 的优秀 mods 和知识分享
* @FakeMichau 的持续支持、测试和功能推动
* @QM 的持续测试投入, 帮助我把 OptiScaler 带到更多游戏
* @TheRazerMD 的持续测试和支持
* @Cryio、@krispy、@krisshietala、@Lordubuntu、@scz、@Veeqo 在 (现已过时的) [兼容性矩阵](https://docs.google.com/spreadsheets/d/1qsvM0uRW-RgAYsOVprDWK2sjCqHnd_1teYAx00_TwUY) 上的辛勤工作
* 以及整个 DLSS2FSR 社区的所有支持

## 声明
本项目使用了 [FreeType](https://gitlab.freedesktop.org/freetype/freetype), 采用 [FTL](https://gitlab.freedesktop.org/freetype/freetype/-/blob/master/docs/FTL.TXT) 许可

## 赞助方
<table>
 <tbody>
  <tr>
   <td align="center"><img alt="[SignPath]" src="https://avatars.githubusercontent.com/u/34448643" height="30"/></td>
   <td>Windows 免费代码签名由 <a href="https://signpath.io/">SignPath.io</a> 提供, 证书由 <a href="https://signpath.org/">SignPath Foundation</a> 提供</td>
  </tr>
 </tbody>
</table>
