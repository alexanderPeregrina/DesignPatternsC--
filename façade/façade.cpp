
/*

the Façade Pattern is all about providing a simplified interface 
to a complex subsystem. Instead of exposing all the details of multiple classes, 
you wrap them in a single class (the façade) that offers easy‑to‑use methods

*/
#include <iostream>
#include <string>

// Subsystem classes
class DVDPlayer {
public:
    void on() { std::cout << "DVD Player on\n"; }
    void play(const std::string& movie) { std::cout << "Playing movie: " << movie << "\n"; }
    void off() { std::cout << "DVD Player off\n"; }
};

class Projector {
public:
    void on() { std::cout << "Projector on\n"; }
    void wideScreenMode() { std::cout << "Projector in widescreen mode\n"; }
    void off() { std::cout << "Projector off\n"; }
};

class SoundSystem {
public:
    void on() { std::cout << "Sound System on\n"; }
    void setSurroundSound() { std::cout << "Surround sound enabled\n"; }
    void off() { std::cout << "Sound System off\n"; }
};

// Façade class
class HomeTheaterFacade {
    DVDPlayer& dvd;
    Projector& projector;
    SoundSystem& sound;
public:
    HomeTheaterFacade(DVDPlayer& d, Projector& p, SoundSystem& s)
        : dvd(d), projector(p), sound(s) {}

    void watchMovie(const std::string& movie) {
        std::cout << "Get ready to watch a movie...\n";
        dvd.on();
        projector.on();
        projector.wideScreenMode();
        sound.on();
        sound.setSurroundSound();
        dvd.play(movie);
    }

    void endMovie() {
        std::cout << "Shutting movie theater down...\n";
        dvd.off();
        projector.off();
        sound.off();
    }
};

// Client code
int main() {
    DVDPlayer dvd;
    Projector projector;
    SoundSystem sound;

    HomeTheaterFacade homeTheater(dvd, projector, sound);

    homeTheater.watchMovie("Inception");
    homeTheater.endMovie();

    return 0;
}