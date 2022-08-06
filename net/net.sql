-- 启用外键
PRAGMA FOREIGN_KEYS=ON;

DROP TABLE IF EXISTS server;
DROP TABLE IF EXISTS session;
DROP TABLE IF EXISTS client;
DROP TABLE IF EXISTS storage;

-- 创建服务表
CREATE TABLE server(
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    [name] VARCHAR(20) NOT NULL,
    [protocol_type] INT8 NOT NULL,                -- 协议类型： 0:TCP 1:UDP
    [port] INT NOT NULL
);
CREATE INDEX server_index on server (id, name, protocol_type, port);

-- 创建客户端会话表
CREATE TABLE session(
    [id] INTEGER PRIMARY KEY NOT NULL,                  -- 随机id
    [server_name] CHAR(20) NOT NULL,                    -- 服务名
    [remote_ip] VARCHAR(50) NOT NULL,                   -- 远程ip
    [remote_port] INTEGER NOT NULL,                     -- 远程端口号
    [connect_time] TimeStamp NOT NULL DEFAULT (datetime('now','localtime')), -- 接入时间
    [disconnect_time] TimeStamp                         -- 连接断开时间
);
CREATE INDEX session_index on session (id, server_name, remote_ip, remote_port, connect_time, disconnect_time);

-- 创建客户端
CREATE TABLE client(
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    [name] VARCHAR(20) NOT NULL,
    [protocol_type] INT8 NOT NULL,                      -- 协议类型： 0:TCP 1:UDP
    [remote_ip] VARCHAR(50) NOT NULL,                   -- 远程ip
    [remote_port] INT NOT NULL,                         -- 远程端口
    [last_connect_time] TimeStamp,                      -- 最后一次连接成功时间
    [last_disconnect_time] TimeStamp                    -- 最后一次连接断开时间
);
CREATE INDEX client_index on client (id, name, protocol_type, remote_ip, remote_port, last_connect_time, last_disconnect_time);

-- 创建收发数据表
CREATE TABLE storage(
    [device_id] INTEGER NOT NULL,                       -- 服务端时该字段为session_id，客户端时该字段为client_id
    [io_type] INT8 NOT NULL,                            -- 输入输出方式： 0：接收 1:发送
    [data] BLOB NOT NULL,                               -- 实际数据
    [byte_count] INTEGER NOT NULL,                      -- 字节计数
    [time] TimeStamp NOT NULL DEFAULT (datetime('now','localtime')) -- 时间
);
CREATE INDEX storage_index on storage (device_id, io_type, byte_count, time);