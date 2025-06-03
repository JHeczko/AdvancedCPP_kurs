# Singleton
**Opis i funkcja wzorca:**
Kreacyjny wzorzec ten zapewnia, ze klasa ma tylko jedna instancje w calym kodzie, ponadto jest ona dostepna grlobalnei

**Zastosowanie i problemy, które rozwiązuje:**

* Gwarantuje istnienie jednej instancji klasy.
* Umożliwia centralne zarządzanie stanem aplikacji.
* Zapobiega mnożeniu się obiektów, które powinny być unikalne (np. menedżer okien, konfiguracja systemu).

**Typowe przypadki użycia:**

* Systemy logowania (Logger)
* Klasy zarządzające konfiguracją
* Połączenia z bazą danych
* Sterowniki urządzeń

**Implementacja w C++:**

```c++
#include <iostream>
#include <mutex>

class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance; // bezpieczny wątkowo od C++11
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }

    // Usuwanie konstruktorów kopiujących i operatorów przypisania
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {
        std::cout << "Singleton constructor\n";
    }
};

// Przykład użycia
int main() {
    Singleton& logger1 = Singleton::getInstance();
    Singleton& logger2 = Singleton::getInstance();

    logger1.log("Pierwszy komunikat");
    logger2.log("Drugi komunikat");

    // Sprawdzenie, czy obie referencje wskazują na ten sam obiekt
    if (&logger1 == &logger2) {
        std::cout << "To ta sama instancja" << std::endl;
    }

    return 0;
}
```

**Zalety:**

* Prosta kontrola instancji
* Oszczędność zasobów
* Zapewnienie spójności danych

**Wady:**

* Może prowadzic do ukrytych zależności globalnych
* Trudniejszy do testowania (np. w testach jednostkowych)
* W niektórych przypadkach może wprowadzać problemy z zarządzaniem cyklem życia obiektu