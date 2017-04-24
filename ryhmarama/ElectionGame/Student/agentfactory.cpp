#include <QDebug>
#include "agentfactory.h"

namespace Interface
{
    AgentFactory AgentFactory::AGENTFACTORY;

    AgentFactory::AgentFactory(): agentsCreated_(0)
    {}

    shared_ptr<Agent> AgentFactory::createAgent()
    {
        shared_ptr<Agent> agent = make_shared<Agent>();
        agent->setName("Agent " + QString::number(++agentsCreated_));
        return agent;
    }
}
