#ifndef QTYPEFACE_H
#define QTYPEFACE_H

#include <QColor>
#include <QDebug>
#include <QFont>
#include <QStringList>

#include "QMWidgetsGlobal.h"

class QMWIDGETS_API QTypeFace {
public:
    QTypeFace();
    QTypeFace(const QColor &color, int pixelSize);
    QTypeFace(const QColor &color, double pointSize);
    ~QTypeFace();

private:
    void init();

public:
    QStringList toStringList() const;

    bool isDefaultFont() const;

    QFont font() const;
    void setFont(const QFont &font);

    double pixelSize() const;
    void setPixelSize(double pixelSize);

    double pointSize() const;
    void setPointSize(double pointSize);

    double weight() const;
    void setWeight(double weight);

    QColor color() const;
    void setColor(const QColor &color);

private:
    QFont m_font;
    QColor m_color;

    bool m_defaultFont;
    double m_pixelSize;
    double m_pointSize;
    double m_weight;

public:
    static QTypeFace fromStringList(const QStringList &stringList);

    static QLatin1String MetaFunctionName();

    friend QDebug operator<<(QDebug debug, const QTypeFace &tf) {
        debug.noquote().nospace() << "QTypeFace(" << tf.m_color << ", " << tf.m_font << ")";
        return debug;
    }
};

Q_DECLARE_METATYPE(QTypeFace)

#endif // QTYPEFACE_H
