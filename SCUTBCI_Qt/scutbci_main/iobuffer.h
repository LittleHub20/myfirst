#ifndef IOBUFFER_H
#define IOBUFFER_H

#include <QObject>
#include <QMutex>
#include <QByteArray>

class IOBuffer : public QByteArray
{
protected:
    QMutex mutex;
public:
    void write(char* buff)
    {
        write(buff, qstrlen(buff));
    }

    void write(char* buff, int len)
    {
        mutex.lock();
        append(buff, len);
        mutex.unlock();
    }

    void write(QByteArray buff)
    {
        mutex.lock();
        append(buff);
        mutex.unlock();
    }

    int read(char* buff, int len)
    {
        mutex.lock();
        int bytesRead = length() > len ? len : length();
        memcpy(buff, data(), bytesRead);
        remove(0, bytesRead);
        mutex.unlock();
        return bytesRead;
    }
};
Q_DECLARE_METATYPE(IOBuffer*)

#endif // IOBUFFER_H
