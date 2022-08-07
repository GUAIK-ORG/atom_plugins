# 怪客工业1号框架（Atom）

> 产品编号：GKIF-No.1
 
---

## 🚀 组件框架的特点

在开发一款软件（上位机）产品时通常采用多人同时对一套代码进行修改的形式，这种将所有功能都写在一套代码中的方式称为【单块架构】。单块架构存在以下缺点如下：

> * 维护成本增加 
> * 持续交付周期长 
> * 新人培养周期长
> * 技术选型成本高
> * 可伸缩性差
> * 构建全功能团队难

为了解决单块架构面临的挑战，出现了新的架构【微服务】，微服务架构的特点如下：

> * 解耦：同一系统内的服务大部分可以被解耦。因此应用，作为一个整体，可以轻易地被构建、修改和扩展。
> * 组件化：微服务可以被看成相互独立的组件，这些组件可以被轻易地替换和升级。
> * 业务能力：微服务很小，它们可以专注于某种单一的能力。
> * 自治：开发者和团队可以独立地工作，提高开发速度。
> * 持续交付：允许持续发布软件新版本，通过系统化的自动手段来创建、测试和批准新版本。
> * 职责明确：微服务不把应用看成一个又一个的项目。相反，它们把应用当成了自己需要负责的项目。
> * 去中心化管理：关注于使用正确的工具来完成正确的工作。这也就是说，没有标准化的方式或者技术模式。开发者们有权选择最好的工具来解决问题。
> * 敏捷性：微服务支持敏捷开发。任何新功能都可以被快速开发或丢弃。

**以上内容来自网络，下面说下我自己的看法**

* 对于C++开发而言，随着项目代码量的增加，编译速度也会越来越慢，如果组件化的开发方式每个人只需要编译自己开发的组件即可，大大**提升编译效率**。

* 由于将项目分解成了不同的模块，分工将会更加明确，有新人入职时只需要培训组件开发相关的技术和相关的业务即可**快速上手**。

* 协作是通过组件接口或组件间通讯实现的，无需担心不同模块的开发者会无意间修改到他人的代码，这将会**更安全**。

* 组件全部开源，随着开源组件的增多，框架将提供更多的功能，**提高开发效率**。

* 《Atom》框架**永久免费**使用，无需担心花费额外的费用。

为了实现上述特性，我推出了 **🎉《怪客工业1号框架 - Atom》🎉**

## 🔆 《Atom》框架特性

* 实现了组件的依赖检查，被依赖的组件优先加载，确保调用时组件已被正确载入，能够检测互相依赖关系（A依赖B的同时B依赖A）。

* 集成了ZeroMQ作为框架间通讯，只需要简单的修改配置文件即可实现多框架通讯。 

* 可通过配置文件指定皮肤资源。

* 内置上百个图标资源可用作插件Icon。

* 生命周期组件，可在不同阶段的生命周期中执行相关代码。

* 多级别日志服务，可同时输出到控制台和文件。

## 🧩 基础组件

| 类型 | 名称 | 简介 | 开发状态 |
| - | - | - | - |
| 服务 | net | 提供TCP客户端和服务端的功能及连接状态管理，断线自动重连 | ✅ |
| 服务 | script | 提供lua脚本相关服务 | ❌ |
| 窗体 | title | 标题栏：显示标题，提供全屏、最大化、最小化、关闭按钮 | ✅ |
| 窗体 | statusbar | 底部状态栏：显示时间和网络连接状态 | ✅ |
| 窗体 | plugin_manager | 插件管理：生成插件模版代码 | 👨‍💻 |

## ⚙️ 开始使用

### 安装 & 配置

* 下载框架可执行程序

https://gitee.com/GuaikOrg/atom_plugins/releases/tag/v1.0.0

https://github.com/GUAIK-ORG/atom_plugins/releases/tag/v1.0.0

* 安装Qt5.15.2版本

> 编译工具：mingw
> 
> 开源协议：LGPL

* 配置环境变量

| 变量名 | 变量值 |
| - | - |
| Path | Qt路径\5.15.2\mingw81_64\bin |
| Path | Qt路径\Tools\mingw810_64\bin |
| Path | 框架路径\env |


## 🗂 插件开发教程

开发内容主要分两类：

* 服务组件

* 窗体组件

服务组件能够为其他的服务组件提供功能接口，窗体组件能够提供一个菜单以及和用户的交互界面，界面组件能够选择不同的展现方式（切换或弹窗）。**界面组件无法对外提供接口**。

