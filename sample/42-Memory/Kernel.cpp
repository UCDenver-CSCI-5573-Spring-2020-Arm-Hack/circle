//
// Created by kamaroyl on 4/29/2020.
//
#include "Kernel.h"
static const char FromKernel[] = "kernel";
#define NUM_ALLOCS 500000
static void* s_addresses[NUM_ALLOCS];
CKernel::CKernel(void):
        m_Screen (m_Options.GetWidth (), m_Options.GetHeight ()),
        m_Timer (&m_Interrupt),
        m_Logger (m_Options.GetLogLevel (), &m_Timer) {
        m_ActLED.Blink (5);	// show we are alive
}

CKernel::~CKernel(void) {
}

boolean CKernel::Initialize(void) {
    boolean bOK = TRUE;

    if (bOK) {
        bOK = m_Screen.Initialize ();
    }

    if (bOK) {
        CDevice *pTarget = m_DeviceNameService.GetDevice(m_Options.GetLogDevice(), FALSE);
        if (pTarget == 0) {
            pTarget = &m_Screen;
        }

        bOK = m_Logger.Initialize(pTarget);
    }

    if (bOK) {
        bOK = m_Interrupt.Initialize();
    }

    if (bOK) {
        bOK = m_Timer.Initialize ();
    }

    return bOK;
}

TShutdownMode CKernel::Run(void) {
    CString Message;
    Message.Format("start %u\n", 1);

    m_Screen.Write(Message, Message.GetLength());
    unsigned shortest = 0xFFFFFFFF;
    unsigned start = m_Timer.GetClockTicks();
    unsigned round_start;
    unsigned diff;
    unsigned i;
    unsigned round_end;
    unsigned mem_size;
    while((m_Timer.GetClockTicks() - start) < 5 * 1000000) {
        diff = 0xFFFFFFFF;
        //unsigned long x = 0;
        round_start = m_Timer.GetClockTicks();
        for ( i= 0; i < NUM_ALLOCS; ++i) {
            mem_size = ((i % 32) + 1) * 4;
           // x += mem_size;
            /*if (i % 10000 == 0) {
                Message.Format("Number:%u, Memory Left: %u, Memory Size: %u\n", i, m_Memory.GetHeapFreeSpace(0), x);
                m_Screen.Write(Message, Message.GetLength());
            }*/
            s_addresses[i] = malloc(mem_size);
            ((char *) s_addresses[i])[0] = 1;
        }
        for (i = 0; i < NUM_ALLOCS; ++i) {
            free(s_addresses[i]);
        }
        //Message.Format("\n");
       // m_Screen.Write(Message, Message.GetLength());
       round_end = m_Timer.GetClockTicks();
        diff = round_end - round_start;

        if (shortest > diff) {
            shortest = diff;
        }
    }
    //

    //}

    Message.Format("Shortest number of ticks: %u.\n", shortest);

    m_Screen.Write(Message, Message.GetLength());
    return ShutdownHalt;
}
