ANTES DE INICIAR OMNINAMES (Serviço de descoberta de serviços CORBA)<br>
sudo rm /var/omninames/omninames-Julio-Queiroz.dat<br>
sudo rm /var/omninames/omninames-Julio-Queiroz.bak<br>

RODAR OMNINAMES<br>
omniNames -start -ORBendPointPublish giop:tcp::2809<br>

buildar servidor <br>
g++ -o server server.cpp CalculadoraSK.cc -I/usr/include/omniorb4 -lomniORB4 -lomnithread <br>

rodar servidor <br>
./server -ORBInitRef NameService=corbaloc::{IP_NAMING_SERVICE}:2809/NameService <br>
