//Versão NCC-1701 - A
//02/07/2014 - 20:30
//Jogo Lê Troca 

//Assunto: Avaliação - LOPA1
//IFSP - Barretos - ADS 
//Guilherme Catani
//Kaio Henrique de Melo Chiarato

//Fork por Lucas Canutto - Thanks

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

		const int qtd_Palavras = 78;
		const int size_palavras = 50;
		char palavras[qtd_Palavras][size_palavras] = { "asa", "casa", "as", "mansao", "saca", "mao", "castelo", "viagem", "missa", "igreja", "terraço", "android",
			"star", "trek", "spock", "kirk", "dia", "primavera", "inverno", "trono", "jogo", "professor", "logica", "vulcano", "calor", "mulher", "homem", "crianca", "humano",
			"arvore", "planta", "respiracao", "sol", "agua", "equilibrio", "oxigenio", "isaac", "asimov", "tres", "leis", "da", "robotica", "guerra", "dos", "mundos", "livro",
			"amor", "musica", "classica", "aleatorio", "caos", "einstein", 
			"grande", "pequeno", "antonimo", "sinonimo", "portugues", "burgues", "comunismo", "luta", "direito", "propriedade", "coletivo", "borg", "cavalo", "simbiose",
			"relacao", "morte", "dor", "felicidade", "tristeza", "noite", "estrelada", "planeta", "sistema", "software", "historia", "napoleao"
		};
	
		int* limpaVetor(int* vetor) {
			int indice = 0;
			while (indice < size_palavras){
				vetor[indice] = -1;
				indice++;
			}
			return vetor;
		}


		int Escolhe(int max) {
			//Escolhe randomicamente um índice
			//Esta função é da biblioteca stdlib						
		
			int num = rand() % max;
			return num;
		}

		int tamanho(int indice){
			//Esta função retorna a quantidade letras de uma palavra
			//contina no vetor "palavras" através de um índice passado por parâmetro
			char* word = palavras[indice];
			int contador = 0;
			while (word[contador] != '\0') {
				contador++;
			}
			return contador;
		}

		int size(char* word){	
			//Esta função retorna a quantidade de letras de uma palavra
			//uma string é passada por parâmetro
			int contador = 0;
			while (word[contador] != '\0') {
				contador++;
			}
			return contador;
		}

		int Quantidade_de_Selecionados(int* lista) {
			//A função retorna a quantidade de palavras que foram
			//selecionadas através das letras da palavra principal
			int contador = 0;
			while (lista[contador] != -1){
				contador++;
			}	
			return contador;
		}

		void ImprimeSelecionadas(int* lista_de_selecionadas, int idPrincipal, int* vetor_Acerto) {
			//Esta função imprime as palavras selecionadas 
			//E por intermédio do vetor acerto, que registras as palavras que ainda não foram acertadas			
			//e as que já foram, ele imprime as palavras com os asteriscos ou não!
			int tam = Quantidade_de_Selecionados(lista_de_selecionadas);
			char* principal = palavras[idPrincipal];
			for (int i = 0; i < tam; i++){
				if (lista_de_selecionadas[i] == -1) {
					break;
				}
				else {
					if (vetor_Acerto[i] == -1){
						int quant_letras = tamanho(lista_de_selecionadas[i]);
						int contador = 0;
						while (contador < quant_letras)
						{
							printf("*");
							contador++;
						}
						printf(" ");
					}
					else {
						printf(" %s ", palavras[lista_de_selecionadas[i]]);
					}
				}
			}
		}

		int Selecionar(int Principal, int Escolhida) {
			//Seleciona a palavra de acordo com suas letras
			//Não deve haver nenhuma letra que não esteja na palavra principal
			//Portanto, a função passa por cada letra da palavra selecionada
			//e compara com as letras da palavra principal
			//Se alguma letra da palavra selecionada não estiver na palavra principal
			//ela e descartada!
			char* palavra_selecionada = palavras[Escolhida];
			char* palavra_principal = palavras[Principal];				
			int teste = 0;
			int tam_escolhida = tamanho(Escolhida);
			int tam_principal = tamanho(Principal);
			for (int i = 0; i < tam_escolhida; i++) {		
				for (int j = 0; j < tam_principal; j++) {
					if (palavra_principal[j] == palavra_selecionada[i]) {
						
						//Caso haja alguma correspondência, a variável teste 
						//é alterada para 1, caso contrário, ela permanece 0
						//e no bloco de condição que se segue o laço
						//se a variável teste for diferente de 1
						//a palavra é descartada
						//por possuir uma letra que não corresponde
						//com as letras da palavra principal
						teste = 1;
					}
				}
			
				if (teste == 0) {
					return 0;
				}
				teste = 0;
			}
			
			return 1;
		}
				
		int Existe(int* vetor, int valor){
			int contador = 0;
			while (contador < size_palavras) {
				if (valor == vetor[contador]){
					return 1;
				}
				contador++;
			}
			return 0;
		}

		void Embaralhar(char* palavra){
			int emb[size_palavras];
			//limpaVetor(emb);
			int tamanho = size(palavra);
			limpaVetor(emb);
			int contador = 0;
			int indice = 0;
			int param = 1;
			while (param) {
				int r = Escolhe(tamanho);
				if (!Existe(emb, r)) {
					emb[indice] = r;
					indice++;
					if (Quantidade_de_Selecionados(emb) == tamanho){
						param = 0;
					}
				}

			}

			char nova_palavra[size_palavras];
			for (int i = 0; i < size_palavras; i++){
				if (i < tamanho){
					nova_palavra[i] = palavra[emb[i]];
				}
				else {
					nova_palavra[i] = '\0';
				}
			}
			strcpy(palavra, nova_palavra);
		}
		
			int Igual(char* str_1, char* str_2) {
			//Como eu não consegui usar as funções
			//devidamente da biblioteca string.h (odeio)
			//Decidi criar a minha própria!
			//A função compara letra por letra, após comparar o tamanho das palavras
			//se houver alguma discrepância, a função retorna 0
			//Caso elas sejam idênticas, a função retorna 1
			int tam_1 = size(str_1);
			int tam_2 = size(str_2);
			if (tam_1 == tam_2){
				for (int i = 0; i < tam_1; i++) {
					if (str_1[i] != str_2[i]){
						return 0;
					}
				}
			}
			else {
				return 0;
			}
			return 1;
		}

	int main() {
		int param = 1;
		int erros = 0;
		int erros_max = 5;
		srand(time(NULL));
		do {
			//Randomicamente, escolhe uma palavra do vetor
			int idPalavra = Escolhe(qtd_Palavras);		
			//int idPalavra = 1;
			//Inicia variáveis
			char* palavra_escolhida = palavras[idPalavra];
			int acertos = 0;						
			int qtd_ = 0;


			//Vetor que armazenará as palavras escolhidas 
			//através das letras do dicionário
			int selecionadas[qtd_Palavras];

			//Limpa o "lixo" do vetor
			limpaVetor(selecionadas);

			//Seleciona as palavras
			selecionadas[0] = idPalavra;
			int indice = 1;
			for (int i = 0; i < qtd_Palavras; i++) {
				if (idPalavra != i) {
					if (Selecionar(idPalavra, i)) {
						selecionadas[indice] = i;
						indice++;
					}
				}
			}
			qtd_ = indice;

			//Os acertos necessário são as palavras adicionadas ao vetor			
			int acertos_nencessarios = indice;									

			//Vetor que armazena as palavras corretas
			int certo[qtd_Palavras];

			//Limpa Vetor
			limpaVetor(certo);

			//Imprime a palavra Principal embaralhada antes de iniciar o jogo
			//Foi preciso copiar a string usando a função da biblioteca string.h
			//strcpy, pois quando era transferida da função Embaralhar
			//o resultado perdia-se no escopo da função e voltava lixo de memória
			//Agora, no entanto, o resultado é apontado para o vetor novapalavra
			//Onde é alterado o resultado
		//	printf("\nAguarde nossos elfos embaralharem a palavra escolhidas...\n");
			char novapalavra[size_palavras];			
			strcpy(novapalavra, palavras[idPalavra]);
			Embaralhar(novapalavra);
			strupr(novapalavra);
			printf("\n-----------------------------------------------------------------");						
			printf("\n%s\n", &novapalavra);
			printf("-----------------------------------------------------------------\n");			
			
			
			//Imprime as palavras selecionadas
			ImprimeSelecionadas(selecionadas, idPalavra, certo);

			int bool_acertou = 0;
			char new_[size_palavras + 1];
			do {				
				printf("\nAcertos %d de %d... Erros %d\n", acertos, acertos_nencessarios , erros);
				
				//Recolhe a tentativa do usuário
				scanf("%50s", &new_);			
				strlwr(new_);				

				//O laço compara a tentativa com o dicionário
				//Através da função "Igual"
				for (int i = 0; i < qtd_; i++) {
					char* palavra = palavras[selecionadas[i]];					
					if (Igual(new_, palavra)){
						if (certo[i] == -1) {
							acertos++;							
							//Se a palavra estiver certa, no vetor "certo",
							//troca-se seu valor de -1 por 1
							//Esta foi a manobra mais simples que eu encontrei
							//De alertar a função "ImprimeSelecionadas"
							//para exibir as palavras já desvendadas pelo usuário
							//e manter as outras ocultas pelo asterisco
							certo[i] = 1;
							bool_acertou = 1;
						}
						break;
					}
					else {
						bool_acertou = 0;
					}
				}

				if (!bool_acertou){
					erros++;
				}
				
				//Imprime novamente as palavras
				ImprimeSelecionadas(selecionadas, idPalavra, certo);
			} while ((acertos < acertos_nencessarios) && (erros < erros_max));			
			printf("\n\n-----------------------------------------------------------------\n");
			printf("Voce acertou %d de %d... E errou %d de %d", acertos, acertos_nencessarios, erros, erros_max);
			if (erros == erros_max){
				printf("\nQue pena! Nao desista... :(\n");
			}
			else {
				printf("\nParabens!!! Pronto para mais uma jogada? :D\n");
			}
			printf("\n-Aperte 1 - se voce deseja continuar!\n-Aperte 0 se voce deseja sair\nOpcao: ");
			erros = 0;
			scanf("%d", &param);		
			printf("\n-----------------------------------------------------------------\n");
		} while (param);

		return 0;
	}
