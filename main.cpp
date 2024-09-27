#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <map>
#include <set>

template<typename Container>
void print(const Container& cnt) {
  for (const auto& item: cnt)
    std::cout << item << " ";
  
//  for (auto it = std::begin(cnt); it != std::end(cnt); ++it)
//    std::cout << *it << " ";
    
//  for (int i = 0; i < std::size(cnt); ++i) {
//    std::cout << cnt[i] << " ";
//  }
  std::cout << std::endl;
}

void ejemplo_vector() {
  std::vector<int> v;
  v.reserve(1000);
  
  v.push_back(10);  // --> O(1)
  v.insert(v.begin() + 1, 20); // equivalente a un push_back --> O(n)
  v.insert(v.begin(), 7);
  v.emplace_back(30); // Es equivalente a push_back --> Aparece a partir de la version C++11
  v.emplace(v.begin(), 5);  // Es equivalente a insert --> Aparece a partir de la version C++11
  print(v);
  std::cout << v.size() << std::endl;
//  std::cout << v.at(5) << std::endl; // Equivalente a v[5]
}

class Point {
  int x{};
  int y{};
public:
  Point(int x, int y): x(x), y(y) {}
  friend std::ostream& operator<< (std::ostream& out, const Point& pto) {
    out <<  "("<< pto.x << " " << pto.y << ")";
    return out;
  }
};

void ejemplo_deque () {
  std::deque<Point> d;
  d.push_back(Point(10, 20));  // deque::push_back(const Point& value) { data[last_pos] = value; }
  d.emplace_back(40, 80);      // deque::emplace_back(Args...args) { data[last_pos](args...); }
  d.emplace_front(100, 200);      // deque::emplace_back(Args...args) { data[last_pos](args...); }
  std::cout << d.front() << std::endl;
  std::cout << d.back() << std::endl;
  std::cout << d[1] << std::endl;
//  std::cout << d.at(3) << std::endl;
  print(d);
}

void ejemplo_list() {
  std::list<int> l = { 10, 20, 30, 40};
  print(l);
}

template <typename Container>
void print_range(const Container cnt, int start, int step) {
  for (int i = start; i < std::size(cnt); i += step)
    std::cout << *std::next(cnt.begin(),i) << " ";
  std::cout << std::endl;
}

void ejemplo_1() {
  std::vector v { 1, 2, 3, 4, 5, 6, 7, 8};
  print_range(v, 0, 2);
  std::deque d { 1, 2, 3, 4, 5, 6, 7, 8};
  print_range(d, 0, 2);
  std::list l { 1, 2, 3, 4, 5, 6, 7, 8};
  print_range(l, 0, 2);
}

void ejemplo_iteradores() {
  std::vector v { 1, 2, 3, 4, 5, 6, 7, 8};
  std::forward_list fl { 1, 2, 3, 4, 5, 6, 7, 8};
  std::list l { 1, 2, 3, 4, 5, 6, 7, 8};
  
  auto it_random = std::begin(v); // iterador Random
  auto it_forward = fl.begin();    // iterador Forward
  auto it_bidireccional = l.begin();     // iterador Bidireccional
  
  // De-refencia
  std::cout << *it_random << " " << *it_forward << " " << *it_bidireccional << std::endl;
  
  // Auto incremento ++it
  ++it_random; ++it_forward; ++it_bidireccional;
  std::cout << *it_random << " " << *it_forward << " " << *it_bidireccional << std::endl;

  // Auto decrementar --it
  --it_random; --it_bidireccional;
//  std::advance(it_forward, -1); // No esta permitido para el Forward
  std::cout << *it_random << " " << *it_forward << " " << *it_bidireccional << std::endl;

  // Acceso por subinidices
  std::cout << it_random[3] << " " << *it_forward << " " << *it_bidireccional << std::endl;
  
//  it_random = it_random + 3;
  std::advance(it_random, 3);
//  it_bidireccional = it_bidireccional + 3;
  it_bidireccional = std::next(it_bidireccional, 3);
  std::cout << *it_random << " " << *it_forward << " " << *it_bidireccional << std::endl;

  std::advance(it_random, -3);
  it_bidireccional = std::prev(it_bidireccional, 3);
  std::cout << *it_random << " " << *it_forward << " " << *it_bidireccional << std::endl;
}

void ejemplo_iterador_reverso() {
  std::vector v { 1, 2, 3, 4, 5, 6, 7, 8};
  for (auto it = std::rbegin(v); it != std::rend(v); ++it) {
    std::cout << *it << " ";
  }
}

template <typename Iterator>
auto sumar_cuadrados(Iterator start, Iterator stop) {
  
  if constexpr (std::is_same_v<typename Iterator::iterator_category, std::random_access_iterator_tag>) {
    std::cout << "Iterador del tipo random\n";
  }
  else if constexpr (std::is_same_v<typename Iterator::iterator_category, std::bidirectional_iterator_tag>) {
    std::cout << "Iterador del tipo bidireccional\n";
  }
  
  typename Iterator::value_type total{};
  for (auto it = start; it != stop; ++it)
    total += (*it)*(*it);
  return total;
}

void ejemplo_sumarizar() {
  std::vector v { 1, 2, 3, 4, 5, 6, 7, 8};
  auto total1 = sumar_cuadrados(std::begin(v), std::end(v));
  std::cout << total1 << std::endl;

  std::list l { 1, 2, 3, 4, 5, 6, 7, 8};
  auto total2 = sumar_cuadrados(std::begin(l), std::end(l));
  std::cout << total2 << std::endl;
}

int main() {
//  ejemplo_vector();
//  ejemplo_deque();
//  ejemplo_list();
//  ejemplo_1();
//  ejemplo_iteradores();
//  ejemplo_iterador_reverso();
  ejemplo_sumarizar();
  return 0;
}
