A process can create a new msgQ or use an existing msgq using below API:

>> There are two favour of API -

>> First one -

mqd_t - msgq FD
mq_open(const char *name,int oflag);


>> Second one -

mq_open(const char *name,int oflag,mode_t mode, struct mq_attr *attr);

name - Name of msg Q
oflag - Operational flags

O_RDONLY - Open for reading only
O_WRONLY - Open for writing only
O_RDWR - Open for both reading and writing
O_CREAT - Create the queue if it does not exist
O_EXCL - Fail if O_CREAT is also specified and the queue already exists

mode - Permission set by the owning process on the queue usually 0660

struct mq_attr{
    long mq_flags;   // Flags: 0 or O_NONBLOCK
    long mq_maxmsg;  // Max number of messages in the queue
    long mq_msgsize; // Max size of each message (in bytes)
    long mq_curmsgs; // Number of messages currently in the queue (read-only)
}

---

## Example 1: Without attributes

mqd_t msgq;

if((msgq=mq_open("/server-msg-q",O_RONLY|O_CREATE|O_EXCL,0660,0))==-1){
    perror("Server:mq_open(server)");
    exit(1);
}

## Example 2: With attributes

mqd_t msgq;

struct mq_attr attr;

attr.mq_flags=0;
attr.mq_maxmsg=10;
attr.mq.msgsize=4096;
attr.mq.curmsgs=0;

if((msgq=mq_open("/server-msg-q",O_RONLY|O_CREATE|O_EXCL,0660,&attr))==-1){
    perror("Server:mq_open(server)");
    exit(1);
}
---

## msgQ close API()

int mq_close(mqd_t msgQ);

Return value:
0 - success
-1 - failure

## Enqueue a Message

int mq_send(mqd_t msgQ, char *msg_ptr,size_t msg_len, unsigned int msg_prio);

Return value :
0 - success
-1 -failure

msgQ - refered by the descriptor msgQ
msg_ptr - points to the message buffer
msg_len - size of message; <= message size
msg_prio - message priority

## Dequeue a Message 

int mq_receive(mqd_t msgQ,char *msg_ptr,size_t msg_len, unsigned int *msg_prio);

Here msg_ptr is empty message buffer for receive message

Return value : 
n_bytes of recvd msg - success
-1 -failure

## Destroying a MSGQ

int mq_unlink(const char *msgQ_name);

// Release the kernel resource
// postpone if other process are using MSGQ
