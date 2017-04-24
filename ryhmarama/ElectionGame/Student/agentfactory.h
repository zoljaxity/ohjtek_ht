#ifndef AGENTFACTORY_H
#define AGENTFACTORY_H

#include "agent.h"

using std::make_shared;
using std::shared_ptr;

namespace Interface
{
    class AgentFactory
    {
        public:
            static AgentFactory AGENTFACTORY;
            shared_ptr<Agent> createAgent();
            ~AgentFactory() = default;

        private:
            AgentFactory();
            QString createName();
            int agentsCreated_;
    };
} // namespace
#endif // AGENTFACTORY_H
