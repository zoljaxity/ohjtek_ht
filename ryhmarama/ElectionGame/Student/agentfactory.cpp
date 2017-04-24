#include <QDebug>
#include "agentfactory.h"

namespace Interface
{
    AgentFactory AgentFactory::AGENTFACTORY;

    shared_ptr<Agent> AgentFactory::createAgent()
    {
        shared_ptr<Agent> agent = make_shared<Agent>();
        agent->setName("Agent " + QString::number(++agentsCreated_));
        return agent;
    }

    AgentFactory::AgentFactory(): agentsCreated_(0)
    {}
}
