/* 
 * File:   DataSentReceived.h
 * Author: towhid
 *
 * Created on August 1, 2016, 10:42 AM
 */

#ifndef DATACOUNTER_H
#define	DATACOUNTER_H

namespace imsdk{
    class DataCounter{
    public:
        DataCounter();
        DataCounter(long long dataSent, long long DataReceived);
        ~DataCounter();
        void setDataReceived(long long dataReceived);
        long long getDataReceived() const;
        void setDataSent(long long dataSent);
        long long getDataSent() const;
        void addDataSent(long long dataAdded);
        void addDataReceived(long long dataReceived);

    private:
        long long dataSent{0};
        long long dataReceived{0};
    };
}
#endif	/* DATACOUNTER_H */

