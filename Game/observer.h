#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
    public:
        ~Observer();
        virtual void Update() = 0;
    protected:
        Observer();
};

#endif // OBSERVER_H
