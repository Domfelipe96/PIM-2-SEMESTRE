#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // Necess�rio para usar setlocale
#include <conio.h>  // Necess�rio para usar getch
#include <windows.h> // Necess�rio para usar contador

struct Conta {
char usuario[20];
char senha[20];
};

int opcaologin;
int opcaoentrada;
int opcaocompra;
int contador = 0; // Inicializa o contador com 0;
int resp;
char nome[50];
struct Conta conta; // Adicione a estrutura Conta aqui

void logo();
void tela();
int save(char nome[], int opcaoentrada, int opcaocompra, int resp);
int countNamesInCSV();

void logo() {
    // Alterando para o padr�o do sistema operacional
    setlocale(LC_ALL, "Portuguese_Brazil");

    system("color B");
    printf("\n\t\t\t--------------------------------------------------");
    printf("\n\t\t\t| SISTEMA DE CADASTRO DE ENTRADA MUSEU DO FUTURO |");
    printf("\n\t\t\t--------------------------------------------------\n");
}

int isFileEmpty(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 1; // Assume que o arquivo est� vazio se n�o puder ser aberto
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fclose(file);
        return 1; // O arquivo est� vazio
    }
    fclose(file);
    return 0; // O arquivo n�o est� vazio
}

int save(char nome[], int opcaoentrada, int opcaocompra, int resp) {
    FILE *pont_arq;

    pont_arq = fopen("respostas.csv", "a");

    if (pont_arq == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return 1;
    } else {
        if (isFileEmpty("respostas.csv")) {
            // Nomeando as colunas no arquivo CSV
            fprintf(pont_arq, "Nome:, Tipo ingresso:, Escolha tema:, Opini�o tema:\n");
        }
        // Formate os dados como colunas separadas no arquivo CSV
        fprintf(pont_arq, "%s, %d, %d, %d\n", nome, opcaoentrada, opcaocompra, resp);
        fclose(pont_arq);

        printf("\nDados salvos com sucesso!\n");
    }

    return 0;
}

int countNamesInCSV() {
    FILE *pont_arq;
    char ch;
    int namesCount = 0;

    pont_arq = fopen("respostas.csv", "r");

    if (pont_arq == NULL) {
        return namesCount; // Se o arquivo n�o existe, a contagem � zero
    } else {
        // Percorre o arquivo e conta as linhas (nomes)
        while ((ch = fgetc(pont_arq)) != EOF) {
            if (ch == '\n') {
                namesCount++;
            }
        }

        fclose(pont_arq);
    }

    return namesCount;
}

