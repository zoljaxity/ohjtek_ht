#ifndef CARD_H
#define CARD_H

#include <QString>

#include <memory>

namespace Interface
{

class Location;
class Player;

class CardInterface
{
public:
    CardInterface() = default;
    virtual ~CardInterface() = default;

    virtual QString typeName() const = 0;
    virtual QString name() const = 0;
    virtual QString title() const = 0;
    virtual std::weak_ptr<Location> location() const = 0;

    virtual std::weak_ptr<Player> owner() const = 0;
    virtual void setOwner(std::weak_ptr<Player> owner) = 0;
};

} // Interface

#endif // CARD_H
