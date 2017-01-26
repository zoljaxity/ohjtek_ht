#ifndef LOCATION_H
#define LOCATION_H

#include <QObject>
#include <QString>

#include <map>
#include <memory>
#include <set>

namespace Interface
{

class AgentInterface;
class Councilor;
class DeckInterface;
class Player;

class Location: public QObject, public std::enable_shared_from_this<Location>
{
    Q_OBJECT
public:
    Location(unsigned short id, const QString& name);
    virtual ~Location() = default;

    virtual void initialize();

    unsigned short id() const;
    QString name() const;

    std::shared_ptr<const DeckInterface> deck() const;
    std::shared_ptr<DeckInterface> deck();
    std::shared_ptr<const DeckInterface> discards() const;
    std::shared_ptr<DeckInterface> discards();

    std::set<std::shared_ptr<const AgentInterface> > agents() const;
    std::set<std::shared_ptr<AgentInterface> > agents();
    virtual bool canSendAgent(std::shared_ptr<const Player> owner) const;
    virtual void sendAgent(std::shared_ptr<AgentInterface> agent);
    virtual void removeAgent(std::shared_ptr<AgentInterface> agent);

    std::shared_ptr<const Councilor> councilor() const;
    std::shared_ptr<Councilor> councilor();
    void setCouncilor(std::shared_ptr<Councilor> councilor);

    unsigned short influence(std::shared_ptr<const Player> owner) const;
    void setInfluence(std::shared_ptr<const Player> owner, unsigned short influence);

signals:
    void agentsChanged(std::shared_ptr<const Location> location) const;
    void influenceChanged(std::shared_ptr<const Location> location) const;
    void deckChanged(std::shared_ptr<const Location> location) const;
    void discardsChanged(std::shared_ptr<const Location> location) const;

private:
    const unsigned short id_;
    const QString name_;

    std::shared_ptr<DeckInterface> deck_;
    std::shared_ptr<DeckInterface> discards_;

    std::set<std::shared_ptr<AgentInterface> > agents_;

    std::shared_ptr<Councilor> councilor_;

    std::map<unsigned short, unsigned short> influence_;

private slots:
    void updateAgents();
    void updateDeck();
    void updateDiscards();
};

} // Interface

#endif // LOCATION_H
