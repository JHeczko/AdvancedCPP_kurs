# Adapter
**Wzorzec projektowy Adapter w C++**

**Opis i funkcja wzorca:**
Wzorzec projektowy Adapter (ang. Adapter Pattern) umożliwia współpracę klas, których interfejsy są niekompatybilne. Adapter działa jak tłumacz: opakowuje istniejący obiekt i udostępnia nowy interfejs oczekiwany przez klienta.

**Zastosowanie i problemy, które rozwiązuje:**

* Integracja starych komponentów z nowym systemem
* Przystosowanie klas o niezgodnych interfejsach bez modyfikowania ich kodu
* Zwiększenie ponownego użycia istniejących klas

**Typowe przypadki użycia:**

* Integracja bibliotek zewnętrznych
* Refaktoryzacja kodu z zachowaniem kompatybilności

**Struktura UML:**

* `Target` – interfejs oczekiwany przez klienta
* `Adaptee` – istniejąca klasa o niekompatybilnym interfejsie
* `Adapter` – dostosowuje `Adaptee` do `Target`

**Implementacja w C++ (przystosowanie klasy z innym interfejsem):**

```cpp
#include <iostream>
#include <memory>

// Interfejs oczekiwany przez klienta
class ITarget {
public:
    virtual void request() = 0;
    virtual ~ITarget() = default;
};

// Klasa z istniejącą funkcjonalnością, ale innym interfejsem
class Adaptee {
public:
    void specificRequest() {
        std::cout << "[Adaptee] Specyficzna metoda została wywołana.\n";
    }
};

// Adapter dostosowuje Adaptee do ITarget
class Adapter : public ITarget {
public:
    Adapter(std::shared_ptr<Adaptee> adaptee) : adaptee(adaptee) {}

    void request() override {
        std::cout << "[Adapter] Tłumaczenie request() na specificRequest()...\n";
        adaptee->specificRequest();
    }

private:
    std::shared_ptr<Adaptee> adaptee;
};

// Przykład użycia
int main() {
    std::shared_ptr<Adaptee> adaptee = std::make_shared<Adaptee>();
    std::shared_ptr<ITarget> adapter = std::make_shared<Adapter>(adaptee);

    // Klient korzysta z interfejsu ITarget, nie znając Adaptee
    adapter->request();

    return 0;
}
```

**Wyjaśnienie działania:**

* `ITarget` to interfejs używany przez klienta.
* `Adaptee` to istniejąca klasa o innym interfejsie.
* `Adapter` opakowuje `Adaptee` i dostosowuje jej metody do interfejsu `ITarget`.

**Zalety:**

* Umożliwia ponowne użycie istniejących klas bez ich modyfikacji
* Rozdziela kod klienta od szczegółów implementacyjnych
* Może być używany z kompozycją lub dziedziczeniem

**Wady:**

* Wprowadza dodatkową warstwę pośrednią
* Może zwiększyć złożoność systemu, jeśli nadużywany

**Podsumowanie:**
Wzorzec Adapter pozwala łączyć niekompatybilne klasy przez udostępnienie nowego interfejsu. Jest szczególnie przydatny podczas integracji starszego kodu lub bibliotek z nowymi aplikacjami bez potrzeby ich modyfikacji.
