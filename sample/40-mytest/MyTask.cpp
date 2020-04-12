//
// Created by kamaroyl on 3/18/2020.
//
#include "MyTask.h"

CMyTask::CMyTask(unsigned taskId, CTimer* timer):
    m_timer(timer),
    m_time(0),
    m_nTaskID(taskId),
    m_done(false) {
}

CMyTask::~CMyTask() {
    m_timer = 0;
}

void CMyTask::Run() {
    unsigned start = m_timer->GetTicks();
    m_done = true;
    unsigned end = m_timer->GetTicks();
    m_time = end - start;
    this->Terminate();
}

TTaskState CMyTask::getTaskState() {
    return this->GetState();
}

bool CMyTask::isDone() {
    return m_done;
}

unsigned CMyTask::getTime() {
    return m_time;
}
