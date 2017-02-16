#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QString>

#include <memory>
#include <vector>

namespace Interface
{

class DeckInterface;
class Location;
class Player;

class Game: public QObject, public std::enable_shared_from_this<Game>
{
    Q_OBJECT
public:
	Game();
	virtual ~Game() = default;

    std::vector<std::shared_ptr<const Interface::Player> > players() const;
    std::vector<std::shared_ptr<Interface::Player> > players();
    std::vector<std::shared_ptr<const Location> > locations() const;
    std::vector<std::shared_ptr<Location> > locations();
    std::shared_ptr<const DeckInterface> councilorDeck() const;
    std::shared_ptr<DeckInterface> councilorDeck();

    std::shared_ptr<const Player> currentPlayer() const;
    std::shared_ptr<Interface::Player> currentPlayer();

    void addLocation(std::shared_ptr<Location> location);
    std::shared_ptr<Player> addPlayer(const QString& name);

    virtual void nextPlayer();

    void notify(std::shared_ptr<const Interface::Player> prevPlayer = nullptr) const;

signals:
    void playerChanged(std::shared_ptr<const Player> actingPlayer) const;
    void councilorDeckChanged() const;

private:
    std::vector<std::shared_ptr<Player> > players_;
    std::vector<std::shared_ptr<Location> > locations_;
    std::shared_ptr<DeckInterface> councilorDeck_;

    unsigned short currentPlayer_;

private slots:
    void updateCouncilors();
};

} // Interface

#endif // GAME_H
