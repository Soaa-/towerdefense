#include "critter.h"
#include "subject.h"
#include "observer.h"
#include "critterobserver.h"

CritterObserver::CritterObserver(){
}

CritterObserver::CritterObserver(Critter* critter){
    critterSubject = critter;

    towerSubject->Attach(this);
}
CritterObserver::~CritterObserver(){
    critterSubject->Detach(this);
}

void CritterObserver::Update(){
    //Todo
}

