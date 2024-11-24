#include "ObjectScene.h"


std::ostream& operator<<(std::ostream &os, const ObjectScene &model) {
    return model.print(os);
}

bool ObjectScene::isComposite() const
{
    return false;
}

bool ObjectScene::add(std::initializer_list<PtrObjectScene> comp) 
{ 
    (void) comp;
    return false; 
}

bool ObjectScene::remove(const iterator& it) 
{ 
    (void) it;
    return false; 
}

ObjectScene::iterator ObjectScene::begin() const 
{ 
    return iterator(); 
}

ObjectScene::iterator ObjectScene::end() const 
{ 
    return iterator(); 
}