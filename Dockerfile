FROM debian:bullseye

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    omniidl \
    omniorb \
    libomniorb4-dev \
    libcos4-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN g++ -o servidor servidor.cpp CalculadoraSK.cc -lomniORB4 -lomnithread -lCOS4

EXPOSE 2809

CMD ["./servidor"]