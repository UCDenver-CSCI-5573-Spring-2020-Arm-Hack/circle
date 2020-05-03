//
// Created by kamaroyl on 4/29/2020.
//
#include "Kernel.h"
static const char FromKernel[] = "kernel";
#define NUM_THREADS 100
//From osBench
static void* thread_fun(void* arg) {
    // We do nothing here...
    (*(int*)arg) += 1;
    return (void*)0;
}

static pthread_t  create_thread(int* a) {
    pthread_t  result;
    pthread_create(&result, (const pthread_attr_t*)0, thread_fun, (void*)a);
    return result;
}

static int join_thread(pthread_t thread) {
    return pthread_join(thread, (void**)0);
}
//End osBench
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
    Message.Format("start\n");

    m_Screen.Write(Message, Message.GetLength());
    int a = 0;
    pthread_t threads[NUM_THREADS];

    unsigned shortest = 0xFFFFFFFF;
    unsigned start = m_Timer.GetClockTicks();
    unsigned round_start;
    unsigned diff;
    unsigned i;
    unsigned round_end;
    while((m_Timer.GetClockTicks() - start) < 5 * 1000000) {
        diff = 0xFFFFFFFF;

        round_start = m_Timer.GetClockTicks();
        for ( i= 0; i < NUM_THREADS; ++i) {
            threads[i] = create_thread(&a);
        }
        for (i = 0; i < NUM_THREADS; ++i) {
            join_thread(threads[i]);
            threads[i] = NULL;
        }
        round_end = m_Timer.GetClockTicks();
        diff = round_end - round_start;

        if (shortest > diff) {
            shortest = diff;
        }
    }

    Message.Format("Shortest number of ticks: %u.\n a: %u\n", shortest, a);
    m_Screen.Write(Message, Message.GetLength());
    return ShutdownHalt;
}