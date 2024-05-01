// 定义进程状态
enum ProcessState {
    READY,
    RUNNING,
    BLOCKED,
    TERMINATED
};

// 定义进程结构体
struct Process {
    int processId;                 // 进程ID
    int arrivalTime;               // 到达时间
    int burstTime;                 // 运行时间（或剩余运行时间）
    int priority;                  // 优先级（用于优先级调度）
    int waitingTime;               // 等待时间
    int turnaroundTime;            // 周转时间
    int responseTime;              // 响应时间
    ProcessState state;            // 进程状态
};
