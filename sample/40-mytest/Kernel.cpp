//
// Created by kamaroyl on 3/19/2020.
//
#include "Kernel.h"

static const char FromKernel[] = "kernel";

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
    unsigned taskCount = 100;
    CMyTask* tasks[100];
    unsigned shortest = 0xFFFFFFFF;
    unsigned start = m_Timer.GetClockTicks();
  //  Message.Format("Main ****\n");
   // m_Screen.Write (Message, Message.GetLength());

    while((m_Timer.GetClockTicks() - start) < 5 * 1000000) {
        unsigned round_start = m_Timer.GetClockTicks();
        unsigned diff = 0xFFFFFFFF;


        for(unsigned i = 0; i < taskCount; ++i) {
            CMyTask* myTask = new CMyTask(i, &m_Timer);
            tasks[i] = myTask;
        }

        for(unsigned i = 0; i < taskCount; ++i){
      //      Message.Format("Waiting for termination of task %d\n", i);
      //      m_Screen.Write (Message, Message.GetLength());
            if(tasks[i]->getTaskState() != TaskStateTerminated) {
                tasks[i]->WaitForTermination();
            }
        }
        for(unsigned i = 0; i < taskCount; ++i){

            m_Scheduler.RemoveTask(tasks[i]);
            tasks[i]->~CMyTask();
        }
        Message.Format("\n");
        m_Screen.Write (Message, Message.GetLength());
        unsigned round_end = m_Timer.GetClockTicks();
        diff = round_end - round_start;
     //   Message.Format("Time took this round was %d\n", diff);
     //   m_Screen.Write (Message, Message.GetLength());
        if(shortest > diff) {
            shortest = diff;
        }
    }

    Message.Format("Shortest number of ticks: %u.\n", shortest);

    m_Screen.Write(Message, Message.GetLength());
    return ShutdownHalt;
}

void CKernel::TimerHandler (TKernelTimerHandle hTimer, void *pParam, void *pContext)
{
    CKernel *pThis = (CKernel *) pParam;
    assert (pThis != 0);

    pThis->m_Event.Set();
}