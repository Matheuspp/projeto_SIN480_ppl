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
    int C; // conjunto de componentes
    int E; // conjunto de especialistas

    // Dados de entrada dependentes dos conjuntos
    char** NomeComponente; // por componente
    char** NomeCelula; // por componente
    char** NomeServico; // por compenente
    float* Desmontagem; // por componente
    float* Limpeza; // por componente
    float* Vdi; // por componente
    float* End; // por componente
    float* Protecao; // por componente
    float* Pintura; // por componente
    float* Conf_pecas; // por componente
    float* Lib_montagem; // por componente
    float* Montagem; // por componente
    float* InspecaoFI; // por componente
    float* Ensaio; // por componente
    float* Montagem_final; // por componente
    float* Pintura_final; // por componente
    float* Finalizacao; // por componente
    float* Cf; // por componente
    float* HH_total; // por componente
    float* Demanda; // por componente

    char** NomeEspec; // por especialista
    char** Mec_leve; // por especialista
    char** Mec_medio; // por especialista
    char** Mec_pesado; // por especialista
    char** Insp_leve; // por especialista
    char** Insp_medio; // por especialista
    char** Insp_pesado; // por especialista
    char** End_esp; // por especialista
    char** Limpeza_esp; // por especialista
    char** Protecao_esp; // por especialista
    char** Pintura_esp; // por especialista


    float* TotalHorasDisponivel; // especialidade

    // Leitura do Arquivo
    FILE* fp;
    fp = fopen(argv[1],"r");

    if( fp == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    // Leitura dos conjuntos
    fscanf(fp, "%d", &C);
    fscanf(fp, "%d", &E);

    // Definindo os dados de entrada de acordo com o tamanho dos conjuntos lidos
    // Por Componente
    NomeComponente = new char*[C];
    for(int c; c < C; c++)
    {
      NomeComponente[c] = new char[51];
    }

    NomeServico = new char*[C];
    for(int c; c < C; c++)
    {
      NomeServico[c] = new char[51];
    }

    NomeCelula = new char*[C];
    for(int c; c < C; c++)
    {
      NomeCelula[c] = new char[51];
    }

    Desmontagem = new float[C];
    Limpeza = new float[C];
    Vdi = new float[C];
    End = new float[C];
    Protecao = new float[C];
    Pintura = new float[C];
    Conf_pecas = new float[C];
    Lib_montagem = new float[C];
    Montagem = new float[C];
    InspecaoFI = new float[C];
    Ensaio = new float[C];
    Montagem_final = new float[C];
    Pintura_final = new float[C];
    Finalizacao= new float[C];
    Cf = new float[C];
    HH_total = new float[C];
    Demanda = new float[C];

    // Por especialidade
    NomeEspec = new char*[E];
    for(int e = 0 ; e < E; e++)
    {
      NomeEspec[e] = new char[51];
    }

    Mec_leve = new char*[E];
    for(int e = 0 ; e < E; e++)
    {
      Mec_leve[e] = new char[51];
    }

    Insp_leve = new char*[E];
    for(int e = 0 ; e < E; e++)
    {
      NomeEspec[e] = new char[51];
    }

    Mec_medio= new char*[E];
    for(int e = 0 ; e < E; e++)
    {
      Mec_medio[e] = new char[51];
    }

    Insp_medio= new char*[E];
    for(int e = 0 ; e < E; e++)
    {
      Insp_medio[e] = new char[51];
    }

    Mec_pesado = new char*[E];
    for(int e = 0 ; e < E; e++)
    {
      Mec_pesado[e] = new char[51];
    }

    Insp_pesado= new char*[E];
    for(int e = 0 ; e < E; e++)
    {
      Insp_pesado[e] = new char[51];
    }

    End_esp= new char*[E];
    for(int e = 0 ; e < E; e++)
    {
      End_esp[e] = new char[51];
    }

    Limpeza_esp = new char*[E];
    for(int e = 0 ; e < E; e++)
    {
      Limpeza_esp[e] = new char[51];
    }

    Protecao_esp = new char*[E];
    for(int e = 0 ; e < E; e++)
    {
      Protecao_esp[e] = new char[51];
    }

    Pintura_esp = new char*[E];
    for(int e = 0 ; e < E; e++)
    {
      Pintura_esp[e] = new char[51];
    }


    // Após a declaração dos tamanhos dos dados de entrada, realizando a leitura
    // por componente
    for(int c = 0; c < C; c++)
    {
        fscanf(fp, "%s", NomeComponente[c]);
        fscanf(fp, "%s", NomeServico[c]);
        fscanf(fp, "%s", NomeCelula[c]);

        fscanf(fp, "%f", &Desmontagem[c]);
        fscanf(fp, "%f", &Limpeza[c]);
        fscanf(fp, "%f", &Vdi[c]);
        fscanf(fp, "%f", &End[c]);
        fscanf(fp, "%f", &Protecao[c]);
        fscanf(fp, "%f", &Pintura[c]);
        fscanf(fp, "%f", &Conf_pecas[c]);
        fscanf(fp, "%f", &Lib_montagem[c]);
        fscanf(fp, "%f", &Montagem[c]);
        fscanf(fp, "%f", &InspecaoFI[c]);
        fscanf(fp, "%f", &Ensaio[c]);
        fscanf(fp, "%f", &Montagem_final[c]);
        fscanf(fp, "%f", &Pintura_final[c]);
        fscanf(fp, "%f", &Finalizacao[c]);
        fscanf(fp, "%f", &Cf[c]);
        fscanf(fp, "%f", &HH_total[c]);
        fscanf(fp, "%f", &Demanda[c]);

    }

    // por especialidade
    for(int e = 0; e < E; e++)
    {
        fscanf(fp, "%s", NomeEspec[e]);
        fscanf(fp, "%s", Mec_leve[e]);
        fscanf(fp, "%s", Insp_leve[e]);
        fscanf(fp, "%s", Mec_medio[e]);
        fscanf(fp, "%s", Insp_medio[e]);
        fscanf(fp, "%s", Mec_pesado[e]);
        fscanf(fp, "%s", Insp_pesado[e]);
        fscanf(fp, "%s", Mec_leve[e]);
        fscanf(fp, "%s", Insp_leve[e]);
        fscanf(fp, "%s", End_esp[e]);
        fscanf(fp, "%s", Limpeza_esp[e]);
        fscanf(fp, "%s", Protecao_esp[e]);
        fscanf(fp, "%s", Pintura_esp[e]);
    }

    // Impressão para Verificação dos dados


    printf("Numero de Componentes: %d\n", C);
    printf("Numero de especialistas: %d\n\n", E);

    printf("Componentes: \n");
    for(int c = 0; c < C; c++)
    {
      printf("x%d \t %s \t %s \t %.2f \n",c+1, NomeComponente[c], NomeCelula[c], HH_total[c]);
    }
    printf("\n\n");

    printf("Especialistas: \n");
    for(int e = 0; e < E; e++)
    {
      printf("T%d \t %s \t %s \t %s\n",e+1, NomeEspec[e], Mec_leve[e], Mec_medio[e]);
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

    IloNumVarArray x(env,C, 0, IloInfinity, ILOFLOAT); //  y >= 0
    for(int c = 0 ; c < C; c++)
    {
        x[c] = IloNumVarArray(env, C, 0, IloInfinity, ILOFLOAT);
    }
    // adicionar as variáveis no modelo
    for(int c = 0 ; c < C; c++)
    {
            stringstream var;
            var << "x["<< NomeComponente[c] << "]";
            x[c].setName(var.str().c_str());
            modelo.add(x[c]);
    }




    // DECLARAÇÃO DA FUNÇÃO OBJETIVO

    IloExpr fo(env);

    //Somatório...
    for(int c = 0; c < C; c++){
        fo += HH_total[c]*x[c];

    }


    //IloMinimize e IloMaximize
    modelo.add(IloMaximize(env, fo));


    // DECLARAÇÃO DAS RESTRIÇÕES DO PROBLEMA

    // declarando a restrição
    // IloRange parametros: ambiente, valor min, expressão, valor maximo

    TotalHorasDisponivel = E*1.617 // calcular o total de horas disponiveis

    // Restrição associada a mao de obra

    // para mecanico leve
    IloExpr soma(env);
    for(int c = 0; c < 26; c++) {
        soma += x[c];
    }
    //declarar minha restrição
    IloRange areaFaz(env, -IloInfinity, soma, 2*1.617);
    // dando um nome para a restrição
    stringstream rest;
    rest << "MLeve[" << NomeEspec[0] << "]: ";
    MLeve.setName(rest.str().c_str());
    //adicionar ao modelo
    modelo.add(MLEVE);



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












