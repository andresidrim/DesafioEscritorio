#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define TAMANHO_NOME 20 // Tamanho máximo para o nome do jogador

// Struct do jogador
typedef struct Jogador {
    char nome[TAMANHO_NOME]; // Nome do jogador
    int pontos; // Quantidade de pontos que o jogador possui
    int pontos_totais_possiveis; // Quantidade total de pontos possiveis do jogador
} Jogador;

// Struct da maquina/adversario
typedef struct Maquina {
    int pontos; // Quantidade de pontos que a maquina possui
    int pontos_totais_possiveis; // Quantidade total de pontos possiveis da maquina
} Maquina;

// Declarando funções
void IniciarJogo(Jogador *jogador, Maquina *maquina);
void Regras();
void CobrancaJogador(Jogador *jogador, Maquina *maquina);
void CobrancaMaquina(Jogador *jogador, Maquina *maquina);
void CobrancasAlternadas(int equipe, Jogador *jogador, Maquina *maquina);

void Start(Jogador *jogador, Maquina *maquina)
{
    // Declarando os valores inciais das variaveis dos jogadores
    jogador->pontos = 0; // Jogador inicia com 0 pontos
    jogador->pontos_totais_possiveis = 5; // Pode fazer até 5 pontos
    maquina->pontos = 0; // Maquina inicia com 0 pontos
    maquina->pontos_totais_possiveis = 5; // Pode fazer até 5 pontos

    int escolha; // Variavel para escolhas dentro do jogo
    do
    {
        printf("####################################\n\n");
        printf("            1 - Iniciar\n            2 - Regras\n            0 - Sair\n\n");
        printf("####################################\n\n");

        escolha = getch(); // Uso o getch para que o usuario nao tenha que apertar o ENTER. Getch() vai retornar o valor do caracter apertado na tabela ASCII

        system("cls || clear"); // Apaga o que já foi printado da tela

        if (escolha == 49) { IniciarJogo(jogador, maquina); } // Se a escolha for = a 49 (valor do 1 na tabela ASCII), o jogo irá inciar
        if (escolha == 50) { Regras(); } // Se a escolha for = 50 (valor do 2 na tabela ASCII), abrirá o menu das regras
    } while (escolha != 48); // Se a escolha for = 48 (valor do 0 na tabela ASCII), o jogo fecha

    printf("Finalizando aplicativo...\n");
    exit(0); // Finaliza a aplicação
}

void Regras()
{
    printf("O jogador tem 5 possibilidades de cobranca e defesa: Canto Superior Esquerdo, Canto Inferior Esquerdo, Centro, Canto Superior Direito e Canto Inferior Direito\n\nA maquina devera escolher a cobranca e o local da defesa de forma aleatoria\n\nSe durante as 5 penalidades a diferenca do placar for irreversivel o jogo deve finalizar e anunciar o vencedor\n\nSe apos as 5 penalidades o placar permanecer empatado, iniciarao as cobranças alternadas, se um time errar e o outro acertar o jogo deve finalizar e anunciar o vencedor");
    printf("\n\n\nPressione qualquer tecla para continuar\n");
    getch(); // Jogo irá pausar até uma tecla ser apertada (Poderia usar o system("pause"), mas ele não funciona em sistemas Linux)
    system("cls || clear");
}

