#ifndef TOWEROBSERVER_H
#define TOWEROBSERVER_H

class TowerObserver : public Observer
{
    public:
        TowerObserver();
        //Creates TowerObserver, which takes as parameter a pointer to the Tower subject it will observe
        TowerObserver(Tower* tower);
        //Upon destruction of TowerObserver, removes this TowerObserver from list of Observers observing a particular Tower
        ~TowerObserver();

        //Is called when Tower (concrete Subject) calls Nofity(), and prints new Tower attributes
        void Update();


    private:
        Tower *towerSubject;//Tower being observed
};

#endif // TOWEROBSERVER_H
