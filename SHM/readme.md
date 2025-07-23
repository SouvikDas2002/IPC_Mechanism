# Fastest way of implementing IPC : Shared memory


>> Shared memory : Based on concept Memory Mapping

>>Steps:

1. Initialize the Shared Memory segment shm_open().
2. Define the size of SHM segment - ftruncate()
3. Map the shared memory segment to Data Source - mmap()
4. Use the Shared Memory (read/write)
5. Destroy the mapping between process and Shared Memory segment - munmap()
6. Destroy shared memory segment - shm_unlink()

## When to use Shared memory IPC :

1. Exactly one process is responsible to update sgared memory(publisher process).

2. The frequency of updating the shared memory by publisher process should not be very high

## Note: IPC using shared memory has to be backed/supported by other types of IPCs 

>> After updating the shared memory, publisher needs to send a notification to all subscribers that "share memory has been updated"

>> For this notification or this small message can be use other IPC mechanishms, such as UNIX domain sockets or MSG Queues
