## Common Signals in Linux 

>> SIGINT - interrupt (CTRL-c)
>> SIGSR1 and SIGUSR2 - user defined signals
>> SIGKILL - sent to process from kernel when kill -9 is invoked on pid. This signal cannot be caught by the process
>> SIGABRT - raised by abort() by the process itself. The process is terminated.
>> SIGTERM - raised when kill is invoked. Can be caught by the process to execute user defined action
>> SIGSEGV - Segmentation fault, raised by the kernel to the process when illegal memory is referenced.
>> SIGCHILD - whenever a child terminates, this signal is sent to the parent.

## Three ways of generating Signals in Linux

1. Raising a signal from OS to a process (ctrl- C etc)

2. Sending a signal from process A to itself (using raise())

3. Sending signal from process A to process B (using kill())

