#ifndef CRITTEROBSERVER_H
#define CRITTEROBSERVER_H

class CritterObserver : public Observer
{
    public:
        CritterObserver();
        //Creates CritterObserver, which takes as parameter a pointer to the Critter subject it will observe
        CritterObserver(Critter* critter);
        //Upon destruction of CritterObserver, removes this CritterObserver from list of Observers observing a particular critter
        ~CritterObserver();
        void Update();


    private:
        Critter *critterSubject;
};

#endif // CRITTEROBSERVER_H
