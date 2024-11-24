#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parant) : QMainWindow(parant), facade(FacadeScene()) {
    ui.setupUi(this);

    graphicsView = new MyQGraphicsView(ui.centralwidget);
    ui.layoutForGraphicsView->addWidget(graphicsView);

    connect(ui.loadModelBtn, &QPushButton::clicked, this, &MainWindow::onLoadModelBtnClicked);
    connect(ui.drawBtn, &QPushButton::clicked, this, &MainWindow::onDrawBtnClicked);
    connect(ui.moveModelBtn, &QPushButton::clicked, this, &MainWindow::onMoveModelBtnClicked);
    connect(ui.rotateModelBtn, &QPushButton::clicked, this, &MainWindow::onRotateModelBtnClicked);
    connect(ui.rotateOXCameraBtn, &QPushButton::clicked, this, &MainWindow::onRotateOXCameraBtnClicked);
    connect(ui.rotateOYCameraBtn, &QPushButton::clicked, this, &MainWindow::onRotateOYCameraBtnClicked);
}

void MainWindow::onLoadModelBtnClicked() {
    std::cout << "onLoadModelBtnClicked: ------------" <<std::endl;

    char filename[] = "/home/kathrine/cg_cp/data/test_model_4.txt";
    char filename2[] = "/home/kathrine/cg_cp/data/pawn.txt";
    
    TrianglesModelLoadCommand load_command(&(filename[0]), STEP_OF_REVOLVING, idMaterial::BLUE);
    facade.execute(load_command);

    TrianglesModelLoadCommand load_command2(&(filename2[0]), STEP_OF_REVOLVING, idMaterial::RED);
    facade.execute(load_command2);


    // size_t stepOfRevolving = 6;
    // std::vector<MoveModelCommand> moveCmds;
    // moveCmds.push_back(MoveModelCommand(0, 0, 0, 0));
    // moveCmds.push_back(MoveModelCommand(1, -50, 0, 0));
    // moveCmds.push_back(MoveModelCommand(2, 50, 0, 0));
    // moveCmds.push_back(MoveModelCommand(3, 0, 50, 0));
    // moveCmds.push_back(MoveModelCommand(4, 0, -50, 0));
    // for (size_t i = 0; i < 5; ++i) {
    //     TrianglesModelLoadCommand load_command(&(filename2[0]), stepOfRevolving, idMaterial::RED);
    //     facade.execute(load_command);
    //     facade.execute(moveCmds[i]);
    //     std::cout << "CountAllFaces = " << facade.getCountFacesOnScene() << "\n";
    // }

    std::cout << "endonLoadModelBtnClicked: ---------" <<std::endl;
}

void MainWindow::onDrawBtnClicked() {
    std::cout << "onDrawBtnClicked: ------------" <<std::endl;

    QtDrawCommand command(graphicsView);
    facade.execute(command);

    std::cout << "end onDrawBtnClicked: --------" <<std::endl;
}

