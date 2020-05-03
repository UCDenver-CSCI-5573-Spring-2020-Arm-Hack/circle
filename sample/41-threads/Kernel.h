//
// Created by kamaroyl on 5/1/2020.
//

#ifndef CIRCLE_KERNEL_H
#define CIRCLE_KERNEL_H

#include <circle/memory.h>
#include <circle/actled.h>
#include <circle/koptions.h>
#include <circle/devicenameservice.h>
#include <circle/screen.h>
#include <circle/exceptionhandler.h>
#include <circle/interrupt.h>
#include <circle/timer.h>
#include <circle/logger.h>
#include <circle/sched/scheduler.h>
#include <circle/sched/synchronizationevent.h>
#include <circle/types.h>
#include <linux/pthread.h>


enum TShutdownMode
{
    ShutdownNone,
    ShutdownHalt,
    ShutdownReboot
};

class CKernel
{
public:
    CKernel (void);
    ~CKernel (void);

    boolean Initialize (void);

    TShutdownMode Run (void);

private:
    // do not change this order
    CMemorySystem		    m_Memory;
    CActLED			        m_ActLED;
    CKernelOptions		    m_Options;
    CDeviceNameService	    m_DeviceNameService;
    CScreenDevice		    m_Screen;
    CExceptionHandler	    m_ExceptionHandler;
    CInterruptSystem	    m_Interrupt;
    CTimer			        m_Timer;
    CLogger			        m_Logger;

    CScheduler		        m_Scheduler;
    CSynchronizationEvent	m_Event;

};

#endif //CIRCLE_KERNEL_H
