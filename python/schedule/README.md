The 'threading.Timer()' is used here to run special task periodly.

这里主要使用threading.Timer()，周期性地执行特定任务。

For some reason, the task is only need to be run at specified period. So, before running the real task, we get the current local time, i.e., hour, minute, second. By checking these information, we decide whether running the task or not.

当然，可能只希望在某天的某个时间段执行任务，为此，在真正开始调度任务之前，需要判断当前是否需要执行，这通过检测当前的时间来实现。