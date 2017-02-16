#ifndef INFLUENCE_H
#define INFLUENCE_H

#include "cardinterface.h"

namespace Interface
{

class Influence : public CardInterface
{
public:
    Influence(const QString& name, std::weak_ptr<Location> location, unsigned short amount);
    virtual ~Influence() = default;

    virtual QString typeName() const;
    QString name() const;
    QString title() const;
    std::weak_ptr<Location> location() const;

    std::weak_ptr<Player> owner() const;
    void setOwner(std::weak_ptr<Player> owner);

    unsigned short amount() const;

private:
    const QString name_;
    const std::weak_ptr<Location> location_;

    std::weak_ptr<Player> owner_;
    const unsigned short amount_;
};

} // Interface

#endif // INFLUENCE_H
