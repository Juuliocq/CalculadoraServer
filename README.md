ANTES DE INICIAR OMNINAMES (Serviço de descoberta de serviços CORBA)
sudo rm /var/omninames/omninames-Julio-Queiroz.dat
sudo rm /var/omninames/omninames-Julio-Queiroz.bak

RODAR OMNINAMES
omniNames -start -ORBendPointPublish giop:tcp::2809

buildar servidor
g++ -o server server.cpp CalculadoraSK.cc -I/usr/include/omniorb4 -lomniORB4 -lomnithread

rodar servidor
./server -ORBInitRef NameService=corbaloc::{IP_NAMING_SERVICE}:2809/NameService
