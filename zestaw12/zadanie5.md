# Visitor
**Wzorzec projektowy Visitor (Odwiedzający) w C++**

**Opis i funkcja wzorca:**
Visitor (Odwiedzający) to wzorzec projektowy, który umożliwia dodanie nowych operacji do zbioru klas bez modyfikowania ich kodu. Działa poprzez oddzielenie algorytmu (odwiedzającego) od struktury obiektów, które są odwiedzane.

**Zastosowanie i problemy, które rozwiązuje:**

* Umożliwia dodawanie nowych operacji bez modyfikowania klas, na których operują
* Przestrzega zasady otwarte-zamknięte (Open/Closed Principle)
* Pomaga oddzielić logikę przetwarzania od struktury danych

**Typowe przypadki użycia:**

* Operacje na strukturach składniowych (np. AST)
* Generowanie raportów, eksport danych
* Walidacja lub analiza danych

**Struktura UML:**

* `Visitor` – interfejs odwiedzającego (zawiera metody visit dla różnych typów)
* `ConcreteVisitor` – konkretna implementacja odwiedzającego
* `Element` – interfejs dla odwiedzanych obiektów (z metodą accept)
* `ConcreteElement` – konkretne klasy akceptujące odwiedzającego

**Implementacja w C++:**

```cpp
#include <iostream>
#include <vector>
#include <memory>

// Przód: klasy odwiedzające
class Circle;
class Rectangle;

class Visitor {
public:
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Rectangle& rectangle) = 0;
    virtual ~Visitor() = default;
};

// Element – interfejs dla odwiedzanych obiektów
class Shape {
public:
    virtual void accept(Visitor& visitor) = 0;
    virtual ~Shape() = default;
};

// Konkretne klasy
class Circle : public Shape {
public:
    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
    void draw() const {
        std::cout << "Rysowanie koła\n";
    }
};

class Rectangle : public Shape {
public:
    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }
    void draw() const {
        std::cout << "Rysowanie prostokąta\n";
    }
};

// Konkretna operacja – np. eksport do SVG
class ExportVisitor : public Visitor {
public:
    void visit(Circle& circle) override {
        std::cout << "Eksportowanie koła do SVG\n";
    }

    void visit(Rectangle& rectangle) override {
        std::cout << "Eksportowanie prostokąta do SVG\n";
    }
};

// Przykład użycia
int main() {
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Circle>());
    shapes.push_back(std::make_shared<Rectangle>());

    ExportVisitor exporter;

    for (auto& shape : shapes) {
        shape->accept(exporter);
    }

    return 0;
}
```

**Wyjaśnienie działania:**

* `Visitor` definiuje operacje dla różnych typów `Shape`
* `Circle` i `Rectangle` implementują `accept`, które deleguje wywołanie do odpowiedniej metody `visit`
* Dzięki temu można dodać np. eksport do PDF, logowanie, analizę bez zmieniania kodu `Shape`

**Zalety:**

* Łatwe dodawanie nowych operacji bez modyfikacji klas
* Oddzielenie struktury danych od logiki operacyjnej
* Czytelny sposób na obsługę wielu typów bez `dynamic_cast`

**Wady:**

* Trudniej dodawać nowe typy elementów (konieczność modyfikacji `Visitor`)
* Może być nadmiarowy w prostych przypadkach

**Podsumowanie:**
Wzorzec Visitor pozwala dodawać operacje do grupy klas bez ingerencji w ich implementację. Ułatwia utrzymanie i rozwijanie systemu, gdy często zmieniają się operacje, a nie struktura danych.
