#ifndef AGENT_H
#define AGENT_H

#include "agentinterface.h"

#include <QObject>

namespace Interface
{
class Player;
}

using std::shared_ptr;

class Agent: public QObject, public Interface::AgentInterface
{
    Q_OBJECT
public:
    static const QString COMMON_NAME;

    static shared_ptr<Agent> commonAgent();

    Agent(const QString& name, const QString& title, std::weak_ptr<Interface::Location> location);
    virtual ~Agent() = default;

    virtual QString typeName() const;
    virtual QString name() const;
    virtual QString title() const;
    virtual std::weak_ptr<Interface::Location> location() const;

    virtual std::weak_ptr<Interface::Player> owner() const;
    virtual void setOwner(std::weak_ptr<Interface::Player> owner);

    virtual bool isCommon() const;

    virtual std::weak_ptr<Interface::Location> placement() const;
    virtual void setPlacement(std::weak_ptr<Interface::Location> placement);
    virtual unsigned short connections() const;
    virtual void setConnections(unsigned short connections);
    virtual void modifyConnections(short amount);

signals:
    void connectionsChanged() const;

private:
    const QString name_;
    const QString title_;
    const std::weak_ptr<Interface::Location> location_;

    std::weak_ptr<Interface::Player> owner_;
    std::weak_ptr<Interface::Location> placement_;
    unsigned short connections_;
};

#endif // AGENT_H
