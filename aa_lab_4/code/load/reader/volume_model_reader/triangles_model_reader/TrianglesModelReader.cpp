#include "TrianglesModelReader.h"


TrianglesModelReader::TrianglesModelReader(const char *fname, size_t _stepOfRevolving) 
: filename(fname), stepOfRevolving(_stepOfRevolving), 
vertices(std::vector<psPoint3>()), triangles(std::vector<std::vector<psPoint3>>()), center(Point3()) {
    assert(stepOfRevolving >= 3);
    alphaStep = 2 * M_PI / static_cast<int>(stepOfRevolving);
}

TrianglesModelReader::~TrianglesModelReader() {
    if (isOpen()) {
        close();
    }
}

void TrianglesModelReader::open() {
    if (isOpen()) {
        return;
    }
    file.open(filename);
    if (!file) {
        time_t curTime = time(NULL);
        throw NoFileReadException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }
}

void TrianglesModelReader::close() {
    if (!isOpen())
        return;
    file.close();
}

bool TrianglesModelReader::isOpen() { return file.is_open(); }

void TrianglesModelReader::readVectex() {
    float x, y, z;
    file >> x >> y >> z;
    if (!file) {
        time_t curTime = time(NULL);
        throw FloatReadException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }

    vertices.push_back(std::make_shared<Point3>(x, y, z));
    if (printing)
        std::cout << "v: " << Point3(x, y, z) << '\n';
}

void TrianglesModelReader::readRadVertex() {
    float x, y;
    file >> x >> y;
    if (!file) {
        time_t curTime = time(NULL);
        throw FloatReadException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }

    double xtmp, ztmp;
    double radius = x;
    std::vector<psPoint3> circle;
    circle.push_back(std::make_shared<Point3>(x, y, 0));
    if (fabs(x) > EPS) {
        for (size_t i = 1; i < stepOfRevolving - 1; ++i) {
            xtmp = radius * cos(alphaStep * static_cast<int>(i));
            ztmp = radius * sin(alphaStep * static_cast<int>(i));
            circle.push_back(std::make_shared<Point3>(xtmp, y, ztmp));
        }
    }
    revolvElems.push_back(circle);

    for (psPoint3 elem : circle) {
        vertices.push_back(elem);
    }
    if (printing)
        std::cout << "r: " << Point3(x, y, 0) << '\n';
}

void TrianglesModelReader::readCirclesConnect() {
    char ch;
    int ind;
    std::vector<size_t> indexes;

    for (size_t i = 0; i < 2; ++i) {
        file >> ch;
        if (!file) {
            time_t curTime = time(NULL);
            throw EndReadException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
        }
        bool symblor_error = true;
        if (ch == 'r') {
            file >> ind;
            if (file) {
                symblor_error = false;

                if (ind <= 0 || static_cast<size_t>(ind) > revolvElems.size()) {
                    time_t curTime = time(NULL);
                    throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
                }
                indexes.push_back(static_cast<size_t>(ind - 1));
            }
        }
        if (symblor_error) {
            if (printing)
                std::cout << "ch = |" << ch << "|\n";
            time_t curTime = time(NULL);
            throw SymbolReadException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
        }
    }

    if (revolvElems[indexes[1]].size() == 1) {
        size_t tmp = indexes[0];
        indexes[0] = indexes[1];
        indexes[1] = tmp;
    }
    if (revolvElems[indexes[0]].size() == 1) {
        size_t n = revolvElems[indexes[1]].size();
        psPoint3 topPoint = revolvElems[indexes[0]][0];

        for (size_t i = 0; i < n - 1; ++i) {
            triangles.push_back({topPoint, revolvElems[indexes[1]][i], revolvElems[indexes[1]][i + 1]});
        }
        triangles.push_back({topPoint, revolvElems[indexes[1]][0], revolvElems[indexes[1]][n - 1]});
    } else {
        size_t n = revolvElems[indexes[0]].size();
        size_t m = revolvElems[indexes[1]].size();
        assert(n == m);

        for (size_t i = 0; i < n - 1; ++i) {
            triangles.push_back({revolvElems[indexes[0]][i], 
                                    revolvElems[indexes[1]][i],
                                    revolvElems[indexes[1]][i + 1]});
            triangles.push_back({revolvElems[indexes[0]][i], 
                                    revolvElems[indexes[0]][i + 1],
                                    revolvElems[indexes[1]][i + 1]});
        }
        triangles.push_back({revolvElems[indexes[0]][n - 1], 
                                revolvElems[indexes[1]][n - 1],
                                revolvElems[indexes[1]][0]});
        triangles.push_back({revolvElems[indexes[0]][n - 1], 
                                revolvElems[indexes[0]][0],
                                revolvElems[indexes[1]][0]});
    }

    if (printing)
        std::cout << "l(links): " << "\n";
}

void TrianglesModelReader::readTriangle() {
    char ch;
    int ind;
    std::vector<size_t> indexes;

    for (size_t i = 0; i < 3; ++i) {
        file >> ch;
        if (!file) {
            time_t curTime = time(NULL);
            throw EndReadException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
        }
        bool symblor_error = true;
        if (ch == 'v') {
            file >> ind;
            if (file) {
                symblor_error = false;

                if (ind <= 0 || static_cast<size_t>(ind) > vertices.size()) {
                    time_t curTime = time(NULL);
                    throw IndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
                }
                indexes.push_back(static_cast<size_t>(ind - 1));
            }
        }
        if (symblor_error) {
            if (printing)
            std::cout << "ch = |" << ch << "|\n";
            time_t curTime = time(NULL);
            throw SymbolReadException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
        }
    }

    if (printing)
        std::cout << "tr: " << *(vertices[indexes[0]]) << " " << *(vertices[indexes[1]]) << " " << *(vertices[indexes[2]]) << "\n";
    triangles.push_back({vertices[indexes[0]], vertices[indexes[1]], vertices[indexes[2]]});
}

void TrianglesModelReader::readData() {
    assert(isOpen());
    file.seekg(0, std::ios::beg);   // переместить курсор на начало файла

    std::string type;
    while (!file.eof()) {
        file >> type;
        if (!file) {
            if (printing)
                std::cout << "end of file;\n";
            continue;
        }
        if (type == "v") {
            readVectex();

        } else if (type == "r") {
            readRadVertex();
        } else if (type == "f") {
            readTriangle();
        } else if (type == "l") {
            readCirclesConnect();
        } else if (type == "c") {
            float x, y, z;
            file >> x >> y >> z;
            if (!file) {
                time_t curTime = time(NULL);
                throw FloatReadException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
            }
            center = Point3(x, y, z);
            if (printing)
                std::cout << "center = " << center << "\n";

        } else if (type[0] == '#' || type == "\n" || type == "") {
            std::getline(file, type);
            if (printing)
                std::cout << "--comment or empty line--\n";

        } else {
            if (printing)
                std::cout << "symbol: |" << type << "|\n";
            time_t curTime = time(NULL);
            throw SymbolReadException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
        }
    }
    
}

std::vector<std::vector<psPoint3>> TrianglesModelReader::getFaces() {
    return triangles;
}

Point3 TrianglesModelReader::getCenter() {
    return center;
}
