#include <stdio.h>
#include <stdlib.h>
#include<conio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct loja{
	
	int num_registro;
	char nome_ferramenta[50];
	int quantidade;
	float valor;
	
};

int main() {
	
	struct loja l = {0, "", 0, 0.0};
	struct loja *lo;
	int i;
	
	lo = &l;
	
	FILE *pl;
	
	pl = fopen("hardware.dat", "r+b");
	
	if(pl == NULL){
		
		printf("\n\nNao existe arquivo.\n\n");
		
		pl = fopen("hardware.dat", "wb");
	
		if(pl == NULL){
		
			printf("\n\nErro na abertura do arquivo.\n\n");
			exit(1);
		
		} 
	
		for(i = 0; i < 100; i++){
		
			fwrite(&l, sizeof(struct loja), 1, pl);
		
		}
		
		printf("\n\nArquivo criado com sucesso.\n\n");
		fclose(pl);
	
	} 
	
	int ativo = 1;
	
	while (ativo == 1){
		
		int menu = 0;
		printf("\nEscolha a opcao:\n");
		printf("1 - Insira o produto.\n");
		printf("2 - Listar todos os produtos.\n");
		printf("3 - Excluir um produto.\n");
		printf("4 - Atualize um produto existente.\n");
		printf("5 - Carrega para memoria Principal.\n");
		printf("6 - Sair.\n");
		scanf("%d", &menu);
		
		int a;
		
		pl = fopen("hardware.dat", "r+b");
	
		if(pl == NULL){
		
			printf("\n\nErro na abertura do arquivo.\n\n");
			exit(1);
		
		}
				
		switch(menu){
		
		case 1:
						
			pl = fopen("hardware.dat", "r+b");
			
			if(pl == NULL){
		
				printf("\n\nErro na abertura do arquivo.\n\n");
		
			} 
	
			
			printf("\n\nQuantos produtos voce quer colocar?\n\n");
			scanf("%d", &a);
			
			for(i = 0; i < a; i++){
				
				printf("\nCodigo do produto: \n");
				scanf("%d", &l.num_registro);
				fflush(stdin);
				printf("Nome da ferramenta: \n");
				gets(l.nome_ferramenta);
				fflush(stdin);
				printf("Quantidade: \n");
				scanf("%d", &l.quantidade);
				printf("Valor do produto: \n");
				scanf("%f", &l.valor);
				
				int ret_fseek = 0;
				ret_fseek = fseek(pl, (l.num_registro-1) * sizeof(struct loja), SEEK_SET);
				
				if(ret_fseek != 0){
					
					printf("\n\nErro do numero do registro, tente novamente.\n\n");
					i--;
					
				}
				
				int ret_fwrite = 0;
				ret_fwrite = fwrite(&l, sizeof(struct loja), 1, pl);
				
				if(ret_fwrite < 1){
					
					printf("\n\nErro do numero do registro, tente novamente.\n\n");
					i--;
					
				}
		
			}
			
			printf("\n\nRegristros feitos com sucesso, tecle enter para continuar.\n\n");
			fclose(pl);
			getch();
			break;
				
		case 2:
			
			pl = fopen("hardware.dat", "r+b");
			
			if(pl == NULL){
		
				printf("\n\nErro na abertura do arquivo.\n\n");
		
			}
			
			
			
			for(i = 1; i <= 100; i++){
				
				int ret_fseek = 0;
				ret_fseek = fseek(pl, (i - 1) * sizeof(struct loja),SEEK_SET);
				
				
				if(ret_fseek != 0){
				
					printf("\n\nErro 1 do numero do registro, tente novamente.\n\n");
				
				}
					
				int ret_fread = 0;
				ret_fread = fread(&l, sizeof(struct loja), 1, pl);
			
				if(ret_fread < 1){
				
					break;
									
				}
				
				if(l.num_registro == 0){
					
					
				} else{
					
					printf("\n\nNo. de registro: %d\n\n", l.num_registro);
					printf("\n\nNome da Ferramenta: %s\n\n", l.nome_ferramenta);
					printf("\n\n\nQuantidade: %d\n\n", l.quantidade);
					printf("\n\nValor: R$%.2f\n\n", l.valor);
					
				}
			
			}
									
			fflush(stdin);
			fclose(pl);
			break;
			
		case 3:	
			
			pl = fopen ("hardware.dat", "r+b");
			
			if(pl == NULL){
		
				printf("\n\nErro na abertura do arquivo.\n\n");
				getch();
				exit(1);
		
			}
			
			int codigo;
			printf("\n\nQual o codigo do produto a ser removido?\n\n");
			scanf("%d", &codigo);
			
			for(i = 1; i <= 100; i++){
				
				int ret_fseek = 0;
				ret_fseek = fseek(pl, (i - 1) * sizeof(struct loja),SEEK_SET);
				
				
				if(ret_fseek != 0){
				
					printf("E\n\nrro 1 do numero do registro, tente novamente.\n\n");
				
				}
				
				int ret_fread = 0;
				ret_fread = fread(&l, sizeof(struct loja), 1, pl);
			
				if(ret_fread < 1){
					
					printf("\n\nErro 2 do numero do registro, tente novamente.\n\n");
									
				}
				
				if(l.num_registro == codigo){
					
					int ret1_fseek = 0;
					ret1_fseek = fseek(pl, (i - 1) * sizeof(struct loja),SEEK_SET);
				
				
					if(ret1_fseek != 0){
				
						printf("\n\nErro 3 do numero do registro, tente novamente.\n\n");
				
					}
					
					l.num_registro = 0;
					strcpy(l.nome_ferramenta, "");
					l.quantidade = 0;
					l.valor = 0.0;
					
					int ret_fwrite = 0;
    				ret_fwrite = fwrite(&l, sizeof(struct loja), 1, pl);
    					
    				if (ret_fwrite < 1){
    						
        				printf("\n\nErro 4 do numero do registro, tente novamente.\n\n");
        					
    				}
						
					printf("\n\nRegistro gravado com sucesso!\n\n");
    				break;
					
				}
				
			}
			fclose(pl);
			fflush(stdin);
			break;
			
		case 4:
			
			pl = fopen ("hardware.dat", "r+b");
			
			if(pl == NULL){
		
				printf("\n\nErro na abertura do arquivo.\n\n");
				getch();
				exit(1);
		
			}
			
			int codigo2;
			printf("\n\nQual o codigo que voce quer alterar?\n\n");
			scanf("%d", &codigo2);
			
			for(i = 1; i <= 100; i++){
				
				int ret_fseek = 0;
				ret_fseek = fseek(pl, (i - 1) * sizeof(struct loja),SEEK_SET);
				
				
				if(ret_fseek != 0){
				
					printf("\n\nErro 1 do numero do registro, tente novamente.\n\n");
				
				}
				
				int ret_fread = 0;
				ret_fread = fread(&l, sizeof(struct loja), 1, pl);
			
				if(ret_fread < 1){
					
					printf("\n\nErro 2 do numero do registro, tente novamente.\n\n");
									
				}
				
				if(l.num_registro == codigo2){
					
					int ret1_fseek = 0;
					ret1_fseek = fseek(pl, (i - 1) * sizeof(struct loja),SEEK_SET);
				
				
					if(ret1_fseek != 0){
				
						printf("\n\nErro 3 do numero do registro, tente novamente.\n\n");
				
					}
					
					char resp;
					
					printf("\n\nCodigo: %d\n\n", l.num_registro);
					printf("\n\nEste e o produto que voce quer alterar? (S \ N)\n\n");
					scanf("%s", &resp);
					
					if(resp == 'S' || resp == 's'){
						
						fflush(stdin);
						printf("\n\nQual o novo nome?\n\n");
						gets(l.nome_ferramenta);
						fflush(stdin);
						printf("\n\nQual a nova quantidade?\n\n");
						scanf("%d", &l.quantidade);
						printf("\n\nQual o novo valor?\n\n");
						scanf("%f", &l.valor);
						
						int ret_fwrite = 0;
    					ret_fwrite = fwrite(&l, sizeof(struct loja), 1, pl);
    					
    					if (ret_fwrite < 1){
    						
        					printf("\n\nErro 4 do numero do registro, tente novamente.\n\n");
        					
    					}
						
						printf("\n\nRegistro gravado com sucesso!\n");
    					break;
					} else{
						
					}
					
				}
				
			}
			fclose(pl);
			fflush(stdin);
			break;
			
		case 5:
			
			pl = fopen ("hardware.dat", "r+b");
			
			if(pl == NULL){
		
				printf("\n\nErro na abertura do arquivo.\n\n");
				getch();
				exit(1);
		
			}
			
			lo = (struct loja *) malloc(100 * sizeof(struct loja));
			
			int cont = 0;
			float total, med;
			
			int ret_fseek = 0;
			ret_fseek = fseek(pl, (1 - 1) * sizeof(struct loja),SEEK_SET);
							
			if(ret_fseek != 0){
				
				printf("\n\nErro do numero do registro, tente novamente.\n\n");
				
			}
			
			for(i = 0; i < 100; i++){
				
				int ret_fread = 0;
				ret_fread = fread(&l, sizeof(struct loja), 1, pl);
			
				if(ret_fread < 1){
					
					printf("\n\nErro 2 do numero do registro, tente novamente.\n\n");
									
				}
				
				*(lo+i) = l;
			}
			
			for(i = 0; i < 100; i++){
				
				if(lo[i].num_registro != 0){
					
					total = total + lo[i].valor;
					cont++;
					
				}
				
			}
			
			med = total/cont;
			
			printf("\n\nA media dos produtos e:\n R$%.2f\n\n", med);
			
			
			fclose(pl);
			fflush(stdin);
			break;
		
		case 6:
			
			printf("Saindo do programa.");
			ativo = 0;
			fflush(stdin);
			break;
			
		}
		fflush(stdin);
	}
	return 0;
}
