FROM debian:bullseye

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    omniidl \
    omniorb \
    omniorb-idl \
    libomniorb4-dev \
    libcos4-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN omniidl -bcpp Calculadora.idl

RUN g++ -o server server.cpp CalculadoraSK.cc -I/usr/include/omniorb4 -lomniORB4 -lomnithread -lCOS4

EXPOSE 2809

CMD ["./server"]