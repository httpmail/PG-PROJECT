#pragma once

namespace PG {
    class State {
    public:
        State():
            m_bSwitchable(false)
        {
        }
        virtual ~State() {}

        virtual bool Enter()    = 0;
        virtual bool Update()   = 0;
        virtual bool Exit()     = 0;

        bool Switchable() const { return m_bSwitchable; }
        void SetSwitchable(bool switchable = true) { m_bSwitchable = switchable; }

    private:
        bool m_bSwitchable;
    };
}