void IniciarJogo(Jogador *jogador, Maquina *maquina)
{
    srand(time(NULL));

    printf("Qual o seu nome: ");
    fgets(jogador->nome, TAMANHO_NOME, stdin); // Salva o nome do jogador na variavel jogador->nome, sendo o limite de caracteres = ao TAMANHO_NOME
    system("cls || clear");

    int jogo_acabou = 0; // funciona como um bool, se o jogo acabar = 1, se nao = 0
    int jogo_empatado = 0; // funciona como um bool, se o jogo empatar = 1, se nao = 0

    // Gera um valor aleatorio entre 0 e 1 e o salva na variavel equipe
    int equipe = rand() % 2; // Funciona como um bool, se equipe = 0 a maquina iniciará as cobranças, se nao o jogador irá

    // Contador para verificar se ambos os times (jogador e maquina) já cobraram os lances
    int contador = 0; // Se o contador for = 2, ambos os times já fizeram suas cobranças

    do
    {
        system("cls || clear");
        // Se algum dos times não tiver como virar o jogo, o jogo acaba
        if (jogador->pontos > maquina->pontos_totais_possiveis || maquina->pontos > jogador->pontos_totais_possiveis) { break; }
        if (equipe) // Se equipe = 1
        {
            printf("%s vai cobrar..\n\nPressione qualquer tecla para continuar\n", jogador->nome);
            getch();
            system("cls || clear");
            CobrancaJogador(jogador, maquina); // Chama a função de cobranças do jogador
            equipe--; // Troca a equpe que irá cobrar
            contador++; // Soma 1 ao contador
        }
        else
        {
            printf("Maquina vai cobrar..\n\nPressione qualquer tecla para continuar\n");
            getch();
            system("cls || clear");
            CobrancaMaquina(jogador, maquina); // Chama a função de cobranças da maquina
            equipe++; // Troca a equpe que irá cobrar
            contador++; // Soma 1 ao contador
        }
    } while (contador < 2); // Se o contador for menor que 2, o jogo continuará

    system("cls || clear");
    printf("Pontuacao de %s: %d\nPontuacao da Maquina: %d\n\nPressione qualquer tecla para continuar\n", jogador->nome, jogador->pontos, maquina->pontos);
    getch();
    system("cls || clear");

    // Se a maquina tiver mais pontos que o jogador, ela ganhará. Jogador voltará ao menu
    if (maquina->pontos > jogador->pontos)
    {
        printf("Maquina venceu!\n\nPressione qualquer tecla para voltar ao menu\n");
        getch();
        // Reinicia os valores das variaveis, deixando-as prontas para um novo jogo
        jogador->pontos = 0;
        jogador->pontos_totais_possiveis = 5;
        maquina->pontos = 0;
        maquina->pontos_totais_possiveis = 5;
    }

    // Se o jogador tiver mais pontos que a maquina, ele ganhará. Jogador voltará ao menu
    else if (maquina->pontos < jogador->pontos)
    {
        printf("%s venceu!\n\nPressione qualquer tecla para voltar ao menu\n", jogador->nome);
        getch();
        // Reinicia os valores das variaveis, deixando-as prontas para um novo jogo
        jogador->pontos = 0;
        jogador->pontos_totais_possiveis = 5;
        maquina->pontos = 0;
        maquina->pontos_totais_possiveis = 5;
    }

    // Se ambos os times tiverem a mesma quantidade de pontos, o jogo empatará
    else
    {
        printf("Empate!\n\nPressione qualquer tecla para avancar para as cobrancas alternadas\n");
        getch();
        system("cls || clear");
        CobrancasAlternadas(equipe, jogador, maquina); // Chama a função de cobranças alternadas
    }

    system("cls || clear");
}

// Jogador cobra os lançes
void CobrancaJogador(Jogador *jogador, Maquina *maquina)
{
    srand(time(NULL));

    int escolha; // Variavel para escolhas dentro do jogo
    int contador = 0; // Conta quantas vezes o jogador já fez um chute

    do
    {
        do
        {
            printf("Onde voce deseja chutar?\n\n1 - Canto Superior Esquerdo\n2 - Canto Inferior Esquerdo\n3 - Canto Superior Direito\n4 - Canto Inferior Esquerdo\n5 - Centro\n\nPontuacao de %s: %d\nPontuacao da Maquina: %d\n", jogador->nome, jogador->pontos, maquina->pontos);
            escolha = getch();
            system("cls || clear");
        } while (escolha < 49 || escolha > 53); // Enquanto a escolha nao estiver entre 49 e 53 (Valores do 1 ao 5 na tabela ASCII), este menu ficará na tela

        int defesa_da_maquina = rand() % 5; // Maquina gera um numero de 0 a 4
        defesa_da_maquina += 49; // Soma com 49, para que a escolha da maquina fique na mesma faixa de valores da escolha do jogador

        if (escolha == defesa_da_maquina) // Se a maquina escolher o mesmo lugar do jogador, ela defende seu chute
        {
            printf("Maquina defendeu\n\nPressione qualquer tecla para continuar\n");
            getch();
            jogador->pontos_totais_possiveis--; // Subtrai 1 dos pontos possiveis do jogador
        }
        else // Se nao, o jogador faz ponto
        {
            printf("%s fez gol!\n\nPressione qualquer tecla para continuar\n", jogador->nome);
            getch();
            jogador->pontos++; // Soma 1 aos pontos do jogador
        }

        system("cls || clear");

        if (maquina->pontos > jogador->pontos_totais_possiveis) { break; } // Se o jogador nao tiver mais como virar o jogo, o jogo acaba

        contador++; // Soma 1 ao contador
    } while (contador < 5); // Vez do jogador acaba quando faz 5 cobranças
}