size_t MainWindow::getSelectedModelId() const {
    int id = 0; // TODO get id from info table

    if (id == -1) {
        time_t curTime = time(NULL);
        throw NoSelectedModelException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
    return static_cast<size_t>(id);
}

void MainWindow::onMoveModelBtnClicked() {
    std::cout << "MoveModelBtnClicked: ------------" <<std::endl;

    try {
        size_t id = getSelectedModelId();

        double dx = ui.dx_dsp->value();
        double dy = ui.dy_dsp->value();
        double dz = ui.dz_dsp->value();

        MoveModelCommand command(id, dx, dy, dz);
        facade.execute(command);
    } catch (NoSelectedModelException &ex) {
        QMessageBox::critical(nullptr, "Ошибка", "Нужно выбрать модель.");
        return;
    } catch (BaseException &ex) {
        std::cout << ex.what() << "\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "end MoveModelBtnClicked ---------" <<std::endl;

    onDrawBtnClicked();
}

void MainWindow::onRotateModelBtnClicked() {
    std::cout << "RotateModelBtnClicked: ------------" <<std::endl;

    try {
        size_t id = getSelectedModelId();

        float angle_grad = static_cast<float>(ui.angle_dsp->value());

        RotateModelCommand command(id, angle_grad);
        facade.execute(command);
    } catch (NoSelectedModelException &ex) {
        QMessageBox::critical(nullptr, "Ошибка", "Нужно выбрать модель.");
        return;
    } catch (BaseException &ex) {
        std::cout << ex.what() << "\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "end RotateModelBtnClicked ---------" <<std::endl;

    onDrawBtnClicked();
}

void MainWindow::rotateCamera(Axis axis) {
    try {
        float angle_grad = static_cast<float>(ui.angle_dsp->value());

        RotateCameraCommand command(angle_grad, axis);
        facade.execute(command);
    } catch (BaseException &ex) {
        std::cout << ex.what() << "\n";
        exit(EXIT_FAILURE);
    }
}

void MainWindow::onRotateOXCameraBtnClicked() {
    std::cout << "onRotateOXCameraBtnClicked: ------------" <<std::endl;
    rotateCamera(Axis::OX);
    std::cout << "end onRotateOXCameraBtnClicked ---------" <<std::endl;

    onDrawBtnClicked();
}

void MainWindow::onRotateOYCameraBtnClicked() {
    std::cout << "onRotateOYCameraBtnClicked: ------------" <<std::endl;
    rotateCamera(Axis::OY);
    std::cout << "end onRotateOYCameraBtnClicked ---------" <<std::endl;

    onDrawBtnClicked();
}

void MainWindow::measureRenderTime() {
    char filename[] = "/home/kathrine/cg_cp/data/pawn.txt";
    char datafilename[] = "../data_time/dataTime.txt";


    size_t stepOfRevolving = 6;
    std::vector<MoveModelCommand> moveCmds;
    moveCmds.push_back(MoveModelCommand(0, 0, 0, 0));
    moveCmds.push_back(MoveModelCommand(1, -50, 0, 0));
    moveCmds.push_back(MoveModelCommand(2, 50, 0, 0));
    moveCmds.push_back(MoveModelCommand(3, 0, 50, 0));
    moveCmds.push_back(MoveModelCommand(4, 0, -50, 0));
    for (size_t i = 0; i < 2; ++i) {
        TrianglesModelLoadCommand load_command(&(filename[0]), stepOfRevolving, idMaterial::RED);
        facade.execute(load_command);
        facade.execute(moveCmds[i]);
    }
    for (size_t i = 2; i < 3; ++i) {
        TrianglesModelLoadCommand load_command(&(filename[0]), stepOfRevolving, idMaterial::RED);
        facade.execute(load_command);
        facade.execute(moveCmds[i]);
        std::cout << "CountAllFaces = " << facade.getCountFacesOnScene() << "\n";
        std::ofstream f(datafilename, std::ios::app);
        if (f.is_open()) {
            f << facade.getCountFacesOnScene() << "\t";
        } else 
            std::cout << "Error: " << strerror(errno) << "\n";
        f.close(); 
        DrawTimeCommand time_draw_command(graphicsView, &(datafilename[0]));
        facade.execute(time_draw_command);
    }
    for (size_t i = 3; i < 4; ++i) {
        TrianglesModelLoadCommand load_command(&(filename[0]), stepOfRevolving, idMaterial::RED);
        facade.execute(load_command);
        facade.execute(moveCmds[i]);
    }
    size_t i = 4;
    TrianglesModelLoadCommand load_command(&(filename[0]), stepOfRevolving, idMaterial::RED);
    facade.execute(load_command);
    facade.execute(moveCmds[i]);
    std::cout << "CountAllFaces = " << facade.getCountFacesOnScene() << "\n";
    std::ofstream f(datafilename, std::ios::app);
    if (f.is_open()) {
        f << facade.getCountFacesOnScene() << "\t";
    } else 
        std::cout << "Error: " << strerror(errno) << "\n";
    f.close(); 
    DrawTimeCommand time_draw_command(graphicsView, &(datafilename[0]));
    facade.execute(time_draw_command);

    // size_t stepOfRevolving = 6;
    // std::vector<MoveModelCommand> moveCmds;
    // moveCmds.push_back(MoveModelCommand(0, 0, 0, 0));
    // moveCmds.push_back(MoveModelCommand(1, -50, 0, 0));
    // moveCmds.push_back(MoveModelCommand(2, 50, 0, 0));
    // moveCmds.push_back(MoveModelCommand(3, 0, 50, 0));
    // moveCmds.push_back(MoveModelCommand(4, 0, -50, 0));
    // for (size_t i = 0; i < 5; ++i) {
    //     TrianglesModelLoadCommand load_command(&(filename[0]), stepOfRevolving, idMaterial::RED);
    //     facade.execute(load_command);
    //     facade.execute(moveCmds[i]);
    //     std::cout << "CountAllFaces = " << facade.getCountFacesOnScene() << "\n";
    //     std::ofstream f(datafilename, std::ios::app);
    //     if (f.is_open()) {
    //         f << facade.getCountFacesOnScene() << "\t";
    //     } else 
    //         std::cout << "Error: " << strerror(errno) << "\n";
    //     f.close(); 
    //     DrawTimeCommand time_draw_command(graphicsView, &(datafilename[0]));
    //     facade.execute(time_draw_command);
    // }
    
    exit(EXIT_SUCCESS);
}