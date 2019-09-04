#include <iostream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

// Minha struct frase
struct Frase{
	// Uma frase tem palavras (no caso as palavras estão mapeadas)
	map<string,int> palavras;

	// Função para ler e criar uma frase
	void criarFrase(){
		string palavra;
		while(cin >> palavra){
			palavras[palavra]++;
		}
	}

	void mostrarFraseMapeada(){
		map<string, int>::const_iterator itr; // Iterador só pra ir percorrendo
		int total = 0;
		float porcentagem;

		// Vou do inicio até o fim do map só pra saber o total de palavras
		for (itr = palavras.begin(); itr != palavras.end(); ++itr){
			total += itr->second;
		}

		cout << fixed << showpoint << setprecision(2); // Fixando duas casas decimais

		// Vou do inicio até o fim novamente para calcular a porcentagem e mostrar os dados corretamente
		for (itr = palavras.begin(); itr != palavras.end(); ++itr){
			porcentagem = (((itr->second) * 100.00)/total)/100;
			cout << itr->first << " " << itr->second << " ";
			cout << porcentagem << endl;
		}
	}
};

int main(int argc, char** argv){
	// Instancio meu objeto frase
	Frase* frase = new Frase;

	// Crio e mostro a frase
	frase->criarFrase();
	frase->mostrarFraseMapeada();

	delete (frase);
	return 0;
}
