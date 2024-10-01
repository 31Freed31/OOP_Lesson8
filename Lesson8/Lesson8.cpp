#include <iostream>
#include <vector>
#include <string>

class Track {
private:
    std::string title;
    std::string creationDate;
    int duration;

public:
    Track(const std::string& title, const std::string& creationDate, int duration)
        : title(title), creationDate(creationDate), duration(duration) {}

    std::string getTitle() const {
        return title;
    }

    void displayInfo() const {
        std::cout << "Название: " << title << std::endl;
        std::cout << "Дата создания: " << creationDate << std::endl;
        std::cout << "Продолжительность: " << duration << " секунд" << std::endl;
    }
};

class AudioPlayer {
private:
    std::vector<Track> playlist;
    bool isPlaying;
    bool isPaused;
    int currentTrackIndex;

public:
    AudioPlayer() : isPlaying(false), isPaused(false), currentTrackIndex(-1) {}

    void addTrack(const Track& track) {
        playlist.push_back(track);
    }

    void play(const std::string& trackTitle) {
        if (isPlaying) {
            std::cout << "Трек уже воспроизводится." << std::endl;
            return;
        }

        for (int i = 0; i < playlist.size(); ++i) {
            if (playlist[i].getTitle() == trackTitle) {
                currentTrackIndex = i;
                isPlaying = true;
                isPaused = false;
                std::cout << "Воспроизведение трека:" << std::endl;
                playlist[i].displayInfo();
                return;
            }
        }

        std::cout << "Трек не найден." << std::endl;
    }

    void pause() {
        if (!isPlaying) {
            std::cout << "Нет воспроизводимого трека." << std::endl;
            return;
        }
        if (isPaused) {
            std::cout << "Трек уже на паузе." << std::endl;
            return;
        }
        isPaused = true;
        std::cout << "Трек поставлен на паузу." << std::endl;
    }

    void next() {
        if (playlist.empty()) {
            std::cout << "Плейлист пуст." << std::endl;
            return;
        }

        int randomIndex = rand() % playlist.size();
        currentTrackIndex = randomIndex;
        isPlaying = true;
        isPaused = false;
        std::cout << "Следующий трек (shuffle):" << std::endl;
        playlist[randomIndex].displayInfo();
    }

    void stop() {
        if (!isPlaying) {
            std::cout << "Нечего останавливать." << std::endl;
            return;
        }
        isPlaying = false;
        currentTrackIndex = -1;
        std::cout << "Воспроизведение остановлено." << std::endl;
    }
};

int main() {
    setlocale(LC_CTYPE, "rus");
    AudioPlayer player;

    player.addTrack(Track("Track 1", "15.06.2021", 240));
    player.addTrack(Track("Track 2", "10.04.2020", 180));
    player.addTrack(Track("Track 3", "20.02.2019", 300));

    std::string command;

    while (true) {
        std::cout << "Введите команду (play, pause, next, stop, exit): ";
        std::cin >> command;

        if (command == "play") {
            std::string trackTitle;
            std::cout << "Введите название трека: ";
            std::cin.ignore();
            std::getline(std::cin, trackTitle);
            player.play(trackTitle);
        }
        else if (command == "pause") {
            player.pause();
        }
        else if (command == "next") {
            player.next();
        }
        else if (command == "stop") {
            player.stop();
        }
        else if (command == "exit") {
            std::cout << "Выход из программы." << std::endl;
            break;
        }
        else {
            std::cout << "Неизвестная команда. Попробуйте снова." << std::endl;
        }
    }
    return 0;
}
