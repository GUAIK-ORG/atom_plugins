#include "keepalive.h"
#include <QObject>

const int keepalive = 1;    // 开启keepalive属性
const int keepidle = 5;     // 如果连接在5秒内没有任何数据来往则进行探测
const int keepinterval = 3; // 探测时发包的时间间隔为3秒
const int keepcount = 3;    // 尝试探测的次数， 如果第一次探测包就收到响应，则不在继续探测

#if defined (Q_OS_LINUX) || defined (Q_OS_MACOS)
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

// 开启TCP心跳检测机制
int enableKeepalive(int fd) {
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive)) < 0) return -1;
    if (setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &keepidle, sizeof(keepidle)) < 0) return -1;
    if (setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &keepinterval, sizeof(keepinterval)) < 0) return -1;
    if (setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &keepcount, sizeof(keepcount)) < 0) return -1;
    return 0;
}
#elif defined (Q_OS_WIN)
#include <winsock2.h>

#define SIO_KEEPALIVE_VALS _WSAIOW(IOC_VENDOR,4)

struct tcp_keepalive {
    unsigned long onoff;
    unsigned long keepalivetime;
    unsigned long keepaliveinterval;
};

int enableKeepalive(int fd) {
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char*)&keepalive, sizeof(keepalive)) < 0) return -1;

    struct tcp_keepalive in_keep_alive;
    memset(&in_keep_alive, 0, sizeof(in_keep_alive));
    unsigned long ul_in_len = sizeof(struct tcp_keepalive);
    struct tcp_keepalive out_keep_alive;
    memset(&out_keep_alive, 0, sizeof(out_keep_alive));
    unsigned long ul_out_len = sizeof(struct tcp_keepalive);
    unsigned long ul_bytes_return = 0;

    in_keep_alive.onoff = 1;                                // 打开keepalive
    in_keep_alive.keepaliveinterval = keepinterval * 1000;  // 发送keepalive心跳时间间隔-单位为毫秒
    in_keep_alive.keepalivetime = keepidle * 1000;          // 多长时间没有报文开始发送keepalive心跳包-单位为毫秒

    if (WSAIoctl(fd, SIO_KEEPALIVE_VALS, (LPVOID)&in_keep_alive, ul_in_len,
                               (LPVOID)&out_keep_alive, ul_out_len, &ul_bytes_return, NULL, NULL) < 0) return -1;

    return 0;
}
#else
int enableKeepalive(int fd) {
    Q_UNUSED(fd);
    return -1;
}
#endif