// Maquina cobra os lançes
void CobrancaMaquina(Jogador *jogador, Maquina *maquina)
{
    srand(time(NULL));

    int escolha; // Variavel para escolhas dentro do jogo
    int contador = 0; // Conta quantas vezes a maquina já fez um chute

    do
    {
        int chute_da_maquina = rand() % 5; // Maquina gera um numero de 0 a 4
        chute_da_maquina += 49; // Soma com 49, para que a escolha da maquina fique na mesma faixa de valores da escolha do jogador

        do
        {
            printf("Onde voce deseja defender?\n\n1 - Canto Superior Esquerdo\n2 - Canto Inferior Esquerdo\n3 - Canto Superior Direito\n4 - Canto Inferior Esquerdo\n5 - Centro\n\nPontuacao de %s: %d\nPontuacao da Maquina: %d\n", jogador->nome, jogador->pontos, maquina->pontos);
            escolha = getch();
            system("cls || clear");
        } while (escolha < 49 || escolha > 53); // Enquanto a escolha nao estiver entre 49 e 53 (Valores do 1 ao 5 na tabela ASCII), este menu ficará na tela

        if (escolha == chute_da_maquina) // Se o jogador escolher o mesmo lugar da maquina, ele defende o seu chute
        {
            printf("%s defendeu\n\nPressione qualquer tecla para continuar\n", jogador->nome);
            getch();
            maquina->pontos_totais_possiveis--; // Subtrai 1 dos pontos possiveis da maquina
        }
        else // Se nao, a maquina faz gol
        {
            printf("Maquina fez gol!\n\nPressione qualquer tecla para continuar\n");
            getch();
            maquina->pontos++; // Soma 1 aos pontos da maquina
        }

        system("cls || clear");

        contador++; // Contador soma 1

        if (jogador->pontos > maquina->pontos_totais_possiveis) { break; } // Se a maquina nao tiver mais como virar o jogo, o jogo acaba
    } while (contador < 5); // Vez da maquina acaba quando faz 5 cobranças
}

