# DevTools
- 这个仓库用于存放所有有关开发阶段数据处理的工具 
- 界面采用 ``Qt Core`` 提供的默认样式与 ../AsulManager 的 ``ElaWidgetTools (@Liniyous)`` 有差异


##  DebugENV
- 提供 Debug 环境，模拟成品中的 CFGs 存储地址 ``(${CS2_Install_Path}/game/csgo/cfg)`` 

## MetaDataDebugTools
- 提供对 ``单个`` 文档的 ``data.json`` 的解析，包括数据处理位置以及 ``AsulSlot``、``AsulSignal`` 的快速 树状解析图

## PackageManager
- 提供对 ``多个`` 文档的 ``data.json``的统一解析，包括对依赖的处理，简单管理包的开关， 如 ``MetaDataDebugTools`` 一致的快速树状解析图
- **[Tips]:** 配套 DebugENV 环境可帮助你更多
