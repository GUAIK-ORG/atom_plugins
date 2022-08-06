/**
 * @file istorage.h
 * @author Rick (rick@guaik.io)
 * @brief 本地存储服务
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ISTORAGE_H__
#define __ISTORAGE_H__

#include <QString>
#include <QMap>

typedef QMap<QString, QString> STORAGE_DATA;

class IStorageManager
{
public:

    /**
     * @brief 获取值（同步）
     * 
     * @param key 键
     * @return QString 
     */
    virtual QString get(const QString &key) = 0;

    /**
     * @brief 存储值（同步）
     * 
     * @param key 键
     * @param value 值
     * @return true 写入成功
     * @return false 写入失败
     */
    virtual bool put(const QString &key, const QString &value) = 0;

    /**
     * @brief 删除数据（同步）
     * 
     * @param key 键
     * @return true 删除成功
     * @return false 删除失败
     */
    virtual bool del(const QString &key) = 0;

    /**
     * @brief 存储值（异步）
     * 
     * @param key 键
     * @param value 值
     * @return true 写入成功
     * @return false 写入失败
     */
    virtual bool aPut(const QString &key, const QString &value) = 0;

    /**
     * @brief 删除数据（异步）
     * 
     * @param key 键
     * @return true 删除成功
     * @return false 删除失败
     */
    virtual bool aDel(const QString &key) = 0;

    /**
     * @brief 获取所有数据
     * 
     * @return QMap<QString, QString> 
     */
    virtual QMap<QString, QString> data() = 0;
};

#endif