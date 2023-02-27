#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "assert.h"
#include "state.h"

template<class entity_type>
class StateMachine
{
private:

  entity_type* m_pOwner;

  State<entity_type>* m_pCurrentState;
  State<entity_type>* m_pPreviousState;
  State<entity_type>* m_pGlobalState;

public:
  StateMachine(entity_type* owner):
    m_pOwner(owner),
    m_pCurrentState(nullptr),
    m_pPreviousState(nullptr),
    m_pGlobalState(nullptr)
  {}

  void SetCurrentState(State<entity_type>* s){m_pCurrentState = s;}
  void SetPreviousState(State<entity_type>* s){m_pPreviousState = s;}
  void SetGlobalState(State<entity_type>* s){m_pGlobalState = s;}

  void Update() const
  {

    // if global state exists, execute it
    if (m_pGlobalState) m_pGlobalState->Update(m_pOwner);

    // if current state exists, execute it
    if (m_pCurrentState) m_pCurrentState->Update(m_pOwner);
  }

  void ChangeState(State<entity_type>* pNewState)
  {
    assert(pNewState && "Can not change null state");

    m_pPreviousState = m_pCurrentState;

    m_pCurrentState->Exit(m_pOwner);

    m_pCurrentState = pNewState;

    m_pCurrentState->Enter(m_pOwner);
  }

  // For global blip states, revert to previous state when done
  void RevertToPreviousState()
  {
    ChangeState(m_pPreviousState);
  }

  bool isInState(const State<entity_type>& st) const;
};

#endif
