#include "agent.h"
#include "location.h"
#include "player.h"
#include "game.h"

#include <QSignalSpy>
#include <QtTest>

using Interface::Location;
using Interface::Player;
using Interface::Game;
using std::shared_ptr;
using std::make_shared;

class TestAgent : public QObject
{
    Q_OBJECT

public:
    TestAgent();


private:
    Agent *agent;

private Q_SLOTS:
    void initTestCase();
    void typeName();
    void name();
    void title();
    void locationAndPlacement();
    void setPlacement();
    void owner();
    void isCommon();
    void connections();
    void setConnections();
    void modifyConnections();
    void canAct();
};

TestAgent::TestAgent()
{
}

void TestAgent::initTestCase()
{
    agent = new Agent();
}

void TestAgent::typeName()
{
    QCOMPARE(agent->typeName(), QString("Agent"));
}

void TestAgent::name()
{

    QCOMPARE(agent->name(), QString(""));
    agent->setName("Player 1");
    QCOMPARE(agent->name(), QString("Player 1"));
    agent->setName("Really really really really really loooong name");
    QCOMPARE(
        agent->name(),
        QString("Really really really really really loooong name")
    );
}

void TestAgent::title()
{
    QCOMPARE(agent->title(), QString(""));
}

void TestAgent::locationAndPlacement()
{
    QVERIFY2(
        agent->location().lock() == nullptr,
        "Failure: location should initially be nullptr"
    );

    QVERIFY2(
        agent->placement().lock() == nullptr,
        "Failure: placement should initially be nullptr"
    );
}

void TestAgent::setPlacement()
{
    shared_ptr<Location> location = make_shared<Location>(1, "testlocation");
    agent->setPlacement(location);

    QCOMPARE(agent->location().lock(), location);
    QCOMPARE(agent->location().lock()->name(), QString("testlocation"));
    QCOMPARE(agent->placement().lock(), location);
    QCOMPARE(agent->placement().lock()->name(), QString("testlocation"));
}

void TestAgent::owner()
{
    QVERIFY2(
        agent->owner().lock() == nullptr,
        "Failure: owner should initially be nullptr"
    );

    shared_ptr<Player> player = make_shared<Player>(shared_ptr<Game>(), 0, "Player 1");
    agent->setOwner(player);
    QCOMPARE(agent->owner().lock(), player);
    QCOMPARE(agent->owner().lock()->name(), QString("Player 1"));
}

void TestAgent::isCommon()
{
    QVERIFY2(agent->isCommon(), "Agent should initially be common");
    shared_ptr<Location> location2 = make_shared<Location>(1, "testlocation 2");
    agent->setPlacement(location2);
    QCOMPARE(agent->isCommon(), false);
}

void TestAgent::connections()
{
    unsigned short initialConnections = 0;
    QCOMPARE(agent->connections(), initialConnections);
}

void TestAgent::setConnections()
{

    agent->setConnections(1);
    unsigned short expectedValue = 1;
    QCOMPARE(agent->connections(), expectedValue);

    agent->setConnections(65535);
    expectedValue = 65535; // Max for unsigned short
    QCOMPARE(agent->connections(), expectedValue);

    agent->setConnections(0);
    expectedValue = 0;
    QCOMPARE(agent->connections(), expectedValue);
}
void TestAgent::modifyConnections()
{

    agent->modifyConnections(1);
    unsigned short expectedValue = 1;
    QCOMPARE(agent->connections(), expectedValue);

    agent->modifyConnections(123);
    expectedValue = 124;
    QCOMPARE(agent->connections(), expectedValue);

    agent->modifyConnections(0);
    QCOMPARE(agent->connections(), expectedValue);
}

void TestAgent::canAct()
{
    QCOMPARE(agent->canAct(), false);
    agent->setCanAct(true);
    QVERIFY2(agent->canAct(), "canAct() should return true after setCanAct(true)");
    agent->setCanAct(false);
    QCOMPARE(agent->canAct(), false);
}

QTEST_APPLESS_MAIN(TestAgent)

#include "tst_testagent.moc"
