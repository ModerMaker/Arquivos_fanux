#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

// Diretório base dos arquivos do sistema
std::string baseDir = "./dados/arquivos/";

// Função para listar arquivos e pastas
void listarArquivos() {
    std::cout << "=== Arquivos do Sistema ===\n";
    for (const auto& entry : fs::directory_iterator(baseDir)) {
        std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename() << "\n";
    }
}

// Função para abrir um arquivo
void abrirArquivo(const std::string &nomeArquivo) {
    std::string path = baseDir + nomeArquivo;
    if (!fs::exists(path)) {
        std::cout << "Arquivo não encontrado: " << nomeArquivo << "\n";
        return;
    }

    if (fs::is_directory(path)) {
        std::cout << "Não é um arquivo, é um diretório: " << nomeArquivo << "\n";
        return;
    }

    std::ifstream file(path);
    std::string linha;
    while (getline(file, linha)) {
        std::cout << linha << "\n";
    }
    file.close();
}

// Função principal do explorador
void explorador() {
    std::string comando;
    while (true) {
        std::cout << "+AgxR/Arquivos =$ ";
        getline(std::cin, comando);

        if (comando == "exit") break;
        else if (comando == "ls") listarArquivos();
        else if (comando.find("open ") == 0) {
            abrirArquivo(comando.substr(5));
        } else {
            std::cout << "Comando inválido. Use 'ls' ou 'open [arquivo]'.\n";
        }
    }
}

int main() {
    // Criar diretório base se não existir
    if (!fs::exists(baseDir)) fs::create_directories(baseDir);

    std::cout << "=== Fanux Linux: Explorador de Arquivos ===\n";
    explorador();
    return 0;
}
