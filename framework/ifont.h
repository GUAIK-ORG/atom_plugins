/**
 * @file ifont.h
 * @author Rick (rick@guaik.io)
 * @brief 字体管理器
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef IFONT_H
#define IFONT_H

#include <QString>
#include <QIcon>

/**
 * @brief 字体管理器
 * 
 */
class IFontManager
{
public:
    /**
     * @brief 根据名称获取字体图标（Font Awesome）
     * 
     * @param 图标名称 
     * @param 图标大小
     * @param 图标颜色
     * @return QIcon 图标对象
     */
    virtual QIcon GetIcon(int name, int size, QColor color) = 0;
};

#endif // IPLUGIN_H