// Cobranças alternadas (Empate)
void CobrancasAlternadas(int equipe, Jogador *jogador, Maquina *maquina)
{
    srand(time(NULL));

    int escolha; // Variavel para escolhas dentro do jogo
    int chutou = 0; // Conta quantos chutes ocorreram

    do
    {
        if (equipe) // O time que iniciou as cobranças iniciais, começará as cobranças alternadas
        {
            printf("Maquina vai cobrar..\n\nPressione qualquer tecla para continuar\n");
            getch();
            system("cls || clear");

            int chute_da_maquina = rand() % 5; // Gera um numero de 0 a 4
            chute_da_maquina += 49; // Soma com 49, para que a escolha da maquina fique na mesma faixa de valores da escolha do jogador

            do
            {
                printf("Onde voce deseja defender?\n\n1 - Canto Superior Esquerdo\n2 - Canto Inferior Esquerdo\n3 - Canto Superior Direito\n4 - Canto Inferior Esquerdo\n5 - Centro\n\nPontuacao de %s: %d\nPontuacao da Maquina: %d\n", jogador->nome, jogador->pontos, maquina->pontos);
                escolha = getch();
                system("cls || clear");
            } while (escolha < 49 || escolha > 53); // Enquanto a escolha nao estiver entre 49 e 53 (Valores do 1 ao 5 na tabela ASCII), este menu ficará na tela

            if (escolha == chute_da_maquina) // Se o jogador escolher o mesmo lugar da maquina, ele defende o seu chute
            {
                printf("%s defendeu\n\nPressione qualquer tecla para continuar\n", jogador->nome);
                getch();
            }
            else // Se nao, a maquina faz gol
            {
                printf("Maquina fez gol!\n\nPressione qualquer tecla para continuar\n");
                getch();
                maquina->pontos++; // Soma 1 aos pontos da maquina
            }

            system("cls || clear");
            printf("Pontuacao de %s: %d\nPontuacao da Maquina: %d\n\nPressione qualquer tecla para continuar\n", jogador->nome, jogador->pontos, maquina->pontos);
            getch();
            system("cls || clear");

            chutou++; // Ocorreu um chute, entao soma 1 a variavel
            equipe--; // Troca a equipe que irá cobrar
        }
        else
        {
            do
            {
                printf("Onde voce deseja chutar?\n\n1 - Canto Superior Esquerdo\n2 - Canto Inferior Esquerdo\n3 - Canto Superior Direito\n4 - Canto Inferior Esquerdo\n5 - Centro\n\nPontuacao de %s: %d\nPontuacao da Maquina: %d\n", jogador->nome, jogador->pontos, maquina->pontos);
                escolha = getch();
                system("cls || clear");
            } while (escolha < 49 || escolha > 53); // Enquanto a escolha nao estiver entre 49 e 53 (Valores do 1 ao 5 na tabela ASCII), este menu ficará na tela

            int defesa_da_maquina = rand() % 5; // Gera um numero de 0 a 4
            defesa_da_maquina += 49; // Soma com 49, para que a escolha da maquina fique na mesma faixa de valores da escolha do jogador

            if (escolha == defesa_da_maquina) // Se a maquina escolher o mesmo lugar do jogador, ela defende seu chute
            {
                printf("Maquina defendeu\n\nPressione qualquer tecla para continuar\n");
                getch();
            }
            else // Se nao, o jogador faz gol
            {
                printf("%s fez gol!\n\nPressione qualquer tecla para continuar\n", jogador->nome);
                getch();
                jogador->pontos++; // Soma 1 aos pontos do jogador
            }

            system("cls || clear");
            printf("Pontuacao de %s: %d\nPontuacao da Maquina: %d\n\nPressione qualquer tecla para continuar\n", jogador->nome, jogador->pontos, maquina->pontos);
            getch();
            system("cls || clear");

            chutou++; // Ocorreu um chute, entao soma 1 a variavel
            equipe++; // Troca a equipe que irá cobrar

            if (jogador->pontos == maquina->pontos) // Se o jogo continuar empatado, as cobranças alternadas continuarão
            {
                printf("Jogo continua empatado..\n\nPressione qualquer tecla para continuar\n");
                getch();
                system("cls || clear");
                chutou = 0; // Reinicia a contagem de cobranças
            }
        }
    } while (chutou < 2); // Se a contagem de cobranças for < 2, as cobranças continurão (Se for = 2, as cobranças irão parar)

    // Se a maquina tiver mais pontos que o jogador, ela ganhará. Jogador voltará ao menu
    if (maquina->pontos > jogador->pontos)
    {
        printf("Maquina venceu!\n\nPressione qualquer tecla para voltar ao menu\n");
        getch();
        // Reinicia os valores das variaveis, deixando-as prontas para um novo jogo
        jogador->pontos = 0;
        jogador->pontos_totais_possiveis = 5;
        maquina->pontos = 0;
        maquina->pontos_totais_possiveis = 5;
    }

    // Se o jogador tiver mais pontos que a maquina, ele ganhará. Jogador voltará ao menu
    else if (maquina->pontos < jogador->pontos)
    {
        printf("%s venceu!\n\nPressione qualquer tecla para voltar ao menu\n", jogador->nome);
        getch();
        // Reinicia os valores das variaveis, deixando-as prontas para um novo jogo
        jogador->pontos = 0;
        jogador->pontos_totais_possiveis = 5;
        maquina->pontos = 0;
        maquina->pontos_totais_possiveis = 5;
    }
}

#endif
