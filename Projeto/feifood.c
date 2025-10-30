#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

// Arquivos de "Banco de Dados"
#define ARQUIVO_USUARIOS "usuarios.txt"
#define ARQUIVO_ESTABELECIMENTOS "estabelecimentos.txt"
#define ARQUIVO_ALIMENTOS "alimentos.txt"
#define ARQUIVO_PEDIDOS "pedidos.txt" 

// Constantes
#define MAX_STRING 100
#define MAX_ITENS_PEDIDO 10 


// ESTRUTURAS DE DADOS 


typedef struct {
    int id;
    char nome[MAX_STRING];
    char login[MAX_STRING];
    char senha[MAX_STRING];
} Usuario;

typedef struct {
    int id;
    char nome[MAX_STRING];
} Estabelecimento;

typedef struct {
    int id;
    int idEstabelecimento;
    char nome[MAX_STRING];
    double preco;
} Alimento;

typedef struct {
    int id; 
    int idUsuario;
    int idAlimentos[MAX_ITENS_PEDIDO]; 
    int numItens;
    double precoTotal;
    int avaliacao; // -1 = N/A, 0 a 5 = Avaliado
} Pedido;


/*
 FUNÇÕES AUXILIARES
*/

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Busca o nome de um estabelecimento pelo ID
void getNomeEstabelecimento(int idEst, char* nomeResultado) {
    FILE *arquivoEst;
    Estabelecimento est;
    char linha[MAX_STRING * 2];

    strcpy(nomeResultado, "Estabelecimento Desconhecido");
    arquivoEst = fopen(ARQUIVO_ESTABELECIMENTOS, "r");
    if (arquivoEst == NULL) {
        return;
    }

    while (fgets(linha, sizeof(linha), arquivoEst) != NULL) {
        sscanf(linha, "%d,%[^\n]", &est.id, est.nome);
        if (est.id == idEst) {
            strcpy(nomeResultado, est.nome);
            break;
        }
    }
    fclose(arquivoEst);
}

// Busca um alimento pelo ID e retorna seus dados
int getAlimentoPorId(int idAlimento, Alimento *alim) {
    FILE *arquivo;
    char linha[MAX_STRING * 3];
    int encontrou = 0;

    arquivo = fopen(ARQUIVO_ALIMENTOS, "r");
    if (arquivo == NULL) {
        return 0; 
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%d,%d,%[^,],%lf",
               &alim->id,
               &alim->idEstabelecimento,
               alim->nome,
               &alim->preco);
        
        if (alim->id == idAlimento) {
            encontrou = 1;
            break;
        }
    }
    fclose(arquivo);
    return encontrou;
}

/*
 FUNÇÕES DE USUÁRIO (Login/Cadastro)
 (Sem alterações)
*/

void cadastrarUsuario() {
    Usuario novoUsuario;
    FILE *arquivo;
    int idAtual = 1;

    arquivo = fopen(ARQUIVO_USUARIOS, "r");
    if (arquivo != NULL) {
        char linha[MAX_STRING * 3];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            idAtual++;
        }
        fclose(arquivo);
    }
    novoUsuario.id = idAtual;

    printf("\n--- Cadastro de Novo Usuario (ID: %d) ---\n", novoUsuario.id);
    limparBuffer(); 
    
    printf("Digite seu nome completo: ");
    fgets(novoUsuario.nome, MAX_STRING, stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = 0;

    printf("Digite seu login: ");
    fgets(novoUsuario.login, MAX_STRING, stdin);
    novoUsuario.login[strcspn(novoUsuario.login, "\n")] = 0;

    printf("Digite sua senha: ");
    fgets(novoUsuario.senha, MAX_STRING, stdin);
    novoUsuario.senha[strcspn(novoUsuario.senha, "\n")] = 0;

    arquivo = fopen(ARQUIVO_USUARIOS, "a"); 
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s!\n", ARQUIVO_USUARIOS);
        return; 
    }
    fprintf(arquivo, "%d,%s,%s,%s\n",
            novoUsuario.id,
            novoUsuario.nome,
            novoUsuario.login,
            novoUsuario.senha);
    fclose(arquivo);
    printf("\nUsuario '%s' cadastrado com sucesso!\n", novoUsuario.login);
}

