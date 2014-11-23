#include "towerobserver.h"
#include "tower.h"
#include "subject.h"
#include "observer.h"

TowerObserver::TowerObserver(){
}

TowerObserver::TowerObserver(Tower* tower){
    towerSubject = tower;
    towerSubject->Attach(this);
}

TowerObserver::~TowerObserver(){
    towerSubject->Detach(this);
}

void TowerObserver::Update(){
    //Update tower display window
}

