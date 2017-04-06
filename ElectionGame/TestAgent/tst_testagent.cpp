#include "agent.h"
#include "location.h"

#include <QSignalSpy>
#include <QtTest>

class TestAgent : public QObject
{
    Q_OBJECT

public:
    TestAgent();

private Q_SLOTS:
    void testCase1();
};

TestAgent::TestAgent()
{
}

void TestAgent::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestAgent)

#include "tst_testagent.moc"
