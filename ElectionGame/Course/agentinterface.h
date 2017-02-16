#ifndef AgentInterface_H
#define AgentInterface_H

#include "cardinterface.h"

namespace Interface
{

class AgentInterface: public CardInterface
{
public:
    AgentInterface() = default;
    virtual ~AgentInterface() = default;

    virtual bool isCommon() const = 0;

    virtual std::weak_ptr<Location> placement() const = 0;
    virtual void setPlacement(std::weak_ptr<Location> placement) = 0;

    virtual unsigned short connections() const = 0;
    virtual void setConnections(unsigned short connections) = 0;
    virtual void modifyConnections(short change) = 0;
};

} // Interface

#endif // AgentInterface_H
