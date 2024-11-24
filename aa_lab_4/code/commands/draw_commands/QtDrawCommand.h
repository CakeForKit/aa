#pragma once

#include "BaseDrawCommand.h"
#include "QtDrawer.h"
#include <QGraphicsView>

class QtDrawCommand : public BaseDrawCommand
{
protected:
    QGraphicsView *graphicsView;

public:
    QtDrawCommand() = delete;
    QtDrawCommand(QGraphicsView* gv);
    
    virtual void execute();
};