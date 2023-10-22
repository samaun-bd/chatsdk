#include "DataCounter.h"

namespace imsdk{

    DataCounter::DataCounter(long long dataSent, long long dataReceived) {
        this->dataSent = dataSent;
        this->dataReceived = dataReceived;
    }
        DataCounter::DataCounter() {
    }
    
    DataCounter::~DataCounter(){
        
    }
    
    void DataCounter::setDataReceived(long long dataReceived) {
        this->dataReceived = dataReceived;
    }

    long long DataCounter::getDataReceived() const {
        return dataReceived;
    }

    void DataCounter::setDataSent(long long dataSent) {
        this->dataSent = dataSent;
    }

    long long DataCounter::getDataSent() const {
        return dataSent;
    }
    
    void DataCounter::addDataReceived(long long dataReceived) {
        this->dataReceived += dataReceived;
    }
    
    void DataCounter::addDataSent(long long dataSent) {
        this->dataSent += dataSent;
    }
}
