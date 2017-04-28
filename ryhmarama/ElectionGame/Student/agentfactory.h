#ifndef AGENTFACTORY_H
#define AGENTFACTORY_H

#include "agent.h"

using std::make_shared;
using std::shared_ptr;

/**
 * @file
 * @brief Agenttitehdasta kuvaava luokka
 */

namespace Interface
{

/**
 * @brief AgentFactory on singleton, joka tuottaa aina eri nimisen agentin
 *
 * Jos luokan metodi ei ole poikkeustakuultaan nothrow, voi metodista aina vuotaa ulos poikkeus `std::bad_alloc` (muisti loppui).
 */
    class AgentFactory
    {
        public:

            /**
             * @brief AgentFactory singleton-olio
             */
            static AgentFactory AGENTFACTORY;

            /**
             * @brief purkaja
             */
            ~AgentFactory() = default;

            /**
             * @brief createAgent tuottaa uuden agentin uniikilla nimellä
             * @pre -
             * @return osoitin luotuun agenttiin
             * @post Poikkeustakuu: vahva
             */
            shared_ptr<Agent> createAgent();


        private:
            AgentFactory();
            QString createName();
            int agentsCreated_;
    };
} // namespace
#endif // AGENTFACTORY_H
