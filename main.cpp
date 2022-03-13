#include<iostream>
#include<stdio.h>
#include <sstream>

#include <ilcplex/ilocplex.h>


typedef IloArray<IloNumVarArray> IloNumVarMatrix; // 2 dimensoes
typedef IloArray<IloNumVarMatrix> IloNumVar3Matrix; // 3 dimensoes
typedef IloArray<IloNumVar3Matrix> IloNumVar4Matrix; // 4 dimensoes

using namespace std;

int main(int argc, char *argv[])
{

    // Declarando conjuntos de entrada
    int F; // conjunto de fazendas
    int C; // conjunto de culturas
    
    // Dados de entrada dependentes dos conjuntos
    char** NomeFazenda; // por fazenda
    float* Area; // por fazenda
    float* Agua; // por fazenda

    char** NomeCultura; // por Cultura
    float* AMax; // por cultura
    float* ConsAgua; // por cultura
    float* Lucro; // por cultura    

    // Leitura do Arquivo
    FILE* fp;
    fp = fopen(argv[1],"r");

    if( fp == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);    
    }
    
    // Leitura dos conjuntos
    fscanf(fp, "%d", &F);
    fscanf(fp, "%d", &C);

    // Definindo os dados de entrada de acordo com o tamanho dos conjuntos lidos
    // Por fazenda
    NomeFazenda = new char*[F];
    for(int f; f < F; f++)
    {
      NomeFazenda[f] = new char[51];
    }

    Area = new float[F];
    Agua = new float[F];

    // Por cultura
    NomeCultura = new char*[C];
    for(int c = 0 ; c < C; c++)
    {
      NomeCultura[c] = new char[51];
    }

    AMax = new float[C];
    ConsAgua = new float[C];
    Lucro = new float[C];


    // Após a declaração dos tamanhos dos dados de entrada, realizando a leitura
    // por fazenda
    for(int f= 0; f < F; f++)
    {
        fscanf(fp, "%s", NomeFazenda[f]);
        fscanf(fp, "%f", &Area[f]);
        fscanf(fp, "%f", &Agua[f]);   
    }    

    // por cultura
    for(int c = 0; c < C; c++)
    {
        fscanf(fp, "%s", NomeCultura[c]);
        fscanf(fp, "%f", &AMax[c]);
        fscanf(fp, "%f", &ConsAgua[c]);
        fscanf(fp, "%f", &Lucro[c]);
    }

    // Impressão para Verificação dos dados
    

    printf("Numero de faz: %d\n", F);
    printf("Numero de cult: %d\n\n", C);

    printf("Fazendas: \n");
    for(int f = 0; f < F; f++)
    {
      printf("%s \t %.2f \t %.2f \n", NomeFazenda[f], Area[f], Agua[f]);
    }
    printf("\n\n");

    printf("Culturas: \n");
    for(int c = 0; c < C; c++)
    {
      printf("%s \t %.2f \t %.2f \t %.2f\n", NomeCultura[c], AMax[c], ConsAgua[c], Lucro[c]);
    }

    printf("\n");


    // DECLARANDO O AMBIENTE E O MODELO MATEMATICO
    IloEnv env;
	  IloModel modelo;
    // iniciando o modelo
    modelo = IloModel(env);
    

    
    /*
    // ---------------  DECLARAÇÃO DE VARIÁVEIS DE UMA DIMENSÃO    
    // parametros para declaração de variáveis: ambiente, tamanho, valor min, valor max, tipo (ILOINT, ILOFLOAT, ILOBOOL)
    IloNumVarArray y(env,TAM, 0, IloInfinity, ILOFLOAT); //  y >= 0

    // adicionar as variáveis ao modelo
    for(int t1 = 0; t1 < TAM; t1++)
    {
        stringstream var;
        var << "y[" << t1 << "]"; // var << "y[0]"
        y[t1].setName(var.str().c_str());
        modelo.add(y[t1]);
    }
    // ---------------  DECLARAÇÃO DE VARIÁVEIS DE DUAS DIMENSÕES
    // parâmetros quando não é IloNumVarArray: ambiente, tamanho
    IloNumVarMatrix k(env, TAM1);
    for(int t1 = 0 ; t1 < TAM1; t1++)
    {
        k[t1] = IloNumVarArray(env, TAM2, 0, IloInfinity, ILOFLOAT);
    }
    // adicionar as variáveis no modelo
    for(int t1 = 0 ; t1 < TAM1; t1++)
    {
        for(int t2 = 0; t2 < TAM2; t2++)
        {
            stringstream var;
            var << "k["<< t1 << "]["<< t2 << "]"; // var << "k[1][3]";
            k[t1][t2].setName(var.str().c_str());
            modelo.add(k[t1][t2]);
        }
    }
    */

    IloNumVarMatrix x(env, F);
    for(int f = 0 ; f < F; f++)
    {
        x[f] = IloNumVarArray(env, C, 0, IloInfinity, ILOFLOAT);
    }
    // adicionar as variáveis no modelo
    for(int f = 0 ; f < F; f++)
    {
        for(int c = 0; c < C; c++)
        {
            stringstream var;
            var << "x["<< NomeFazenda[f] << "]["<< NomeCultura[c] << "]";
            x[f][c].setName(var.str().c_str());
            modelo.add(x[f][c]);
        }
    }


    

    // DECLARAÇÃO DA FUNÇÃO OBJETIVO

    IloExpr fo(env);

    //Somatório...
    for(int f = 0; f < F; f++)
    {
      for(int c = 0; c < C; c++)
      {
        fo += Lucro[c]*x[f][c];
      }
    }

      
    //IloMinimize e IloMaximize
    modelo.add(IloMaximize(env, fo));

    
    // DECLARAÇÃO DAS RESTRIÇÕES DO PROBLEMA

    // declarando a restrição
    // IloRange parametros: ambiente, valor min, expressão, valor maximo
    
    // Restrição associada a area da fazenda
    for(int f = 0; f < F; f++) //para todo
    {
      IloExpr soma(env);
      for( int c = 0; c < C; c++)
      {
        soma += x[f][c];
      }
      //declarar minha restrição
      IloRange areaFaz(env, -IloInfinity, soma, Area[f]);
      // dando um nome para a restrição
      stringstream rest;
      rest << " AreaFaz[" << NomeFazenda[f] << "]: "; 
      areaFaz.setName(rest.str().c_str());
      //adicionar ao modelo
      modelo.add(areaFaz);       

    }

    // associada a água disponivel nas Fazendas
    
    for(int f = 0; f < F; f++)
    {
       IloExpr soma(env);
       for(int c = 0; c < C; c++)
       {
          soma+= ConsAgua[c]*x[f][c];
       }
        //declarar minha restrição
       IloRange rest_consAgua(env, -IloInfinity , soma, Agua[f]);
       //nome restrição
       stringstream rest;
       rest << "ConsAgua[" << NomeFazenda[f] << "]:";
       rest_consAgua.setName(rest.str().c_str());
       // adiciono ao modelo
      modelo.add(rest_consAgua);
      
    }


    // associada a área máxima plantada por cultura
    for(int c = 0; c < C; c++)
    {
        IloExpr soma(env);
        for(int f = 0; f < F; f++)
        {
          soma+= x[f][c];
        }
        // declarar minha restrição
        IloRange rest_areaCultura(env, -IloInfinity, soma, AMax[c]);
        //nome da restrição
        stringstream rest;
        rest << "AreaMaxCult[" << NomeCultura[c] << "]:";
        rest_areaCultura.setName(rest.str().c_str());
        //adicionar ao modelo
        modelo.add(rest_areaCultura);
        
    }

    // restrição associada a proporção de area plantada
    for(int f = 0; f < F; f++)
    {
      for(int g = 0; g < F; g++)
      {
          if( f != g)
          {
              IloExpr soma1(env);
              IloExpr soma2(env);

              for(int c = 0 ; c < C; c++)
              {
                  soma1+=x[f][c];            
                  soma2+=x[g][c];
              }
              //declarar minha restrição
              IloRange rest_proporcao(env, 0, soma1/Area[f] - soma2/Area[g], 0);
              stringstream rest;
              rest << "Proporc[" << NomeFazenda[f] <<"]["<< NomeFazenda[g] <<"]:";
              rest_proporcao.setName(rest.str().c_str());
              //adicionar ao modelo
              modelo.add(rest_proporcao);
          }
      }
    }


    // RESOLVENDO O MODELO

    // Carregando o módulo do Cplex
    IloCplex cplex(modelo);
    // exportando o lp
    cplex.exportModel("fazenda.lp");
    // Executando o modelo
    cplex.solve();
    
    // PEGAR OS VALORES DAS VARIÁVEIS 
    //cplex.getValue(NOME_VAR)    
    printf("\n ---------- Valor das variaveis -------------\n");
    for(int f = 0; f < F; f++)
    {
      printf("********");
      printf("%s \n", NomeFazenda[f]);
      for(int c = 0; c < C; c++)
      {
        double valor = cplex.getValue(x[f][c]);
        printf("%s: %.2f \n", NomeCultura[c], valor);
      }
    }

    printf("Funcao objetivo: %.2f\n", cplex.getObjValue());

    return 0;
}












