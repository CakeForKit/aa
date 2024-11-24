#include "CompositeObjectScene.h"

// при срздании надо добавлять Default() как последнюю переменную
// Пример: make_shared<Composite>(make_shared<Figure>(), composite1, Default());
CompositeObjectScene::CompositeObjectScene(PtrObjectScene first, ...)
{
    for (std::shared_ptr<ObjectScene>* ptr = &first; *ptr; ++ptr)
        vec.push_back(*ptr);
}

bool CompositeObjectScene::isComposite() const { return true; }

bool CompositeObjectScene::add(std::initializer_list<PtrObjectScene> list)
{
    for (auto elem: list)
        vec.push_back(elem);
    return true;
}

bool CompositeObjectScene::remove(const iterator& it)
{
    vec.erase(it);
    return true;
}

CompositeObjectScene::iterator CompositeObjectScene::begin() const
{
    return vec.begin();
}

CompositeObjectScene::iterator CompositeObjectScene::end() const
{
    return vec.end();
}
