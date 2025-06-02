# Obserwator
**Opis i funkcja wzorca:**
Wzorzec behawioralny, który umożliwia wprowadzenie tak zwanych subskrypcji, gdzie dodajemy obiekty subskrybujące do obiektu publikującego(subskrybenci maja odpowiednia metodę `notify`), ktory to kiedy zajdzie taka sytuacja, przechodzi po swoich subskrybentach i wywoluje na nich okresloną metodę powiadamiającą.

**Zastosowanie i problemy, które rozwiązuje:**

* Oddziela logikę zmiany stanu od logiki reagowania na tę zmianę.
* Pozwala wielu obiektom nasłuchiwać zmian jednego źródła.
* Zapewnia spójność danych między komponentami bez silnego powiązania między nimi (luźne sprzężenie).

**Typowe przypadki użycia:**

* GUI (np. model widoku powiadamiający widoki o zmianach)
* Systemy zdarzeniowe
* Subskrypcje i powiadomienia
* Reagowanie na zmiany konfiguracji

**Implementacja w C++ (z użyciem interfejsów):**

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Interfejs Obserwatora
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() {}
};

// Interfejs Obiektu Obserwowanego (Subject)
class Subject {
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(const std::string& message) {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }

private:
    std::vector<Observer*> observers;
};

// Konkretna implementacja Obserwatora
class User : public Observer {
public:
    User(const std::string& name) : name(name) {}

    void update(const std::string& message) override {
        std::cout << "Użytkownik " << name << " otrzymał powiadomienie: " << message << std::endl;
    }

private:
    std::string name;
};

// Przykładowy Obiekt Obserwowany (np. Kanał powiadomień)
class NotificationChannel : public Subject {
public:
    void postMessage(const std::string& message) {
        std::cout << "[Kanał] Nowa wiadomość: " << message << std::endl;
        notify(message);
    }
};

// Przykład użycia
int main() {
    NotificationChannel channel;

    User user1("Anna");
    User user2("Tomasz");
    User user3("Zofia");

    channel.attach(&user1);
    channel.attach(&user2);

    channel.postMessage("Nowa aktualizacja systemu dostępna!");

    channel.attach(&user3);
    channel.postMessage("Spotkanie zespołu o 10:00");

    channel.detach(&user1);
    channel.postMessage("Test powiadomień po wypisaniu");

    return 0;
}
```

**Wyjaśnienie działania:**

* `NotificationChannel` to obserwowany obiekt (Subject).
* `User` to konkretni obserwatorzy reagujący na wiadomości.
* Obserwatorzy są dodawani za pomocą `attach`, usuwani przez `detach`, a informowani przez `notify`.
* Zmiana stanu (np. nowa wiadomość) powoduje automatyczne powiadomienie wszystkich obserwatorów.

**Zalety:**

* Luźne powiązania między komponentami
* Możliwość dynamicznego dodawania/usuwania obserwatorów
* Reaktywna architektura — propagacja zmian

**Wady:**

* Możliwa złożoność zarządzania cyklem życia obiektów (pamięć)
* Możliwość powstawania błędów trudnych do debugowania (np. powiadomienia po usunięciu obserwatora)

**Podsumowanie:**
Wzorzec Obserwator jest fundamentem wielu systemów zdarzeniowych i GUI. Pozwala tworzyć systemy reagujące na zmiany w sposób skalowalny i czytelny, bez silnego powiązania między komponentami.
