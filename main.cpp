#include <iostream>
#include <string>
#include <cstdlib>
//#include <ctime> 
#include <chrono> //para a semente no tempo unix (1/1/1970) 

using namespace std;
using namespace chrono;

const string characters = "abcdefghijklmnopqrstuvwxyz";

const int max_len = 9;
const int min_len = 3;

string generate_password(){

    string PASSWORD = "";

    //calcula em milisegundos quanto tempo se passou desde o tempo unix ate horario atual na minha maquina
    //ele converte de nanosegundos para milisegundos (duration_cast) porque nanosegundos mudam rapido demais que da overflow
    //desse jeito fica ideal e a string nao se repete
    auto mil_secs = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
    
    srand(static_cast<unsigned int>(mil_secs)); //define a seed e faz um type casting pra nao ser um numero tao grande ass

    int len = (rand() % (max_len - min_len + 1)) + min_len; //13 + 3

    for(int i =0; i < len; i++){
        int idx = (rand() % characters.size());
        PASSWORD.push_back(characters[idx]);
    }
    return PASSWORD;
}

void tutorial(){
    cout << "Inicialmente, é dado a você a quantidade de caracteres na senha, e você deve tentar adivinhá-la." << endl;
    cout << "As senhas não possuem números, caracteres especiais e letras maiúsculas, e não forma palavras existentes no dicionário." << endl;
    cout << "Com cada 'guess' que você faz, você é informado do status do seu palpite, contendo informações sobre quantas letras estão corretas, no lugar certo ou existe na palavra e estão no lugar errado." << endl;
    cout << "Vamos para o jogo." << endl;
}

void verify_guess(string guess, string password){
    int correct = 0;
    int correct_misplaced = 0;
    int correct_placed = 0;

    for(int i = 0; i < guess.size(); i++){
        char curchar = guess[i];
        auto it = password.find(curchar);
        if(it != password.npos){
            correct++;
            if(i == it){
                correct_placed++;
            }
            else{
                correct_misplaced++;
            }
        }
    }

    cout << "Letras corretas: " << correct << endl;
    cout << "Letras corretas e no lugar certo: " << correct_placed << endl;
    cout << "Letras corretas e no lugar errado: " << correct_misplaced << endl;
}

bool validate_guess(string guess){
    bool valid = true;
    for(int i = 0; i < guess.size(); i++){
        if(!isalpha(guess[i]) || !islower(guess[i])){
            valid = false;
        }
    }
    return valid;
}

void game(string password){
    
    string GUESS;
    char resp;

    cout << "Bem Vindo(a) ao jogo de adivinhar a senha secreta. Deseja ler um tutotial? (S/N): " << endl;
    cin >> resp;
    if(resp == 'S' || resp == 's'){
        tutorial();
    }
    
    cout << "Tamanho da senha = " << password.size() << " caracteres." << endl;
    while(1){
        GUESS = "";
        cout << "Digite a senha: ";
        cin >> GUESS;

        while(validate_guess(GUESS) == false){
            cout << "Palavra inválida, tente de novo: ";
            cin >> GUESS;
        }

        if(GUESS == password){
            cout << "Parabéns, você acertou a senha! ( " << password << " )" << endl; 
            return;
        }
        else{
            verify_guess(GUESS, password);
        }
    }
}



int main(){

    //take into input: a password guess
    //output how many characters are there in the password (max is 25)
    //there are no special chars and uppercase letters
    //verify if that matches the password generated when the game begins
    //give tips about it:
        //length is already given
        //number of letters correct and placed correct
        //number of letters correct and misplaced

    string PASSWORD = generate_password(); 
    cout << PASSWORD << endl;

    game(PASSWORD); 

    char play_again;
    cout << "Deseja jogar novamente? "; cin >> play_again;

    while(play_again == 's' || play_again == 'S'){
        string PASSWORD = generate_password();
        game(PASSWORD);

        cout << "Deseja jogar novamente? "; cin >> play_again;
    }

    return 0;
}