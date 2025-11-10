#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

// constantes para os nomes dos arquivos de texto
#define ARQUIVO_USUARIOS "usuarios.txt"
#define ARQUIVO_ESTABELECIMENTOS "estabelecimentos.txt"
#define ARQUIVO_ALIMENTOS "alimentos.txt"
#define ARQUIVO_PEDIDOS "pedidos.txt" 

// constantes
#define MAX_STRING 100         
#define MAX_ITENS_PEDIDO 10   


//estruturas de dados


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
    int avaliacao; 
} Pedido;






// função para limpar o buffer do teclado 
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// busca o nome de um estabelecimento pelo ID
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
        // lê a linha (ID,Nome) e armazena em 'est'
        sscanf(linha, "%d,%[^\n]", &est.id, est.nome); 
        if (est.id == idEst) {
            strcpy(nomeResultado, est.nome); 
            break;
        }
    }
    fclose(arquivoEst);
}

// busca um alimento pelo ID e retorna seus dados 
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
            encontrou = 1; // Dados do alimento estão agora em 'alim'
            break;
        }
    }
    fclose(arquivo);
    return encontrou; // Retorna 1 se encontrou, 0 se não
}


 //funções de usuario (login/cadastro)
 


void cadastrarUsuario() {
    Usuario novoUsuario;
    FILE *arquivo;
    int idAtual = 1;

    // tenta calcular o próximo ID, contando as linhas do arquivo de usuários
    arquivo = fopen(ARQUIVO_USUARIOS, "r");
    if (arquivo != NULL) {
        char linha[MAX_STRING * 3];
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            idAtual++; // incrementa o ID para cada linha existente
        }
        fclose(arquivo);
    }
    novoUsuario.id = idAtual;

    printf("\n--- Cadastro de Novo Usuario (ID: %d) ---\n", novoUsuario.id);
    limparBuffer(); // limpa o buffer antes de ler strings com fgets
    
    // coleta dados do novo usuário
    printf("Digite seu nome completo: ");
    fgets(novoUsuario.nome, MAX_STRING, stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = 0; // Remove o \n final

    printf("Digite seu login: ");
    fgets(novoUsuario.login, MAX_STRING, stdin);
    novoUsuario.login[strcspn(novoUsuario.login, "\n")] = 0;

    printf("Digite sua senha: ");
    fgets(novoUsuario.senha, MAX_STRING, stdin);
    novoUsuario.senha[strcspn(novoUsuario.senha, "\n")] = 0;

    // Grava o novo usuário no arquivo (modo "a" - append)
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

// Tenta logar um usuário. Retorna 1 se sucesso, 0 se falha.
int loginUsuario(int *idUsuarioLogado) {
    char loginInput[MAX_STRING];
    char senhaInput[MAX_STRING];
    Usuario usuarioLido; 
    FILE *arquivo;
    char linhaDoArquivo[MAX_STRING * 4]; 
    int loginSucesso = 0; 

    printf("\n--- FEIFood: Login de Usuario ---\n");
    limparBuffer(); 

    // Coleta as credenciais
    printf("Digite seu login: ");
    fgets(loginInput, MAX_STRING, stdin);
    loginInput[strcspn(loginInput, "\n")] = 0; 

    printf("Digite sua senha: ");
    fgets(senhaInput, MAX_STRING, stdin);
    senhaInput[strcspn(senhaInput, "\n")] = 0; 

    // Abre o arquivo para leitura
    arquivo = fopen(ARQUIVO_USUARIOS, "r");
    if (arquivo == NULL) {
        printf("Erro! Nao foi possivel abrir o arquivo %s\n", ARQUIVO_USUARIOS);
        return 0; 
    }

    // Compara linha por linha
    while (fgets(linhaDoArquivo, sizeof(linhaDoArquivo), arquivo) != NULL) {
        // Usa sscanf para extrair os dados da linha para a estrutura 'usuarioLido'
        sscanf(linhaDoArquivo, "%d,%[^,],%[^,],%[^\n]",
               &usuarioLido.id,
               usuarioLido.nome,
               usuarioLido.login,
               usuarioLido.senha);

        // Compara login e senha
        if (strcmp(loginInput, usuarioLido.login) == 0 && 
            strcmp(senhaInput, usuarioLido.senha) == 0) {
            loginSucesso = 1; 
            *idUsuarioLogado = usuarioLido.id; // Armazena o ID do usuário logado
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
*/

// Permite buscar alimentos por um termo no nome
void buscarAlimento() {
    char termoBusca[MAX_STRING];
    Alimento alimento;
    FILE *arquivo;
    char linhaDoArquivo[MAX_STRING * 3];
    int encontrou = 0;

    printf("\n--- Buscar Alimento ---\n");
    limparBuffer(); 
    
    printf("Digite o nome do alimento: ");
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

        // strstr() verifica se 'termoBusca' está contido em 'alimento.nome'
        if (strstr(alimento.nome, termoBusca) != NULL) {
            char nomeEstab[MAX_STRING];
            getNomeEstabelecimento(alimento.idEstabelecimento, nomeEstab); // Busca o nome do estab
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

// Lista todos os alimentos disponíveis no sistema
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

    // Cabeçalho formatado
    printf("%-5s | %-20s | %-8s | %s\n", "ID", "Alimento", "Preco", "Estabelecimento");
    printf("------------------------------------------------------------------\n");
    
    while (fgets(linha, sizeof(linha), arquivoAlimentos) != NULL) {
        sscanf(linha, "%d,%d,%[^,],%lf",
               &alimento.id,
               &alimento.idEstabelecimento,
               alimento.nome,
               &alimento.preco);
        
        getNomeEstabelecimento(alimento.idEstabelecimento, nomeEstabelecimento); // Obtém o nome do Estab

        // Imprime a linha formatada
        printf("%-5d | %-20s | R$%-5.2f | %s\n",
               alimento.id,
               alimento.nome,
               alimento.preco,
               nomeEstabelecimento);
    }
    fclose(arquivoAlimentos);
}



// FUNÇÕES DE PEDIDO (CRUD)


void gerenciarNovoPedido(int idUsuario) {
    
    Pedido carrinho; // Variável local para simular o carrinho
    Alimento alimTemp; 
    int opcao = -1;
    int idAlimentoInput = 0;
    
    // Inicializa o carrinho
    carrinho.idUsuario = idUsuario;
    carrinho.numItens = 0;
    carrinho.precoTotal = 0.0;
    carrinho.avaliacao = -1; // -1 = N/A (não avaliado)

    printf("\n--- Criando Novo Pedido ---\n");

    while (opcao != 0) {
        printf("\n--- Carrinho (Itens: %d | Total: R$%.2f) ---\n", carrinho.numItens, carrinho.precoTotal);
        // Menu de carrinho
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
                // Verifica se o ID existe
                if (getAlimentoPorId(idAlimentoInput, &alimTemp) == 1) {
                    // Adiciona o ID do alimento ao array do carrinho
                    carrinho.idAlimentos[carrinho.numItens] = alimTemp.id; 
                    carrinho.precoTotal += alimTemp.preco;
                    carrinho.numItens++;
                    printf("'%s' foi adicionado ao carrinho!\n", alimTemp.nome);
                } else {
                    printf("ID de alimento invalido ou nao encontrado.\n");
                }
                break;
            case 2:
                // Lista os itens, usando getAlimentoPorId para buscar os nomes e preços
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
                // Salvar Pedido
                if (carrinho.numItens == 0) {
                    printf("Nao e possivel salvar um pedido vazio!\n");
                    break;
                }
                // Calcula o próximo ID do Pedido
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
                
                // Grava os dados do pedido (modo "a" - append)
                arquivoPedidos = fopen(ARQUIVO_PEDIDOS, "a");
                if (arquivoPedidos == NULL) {
                    printf("Erro ao salvar o pedido!\n");
                    return; 
                }
                // Grava os 5 campos principais (ID, UserID, Preco, Avaliacao, NumItens)
                fprintf(arquivoPedidos, "%d,%d,%.2f,%d,%d",
                        carrinho.id,
                        carrinho.idUsuario,
                        carrinho.precoTotal,
                        carrinho.avaliacao,
                        carrinho.numItens);
                // Grava a lista de IDs de alimentos, separados por vírgula
                for (int i = 0; i < carrinho.numItens; i++) {
                    fprintf(arquivoPedidos, ",%d", carrinho.idAlimentos[i]);
                }
                fprintf(arquivoPedidos, "\n"); // Quebra de linha para o próximo pedido
                fclose(arquivoPedidos);
                printf("\nPedido %d salvo com sucesso!\n", carrinho.id);
                opcao = 0; // Sai do loop do carrinho
                break;
            case 0:
                printf("Criacao do pedido cancelada.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }
}

// Lista os pedidos do usuário logado (usada como auxiliar para Avaliar, Editar e Excluir)
int listarMeusPedidos(int idUsuario) {
    
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
        // Lê os 5 campos principais
        sscanf(linha, "%d,%d,%lf,%d,%d",
               &pedido.id,
               &pedido.idUsuario,
               &pedido.precoTotal,
               &pedido.avaliacao,
               &pedido.numItens);

        if (pedido.idUsuario == idUsuario) { // Filtra apenas pedidos do usuário logado
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

// Permite ao usuário atribuir uma avaliação (nota) a um pedido existente
void avaliarPedido(int idUsuario) {
    int idPedidoInput;
    int novaAvaliacao;
    int pedidoEncontrado = 0;

    printf("\n--- Avaliar Pedido ---\n");
    if (listarMeusPedidos(idUsuario) == 0) { // Lista para que o usuário saiba o ID
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

    // Processo de UPDATE (lê do Original, escreve no Temp)
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
        // Lê os 5 campos principais (necessário para pegar 'id' e 'idUser')
        sscanf(linha, "%d,%d,%lf,%d,%d", &id, &idUser, &preco, &avaliacaoAntiga, &numItens);

        if (id == idPedidoInput && idUser == idUsuario) { // Pedido a ser modificado
            pedidoEncontrado = 1;
            
            // 1. Escreve a linha MODIFICADA no arquivo temporário, mudando apenas a avaliação
            fprintf(arquivoTemp, "%d,%d,%.2f,%d,%d",
                    id, idUser, preco, novaAvaliacao, numItens); // Escreve a nova avaliação
            
            // 2. Encontra a 5ª vírgula (após 'numItens') para copiar o resto da linha (IDs dos alimentos)
            int i = 0;
            int virgulas = 0;
            while (linha[i] != '\0') {
                if (linha[i] == ',') {
                    virgulas++;
                    if (virgulas == 5) {
                        break; 
                    }
                }
                i++;
            }
            
            // 3. Copia o resto da string (que contém os IDs de alimentos)
            if (linha[i] != '\0') {
                fprintf(arquivoTemp, "%s", &linha[i]); // &linha[i] aponta para a 5ª vírgula e o resto
            }
            
        } else {
            // Se não for o pedido, apenas copia a linha original
            fprintf(arquivoTemp, "%s", linha);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    // Finaliza o UPDATE (troca de arquivos)
    if (pedidoEncontrado) {
        remove(ARQUIVO_PEDIDOS); // Deleta o arquivo antigo
        rename("pedidos_temp.txt", ARQUIVO_PEDIDOS); // Renomeia o temporário
        printf("Pedido %d avaliado com %d estrelas!\n", idPedidoInput, novaAvaliacao);
    } else {
        remove("pedidos_temp.txt"); // Deleta o temporário se não encontrou o pedido
        printf("Pedido %d nao encontrado ou nao pertence a voce.\n", idPedidoInput);
    }
}

// Exclui um pedido do usuário logado (DELETE)
void excluirPedido(int idUsuario) {
    int idPedidoInput;
    int pedidoEncontrado = 0;

    printf("\n--- Excluir Pedido ---\n");
    if (listarMeusPedidos(idUsuario) == 0) {
        return; 
    }

    printf("\nDigite o ID do pedido que deseja EXCLUIR: ");
    scanf("%d", &idPedidoInput);

    // Confirmação de segurança
    char certeza[10];
    printf("Tem certeza que deseja excluir o pedido %d? (s/n): ", idPedidoInput);
    scanf("%s", certeza);

    if (strcmp(certeza, "s") != 0 && strcmp(certeza, "S") != 0) {
        printf("Exclusao cancelada.\n");
        return;
    }

    // Processo de DELETE (lê do Original, escreve no Temp)
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
            continue; // Pula para a próxima linha (o pedido é *ignorado* e não copiado)
        } else {
            fprintf(arquivoTemp, "%s", linha); // Copia a linha original
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    // Finaliza o DELETE (troca de arquivos)
    if (pedidoEncontrado) {
        remove(ARQUIVO_PEDIDOS); 
        rename("pedidos_temp.txt", ARQUIVO_PEDIDOS); 
        printf("Pedido %d excluido com sucesso!\n", idPedidoInput);
    } else {
        remove("pedidos_temp.txt"); 
        printf("Pedido %d nao encontrado ou nao pertence a voce.\n", idPedidoInput);
    }
}

// Edita um pedido, permitindo remover um item (UPDATE complexo)
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
        strcpy(linhaOriginalCopia, linha); // Salva a linha original caso a edição seja cancelada
        
        sscanf(linha, "%d,%d,%lf,%d,%d", &id, &idUser, &preco, &avaliacao, &numItens);

        if (id == idPedidoInput && idUser == idUsuario) {
            pedidoEncontrado = 1;
            
            // 1. Carregar os IDs dos itens manualmente (sscanf não funciona bem para arrays de tamanho variável)
            int i = 0;
            int virgulas = 0;
            // Encontra o ponto de início (após a 5ª vírgula - que delimita 'numItens')
            while(linha[i] != '\0' && virgulas < 5) {
                if (linha[i] == ',') virgulas++;
                i++;
            }

            char bufferId[10];
            int j = 0; 
            int itemIndex = 0; 
            
            // Faz o parsing dos IDs um por um
            while(linha[i] != '\0' && linha[i] != '\n') {
                if (linha[i] == ',') {
                    bufferId[j] = '\0';
                    idAlimentos[itemIndex] = atoi(bufferId);
                    itemIndex++;
                    j = 0; 
                } else {
                    bufferId[j] = linha[i];
                    j++;
                }
                i++;
            }
            // Pega o último ID
            bufferId[j] = '\0';
            idAlimentos[itemIndex] = atoi(bufferId);

            printf("\n--- Itens do Pedido %d ---\n", id);
            Alimento alimTemp;
            for (int k = 0; k < numItens; k++) {
                getAlimentoPorId(idAlimentos[k], &alimTemp);
                printf("%d. %s (R$%.2f)\n", k+1, alimTemp.nome, alimTemp.preco);
            }

            // 2. Pergunta qual item remover
            int itemParaRemover;
            printf("Digite o numero do item a remover (1 a %d) (ou 0 para cancelar): ", numItens);
            scanf("%d", &itemParaRemover);

            if (itemParaRemover <= 0 || itemParaRemover > numItens) {
                printf("Remocao cancelada ou item invalido.\n");
                fprintf(arquivoTemp, "%s", linhaOriginalCopia); // Volta a linha original
            } else {
                int indexRemovido = itemParaRemover - 1;
                getAlimentoPorId(idAlimentos[indexRemovido], &alimTemp);
                
                // Recalcula o preço total e o número de itens
                double novoPreco = preco - alimTemp.preco;
                int novoNumItens = numItens - 1;

                // 3. Escreve a linha modificada (Novos Preco e NumItens)
                fprintf(arquivoTemp, "%d,%d,%.2f,%d,%d",
                        id, idUser, novoPreco, avaliacao, novoNumItens);
                
                // 4. Escreve os IDs dos itens restantes (o item removido é pulado)
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

    // Finaliza o UPDATE (troca de arquivos)
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
*/

// Menu de gerenciamento de pedidos (Editar/Excluir)
void gerenciarPedidos(int idUsuario) {
    int opcao = -1;
    
    while (opcao != 0) {
        printf("\n--- Gerenciar Meus Pedidos ---\n");
        printf("1. Editar Pedido/Remover Item\n");
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

// Menu principal após o login
void menuUsuarioLogado(int idUsuario) {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n--- FEIFood (Logado como ID: %d) ---\n", idUsuario);
        printf("1. Buscar Alimento\n");
        printf("2. Lista de Todos os Alimentos\n"); 
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


// FUNÇÃO PRINCIPAL
 

int main() {
    int opcao = -1;
    int idUsuarioLogado = 0; 
    int loginStatus = 0;     

    while (opcao != 0) { // Loop do menu inicial (Login/Cadastro/Sair)
        printf("\n--- BEM-VINDO AO FEIFOOD ---\n");
        printf("1. Fazer Login\n");
        printf("2. Cadastrar Novo Usuario\n");
        printf("0. Sair do Programa\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                loginStatus = loginUsuario(&idUsuarioLogado); // Tenta fazer login
                if (loginStatus == 1) {
                    menuUsuarioLogado(idUsuarioLogado); // Entra no menu principal se logado com sucesso
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