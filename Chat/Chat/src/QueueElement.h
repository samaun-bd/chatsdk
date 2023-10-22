/* 
 * File:   QueueElement.h
 * Author: dipal
 *
 * Created on August 18, 2015, 4:17 PM
 */

#ifndef QUEUEELEMENT_H
#define	QUEUEELEMENT_H

#include "Scheduler.h"

namespace imsdk {
enum Priority {
    l1,
    l2,
    l3,
    l4,
    l5
};

template <class CLASS_TYPE>
class QueueElement {
public:
    QueueElement(CLASS_TYPE coreElement, long long time, Priority priority = Priority::l1);
    CLASS_TYPE value();
    virtual ~QueueElement();
    
    bool operator < (const QueueElement<CLASS_TYPE> &queueElement) const;
private:
    long long elementTime;
    Priority priority;
    CLASS_TYPE coreElement;
};







/**
 * Template Impl
 */


template <class CLASS_TYPE>
QueueElement<CLASS_TYPE>::QueueElement(CLASS_TYPE coreElement, long long time, Priority priority) {
    this->coreElement = coreElement;
    this->elementTime = time;
    this->priority = priority;
}

template <class CLASS_TYPE>
QueueElement<CLASS_TYPE>::~QueueElement() {
    
}

template <class CLASS_TYPE>
CLASS_TYPE QueueElement<CLASS_TYPE>::value()
{
    return coreElement;
}

template <class CLASS_TYPE>
bool QueueElement<CLASS_TYPE>::operator < (const QueueElement<CLASS_TYPE> &queueElement) const {
    if (priority != queueElement.priority) 
    {
        return priority>queueElement.priority;
    }
    
    return elementTime<queueElement.elementTime;
}
}

#endif	/* QUEUEELEMENT_H */

