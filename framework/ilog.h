/**
 * @file ilog.h
 * @author Rick (rick@guaik.io)
 * @brief 日志管理器
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ILOG_H__
#define __ILOG_H__
#include "icontext.h"
#include <QString>
#include <QVariant>

class ILogManager
{
public:
    virtual void _debug(const char *file, int line, const char *func, const QString &msg) = 0;
    virtual void _info(const char *file, int line, const char *func, const QString &msg) = 0;
    virtual void _warn(const char *file, int line, const char *func, const QString &msg) = 0;
    virtual void _error(const char *file, int line, const char *func, const QString &msg) = 0;

    virtual void debug(const char *file, int line, const char *func, const char *format, ...) = 0;
    virtual void info(const char *file, int line, const char *func, const char *format, ...) = 0;
    virtual void warn(const char *file, int line, const char *func, const char *format, ...) = 0;
    virtual void error(const char *file, int line, const char *func, const char *format, ...) = 0;
};

class Log
{
public:
    static Log &getInstance()
    {
        static Log m_instance;
        return m_instance;
    }
    void init(IContext *ctx)
    {
        if (0 == ctx->query(QUERY_TYPE::LOG_MANAGER, (void **)&m_mgr))
        {
            m_isInit = true;
        }
    }
    ILogManager *mgr() { return m_mgr; }
    bool isInit() { return m_isInit; }

private:
    ILogManager *m_mgr;
    bool m_isInit = false;
};

class Debug
{
public:
    Debug(const char *file, int line, const char *func)
    {
        m_file = file;
        m_line = line;
        m_func = func;
    }
    ~Debug()
    {
        if (Log::getInstance().isInit())
            Log::getInstance().mgr()->_debug(m_file, m_line, m_func, m_data);
    }
    Debug &operator<<(const QVariant value)
    {
        m_data.append(value.value<QString>());
        return *this;
    }

private:
    const char *m_file;
    int m_line;
    const char *m_func;
    QString m_data;
};

class Info
{
public:
    Info(const char *file, int line, const char *func)
    {
        m_file = file;
        m_line = line;
        m_func = func;
    }
    ~Info()
    {
        if (Log::getInstance().isInit())
            Log::getInstance().mgr()->_info(m_file, m_line, m_func, m_data);
    }
    Info &operator<<(const QVariant value)
    {
        m_data.append(value.value<QString>());
        return *this;
    }

private:
    const char *m_file;
    int m_line;
    const char *m_func;
    QString m_data;
};

class Warn
{
public:
    Warn(const char *file, int line, const char *func)
    {
        m_file = file;
        m_line = line;
        m_func = func;
    }
    ~Warn()
    {
        if (Log::getInstance().isInit())
            Log::getInstance().mgr()->_warn(m_file, m_line, m_func, m_data);
    }
    Warn &operator<<(const QVariant value)
    {
        m_data.append(value.value<QString>());
        return *this;
    }

private:
    const char *m_file;
    int m_line;
    const char *m_func;
    QString m_data;
};

class Error
{
public:
    Error(const char *file, int line, const char *func)
    {
        m_file = file;
        m_line = line;
        m_func = func;
    }
    ~Error()
    {
        if (Log::getInstance().isInit())
            Log::getInstance().mgr()->_error(m_file, m_line, m_func, m_data);
    }
    Error &operator<<(const QVariant value)
    {
        m_data.append(value.value<QString>());
        return *this;
    }

private:
    const char *m_file;
    int m_line;
    const char *m_func;
    QString m_data;
};

#define LOG_DEBUG(...) Log::getInstance().mgr()->debug(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__), __VA_ARGS__)
#define LOG_INFO(...) Log::getInstance().mgr()->info(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__), __VA_ARGS__)
#define LOG_WARN(...) Log::getInstance().mgr()->warn(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__), __VA_ARGS__)
#define LOG_ERROR(...) Log::getInstance().mgr()->error(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__), __VA_ARGS__)

#define aDebug() Debug(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__))
#define aInfo() Info(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__))
#define aWarn() Warn(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__))
#define aError() Error(__FILE__, __LINE__, static_cast<const char *>(__FUNCTION__))

#endif
