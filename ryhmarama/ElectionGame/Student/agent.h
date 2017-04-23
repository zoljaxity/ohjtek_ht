#ifndef AGENT_H
#define AGENT_H

#include "agentinterface.h"

namespace Interface
{
class Player;
}

class Agent: public Interface::AgentInterface
{
public:
    virtual ~Agent() = default;

    virtual QString typeName() const;
    virtual QString name() const;
    virtual QString title() const;
    virtual std::weak_ptr<Interface::Location> location() const;

    virtual std::weak_ptr<Interface::Player> owner() const;
    void setOwner(std::weak_ptr<Interface::Player> owner);

    virtual bool isCommon() const;

    virtual std::weak_ptr<Interface::Location> placement() const;
    virtual void setPlacement(std::weak_ptr<Interface::Location> placement);
    virtual unsigned short connections() const;
    virtual void setConnections(unsigned short connections);
    virtual void modifyConnections(short amount);

private:
    std::weak_ptr<Interface::Location> location_;
    std::weak_ptr<Interface::Player> owner_;
    unsigned short connections_;
};

#endif // AGENT_H
