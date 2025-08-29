#include <iostream>
#include <string>
#include <vector>
#include "Calculadora.hh" // Arquivo gerado pelo omniidl - Skeleton

class CalculadoraImpl : public POA_CalculadoraApp::Calculadora {
public:
    virtual CORBA::Double calculate(CORBA::Double valor1, CORBA::Double valor2, const char* operacao) {
        std::string op(operacao);

        if (op == "soma" || op == "+" || op == "sum") {
            return valor1 + valor2;
        } else if (op == "subtracao" || op == "-" || op == "sub") {
            return valor1 - valor2;
        } else if (op == "multiplicacao" || op == "*" || op == "mul") {
            return valor1 * valor2;
        } else if (op == "divisao" || op == "/" || op == "div") {
            if (valor2 == 0) {
                std::cerr << "Erro: divisão por zero!" << std::endl;
                return 0;
            }
            return valor1 / valor2;
        } else {
            std::cerr << "Operação desconhecida: " << op << std::endl;
            return 0;
        }
    }
};

int main(int argc, char* argv[]) {
    try {
        const char* orbInitRef = std::getenv("ORB_INITREF_NAME_SERVICE");

        std::vector<std::string> args;

        // Sempre o nome do programa primeiro
        args.push_back(argv[0]);

        if (orbInitRef) {
            args.push_back("-ORBInitRef");
            args.push_back(std::string(orbInitRef));
        }

        args.push_back("-ORBendPoint");
        args.push_back("giop:tcp:10.0.0.206:37000"); // <--- Porta fixa

        // Cria vetor de char* para ORB_init
        std::vector<char*> argv_orb;
        for (auto& arg : args) {
            argv_orb.push_back(const_cast<char*>(arg.c_str()));
        }

        int orbArgc = static_cast<int>(argv_orb.size());

        CORBA::ORB_var orb = CORBA::ORB_init(orbArgc, argv_orb.data());

        // Obtém RootPOA e ativa o POAManager
        CORBA::Object_var poa_obj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var root_poa = PortableServer::POA::_narrow(poa_obj);
        PortableServer::POAManager_var poa_manager = root_poa->the_POAManager();
        poa_manager->activate();

        // Instancia servant
        PortableServer::Servant_var<CalculadoraImpl> calculadora_servant = new CalculadoraImpl();

        // Ativa servant no POA
        root_poa->activate_object(calculadora_servant);
        CORBA::Object_var objref = calculadora_servant->_this();

        // Obtém Naming Service
        CORBA::Object_var ns_obj = orb->resolve_initial_references("NameService");
        CosNaming::NamingContext_var rootContext = CosNaming::NamingContext::_narrow(ns_obj);

        if (CORBA::is_nil(rootContext)) {
            std::cerr << "Falha ao obter Naming Service." << std::endl;
            return 1;
        }

        // Define nome para o objeto no Naming Service
        CosNaming::Name name;
        name.length(1);
        name[0].id = CORBA::string_dup("Calculadora");
        name[0].kind = CORBA::string_dup("");

        // Registra o objeto no Naming Service
        rootContext->rebind(name, objref);
        std::cout << "Objeto registrado no Naming Service com o nome 'Calculadora'." << std::endl;

        orb->run();
        orb->destroy();
    } catch (const CORBA::Exception& ex) {
        std::cerr << "Exceção CORBA: " << ex._name() << std::endl;
        return 1;
    }
    return 0;
}