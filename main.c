#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

// Função de retorno de chamada do cURL para lidar com a resposta da solicitação HTTP
size_t curlWriteCallback(void *contents, size_t size, size_t nmemb, char *buffer) {
    // Aqui processa os dados recebidos da resposta HTTP, se necessário
    // Neste exemplo, está apenas imprimindo a resposta no console
    printf("%s", (char *)contents);
    return size * nmemb;
}

// Função para obter estatísticas do jogador de Valorant usando a API do Valorant
void getValorantStats(const char* servidor, const char* username) {
    CURL *curl;
    CURLcode res;

    // URL da API do Valorant para obter as estatísticas do jogador
    char url[100];
    sprintf(url, "https://api.valorant.com/v1/players?server=%s&name=%s", servidor, username);

    curl = curl_easy_init();
    if (curl) {
        // Definir a URL e a função de retorno de chamada do cURL
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);

        // Fazer a solicitação HTTP
        res = curl_easy_perform(curl);

        // Verificar se a solicitação foi bem-sucedida
        if (res != CURLE_OK)
            fprintf(stderr, "Erro ao fazer a solicitação: %s\n", curl_easy_strerror(res));

        // Liberar recursos do cURL
        curl_easy_cleanup(curl);
    }
}

void showValorantInfo() {
    char servidor[50];
    char username[50];

    printf("Digite o servidor em que você joga (por exemplo, BR, NA, EU): ");
    scanf("%s", servidor);

    printf("Digite o seu nome de usuário: ");
    scanf("%s", username);

    getValorantStats(servidor, username);
}

void showRandomGameInfo() {
    printf("Exibindo informações de um jogo aleatório.\n");
}


int main() {
	int option;

	// Inicializar o cURL
    curl_global_init(CURL_GLOBAL_ALL);

    do {
        printf("Escolha um jogo para ver informações:\n");
        printf("1. Valorant\n");
        printf("2. Jogo aleatório\n");
        printf("0. Sair\n");
        printf("Digite o número da opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                showValorantInfo();
                break;
            case 2:
                showRandomGameInfo();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        printf("\n");
    } while (opcao != 0);

    // Finalizar o cURL
    curl_global_cleanup();

    return 0;
}