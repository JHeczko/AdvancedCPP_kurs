# Dekorator
**Wzorzec projektowy Dekorator w C++**

**Opis i funkcja wzorca:**
Wzorzec projektowy Dekorator (ang. Decorator) pozwala na dynamiczne rozszerzanie funkcjonalności obiektów bez modyfikacji ich kodu. Osiąga się to przez opakowanie oryginalnego obiektu w nowy obiekt dekorujący, który dodaje nowe zachowania przed lub po delegacji do oryginalnego obiektu.

**Zastosowanie i problemy, które rozwiązuje:**

* Potrzeba dodania nowych funkcji do klasy bez dziedziczenia.
* Unikanie tworzenia dużych hierarchii klas.
* Zwiększenie elastyczności przez składanie funkcjonalności dynamicznie.

**Typowe przypadki użycia:**

* Rozszerzanie funkcjonalności GUI (np. dekorowanie komponentów)
* Logowanie, autoryzacja, buforowanie
* Kompresja / szyfrowanie danych

**Struktura UML:**

* `Component` – interfejs bazowy
* `ConcreteComponent` – podstawowy obiekt
* `Decorator` – klasa bazowa dekoratora (dziedziczy po `Component`)
* `ConcreteDecorator` – dodaje nowe funkcjonalności

**Implementacja w C++ (dekorowanie strumienia):**

```cpp
#include <iostream>
#include <memory>

// Komponent bazowy
class DataSource {
public:
    virtual void writeData(const std::string& data) = 0;
    virtual std::string readData() = 0;
    virtual ~DataSource() = default;
};

// Konkretna implementacja komponentu
class FileDataSource : public DataSource {
public:
    void writeData(const std::string& data) override {
        buffer = data; // symulacja zapisu do pliku
        std::cout << "[File] Zapisano: " << data << std::endl;
    }

    std::string readData() override {
        return buffer;
    }

private:
    std::string buffer;
};

// Dekorator bazowy
class DataSourceDecorator : public DataSource {
public:
    DataSourceDecorator(std::shared_ptr<DataSource> wrappee) : wrappee(wrappee) {}

    void writeData(const std::string& data) override {
        wrappee->writeData(data);
    }

    std::string readData() override {
        return wrappee->readData();
    }

protected:
    std::shared_ptr<DataSource> wrappee;
};

// Konkretna dekoracja: dodanie kompresji (symulacja)
class CompressionDecorator : public DataSourceDecorator {
public:
    CompressionDecorator(std::shared_ptr<DataSource> wrappee) : DataSourceDecorator(wrappee) {}

    void writeData(const std::string& data) override {
        std::string compressed = "[COMPRESSED]" + data;
        wrappee->writeData(compressed);
    }

    std::string readData() override {
        std::string data = wrappee->readData();
        return data.substr(12); // usunięcie prefiksu [COMPRESSED]
    }
};

// Konkretna dekoracja: dodanie szyfrowania (symulacja)
class EncryptionDecorator : public DataSourceDecorator {
public:
    EncryptionDecorator(std::shared_ptr<DataSource> wrappee) : DataSourceDecorator(wrappee) {}

    void writeData(const std::string& data) override {
        std::string encrypted = "[ENCRYPTED]" + data;
        wrappee->writeData(encrypted);
    }

    std::string readData() override {
        std::string data = wrappee->readData();
        return data.substr(11); // usunięcie prefiksu [ENCRYPTED]
    }
};

// Przykład użycia
int main() {
    std::shared_ptr<DataSource> file = std::make_shared<FileDataSource>();
    std::shared_ptr<DataSource> encrypted = std::make_shared<EncryptionDecorator>(file);
    std::shared_ptr<DataSource> compressed = std::make_shared<CompressionDecorator>(encrypted);

    compressed->writeData("Ważne dane użytkownika");
    std::cout << "Odczytane dane: " << compressed->readData() << std::endl;

    return 0;
}
```

**Wyjaśnienie działania:**

* `FileDataSource` to podstawowy komponent.
* `CompressionDecorator` i `EncryptionDecorator` to dodatkowe funkcjonalności.
* Obiekty dekoratorów można łączyć w łańcuch (np. kompresja + szyfrowanie).

**Zalety:**

* Elastyczne rozszerzanie funkcjonalności
* Unikanie przeciążonego dziedziczenia
* Możliwość łączenia wielu dekoratorów dynamicznie

**Wady:**

* Może prowadzić do wielu małych klas
* Zwiększona złożoność debugowania

**Podsumowanie:**
Wzorzec Dekorator pozwala dynamicznie rozbudowywać zachowanie obiektów bez modyfikowania istniejącego kodu. Jest szczególnie przydatny, gdy potrzebujemy elastycznego systemu modyfikacji funkcjonalności w czasie działania aplikacji.