int loginUsuario(int *idUsuarioLogado) {
    char loginInput[MAX_STRING];
    char senhaInput[MAX_STRING];
    Usuario usuarioLido; 
    FILE *arquivo;
    char linhaDoArquivo[MAX_STRING * 4]; 
    int loginSucesso = 0; 

    printf("\n--- FEIFood: Login de Usuario ---\n");
    limparBuffer(); 

    printf("Digite seu login: ");
    fgets(loginInput, MAX_STRING, stdin);
    loginInput[strcspn(loginInput, "\n")] = 0; 

    printf("Digite sua senha: ");
    fgets(senhaInput, MAX_STRING, stdin);
    senhaInput[strcspn(senhaInput, "\n")] = 0; 

    arquivo = fopen(ARQUIVO_USUARIOS, "r");
    if (arquivo == NULL) {
        printf("Erro! Nao foi possivel abrir o arquivo %s\n", ARQUIVO_USUARIOS);
        return 0; 
    }

    while (fgets(linhaDoArquivo, sizeof(linhaDoArquivo), arquivo) != NULL) {
        sscanf(linhaDoArquivo, "%d,%[^,],%[^,],%[^\n]",
               &usuarioLido.id,
               usuarioLido.nome,
               usuarioLido.login,
               usuarioLido.senha);

        if (strcmp(loginInput, usuarioLido.login) == 0 && 
            strcmp(senhaInput, usuarioLido.senha) == 0) {
            loginSucesso = 1; 
            *idUsuarioLogado = usuarioLido.id;
            printf("\nLogin bem-sucedido!\n");
            printf("Bem-vindo(a), %s (ID: %d).\n", usuarioLido.nome, usuarioLido.id);
            break; 
        }
    }
    fclose(arquivo);
    if (loginSucesso == 0) {
        printf("\nFalha no login. Login ou senha invalidos.\n");
    }
    return loginSucesso; 
}


/*
 FUNÇÕES DE ALIMENTOS (Busca/Listagem)
 (Sem alterações)
*/

