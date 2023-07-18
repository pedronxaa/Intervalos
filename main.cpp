#include "lista.h"
#include <iostream>
using namespace std;

//funções auxiliares 
int min(int *vet) {
  int i, menor = vet[0];
  for (i = 1; i < 4; i++) {
    if (vet[i] < vet[i - 1]) {
      menor = vet[i];
    }
  }
  return menor;
}
int max(int *vet) {
  int i, maior = vet[0];
  for (i = 1; i < 4; i++) {
    if (vet[i] > vet[i - 1]) {
      maior = vet[i];
    }
  }
  return maior;
}

int pertence(int x, Lista *l) {
  for (; l != NULL; l = l->prox) {
    if (l->info == x) {
      return 0;
    }
  }
  return 1;
}

class Conjunto {
public:
  int inf, sup, ini, fim;
  Lista *ele_fora = inicializar();
  Conjunto() {
    ini = 0;
    fim = 0;
    inf = 0;
    sup = 0;
  }
  Conjunto(char af1, int num1, int num2, char af2) {
    if (af1 == '[') {
      ini = 1;
    } else if (af1 == '(' or af1 == ']') {
      ini = 0;
    }
    if (af2 == ']') {
      fim = 1;
    } else if (af2 == ')' or af2 == '[') {
      fim = 0;
    }
    inf = num1;
    sup = num2;
  }
  //método para verificar se o elemento pertence ao conjunto
  int contem(int x) {
    if (!pertence(x, ele_fora)) {
      return 0;
    } else if (x == this->inf && this->ini) {
      return 1;
    } else if (x == this->sup && this->fim) {
      return 1;
    } else if (x > this->inf && x < this->sup) {
      return 1;
    } else {
      return 0;
    }
  }
  //método para verificar se há interseção
  int intercepta(Conjunto b) {
    int prim = b.inf;
    int ult = b.sup;
    if (!b.contem(b.inf)) {
      prim++;
    }
    if (!b.contem(b.sup)) {
      ult--;
    }
    for (int i = prim; i <= ult; i++) {
      if (this->contem(i)) {
        return 1;
      }
    }
    return 0;
  }
  //metodo para calcular a media entre os elementos do intervalo
  float media() {
    float sum = 0;
    float media;
    int prim = this->inf;
    int ult = this->sup;
    if (!this->contem(this->inf)) {
      prim++;
    }
    if (!this->contem(this->sup)) {
      ult--;
    }
    int j = 0;
    for (int i = prim; i <= ult; i++) {
      if (pertence(i, ele_fora)) {
        sum += i;
        j++;
      }
    }
    media = sum / j;
    return media;
  }
  // método para calcular o produto de dois conjuntos
  Conjunto produto(Conjunto b) {
    int vet[] = {this->inf * b.inf, this->inf * b.sup, this->sup * b.inf,this->sup * b.sup};
    Conjunto c('[', min(vet), max(vet), ']');
    return c;
  }

  // método para fazer a união de dois conjuntos
  void uniao(Conjunto b) {
    if (this->intercepta(b)) {
      if (this->inf > b.inf) {
        this->inf = b.inf;
        this->ini = b.ini;
      } else if (this->inf == b.inf && b.ini && !this->ini) {
        this->ini = 1;
      }
      if (this->sup < b.sup) {
        this->sup = b.sup;
        this->fim = b.fim;
      } else if (this->sup == b.sup && b.fim && !this->fim) {
        this->fim = 1;
      }
    } else {
      if (this->sup == (b.inf - 1)) {
        if (!this->fim) {
          inserir(&ele_fora, this->sup);
        }
        if (!b.ini) {
          inserir(&ele_fora, b.inf);
        }
        this->sup = b.sup;
        this->fim = b.fim;
      } else if (this->inf == (b.sup + 1)) {
        if (!b.fim) {
          inserir(&ele_fora, b.sup);
        }
        if (!this->ini) {
          inserir(&ele_fora, this->inf);
        }
        this->inf = b.inf;
        this->ini = b.ini;
      } else {
        if (this->sup < b.inf) {
          if (!this->fim) {
            inserir(&ele_fora, this->sup);
          }
          for (int i = this->sup + 1; i <= b.inf - 1; i++) {
            inserir(&ele_fora, i);
          }
          this->sup = b.sup;
          this->fim = b.fim;

        } else if (this->inf > b.sup) {
          if (!b.fim) {
            inserir(&ele_fora, b.sup);
          }
          this->inf = b.inf;
          this->ini = b.ini;
          for (int i = b.sup + 1; i <= this->inf - 1; i++) {
            inserir(&ele_fora, i);
          }
        }
      }
    }
  }
};

int main() {
  Conjunto a('[', 0, 4, ')');
  Conjunto b('[', 5, 10, ']');
  Conjunto d;

  cout << "O conjunto d é: "<< (!(bool)d.ini && !(bool)d.fim && d.inf==d.sup ? "Conjunto vazio\n" : "") << endl;
  
  if (a.contem(4)) {
    cout << "O valor está contido\n\n";
  } else {
    cout << "O valor não está contido\n\n";
  }
  
  if (a.intercepta(b)) {
    cout << "Há interseção\n\n";
  } else {
    cout << "Não há interseção\n\n";
  }
   printf("A media é: %.2f\n\n", a.media());
  
  Conjunto c = a.produto(b);
  
  cout << "O conjunto produto é: "<< ((bool)c.ini ? "[" : "(") << c.inf << ", "<< c.sup << ((bool)c.fim ? "]\n" : ")\n") << endl;

  a.uniao(b);
  cout << "A união entre os conjuntos é: "<< ((bool)a.ini ? "[" : "(") << a.inf << ", "<< a.sup << ((bool)a.fim ? "]" : ")") << endl;
  
  printf("Elementos não inseridos na união: ");
  for (Lista *aux = a.ele_fora; aux != NULL; aux = aux->prox) {
    printf("%d ", aux->info);
  }
}
