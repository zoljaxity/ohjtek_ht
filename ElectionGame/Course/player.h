#ifndef PLAYER_H
#define PLAYER_H

#include <QString>

#include <memory>
#include <vector>

namespace Interface
{

class CardInterface;
class Councilor;
class Game;

class Player: public std::enable_shared_from_this<Player>
{
public:
    Player(std::weak_ptr<Interface::Game> game, unsigned short id, const QString& name);
    virtual ~Player() = default;

    virtual unsigned short id() const;
    virtual QString name() const;

    virtual std::shared_ptr<const Interface::Councilor> councilor() const;
    virtual std::shared_ptr<Interface::Councilor> councilor();
    virtual void setCouncilor(std::shared_ptr<Interface::Councilor> councilor);

    virtual std::vector<std::shared_ptr<const Interface::CardInterface> > cards() const;
    virtual std::vector<std::shared_ptr<Interface::CardInterface> > cards();
    virtual void addCard(std::shared_ptr<Interface::CardInterface> card);
    virtual void playCard(std::shared_ptr<const Interface::CardInterface> card);

private:
    const std::weak_ptr<Interface::Game> game_;

    const unsigned short id_;
    const QString name_;

    std::shared_ptr<Interface::Councilor> councilor_;
    std::vector<std::shared_ptr<Interface::CardInterface> > cards_;
};

} // Interface

#endif // PLAYER_H
