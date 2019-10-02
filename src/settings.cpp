#include "settings.h"
#include <QSettings>

QVariant settingsLoad(const QString &g, const QString &k, const QVariant &vd)
{
    QSettings L;
    L.beginGroup(g);
    auto val = L.value(k, vd);
    L.endGroup();
    return val;

}

void settingsSave(const QString &g, const QString &k, const QVariant &v)
{
    QSettings S;
    S.beginGroup(g);
    S.setValue(k, v);
    S.endGroup();
    // return val;

}

