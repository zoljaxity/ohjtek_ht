#include <QDebug>
#include "agent.h"
#include "agentinterface.h"
#include "player.h"
#include "locationdata.h"

using std::shared_ptr;

namespace Interface
{
class Player;
}

QString Agent::typeName() const {
    return "Agent";
}
QString Agent::name() const {
    return name_;
}
QString Agent::title() const {
    return "";
}
std::weak_ptr<Interface::Location> Agent::location() const {
    return location_;
}

std::weak_ptr<Interface::Player> Agent::owner() const {
    return owner_;
}
void Agent::setOwner(std::weak_ptr<Interface::Player> owner) {
    owner_ = owner;
}

bool Agent::isCommon() const {
    if (location_.lock()) {
        return false;
    }
    return true;
}

std::weak_ptr<Interface::Location> Agent::placement() const {
    return location_;
}
void Agent::setPlacement(std::weak_ptr<Interface::Location> placement) {
    location_ = placement;
}
unsigned short Agent::connections() const {
    return connections_;
}
void Agent::setConnections(unsigned short connections){
    connections_ = connections;
}
void Agent::modifyConnections(short amount){
    if (connections_ + amount >= 0) {
        connections_ += amount;
    } else {
        connections_ = 0;
    }
}

void Agent::setName(QString name)
{
    qDebug() << "jebule:" << name;
    name_ = name;
}


