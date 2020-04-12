//
// Created by kamaroyl on 3/17/2020.
//

#ifndef CIRCLE_MYTASK_H
#define CIRCLE_MYTASK_H
#include <circle/sched/task.h>
#include <circle/sched/scheduler.h>
#include <circle/timer.h>
class CMyTask: public CTask {
    public:
        CMyTask(unsigned taskId, CTimer* timer);
        ~CMyTask(void);
        void Run(void);
        bool isDone(void);
        unsigned getTime(void);
        TTaskState getTaskState(void);
    private:
        CTimer* m_timer;
        unsigned m_time;
        unsigned m_nTaskID;
        bool m_done;
};

#endif //CIRCLE_MYTASK_H
