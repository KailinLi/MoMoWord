#include "wordentry.h"

WordEntry::WordEntry(int wid, const QString &word,
                     const QString &phonogram, const QString &translation, bool is_new):
    wid(wid),
    word(word),
    phonogram(phonogram),
    translation(translation),
    is_new(is_new),
    count(1),
    first_time(true)
{

}
