#pragma once

#include "BaseCommand.h"
#include "QtDrawer.h"
#include <QGraphicsView>

class DrawTimeCommand : public BaseCommand
{
protected:
    QGraphicsView *graphicsView;
    char *filename;

public:
    DrawTimeCommand() = delete;
    DrawTimeCommand(QGraphicsView* gv, char *_filename);
    
    virtual void execute();
};