# µC/OS-II 在 C51 单片机上的移植

[Porting µC/OS-II](https://micrium.atlassian.net/wiki/spaces/osiidoc/pages/163858/Porting+C+OS-II)

## 1. µC/OS-II 架构

### 1.1. 处理器要求

1. 处理器有一个 C 编译器来生成**可重入代码**
2. 可以从 C 禁用中断并启用**中断**
3. **处理器支持中断**，并且可以提供在规则的间隔（通常在 10 到 100Hz 之间）发生的中断
4. 处理器支持可以容纳大量数据（可能是千字节）的**硬件堆栈**
5. 处理器有**加载和存储**堆栈指针和其他 **CPU 寄存器**的指令，无论是在堆栈中还是在内存中

### 1.2. 硬件/软件架构

![Figure 13.1 µC/OS-II hardware/software architecture](https://micrium.atlassian.net/wiki/download/thumbnails/163858/uCOS-II-hardwaresoftware-architecture.png?version=1&modificationDate=1435937534000&cacheVersion=1&api=v2&width=1000&height=1148)

### 1.3. 端口汇总

|         Name          |   Type    |     File     | C or Assembly | Complexity |
| :-------------------: | :-------: | :----------: | :-----------: | :--------: |
|       `BOOLEAN`       | Data Type |   OS_CPU.H   |       C       |     1      |
|        `INT8U`        | Data Type |   OS_CPU.H   |       C       |     1      |
|        `INT8S`        | Data Type |   OS_CPU.H   |       C       |     1      |
|       `INT16U`        | Data Type |   OS_CPU.H   |       C       |     1      |
|       `INT16S`        | Data Type |   OS_CPU.H   |       C       |     1      |
|       `INT32U`        | Data Type |   OS_CPU.H   |       C       |     1      |
|       `INT32S`        | Data Type |   OS_CPU.H   |       C       |     1      |
|        `FP32`         | Data Type |   OS_CPU.H   |       C       |     1      |
|        `FP64`         | Data Type |   OS_CPU.H   |       C       |     1      |
|       `OS_STK`        | Data Type |   OS_CPU.H   |       C       |     2      |
|      `OS_CPU_SR`      | Data Type |   OS_CPU.H   |       C       |     2      |
| `OS_CRITICAL_METHOD`  |  #define  |   OS_CPU.H   |       C       |     3      |
|    `OS_STK_GROWTH`    |  #define  |   OS_CPU.H   |       C       |     1      |
| `OS_ENTER_CRITICAL()` |   Macro   |   OS_CPU.H   |       C       |     3      |
| `OS_EXIT_CRITICAL()`  |   Macro   |   OS_CPU.H   |       C       |     3      |
|  `OSStartHighRdy()`   | Function  | OS_CPU_A.ASM |   Assembly    |     2      |
|      `OSCtxSw()`      | Function  | OS_CPU_A.ASM |   Assembly    |     3      |
|    `OSIntCtxSw()`     | Function  | OS_CPU_A.ASM |   Assembly    |     3      |
|     `OSTickISR()`     | Function  | OS_CPU_A.ASM |   Assembly    |     3      |
|   `OSTaskStkInit()`   | Function  |  OS_CPU_C.C  |       C       |     3      |
|  `OSInitHookBegin()`  | Function  |  OS_CPU_C.C  |       C       |     1      |
|   `OSInitHookEnd()`   | Function  |  OS_CPU_C.C  |       C       |     1      |
| `OSTaskCreateHook()`  | Function  |  OS_CPU_C.C  |       C       |     1      |
|   `OSTaskDelHook()`   | Function  |  OS_CPU_C.C  |       C       |     1      |
|   `OSTaskSwHook()`    | Function  |  OS_CPU_C.C  |       C       |     1      |
|  `OSTaskStatHook()`   | Function  |  OS_CPU_C.C  |       C       |     1      |
|   `OSTCBInitHook()`   | Function  |  OS_CPU_C.C  |       C       |     1      |
|  `OSTimeTickHook()`   | Function  |  OS_CPU_C.C  |       C       |     1      |
|  `OSTaskIdleHook()`   | Function  |  OS_CPU_C.C  |       C       |     1      |

### 开发工具

1. μc/OS-II 大部分是用 ANSI C 编写的，所以需要一个 ANSI C 编译器（现行的 C 编译器均符合）。另外，因为 μc/OS-II 是抢占式内核，所以应该只使用**生成可重入代码**的 C 编译器（面向 C51，考虑使用 KEIL）。
2. 一个汇编程序，因为有些端口需要保存和恢复 CPU 寄存器，而这些寄存器通常是 C 语言无法访问的。然而，一些 C 编译器的确有一些扩展，允许你直接从 C 语言操作 CPU 寄存器，或者允许你编写在线汇编语言语句。
3. 一个链接器和一个定位器。链接器用于组合来自不同模块的对象文件（编译和汇编的文件），而定位器允许您将代码和数据放置在目标处理器的内存映射中的任何位置。
4. C 编译器必须能够提供一种机制来**禁用和启用 C 中断**。有些编译器允许您将内联汇编语言语句插入到 C 源代码中。这使得插入正确的处理器指令来启用和禁用中断变得非常容易。其他编译器实际上包含语言扩展，可以直接从 C 启用和禁用中断。
