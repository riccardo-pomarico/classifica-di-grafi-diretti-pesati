#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
  int numeroDiNodi, classifica;
  char line[1000000], *str;
  char line2[20];
  int conta1 = 0, conta2 = 0;

  str = fgets(line, 1000000, stdin);

  numeroDiNodi = atoi(str);
  int matrix[numeroDiNodi][numeroDiNodi];

  while (*str != ' ') {
    str++;
  }
  str++;

  classifica = atoi(str);
  int topGraphs[classifica+1], weightGraphs[classifica+1];

  for (int i = 0; i < classifica; i++) {
    topGraphs[i] = -1;
    weightGraphs[i] = 0;
  }

  int min = -1, nodo = -1;
  int costoTotale = 0, numGrafo = 0, somma = 0, pos = 1, true = 0, max = 0, count = 0, n = 0;
  int daAnalizzare[numeroDiNodi], visitati[numeroDiNodi], costi[numeroDiNodi];
  int l, r, posmax, heap, top, temp;
  int in, unita = 1;

  for (int i = 0; i < numeroDiNodi; i++) {
    costi[i] = -1;
    daAnalizzare[i] = i;
  }

  costi[0] = 0;
  visitati[0] = 0;
  daAnalizzare[0] = -1;
  topGraphs[0] = 0;
  weightGraphs[0] = 0;

  while ((str = fgets(line2, 20, stdin)) != NULL) {
    switch (*str) {
      case 'A':
                conta1 = 0;

                in = getchar_unlocked();

                while (in != '\n' && conta1 != numeroDiNodi) {

                  while (in != '\n' && in != ',') {
                    in -= 48;

                    if (unita != 1) {
                      matrix[conta1][conta2] *= 10;
                      matrix[conta1][conta2] += in;
                    } else {
                      matrix[conta1][conta2] = in;
                      unita = 0;
                    }

                    in = getchar_unlocked();
                  }

                  if (in != '\n') {
                    in = getchar_unlocked();
                    conta2++;
                  } else {
                    conta1++;
                    conta2 = 0;

                    if (conta1 != numeroDiNodi) {
                      in = getchar_unlocked();
                    }
                  }

                  unita = 1;

                }

                while (true == 0) {

                  for (int i = 0; i < numeroDiNodi; i++) {

                    if (matrix[visitati[n]][i] != 0 && visitati[n] != i && i != 0) {

                      somma = matrix[visitati[n]][i] + costi[visitati[n]];

                      if (costi[i] > somma || costi[i] == -1) {
                        costi[i] = somma;

                        if (daAnalizzare[i] == -1) {

                          daAnalizzare[i] = i;
                          visitati[i] = 0;
                          count--;

                        }

                        if (costi[i] < min || min == -1) {
                          min = costi[i];
                          nodo = i;
                        }
                      }
                    }
                  }

                  min = -1;

                  if (nodo != -1 && count != numeroDiNodi) {
                    if (daAnalizzare[nodo] != -1) {
                      count++;
                      visitati[nodo] = nodo;
                      daAnalizzare[nodo] = -1;
                      n = nodo;
                    } else {
                      int num = 0;

                      for (int i = 0; i < numeroDiNodi; i++) {
                        if (daAnalizzare[i] != -1) {

                          if (costi[i] != -1) {
                            if (min == -1) {
                              min = costi[i];
                              nodo = i;
                            } else if (min > costi[i]) {
                              min = costi[i];
                              nodo = i;
                            }
                          } else {
                            num++;
                          }

                        } else {
                          num++;
                        }
                      }

                      if (num == numeroDiNodi) {
                        true = 1;
                      } else {
                        count++;
                        visitati[nodo] = nodo;
                        daAnalizzare[nodo] = -1;
                        n = nodo;
                      }

                    }
                  } else {
                    true = 1;
                  }
                }

                if (nodo == -1) {

                  costoTotale = 0;

                } else {
                  for (int i = 0; i < numeroDiNodi; i++) {

                    if (costi[i] != -1) {
                      costoTotale += costi[i];
                    }

                    costi[i] = -1;
                    visitati[i] = 0;
                    daAnalizzare[i] = i;
                  }

                  costi[0] = 0;
                  visitati[0] = 0;
                  daAnalizzare[0] = -1;
                }

                if (pos <= classifica) {

                  weightGraphs[pos] = costoTotale;
                  topGraphs[pos] = numGrafo;

                  if (pos == 1) {

                    max = weightGraphs[1];

                  } else {

                    if (max < weightGraphs[pos]) {
                      max = weightGraphs[pos];
                    }

                  }

                  if (pos == classifica) {

                    for (int i = pos/2; i >= 1; i--) {

                      top = i;
                      heap = 0;

                      while (heap == 0) {

                        l = 2 * top;
                        r = 2 * top;
                        r++;

                        if (l <= classifica && weightGraphs[l] > weightGraphs[top]) {
                          posmax = l;
                        } else {
                          posmax = top;
                        }

                        if (r <= classifica && weightGraphs[r] > weightGraphs[posmax]) {
                          posmax = r;
                        }

                        if (posmax != top) {

                          temp = weightGraphs[top];
                          weightGraphs[top] = weightGraphs[posmax];
                          weightGraphs[posmax] = temp;
                          temp = topGraphs[top];
                          topGraphs[top] = topGraphs[posmax];
                          topGraphs[posmax] = temp;

                          top = posmax;

                        } else {
                          heap = 1;
                        }
                      }
                    }
                  }

                  pos++;

                } else {

                  pos = classifica;

                  if (costoTotale < max) {

                    max = weightGraphs[2];
                    if (max < weightGraphs[3]) {
                      max = weightGraphs[3];
                    }

                    if (costoTotale > max) {

                      weightGraphs[1] = costoTotale;
                      topGraphs[1] = numGrafo;

                      max = costoTotale;

                    } else {

                      weightGraphs[1] = costoTotale;
                      topGraphs[1] = numGrafo;

                      top = 1;
                      heap = 0;

                      while (heap == 0) {
                        l = 2 * top;
                        r = 2 * top;
                        r++;

                        if (l <= classifica && weightGraphs[l] > weightGraphs[top]) {
                          posmax = l;
                        } else {
                          posmax = top;
                        }

                        if (r <= classifica && weightGraphs[r] > weightGraphs[posmax]) {
                          posmax = r;
                        }

                        if (posmax != top) {

                          temp = weightGraphs[top];
                          weightGraphs[top] = weightGraphs[posmax];
                          weightGraphs[posmax] = temp;
                          temp = topGraphs[top];
                          topGraphs[top] = topGraphs[posmax];
                          topGraphs[posmax] = temp;

                          top = posmax;
                        } else {
                          heap = 1;
                        }
                      }

                      max = weightGraphs[1];
                    }
                  }

                  pos++;
                }

                numGrafo++;

                costi[0] = 0;
                true = 0;
                costoTotale = 0;
                count = 0;
                min = -1;
                nodo = -1;

                break;

      case 'T':
                for (int x = 1; x <= classifica; x++) {
                  if (topGraphs[x] == -1) {
                    printf("\n");
                    x = classifica;
                  } else if ((topGraphs[x+1] == -1) || (x + 1 == classifica + 1)) {
                    printf("%d\n", topGraphs[x]);
                    x = classifica;
                  } else {
                    printf("%d ", topGraphs[x]);
                  }
                }

                break;

      default:
                break;
    }
  }

  return 0;
}
