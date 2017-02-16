#ifndef DECKINTERFACE_H
#define DECKINTERFACE_H

#include <memory>

namespace Interface
{

class CardInterface;

class DeckInterface
{
public:
    DeckInterface() = default;
    virtual ~DeckInterface() = default;

    virtual unsigned int size() const = 0;
    virtual std::shared_ptr<const CardInterface> cardAt(unsigned int i) const = 0;
    virtual std::shared_ptr<CardInterface> cardAt(unsigned int i) = 0;
    virtual bool canDraw() const = 0;
    virtual bool visible() const = 0;

    virtual void addCard(std::shared_ptr<CardInterface> card, bool toBottom = false) = 0;
    virtual std::shared_ptr<CardInterface> draw() = 0;
    virtual std::shared_ptr<const CardInterface> peek() const = 0;
    virtual std::shared_ptr<CardInterface> peek() = 0;
    virtual void shuffle() = 0;
};

} // Interface

#endif // DECKINTERFACE_H
