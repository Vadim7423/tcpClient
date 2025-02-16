#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QString>

class Protocol
{
public:
    virtual ~Protocol() = default;
    virtual void recieve(const std::string& str) = 0;
};

#endif // PROTOCOL_H
