/* 
 * File:   EventProcessor.h
 * Author: dipal
 *
 * Created on August 18, 2015, 1:12 PM
 */

#ifndef EVENTPROCESSOR_H
#define	EVENTPROCESSOR_H

#include "ChatEvent.h"
#include "Processor.h"
#include "Scheduler.h"
#include "Types.h"
#include <memory>
#include "IChatEventHandler.h"
#include "DuplicateChecker.h"
#include <sstream>
#include <queue>
#include <unordered_map>
#include <set>


namespace imsdk {
class EventProcessor : public Processor<ChatEvent> {
public:
    
    virtual ~EventProcessor();

    static EventProcessor& getInstance();

    void setEventHandler(std::shared_ptr< IChatEventHandler> eventHandler);
    void unsetEventHandler();
    
    void clear();
    
    void run();
    void onThreadStopped();
    
private:
    EventProcessor();
    std::shared_ptr< IChatEventHandler> eventHandler{nullptr};
    DuplicateChecker duplicateChecker;
};
}

#endif	/* EVENTPROCESSOR_H */

