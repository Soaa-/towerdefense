#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"

class Subject
{
    public:
        Subject(){
            observers = new list<Observer*>;
        }
        ~Subject(){
            delete observers;
        }

        //Pushes Observer onto end of list of Observers
        virtual void Attach(Observer* observer){
            observers->push_back(observer);
        }

        //Removes Observer from list of Observers
        virtual void Detach(Observer* observer){
            observers->remove(observer);
        }

        //Notify all Observers of a change
        virtual void Notify(){
            //iterate through list of Observers, calling each Observer's Update() method
            list<Observer *>::iterator i = observers->begin();
            for (; i != observers->end(); ++i)
              (*i)->Update();
        }

    private:
        //List of Observers for particular instance of a Subject
        list<Observer*> *observers;

};

#endif // SUBJECT_H
