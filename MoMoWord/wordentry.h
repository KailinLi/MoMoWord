#ifndef WORDENTRY_H
#define WORDENTRY_H

#include <QString>


class WordEntry
{
public:
    WordEntry(int wid, const QString &word, const QString &phonogram,
              const QString &translation, bool is_new);
    int wid;
    QString word;
    QString phonogram;
    QString translation;
    bool is_new;
    int count;
    bool first_time;
};

#endif // WORDENTRY_H
