# Visitor
**Opis i funkcja wzorca:**
Jest to behawioralny wzorzec projektowy, który oddziela operacje na obiektach od samych obiektów. Algorytmy dzialaja w sepracji od obiektow na ktorcyh pracuja


**Zastosowanie i problemy, które rozwiązuje:**

* Umożliwia dodawanie nowych operacji bez modyfikowania klas, na których operują
* Przestrzega zasady otwarte-zamknięte (Open/Closed Principle)
* Pomaga oddzielić logikę przetwarzania od struktury danych

**Typowe przypadki użycia:**

* Operacje na strukturach składniowych (np. AST)
* Generowanie raportów, eksport danych
* Walidacja lub analiza danych

**Implementacja w C++:**

```cpp

```

**Zalety:**

* Zachowanie zasady otwarte/zamkniete, bo pozwala dodawac funckjonalnoc do obiektow roznych klas bez zmiany tych klas(jest metoda accept, ale on jest trywialna)
* Zasada pojedynczej odpowiedzalnosc, wiele roznych wersji jednego zachowania w jednej klasie(generator xml na przyklad)
* Pomaga zebrac informacje o roznych obiektach

**Wady:**

* Trzeba aktualizowac odwiedzajacych, za kazdym razem jak dodamy nowa klase, z ktorej odwiedzajacy ma korzystac
* czasami brak dostepu do prywatncyh skladowych klasy przez odwiedzajacyh

> [!NOTE] Zasada otwarte/zamkniete
> Oznacza mniej wiecej tyle, ze obiekty klas powinny byc otwarte na rozszerzenia, a zamkniete na modyfikacje. Innymi słowy: powinniśmy móc dodać nowe zachowania bez zmieniania istniejącego kodu. Anty przykładem może być coś takiego:
> ```c++
> class Shape {
> public:
>     virtual string getType() = 0;
> };
> 
> class Circle : public Shape {
> public:
>     string getType() override { return "circle"; }
> };
> 
> class Rectangle : public Shape {
> public:
>     string getType() override { return "rectangle"; }
> };
> 
> class AreaCalculator {
> public:
>     double calculate(Shape* shape) {
>         if (shape->getType() == "circle") {
>             // oblicz pole koła
>         } else if (shape->getType() == "rectangle") {
>             // oblicz pole prostokąta
>         }
>         // musimy modyfikować za każdym razem, gdy dodamy nowy typ figury
>     }
> };
> ```
> Zamiast tego dobrym rozwiazaniem, ktore zachowuje te zasade jest
> ```c++
>> class Shape {
> public:
>     virtual double area() = 0;
>     virtual ~Shape() = default;
> };
> 
> class Circle : public Shape {
> private:
>     double radius;
> public:
>     Circle(double r) : radius(r) {}
>     double area() override { return 3.14 * radius * radius; }
> };
> 
> class Rectangle : public Shape {
> private:
>     double width, height;
> public:
>     Rectangle(double w, double h) : width(w), height(h) {}
>     double area() override { return width * height; }
> };
> 
> class AreaCalculator {
> public:
>     double calculate(Shape* shape) {
>         return shape->area();
>     }
> };
> ```