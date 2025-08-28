FROM ubuntu:20.04

# Evita prompts interativos
ENV DEBIAN_FRONTEND=noninteractive

# Atualiza pacotes e instala dependências
RUN apt-get update && apt-get install -y \
    build-essential \
    omniORB \
    omniidl \
    libomniorb4-dev \
    libcos4-dev \
    && rm -rf /var/lib/apt/lists/*

# Cria diretório da aplicação
WORKDIR /app

# Copia todos os arquivos do projeto
COPY . .

# Compila o código
RUN g++ -o servidor servidor.cpp CalculadoraSK.cc -lomniORB4 -lomnithread -lCOS4

# Porta padrão para objetos CORBA (omniORB usa 2809 por padrão)
EXPOSE 2809

# Comando de inicialização
CMD ["./servidor"]