### 框架配置文件

| 字段名称 | 描述 |
| - | - |
| version | 版本号 |
| index | 首页组件 |
| show_type | 启动时窗口状态 |
| win_size | 窗口大小 |
| titlebar | 标题栏组件 |
| statusbar | 状态栏组件 |
| skin | 皮肤 |
| mq_port | 消息队列本地监听端口 |
| mq_nodes | 消息队列连接地址 |
| log_level | 日志级别 |

### 组件配置文件

| 字段名称 | 描述 |
| - | - |
| name | 组件名 |
| id | 组件id（必须全局唯一） |
| version | 版本号 |
| description | 描述 |
| type | 类型[服务:0 窗体:1] |
| icon | 图标 |
| icon_color | 图标颜色 |
| display_mode | 显示方式[内嵌:0 弹窗:1] |
| sort_weight | 排序权重 |
| dependents | 依赖项 |

### 框架接口服务

💎 一个重要的目录：**framework**

**framework**目录下存放了所有框架对外提供的接口。要了解框架功能的话可以把该目录下的所有接口头文件看一遍。

下面挑部分常用接口讲解

#### 组件管理器

> 提供了接口对象的注册与获取

```cpp
/**
 * @brief 注册接口对象（仅服务可用）
 * 
 * @param ctx 上下文对象
 * @param interfaceObj 接口对象
 * @return int 成功:0
 */
int registerInterfaceObj(IContext* ctx, void* interfaceObj);
```

```cpp
/**
 * @brief 获取接口对象
 * 
 * @param ctx 上下文对象
 * @param id 插件ID
 * @return void* 接口对象
 */
void* interfaceObj(IContext* ctx, QString id);
```

**使用示例**

```cpp
// net
// 在网络插件中注册网络服务接口
IPluginManager *pluginManager;
if (0 == m_ctx->query(QUERY_TYPE::PLUGIN_MANAGER, (void**)&pluginManager)) {
    m_netService = dynamic_cast<INetService*>(new NetService);
    pluginManager->registerInterfaceObj(m_ctx, m_netService);
}

// dbg
// 在调试插件中获取网络服务对象
IPluginManager* pluginManager;
if (0 == m_ctx->query(QUERY_TYPE::PLUGIN_MANAGER, (void**)&pluginManager)) {
    INetService* net = (INetService*)pluginManager->interfaceObj(m_ctx, "net");
    if (net) {
        // ......
    }
}
```

#### 窗体管理器

> 控制框架窗体和插件窗体：注册窗体、最大化、最小化、全屏、显示、隐藏窗体等

```cpp
/**
 * @brief 注册窗体对象
 * 
 * @param ctx 上下文对象
 * @param id 注册窗体对象ID（插件ID）
 * @param widget 窗体对象
 * @return int 成功:0
 */
virtual int registerWidget(IContext *ctx, QString id, QWidget *widget) = 0;

```

**使用示例**

```cpp
// dbg
// 在调试插件中注册窗体对象
IWindowManager *winManager;
if (0 == m_ctx->query(QUERY_TYPE::WINDOW_MANAGER, (void**)&winManager)) {
    winManager->registerWidget(m_ctx, "dbg", new MainWidget(m_ctx));
}
```

#### 消息管理器

#### 字体管理器

> 字体管理器主要提供了“Font Awesome”字体图标服务

#### 日志管理器

> 提供了异步日志的功能，支持 **debug** **info** **warn** **error** 四种级别，能同时输出控制台和文件，默认存储在log目录下。



### 创建服务组件

> 服务组件可以为窗体组件或其他服务组件提供接口

### 组件间通讯

### 框架间通讯

> 基于消息队列的框架间通讯，通过修改框架配置文件添加节点信息即可实现框架间连接

### 基础组件

#### 网络组件

> 网络组件目前提供了TCP服务端与TCP客户端的接口，TCP客户端实现了断线检测与重连的功能（基于keepalive，相关文章：https://caw.guaik.io/d/1-keepalive）


### 本地数据存储

> 提供了键值对（K/V）数据的存储

| 操作 | 同步 | 异步 |
| - | - | - |
| read | ✅ | ❌ |
| write | ✅ | ✅ |
| delete | ✅ | ✅ |

# 联系我们

* 作者：Rick
* 邮箱：rick@guaik.io
* QQ：3558888808
* QQ群：564354254