void tela() {
    logo();
    printf("\n\t\t\t\t-------------------------------");
    printf("\n\t\t\t\t| ESCOLHA SEU TIPO DE USU�RIO |");
    printf("\n\t\t\t\t-------------------------------\n\n");
    printf("\n\t\t[1] CLIENTE \t\t[2] STAFF \t\t[3] CR�DITOS FINAIS");
    printf("\n\t\t-------------------------------------------------------------------\n");
    printf("\n\t\t-> ");
    scanf("%d", &opcaologin);

    switch (opcaologin) {
    case 1:
        contador = countNamesInCSV(); // Atualiza o contador com base na contagem de nomes no CSV
        if (isFileEmpty("respostas.csv")) {
            contador = countNamesInCSV() + 1; // Atualiza o contador com base na contagem de nome
        }
        printf("\n\t\tEntrada: %d\n", contador ++);
        printf("\n\t\tDigite seu nome: ");
        fflush(stdin); // Limpa o buffer de entrada
        fgets(nome, sizeof(nome), stdin); // L� a linha inteira
        nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha
        printf("\n\t\tOBS: Seus dados est�o seguros de acordo com a LGPD decreto da lei n. 13.709/2018.\n");

        do {
            printf("\n\n\t\t\t\t-----------------------------------");
            printf("\n\t\t\t\t| QUAL SER� SUA OP��O DE INGRESSO |");
            printf("\n\t\t\t\t-----------------------------------");
            printf("\n\n\t\t[1] ENTRADA INTEGRAL \t\t[2] MEIA ENTRADA \t\t[3] ISENTA");
            printf("\n\t\t--------------------------------------------------------------------------\n");
            printf("\n\t\t-> ");
            scanf("%d", &opcaoentrada);

            switch (opcaoentrada) {
            case 1:
                printf("\nVoc� escolheu a op��o de entrada integral no valor de R$ 49,90.\n");
                break;
            case 2:
                printf("\nVoc� escolheu a op��o de meia entrada no valor de R$ 24,90.\n");
                break;
            case 3:
                printf("\nVoc� escolheu a op��o de entrada isenta no valor de R$ 0,00.\n");
                break;
            default:
                printf("\nOp��o inv�lida. Por favor, escolha 1, 2, ou 3.");
                continue;
            }

            printf("\nDirecionando ao question�rio de valida��o de seu ingresso aguarde...\n");
            int segundos = 5;
            while (segundos > 0) {
                printf("%d\n", segundos);
                Sleep(1000); // Pausa por 1 segundo (1000 ms)
                segundos--;
            }

            system("cls"); // Limpa a tela
            printf("\n\n\t\t\t\t-----------------------------");
            printf("\n\t\t\t\t| QUAL TEMA DE SUA ESCOLHA? |");
            printf("\n\t\t\t\t-----------------------------");
            printf("\n\n[1] 100 anos da semana de arte moderna.");
            printf("\n[2] 150 anos de Santos Dumont.");
            printf("\n[3] Jogos ol�mpicos de Paris 2024.");
            printf("\n[4] 20� Semana nacional da ci�ncia e tecnologia.");
            printf("\n------------------------------------------------\n");
            printf("\n-> ");
            scanf("%d", &opcaocompra);

            switch (opcaocompra) {
            case 1:
                printf("\nVoc� escolheu conhecer o 1� tema: 100 anos da semana de arte moderna, responda a seguinte pergunta:");
                printf("\n---------------------------------------------------------------------------------------------------\n");
                printf("\n\t\t\t\t-------------------------------------------");
                printf("\n\t\t\t\t| O QUE VOC� ACHA E CONHECE SOBRE O TEMA? |");
                printf("\n\t\t\t\t-------------------------------------------");
                printf("\n\n[1] Gosto bastante de cultura, e sempre procuro me manter informado sobre os eventos.");
                printf("\n[2] N�o acompanho muitos eventos de arte, mas visito sempre que poss�vel.");
                printf("\n[3] N�o entendo muito sobre o assunto, me indicaram e estou visitando pela primeira vez.\n");
                printf("----------------------------------------------------------------------------------------\n");
                printf("\n-> ");
                scanf("%d", &resp);
                break;
            case 2:
                printf("\nVoc� escolheu conhecer o 2� tema: 150 anos de Santos Dumont, responda a seguinte pergunta:");
                printf("\n------------------------------------------------------------------------------------------\n");
                printf("\n\t\t\t\t-------------------------------------------");
                printf("\n\t\t\t\t| O QUE VOC� ACHA E CONHECE SOBRE O TEMA? |");
                printf("\n\t\t\t\t-------------------------------------------");
                printf("\n\n[1] Gosto bastante da hist�ria da avia��o em geral, e sempre que posso acompanho todos os eventos e exposi��es.");
                printf("\n[2] Gosto dos meios de transportes em geral e acompanho todos os eventos do tipo.");
                printf("\n[3] Sou de uma �poca mais recente, mas por influ�ncia de parentes mais velhos fui pegando gosto pela hist�ria da avia��o e de Santos Dumont.\n");
                printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("\n-> ");
                scanf("%d", &resp);
                break;
            case 3:
                printf("\nVoc� escolheu conhecer o 3� tema: Jogos ol�mpicos de Paris 2024, responda a seguinte pergunta:");
                printf("\n-----------------------------------------------------------------------------------------------\n");
                printf("\n\t\t\t\t-------------------------------------------");
                printf("\n\t\t\t\t| O QUE VOC� ACHA E CONHECE SOBRE O TEMA? |");
                printf("\n\t\t\t\t-------------------------------------------");
                printf("\n\n[1] Gosto bastante de praticar esportes em geral e acompanho a Olimp�ada inteira.");
                printf("\n[2] Acompanho apenas os principais esportes e vou me mantendo informado pela TV e internet.");
                printf("\n[3] N�o consigo arrumar um tempo para assistir e encaixar na minha rotina.\n");
                printf("-----------------------------------------------------------------------------------------------\n");
                printf("\n-> ");
                scanf("%d", &resp);
                break;
            case 4:
                printf("\nVoc� escolheu conhecer o 4� tema: 20� Semana nacional da ci�ncia e tecnologia, responda a seguinte pergunta:");
                printf("\n------------------------------------------------------------------------------------------------------------\n");
                printf("\n\t\t\t\t-------------------------------------------");
                printf("\n\t\t\t\t| O QUE VOC� ACHA E CONHECE SOBRE O TEMA? |");
                printf("\n\t\t\t\t-------------------------------------------");
                printf("\n\n[1] Gosto bastante do universo de tecnologia em geral.");
                printf("\n[2] N�o sou da �rea, mas por hobby acompanho sempre que poss�vel.");
                printf("\n[3] N�o entendo muito sobre o assunto e estou conhecendo e come�ando a acompanhar para aprender aos poucos.\n");
                printf("-----------------------------------------------------------------------------------------------------------\n");
                printf("\n-> ");
                scanf("%d", &resp);
                break;
            default:
                printf("\nOp��o inv�lida. Por favor, escolha 1, 2, 3 ou 4.\n");
                continue;
            }

            save(nome, opcaoentrada, opcaocompra, resp);
        } while (opcaocompra != 1 && opcaocompra != 2 && opcaocompra != 3 && opcaocompra != 4);

            printf("\nFinalizando sua compra aguarde...\n");
            int segundos = 10;
            while (segundos > 0) {
                printf("%d\n", segundos);
                Sleep(1000); // Pausa por 1 segundo (1000 ms)
                segundos--;
            }
            system("cls"); // Limpa a tela
            return 0;

            default:
            tela();
    case 2:
        {
            char usuarioInput[20];
            char senhaInput[20];

            printf("\n\t\t\t\t--------------------------");
            printf("\n\t\t\t\t| LOGIN DE ADMINISTRADOR |");
            printf("\n\t\t\t\t--------------------------\n\n");
            printf("\n\t\tUSU�RIO: ");
            scanf("%s", usuarioInput);

            printf("\t\tSENHA: ");
            int i = 0;
            char ch;
            while (i < sizeof(senhaInput) - 1) {
                ch = getch();
                if (ch == '\r' || ch == '\n') { // Enter key
                    break;
                }
                senhaInput[i] = ch;
                printf("*");
                i++;
            }
            senhaInput[i] = '\0'; // Null-terminate the password string

            // Verifique se o usu�rio e senha correspondem � conta v�lida
            if (strcmp(usuarioInput, conta.usuario) == 0 && strcmp(senhaInput, conta.senha) == 0) {
                printf("\nLogado como administrador\n");
                // Adicione aqui as a��es do administrador
                contador = countNamesInCSV(); // Atualiza o contador com base na contagem de nomes no CSV
                system("cls"); // Limpa a tela
                printf("\n\t\t\t\t\t------------------------");
                printf("\n\t\t\t\t\t| ACESSO ADMINISTRADOR |");
                printf("\n\t\t\t\t\t------------------------\n\n");
                printf("At� o momento j� recebemos %d visitas em nosso museu.\n", contador);
                printf("-----------------------------------------------------\n");
                // Continuar com outras a��es do administrador, se necess�rio
            } else {
                printf("\n\n\t\tErro: Usu�rio ou senha incorretos...\n");
                printf("\t\t------------------------------------\n");
            }
            break;
        }
    case 3:
        system("cls"); // Limpa a tela
        printf("\n\t\t\t\t\t-------------------");
        printf("\n\t\t\t\t\t| CR�DITOS FINAIS |");
        printf("\n\t\t\t\t\t-------------------\n\n");
        printf("\nUm agradecimento especial do nosso grupo aos professores por toda ajuda, aten��o e conte�do passado com excelencia durante o semestre...\n ");
        printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
        return 0;

        system("cls"); // Limpa a tela
        }
    }

int main() {
    	strcpy(conta.usuario, "MuseuFuturo");
    	strcpy(conta.senha, "1234");
	int continuar = 1; // Inicializa a vari�vel continuar com 1 para entrar no loop

    while (continuar) {
        tela(); // Chama a fun��o tela()

        printf("\n\t\t\t\t------------------------------------");
        printf("\n\t\t\t\t| DESEJA VOLTAR AO MENU PRINCIPAL? |");
        printf("\n\t\t\t\t------------------------------------\n\n");
        printf("\n\t\t[1] SIM, VOLTAR AO MENU PRINCIPAL \t[2] N�O, FINALIZAR O SISTEMA\n");
        printf("\t\t---------------------------------------------------------------------\n");
        printf("\n\t\t-> ");
        scanf("%d", &continuar);

        if (continuar != 1) {
            printf("\nCompra finalizada com sucesso, seja bem vindo e boa divers�o!!!\n");
            return 0;
            system("cls"); // Limpa a tela
        }
    }

    return 0;
}
