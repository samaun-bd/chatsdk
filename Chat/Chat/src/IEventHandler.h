/* 
 * File:   IEventHandler.h
 * Author: dipal
 *
 * Created on August 18, 2015, 1:22 PM
 */

#ifndef IEVENTHANDLER_H
#define	IEVENTHANDLER_H

namespace imsdk {
template <class CLASS_TYPE>
class IEventHandler {
public:
    IEventHandler();
    virtual ~IEventHandler();
    virtual void notify(CLASS_TYPE)=0;
};
}

#endif	/* IEVENTHANDLER_H */

