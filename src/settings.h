#ifndef SETTINGS_H
#define SETTINGS_H
#define GFONT "GFONTTYPE"  // group -> &g
#define KFONTTYPE "KFONTTYPE"  // key -> &k
#define KFONTSIZE "KFONTSIZE"  // key -> &k the group is the same
#include <QString>
#include <QVariant>

// upload settings
QVariant settingsLoad(const QString &g, const QString &k, const QVariant &vd = QVariant());

// save settings
void settingsSave(const QString &g, const QString &k, const QVariant &v);



#endif // SETTINGS_H

