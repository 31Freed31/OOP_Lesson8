#include <iostream>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 50;

class Window {
private:
    int x, y;
    int width, height;

public:
    Window(int startX, int startY, int w, int h) {
        x = (startX >= 0 && startX < SCREEN_WIDTH) ? startX : 0;
        y = (startY >= 0 && startY < SCREEN_HEIGHT) ? startY : 0;
        width = (w >= 0) ? w : 1;
        height = (h >= 0) ? h : 1;
        adjustToScreenBounds();
    }

    void move(int dx, int dy) {
        x += dx;
        y += dy;
        adjustToScreenBounds();
        std::cout << "Окно перемещено. Новые координаты: (" << x << ", " << y << ")\n";
    }

    void resize(int newWidth, int newHeight) {
        width = (newWidth >= 0) ? newWidth : 1;
        height = (newHeight >= 0) ? newHeight : 1;
        adjustToScreenBounds();
        std::cout << "Размер окна изменён. Новые размеры: ширина = " << width << ", высота = " << height << "\n";
    }

    void display() const {
        for (int i = 0; i < SCREEN_HEIGHT; ++i) {
            for (int j = 0; j < SCREEN_WIDTH; ++j) {
                if (i >= y && i < y + height && j >= x && j < x + width) {
                    std::cout << "1";
                }
                else {
                    std::cout << "0";
                }
            }
            std::cout << "\n";
        }
    }

    bool isInsideScreen() const {
        return x >= 0 && y >= 0 && x + width <= SCREEN_WIDTH && y + height <= SCREEN_HEIGHT;
    }

private:
    void adjustToScreenBounds() {
        if (x + width > SCREEN_WIDTH) {
            x = SCREEN_WIDTH - width;
        }
        if (y + height > SCREEN_HEIGHT) {
            y = SCREEN_HEIGHT - height;
        }
        if (x < 0) {
            x = 0;
        }
        if (y < 0) {
            y = 0;
        }
    }
};

int main() {
    setlocale(LC_CTYPE, "rus");

    int startX, startY, width, height;
    std::cout << "Введите начальные координаты окна (x, y) и размеры (ширина, высота): ";
    std::cin >> startX >> startY >> width >> height;

    Window window(startX, startY, width, height);
    std::string command;

    while (true) {
        std::cout << "Введите команду (move, resize, display, close): ";
        std::cin >> command;

        if (command == "move") {
            int dx, dy;
            std::cout << "Введите вектор смещения (dx, dy): ";
            std::cin >> dx >> dy;
            window.move(dx, dy);
        }
        else if (command == "resize") {
            int newWidth, newHeight;
            std::cout << "Введите новые размеры (ширина, высота): ";
            std::cin >> newWidth >> newHeight;
            window.resize(newWidth, newHeight);
        }
        else if (command == "display") {
            window.display();
        }
        else if (command == "close") {
            std::cout << "Окно закрыто.\n";
            break;
        }
        else {
            std::cout << "Неизвестная команда. Попробуйте снова.\n";
        }
    }

    return 0;
}
