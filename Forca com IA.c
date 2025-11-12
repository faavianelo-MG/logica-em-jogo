#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
	char palavracerta[50];
	char display[50];
	int tamanho;
	int vida;
	int vitoria;
	char tentativa;
	int morte;
	char letrasErradas[10];
	int numErros;
} jogoforca;






int main()
{


	// 1. Escolher o tema


    // 1. Escolher o tema
    char tema[] = "Animais"; // (Experimente pedir ao usuário com scanf)

    // 2. Criar o prompt
    char prompt[512];
    snprintf(prompt, sizeof(prompt),
             "Voce eh um mestre do jogo da forca. "
             "Sua tarefa eh gerar uma palavra e uma dica. "
             "RESTRICOES: "
             "1. O tema deve ser '%s'. "
             "2. A palavra deve ter entre 6 e 10 letras. "
             "3. A palavra deve ser UMA UNICA PALAVRA, sem espacos e sem acentos. "
             "4. A dica deve ser curta (max 5 palavras). "
             "5. Responda APENAS no formato: PALAVRA;DICA (tudo maiusculo). "
             "Exemplo: CACHORRO;Melhor amigo do homem.",
             tema);

    char palavra_secreta[20];
    char dica[50];
    
    // Buffer para ler a saída do Python (resposta no formato PALAVRA;DICA).
    char buffer_saida_python[512];
    // Buffer para montar o comando shell que será executado.
    char comando_shell[768];
    FILE *pipe; // Pipe em inglês é cano. Um “cano” que liga o Python ao C

    // 1. Montar o comando que o C vai executar
    // Lembre-se de colocar o prompt entre aspas!
    // Monta o comando de forma segura usando snprintf.
    // Lembre-se a atualizar o caminho para o bridge
    snprintf(comando_shell, sizeof(comando_shell), "python \"C:\\CAMINHO_PARA_O_BRIDGE\\gemini_bridge.py\" \"%s\"", prompt);

    // 2. Executar o comando e abrir um "pipe" para ler a saida
    printf("Pensando...\n");
    pipe = popen(comando_shell, "r");
    if (pipe == NULL)
    {
        printf("Erro ao executar a ponte Python!\n");
        return 1;
    }

    // 3. Ler a resposta do pipe (o que o Python imprimiu)
    if (fgets(buffer_saida_python, sizeof(buffer_saida_python), pipe) != NULL)
    {
        // 4. Quebrar a resposta "PALAVRA;DICA" usando strtok
        char *token = strtok(buffer_saida_python, ";");
        if (token != NULL)
        {
            strncpy(palavra_secreta, token, sizeof(palavra_secreta) - 1);
            palavra_secreta[sizeof(palavra_secreta) - 1] = '\0';
        }
        token = strtok(NULL, "\n"); // Pega o resto (a dica)
        if (token != NULL)
        {
            strncpy(dica, token, sizeof(dica) - 1);
            dica[sizeof(dica) - 1] = '\0';
        }
    }
    else
    {
        printf("Erro ao ler a saida da IA.\n");
        return 1;
    }

    // 5. Fechar o pipe
    pclose(pipe);

    printf("IA Gerou a Palavra! Dica: %s\n", dica);

    // O JOGO COMECA AQUI
    // O resto do seu código (inicializar display, loop while, etc.)
    // funciona exatamente como antes

    


	jogoforca jogo;
	
	

    
	
	jogo.tamanho = strlen(palavra_secreta);
	jogo.vida = 6;
	jogo.vitoria = 0;
	jogo.numErros = 0;
    jogo.letrasErradas[0] = '\0';
	jogo.display[jogo.tamanho] = '\0';
	for(int i = 0; i < jogo.tamanho; i++ ) {
		jogo.display[i] = '_';
	}
	printf("%d Letras\n", jogo.tamanho);
	while(jogo.vida != 0 && jogo.vitoria != 1) {
		jogo.morte = 0;
		for(int i = 0; i < jogo.tamanho; i++ ) {
			printf("%c",jogo.display[i]);	
		}
		if(jogo.vida == 6){
		printf("\n ________  \n");
		printf("|       |  \n");
		printf("|          \n");
		printf("|          \n");
		printf("|          \n");
		}
		if(jogo.vida == 5){
		printf("\n ________  \n");
		printf("|       |  \n");
		printf("|       O  \n");
		printf("|          \n");
		printf("|          \n");
	}
		if(jogo.vida == 4){
		printf("\n ________  \n");
		printf("|       |  \n");
		printf("|       O  \n");
		printf("|       |  \n");
		printf("|          \n");
	}
		if(jogo.vida == 3){
		printf("\n ________  \n");
		printf("|       |  \n");
		printf("|       O  \n");
		printf("|      /|  \n");
		printf("|          \n");
	}
		if(jogo.vida == 2){
		printf("\n ________  \n");
		printf("|       |  \n");
		printf("|       O  \n");
		printf("|      /|/ \n");
		printf("|          \n");
	}
		if(jogo.vida == 1){
		printf(" \n________  \n");
		printf("|       |  \n");
		printf("|       O  \n");
		printf("|      /|/ \n");
		printf("|      /   \n");
	}
	if (jogo.numErros > 0) {
            printf("\nLetras erradas: %s", jogo.letrasErradas);
        }
	
		printf("\n\nDigite o seu chute: ");
		scanf(" %c", &jogo.tentativa);
		jogo.tentativa = toupper(jogo.tentativa);
		for(int i = 0; i < jogo.tamanho; i++ ) {
			if(palavra_secreta[i] == jogo.tentativa) {
				jogo.display[i] = palavra_secreta[i];
				jogo.morte = jogo.morte + 1;
			}
			else {
				jogo.morte = jogo.morte + 0;
			}
		}
		if(jogo.morte == 0) {
			jogo.letrasErradas[jogo.numErros] = jogo.tentativa;                      
            jogo.numErros++; 
            jogo.letrasErradas[jogo.numErros] = '\0'; 
			jogo.vida = jogo.vida - 1;
			printf("Errou\n");
		}
		if(strcmp(jogo.display, palavra_secreta) == 0)
		{
			jogo.vitoria = 1;
			printf("%s\nGanhou", palavra_secreta);
			printf("\nA palavra e: %s", palavra_secreta);
		}
		if(jogo.vida == 0) {
					if (jogo.vida == 0){
		printf("\n ________  \n");
		printf("|       |  \n");
		printf("|       X  \n");
		printf("|      /|/ \n");
		printf("|      / / \n");
	}
			printf("Acabaram as vidas\nPerdeu");
			printf("\nA palavra e: %s", palavra_secreta);
		}
	}

    return 0;
}