void buscarAlimento() {
    char termoBusca[MAX_STRING];
    Alimento alimento;
    FILE *arquivo;
    char linhaDoArquivo[MAX_STRING * 3];
    int encontrou = 0;

    printf("\n--- Buscar Alimento ---\n");
    limparBuffer(); 
    
    printf("Digite o nome (ou parte do nome) do alimento: ");
    fgets(termoBusca, MAX_STRING, stdin);
    termoBusca[strcspn(termoBusca, "\n")] = 0; 

    arquivo = fopen(ARQUIVO_ALIMENTOS, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de alimentos!\n");
        return;
    }

    printf("\nResultados da busca por '%s':\n", termoBusca);
    
    while (fgets(linhaDoArquivo, sizeof(linhaDoArquivo), arquivo) != NULL) {
        sscanf(linhaDoArquivo, "%d,%d,%[^,],%lf",
               &alimento.id,
               &alimento.idEstabelecimento,
               alimento.nome,
               &alimento.preco);

        if (strstr(alimento.nome, termoBusca) != NULL) {
            char nomeEstab[MAX_STRING];
            getNomeEstabelecimento(alimento.idEstabelecimento, nomeEstab);
            printf("  ID: %d | Nome: %s | Preco: R$%.2f | Estab: %s\n",
                   alimento.id,
                   alimento.nome,
                   alimento.preco,
                   nomeEstab);
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhum alimento encontrado com o termo '%s'.\n", termoBusca);
    }
    fclose(arquivo);
}

void listarTodosAlimentos() {
    Alimento alimento;
    FILE *arquivoAlimentos;
    char linha[MAX_STRING * 3];
    char nomeEstabelecimento[MAX_STRING];

    printf("\n--- Lista de Todos os Alimentos ---\n");

    arquivoAlimentos = fopen(ARQUIVO_ALIMENTOS, "r");
    if (arquivoAlimentos == NULL) {
        printf("Erro ao abrir o arquivo de alimentos!\n");
        return;
    }

    printf("%-5s | %-20s | %-8s | %s\n", "ID", "Alimento", "Preco", "Estabelecimento");
    printf("------------------------------------------------------------------\n");
    
    while (fgets(linha, sizeof(linha), arquivoAlimentos) != NULL) {
        sscanf(linha, "%d,%d,%[^,],%lf",
               &alimento.id,
               &alimento.idEstabelecimento,
               alimento.nome,
               &alimento.preco);
        
        getNomeEstabelecimento(alimento.idEstabelecimento, nomeEstabelecimento);

        printf("%-5d | %-20s | R$%-5.2f | %s\n",
               alimento.id,
               alimento.nome,
               alimento.preco,
               nomeEstabelecimento);
    }
    fclose(arquivoAlimentos);
}


/*
 FUNÇÕES DE PEDIDO (CRUD)
*/

void gerenciarNovoPedido(int idUsuario) {
    // Esta função está ok, sem alterações.
    Pedido carrinho; 
    Alimento alimTemp; 
    int opcao = -1;
    int idAlimentoInput = 0;
    
    carrinho.idUsuario = idUsuario;
    carrinho.numItens = 0;
    carrinho.precoTotal = 0.0;
    carrinho.avaliacao = -1; 

    printf("\n--- Criando Novo Pedido ---\n");

    while (opcao != 0) {
        printf("\n--- Carrinho (Itens: %d | Total: R$%.2f) ---\n", carrinho.numItens, carrinho.precoTotal);
        printf("1. Adicionar Alimento ao Pedido\n");
        printf("2. Ver Carrinho Detalhado\n");
        printf("3. Salvar Pedido\n");
        printf("0. Cancelar Pedido\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                if (carrinho.numItens >= MAX_ITENS_PEDIDO) {
                    printf("Carrinho cheio! Nao e possivel adicionar mais itens.\n");
                    break;
                }
                listarTodosAlimentos(); 
                printf("\nDigite o ID do alimento que deseja adicionar: ");
                scanf("%d", &idAlimentoInput);
                if (getAlimentoPorId(idAlimentoInput, &alimTemp) == 1) {
                    carrinho.idAlimentos[carrinho.numItens] = alimTemp.id; 
                    carrinho.precoTotal += alimTemp.preco;
                    carrinho.numItens++;
                    printf("'%s' foi adicionado ao carrinho!\n", alimTemp.nome);
                } else {
                    printf("ID de alimento invalido ou nao encontrado.\n");
                }
                break;
            case 2:
                printf("\n--- Itens no Carrinho ---\n");
                if (carrinho.numItens == 0) {
                    printf("Carrinho vazio.\n");
                } else {
                    for (int i = 0; i < carrinho.numItens; i++) {
                        getAlimentoPorId(carrinho.idAlimentos[i], &alimTemp);
                        printf("  %d. %s (R$%.2f)\n", i+1, alimTemp.nome, alimTemp.preco);
                    }
                }
                printf("---------------------------\n");
                printf("Total: R$%.2f\n", carrinho.precoTotal);
                break;
            case 3:
                if (carrinho.numItens == 0) {
                    printf("Nao e possivel salvar um pedido vazio!\n");
                    break;
                }
                FILE *arquivoPedidos;
                int idAtual = 1;
                arquivoPedidos = fopen(ARQUIVO_PEDIDOS, "r");
                if (arquivoPedidos != NULL) {
                    char linha[MAX_STRING * 4];
                    while (fgets(linha, sizeof(linha), arquivoPedidos) != NULL) {
                        idAtual++;
                    }
                    fclose(arquivoPedidos);
                }
                carrinho.id = idAtual;
                arquivoPedidos = fopen(ARQUIVO_PEDIDOS, "a");
                if (arquivoPedidos == NULL) {
                    printf("Erro ao salvar o pedido!\n");
                    return; 
                }
                fprintf(arquivoPedidos, "%d,%d,%.2f,%d,%d",
                        carrinho.id,
                        carrinho.idUsuario,
                        carrinho.precoTotal,
                        carrinho.avaliacao,
                        carrinho.numItens);
                for (int i = 0; i < carrinho.numItens; i++) {
                    fprintf(arquivoPedidos, ",%d", carrinho.idAlimentos[i]);
                }
                fprintf(arquivoPedidos, "\n"); 
                fclose(arquivoPedidos);
                printf("\nPedido %d salvo com sucesso!\n", carrinho.id);
                opcao = 0;
                break;
            case 0:
                printf("Criacao do pedido cancelada.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }
}

// Lista os pedidos do usuário
int listarMeusPedidos(int idUsuario) {
    // Esta função está ok, sem alterações.
    FILE *arquivo;
    char linha[MAX_STRING * 5]; 
    Pedido pedido;
    int encontrouPedidos = 0;

    printf("\n--- Meus Pedidos ---\n");
    arquivo = fopen(ARQUIVO_PEDIDOS, "r");
    if (arquivo == NULL) {
        printf("Nenhum pedido cadastrado no sistema ainda.\n");
        return 0;
    }

    printf("%-5s | %-10s | %s\n", "ID", "Valor Total", "Avaliacao");
    printf("------------------------------------------\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%d,%d,%lf,%d,%d",
               &pedido.id,
               &pedido.idUsuario,
               &pedido.precoTotal,
               &pedido.avaliacao,
               &pedido.numItens);

        if (pedido.idUsuario == idUsuario) {
            char avaliacaoStr[5];
            if (pedido.avaliacao == -1) {
                strcpy(avaliacaoStr, "N/A");
            } else {
                sprintf(avaliacaoStr, "%d*", pedido.avaliacao);
            }
            printf("%-5d | R$ %-8.2f | %s\n",
                   pedido.id,
                   pedido.precoTotal,
                   avaliacaoStr);
            encontrouPedidos = 1;
        }
    }

    if (encontrouPedidos == 0) {
        printf("Voce ainda nao fez nenhum pedido.\n");
    }
    
    fclose(arquivo);
    return encontrouPedidos;
}

void avaliarPedido(int idUsuario) {
    int idPedidoInput;
    int novaAvaliacao;
    int pedidoEncontrado = 0;

    printf("\n--- Avaliar Pedido ---\n");
    if (listarMeusPedidos(idUsuario) == 0) {
        return;
    }

    printf("\nDigite o ID do pedido que deseja avaliar: ");
    scanf("%d", &idPedidoInput);

    printf("Digite a nota (0 a 5 estrelas): ");
    scanf("%d", &novaAvaliacao);

    if (novaAvaliacao < 0 || novaAvaliacao > 5) {
        printf("Avaliacao invalida. A nota deve ser entre 0 e 5.\n");
        return;
    }

    FILE *arquivoOriginal;
    FILE *arquivoTemp;
    char linha[MAX_STRING * 5];
    int id, idUser, numItens, avaliacaoAntiga;
    double preco;

    arquivoOriginal = fopen(ARQUIVO_PEDIDOS, "r");
    arquivoTemp = fopen("pedidos_temp.txt", "w"); 

    if (arquivoOriginal == NULL || arquivoTemp == NULL) {
        printf("Erro ao processar os arquivos de pedidos!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL) {
        // Lê os 5 campos principais
        sscanf(linha, "%d,%d,%lf,%d,%d", &id, &idUser, &preco, &avaliacaoAntiga, &numItens);

        if (id == idPedidoInput && idUser == idUsuario) {
            pedidoEncontrado = 1;
            
            // Escreve a linha MODIFICADA no arquivo temporário
            fprintf(arquivoTemp, "%d,%d,%.2f,%d,%d",
                    id, idUser, preco, novaAvaliacao, numItens); // Escreve a nova avaliação
            
            // Agora, precisamos copiar o resto da linha (os IDs dos itens)
            // Vamos encontrar a 5ª vírgula
            int i = 0;
            int virgulas = 0;
            while (linha[i] != '\0') {
                if (linha[i] == ',') {
                    virgulas++;
                    if (virgulas == 5) {
                        break; // Para *na* 5ª vírgula
                    }
                }
                i++;
            }
            
            // Copia o resto da string a partir da 5ª vírgula
            if (linha[i] != '\0') {
                fprintf(arquivoTemp, "%s", &linha[i]); // &linha[i] aponta para a 5ª vírgula
            }
            
        } else {
            // Se não for o pedido, apenas copia a linha original
            fprintf(arquivoTemp, "%s", linha);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    if (pedidoEncontrado) {
        remove(ARQUIVO_PEDIDOS); 
        rename("pedidos_temp.txt", ARQUIVO_PEDIDOS); 
        printf("Pedido %d avaliado com %d estrelas!\n", idPedidoInput, novaAvaliacao);
    } else {
        remove("pedidos_temp.txt"); 
        printf("Pedido %d nao encontrado ou nao pertence a voce.\n", idPedidoInput);
    }
}

// Exclui um pedido (Esta função não usa token)
void excluirPedido(int idUsuario) {
    int idPedidoInput;
    int pedidoEncontrado = 0;

    printf("\n--- Excluir Pedido ---\n");
    if (listarMeusPedidos(idUsuario) == 0) {
        return; 
    }

    printf("\nDigite o ID do pedido que deseja EXCLUIR: ");
    scanf("%d", &idPedidoInput);

    char certeza[10];
    printf("Tem certeza que deseja excluir o pedido %d? (s/n): ", idPedidoInput);
    scanf("%s", certeza);

    if (strcmp(certeza, "s") != 0 && strcmp(certeza, "S") != 0) {
        printf("Exclusao cancelada.\n");
        return;
    }

    FILE *arquivoOriginal;
    FILE *arquivoTemp;
    char linha[MAX_STRING * 5];
    int id, idUser;

    arquivoOriginal = fopen(ARQUIVO_PEDIDOS, "r");
    arquivoTemp = fopen("pedidos_temp.txt", "w");

    if (arquivoOriginal == NULL || arquivoTemp == NULL) {
        printf("Erro ao processar os arquivos de pedidos!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL) {
        sscanf(linha, "%d,%d,", &id, &idUser);

        if (id == idPedidoInput && idUser == idUsuario) {
            pedidoEncontrado = 1;
            continue; // Pula para a próxima linha (não copia)
        } else {
            fprintf(arquivoTemp, "%s", linha);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    if (pedidoEncontrado) {
        remove(ARQUIVO_PEDIDOS); 
        rename("pedidos_temp.txt", ARQUIVO_PEDIDOS); 
        printf("Pedido %d excluido com sucesso!\n", idPedidoInput);
    } else {
        remove("pedidos_temp.txt"); 
        printf("Pedido %d nao encontrado ou nao pertence a voce.\n", idPedidoInput);
    }
}

// Edita um pedido (removendo um item) (SEM STRTTOK)
void editarPedido(int idUsuario) {
    int idPedidoInput;
    int pedidoEncontrado = 0;

    printf("\n--- Editar Pedido (Remover Item) ---\n");
    if (listarMeusPedidos(idUsuario) == 0) {
        return;
    }

    printf("\nDigite o ID do pedido que deseja EDITAR: ");
    scanf("%d", &idPedidoInput);

    FILE *arquivoOriginal;
    FILE *arquivoTemp;
    char linha[MAX_STRING * 5];
    char linhaOriginalCopia[MAX_STRING * 5];
    int id, idUser, numItens, avaliacao;
    double preco;
    int idAlimentos[MAX_ITENS_PEDIDO];
    
    arquivoOriginal = fopen(ARQUIVO_PEDIDOS, "r");
    arquivoTemp = fopen("pedidos_temp.txt", "w");

    if (arquivoOriginal == NULL || arquivoTemp == NULL) {
        printf("Erro ao processar os arquivos de pedidos!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL) {
        strcpy(linhaOriginalCopia, linha); 
        
        sscanf(linha, "%d,%d,%lf,%d,%d", &id, &idUser, &preco, &avaliacao, &numItens);

        if (id == idPedidoInput && idUser == idUsuario) {
            pedidoEncontrado = 1;
            
            // 1. Carregar os IDs dos itens manualmente
            int i = 0;
            int virgulas = 0;
            while(linha[i] != '\0' && virgulas < 5) {
                if (linha[i] == ',') virgulas++;
                i++;
            }
            // i agora aponta para o início do primeiro ID

            char bufferId[10];
            int j = 0; // índice do bufferId
            int itemIndex = 0; // índice do idAlimentos
            
            while(linha[i] != '\0' && linha[i] != '\n') {
                if (linha[i] == ',') {
                    bufferId[j] = '\0';
                    idAlimentos[itemIndex] = atoi(bufferId);
                    itemIndex++;
                    j = 0; // Reseta buffer
                } else {
                    bufferId[j] = linha[i];
                    j++;
                }
                i++;
            }
            // Pega o último ID (que não termina em vírgula)
            bufferId[j] = '\0';
            idAlimentos[itemIndex] = atoi(bufferId);

            printf("\n--- Itens do Pedido %d ---\n", id);
            Alimento alimTemp;
            for (int k = 0; k < numItens; k++) {
                getAlimentoPorId(idAlimentos[k], &alimTemp);
                printf("%d. %s (R$%.2f)\n", k+1, alimTemp.nome, alimTemp.preco);
            }

            // 2. Perguntar qual item remover
            int itemParaRemover;
            printf("Digite o numero do item a remover (1 a %d) (ou 0 para cancelar): ", numItens);
            scanf("%d", &itemParaRemover);

            if (itemParaRemover <= 0 || itemParaRemover > numItens) {
                printf("Remocao cancelada ou item invalido.\n");
                fprintf(arquivoTemp, "%s", linhaOriginalCopia);
            } else {
                int indexRemovido = itemParaRemover - 1;
                getAlimentoPorId(idAlimentos[indexRemovido], &alimTemp);
                
                double novoPreco = preco - alimTemp.preco;
                int novoNumItens = numItens - 1;

                // 3. Escreve a linha modificada
                fprintf(arquivoTemp, "%d,%d,%.2f,%d,%d",
                        id, idUser, novoPreco, avaliacao, novoNumItens);
                
                // 4. Escreve os itens restantes
                for (int k = 0; k < numItens; k++) {
                    if (k == indexRemovido) continue; // Pula o item removido
                    fprintf(arquivoTemp, ",%d", idAlimentos[k]);
                }
                fprintf(arquivoTemp, "\n");
                printf("Item '%s' removido do pedido %d.\n", alimTemp.nome, id);
            }
            
        } else {
            fprintf(arquivoTemp, "%s", linhaOriginalCopia);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    if (pedidoEncontrado) {
        remove(ARQUIVO_PEDIDOS);
        rename("pedidos_temp.txt", ARQUIVO_PEDIDOS);
    } else {
        remove("pedidos_temp.txt");
        if (pedidoEncontrado == 0) {
             printf("Pedido %d nao encontrado ou nao pertence a voce.\n", idPedidoInput);
        }
    }
}

/*
 MENUS DE NAVEGAÇÃO
 (Sem alterações)
*/

void gerenciarPedidos(int idUsuario) {
    int opcao = -1;
    
    while (opcao != 0) {
        printf("\n--- Gerenciar Meus Pedidos ---\n");
        printf("1. Editar Pedido (Remover Item)\n");
        printf("2. Excluir Pedido\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                editarPedido(idUsuario);
                break;
            case 2:
                excluirPedido(idUsuario);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }
}

void menuUsuarioLogado(int idUsuario) {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n--- FEIFood (Logado como ID: %d) ---\n", idUsuario);
        printf("1. Buscar Alimento\n");
        printf("2. Listar Todos os Alimentos\n"); 
        printf("3. Criar Novo Pedido\n");
        printf("4. Avaliar Pedido\n");
        printf("5. Gerenciar Pedidos (Editar/Excluir)\n");
        printf("0. Deslogar (Voltar ao menu inicial)\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                buscarAlimento();
                break;
            case 2:
                listarTodosAlimentos(); 
                break;
            case 3:
                gerenciarNovoPedido(idUsuario); 
                break;
            case 4:
                avaliarPedido(idUsuario); 
                break;
            case 5:
                gerenciarPedidos(idUsuario);
                break;
            case 0:
                printf("Deslogando...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }
}

/*
 FUNÇÃO PRINCIPAL
 (Sem alterações)
*/
int main() {
    int opcao = -1;
    int idUsuarioLogado = 0; 
    int loginStatus = 0;     

    while (opcao != 0) {
        printf("\n--- BEM-VINDO AO FEIFOOD ---\n");
        printf("1. Fazer Login\n");
        printf("2. Cadastrar Novo Usuario\n");
        printf("0. Sair do Programa\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                loginStatus = loginUsuario(&idUsuarioLogado); 
                if (loginStatus == 1) {
                    menuUsuarioLogado(idUsuarioLogado);
                }
                break;
            case 2:
                cadastrarUsuario();
                break;
            case 0:
                printf("Saindo do FEIFood. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }
    return 0; 
}