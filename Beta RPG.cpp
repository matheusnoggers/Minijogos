#include<string>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<conio.h>

using namespace std;

string lista_nomes[6]={
    "Jeromeu", "Jorge", "Adamastor", "Tingo-Lingo", "Papa-Papaya", "Talco-Man"
};

string lista_racas[6]={
    "Goblin", "Orc", "Humano", "Elfo", "Anao", "Golem"
};

namespace monstros{
    class inimigo{
    protected:
        string nome;
        string raca;

    public:
        int vida;
        int atk_power;
        int resistencia;


        inimigo(){
            nome="";
            raca="Indefinido";
            vida=0;
            resistencia=0;
            atk_power=0;
        }
        inimigo(string n, string r, int v, int rs, int atk){
            nome=n;
            raca=r;
            vida=v;
            resistencia=rs;
            atk_power=atk;
        }

        int dano(){
            return atk_power-rand()%(atk_power-1);
        }
        int ataque(){
            cout << nome << " realiza um ataque!" << endl;
            return atk_power+rand()%11;
        }
        int defesa(){
            cout << nome << " tenta se defender!" << endl;
            return resistencia+rand()%5;
        }

        string getNome(){
            return nome;
        }
        string getRaca(){
            return raca;
        }

        void inimigoSet(string n, string r, int v, int rs, int atk){
            nome=n;
            raca=r;
            vida=v;
            resistencia=rs;
            atk_power=atk;
        }
    };

    class magico : public inimigo{
    public:
        int mana;
        magico() : inimigo(){
            mana=0;
        }
        magico(string n, string r, int v, int rs, int atk, int m){
            nome=n;
            raca=r;
            vida=v;
            resistencia=rs;
            atk_power=atk;
            mana=m;
        }

        int atk_magico(){
            int atk;
            atk=ataque()+mana+rand()%mana;
            mana--;
            cout << nome << " perde mana por realizar um ataque magico." << endl;
            return atk;
        }
        int dfs_magico(){
            int dfs;
            dfs=defesa()+mana;
            mana--;
            cout << nome << " perde mana por realizar uma defesa magica." << endl;
            return dfs;
        }

        void magicoSet(string n, string r, int v, int rs, int atk, int m){
            nome=n;
            raca=r;
            vida=v;
            resistencia=rs;
            atk_power=atk;
            mana=m;
        }
    };

    class boss : public magico{
    public:
        int delay;

        boss() : magico(){
            delay=1000;
        }
        boss(string n, string r, int v, int rs, int atk, int m, int d){
            nome=n;
            raca=r;
            resistencia=rs;
            atk_power=atk;
            mana=m;
            delay=d;
            vida=v;
        }

        int especial(){
            int sanguessuga=dano()*2;
            vida+=sanguessuga;
            cout << nome << " realiza um especial e rouba " << sanguessuga << " pontos de vida!" << endl;
            return sanguessuga;
        }

        void bossSet(string n, string r, int v, int rs, int atk, int m, int d){
            nome=n;
            raca=r;
            resistencia=rs;
            atk_power=atk;
            mana=m;
            delay=d;
            vida=v;
        }
    };
}

// Namespace para geracao de monstros

class player{
private:
    string nome;
public:
    int atk_power, vida, resistencia;

    player(){
        nome="";
        atk_power=0;
        vida=0;
        resistencia=0;
    }
    player(string n, int atk, int v, int r){
        atk_power=atk;
        vida=v;
        resistencia=r;
        nome=n;
    }

    string getNome(){
        return nome;
    }
    void setNome(string n){
        nome=n;
    }

    int dano(){
        return atk_power-rand()%(atk_power-1);
    }
    int ataque(){
        cout << "Voce realiza um ataque!" << endl;
        return atk_power+rand()%13;
    }
    int defesa(){
        cout << "Voce tenta se defender!" << endl;
        return resistencia+rand()%7;
    }
    void descanso(){
        int cura=rand()%10+10;
        cout << "Voce descansa por uma rodada e cura " << cura << " pontos de vida!" << endl;
        vida+=cura;
    }

    void show(){
        cout << "----" << nome << "----" << endl;
        cout << "-Vida atual: " << vida << "-" << endl;
        cout << "-Forca de ataque: " << atk_power << "-" << endl;
        cout << "-Resistencia: " << resistencia << "-" << endl;
        cout << endl << "-----Acoes-----" << endl;
        cout << "-Dano: " << atk_power << " - 1d" << atk_power-1 << endl;
        cout << "-Ataque: 1d12 + " << atk_power << endl;
        cout << "-Defesa: 1d6 + " << resistencia << endl;
        cout << "-Descanso: 1d9 + 10" << endl;
    }
};

// classe para geracao do jogador

string batalha_comum(monstros::inimigo* i, player* p);
string batalha_magica(monstros::magico* i, player* p);
string batalha_boss(monstros::boss* i, player* p);

int main(void){
    srand(time(NULL));

    int opc, opc_2, magic;
    string nome_personagem;
    string vencedor;
    monstros::inimigo inimigo_generico;
    monstros::magico magico_generico;
    monstros::boss BOSS_generico;
    player personagem("", 10, 100, 12);

    do{
        cout << "Deseja comecar?\n" << "1 para sim\n" << "0 para nao" << endl;
        cin >> opc;
        if(!opc){
            cout << "Tem certeza?\n" << "1 para sim\n" << "0 para nao" << endl;
            cin >> opc;
            if(!opc){
                break;
            }else{
                cout << "Obrigado por testar!" << endl;
                return 0;
            }
        }else{
            break;
        }
    }while(opc>1 && opc<0);

    cout << "Pressione qualquer tecla para continuar..." << endl;

    getch();
    system("cls");

    cout << "Antes de comecar selecione um nome para seu personagem (sem espacos):" << endl;
    cin >> nome_personagem;
    getchar();
    personagem.setNome(nome_personagem);

    system("cls");

    while(1){
        cout << "Escolha uma opcao:\n" << "1 para ver personagem\n" << "2 para reiniciar personagem" << endl;
        cout << "3 para lutar contra oponente generico\n" << "4 para lutar contra oponente magico generico" << endl;
        cout << "5 para lutar contra boss generico\n" << "6 para lutar ate a morte\n" << "7 para mudar nome do personagem" << endl;
        cout << "8 para ver creditos\n" << "9 para sair" << endl;
        cin >> opc_2;

        system("cls");

        switch(opc_2){
        case 1:
            personagem.show();
            break;
        case 2:
            personagem.atk_power=10;
            personagem.vida=100;
            personagem.resistencia=12;
            break;
        case 3:
            inimigo_generico.inimigoSet(lista_nomes[rand()%6], lista_racas[rand()%6], rand()%16+65, rand()%5+8, rand()%4+7);
            vencedor=batalha_comum(&inimigo_generico, &personagem);
            cout << "Vencedor: " << vencedor << endl;
            break;
        case 4:
            magico_generico.magicoSet(lista_nomes[rand()%6], lista_racas[rand()%6], rand()%16+65, rand()%5+8, rand()%4+7, rand()%6+5);
            vencedor=batalha_magica(&magico_generico, &personagem);
            cout << "Vencedor: " << vencedor << endl;
            break;
        case 5:
            BOSS_generico.bossSet(lista_nomes[rand()%6], lista_racas[rand()%6], rand()%16+90, rand()%5+10, rand()%4+9, rand()%6+7, rand()%10+3);
            vencedor=batalha_boss(&BOSS_generico, &personagem);
            cout << "Vencedor: " << vencedor << endl;
            break;
        case 6:
            for(int i=1;1;i++){
                if(i%6==0){
                    BOSS_generico.bossSet(lista_nomes[rand()%6], lista_racas[rand()%6], rand()%16+90, rand()%5+10, rand()%4+9, rand()%6+7, rand()%10+3);
                    vencedor=batalha_boss(&BOSS_generico, &personagem);
                }else{
                    magic=rand()%4;
                    switch(magic){
                    case 0 ... 2:
                        inimigo_generico.inimigoSet(lista_nomes[rand()%6], lista_racas[rand()%6], rand()%16+65, rand()%5+8, rand()%4+7);
                        vencedor=batalha_comum(&inimigo_generico, &personagem);
                        break;
                    case 3:
                        magico_generico.magicoSet(lista_nomes[rand()%6], lista_racas[rand()%6], rand()%16+65, rand()%5+8, rand()%4+7, rand()%6+5);
                        vencedor=batalha_magica(&magico_generico, &personagem);
                        break;
                    }
                }
                if(vencedor!=personagem.getNome()){
                    cout << "Voce morreu!" << endl;
                    break;
                }
            }
            break;
        case 7:
            cout << "Selecione o nome para seu personagem:" << endl;
            cin >> nome_personagem;
            personagem.setNome(nome_personagem);
            getchar();
            break;
        case 8:
            cout << "Programador principal: Matheus" << endl;
            cout << "Designer da parte grafica: Nogueira" << endl;
            cout << "Escritor da lore: da" << endl;
            cout << "Mencao honrosa: Silva" << endl;
            break;
        case 9:
            cout << "Obrigado por experimentar nosso jogo!" << endl;
            return 0;
            break;
        default:
            cout << "Opcao invalida." << endl;
        }
        cout << "Pressione qualquer tecla para continuar..." << endl;
        getch();
        system("cls");
    }
}

// fim da main

string batalha_comum(monstros::inimigo* i, player* p){
    int opcao, acao, auxatki, auxatkp, auxdfsi, auxdfsp, dmp, dmi;

    cout << "Voce encontra um oponente do tipo " << i->getRaca() << "!" << endl;
    cout << "Batalha de " << p->getNome() << " contra " << i->getNome() << endl;

    while(1){
    escolha:

        cout << "Selecione o que deseja fazer:" << endl;
        cout << "1 para atacar" << endl;
        cout << "2 para defender" << endl;
        cout << "3 para descansar" << endl;
        cin >> opcao;

        switch(opcao){
        case 1:
            auxatkp=p->ataque();
            auxdfsp=p->resistencia;
            break;
        case 2:
            auxatkp=0;
            auxdfsp=p->defesa();
            break;
        case 3:
            auxatkp=0;
            auxdfsp=p->resistencia;
            p->descanso();
            break;
        default:
            cout << "Invalido." << endl;
            goto escolha;
        }

        acao=rand()%4;
        switch(acao){
        case 0 ... 2:
            auxatki=i->ataque();
            auxdfsi=i->resistencia;
            break;
        case 3:
            auxatki=0;
            auxdfsi=i->defesa();
            break;
        }

        if(auxatkp>=auxdfsi){
            dmp=p->dano();

            cout << "Voce acerta um ataque, causando " << dmp << " dano!" << endl;
            i->vida-=dmp;
        }else if(auxatkp>0){
            cout << "Voce erra o ataque!" << endl;
        }

        if(i->vida<=0){
            return p->getNome();
        }

        if(auxatki>=auxdfsp){
            dmi=i->dano();

            cout << i->getNome() << " acerta um ataque, causando " << dmi << " dano!" << endl;
            p->vida-=dmi;
        }else if(auxatki>0){
            cout << i->getNome() << " erra o ataque!" << endl;
        }

        if(p->vida<=0){
            return i->getNome();
        }

        cout << "Vida atual de " << i->getNome() << ": " << i->vida << endl;
        cout << "Sua vida atual: " << p->vida << endl;
        cout << "Pressione qualquer tecla para prosseguir..." << endl;
        getch();
        system("cls");
    }
}

// So pra nao me perder

string batalha_magica(monstros::magico* i, player* p){
    int opcao, acao, auxatki, auxatkp, auxdfsi, auxdfsp, dmp, dmi, acao_magica;

    cout << "Voce encontra um oponente magico do tipo " << i->getRaca() << "!" << endl;
    cout << "Batalha de " << p->getNome() << " contra " << i->getNome() << endl;

    while(1){
    escolha:

        cout << "Selecione o que deseja fazer:" << endl;
        cout << "1 para atacar" << endl;
        cout << "2 para defender" << endl;
        cout << "3 para descansar" << endl;
        cin >> opcao;

        switch(opcao){
        case 1:
            auxatkp=p->ataque();
            auxdfsp=p->resistencia;
            break;
        case 2:
            auxatkp=0;
            auxdfsp=p->defesa();
            break;
        case 3:
            auxatkp=0;
            auxdfsp=p->resistencia;
            p->descanso();
            break;
        default:
            cout << "Invalido." << endl;
            goto escolha;
        }

        acao=rand()%4;
        switch(acao){
        case 0 ... 2:
            acao_magica=rand()%3;
            switch(acao_magica){
            case 0: case 1:
                ataque_normal:
                auxatki=i->ataque();
                auxdfsi=i->resistencia;
                break;
            case 2:
                if(i->mana<=0){
                    goto ataque_normal;
                    break;
                }else{
                    auxatki=i->atk_magico();
                    auxdfsi=i->resistencia;
                }
                break;
            }
            break;
        case 3:
            acao_magica=rand()%3;
            switch(acao_magica){
            case 0: case 1:
                defesa_normal:
                auxatki=0;
                auxdfsi=i->defesa();
                break;
            case 2:
                if(i->mana>0){
                    auxatki=0;
                    auxdfsi=i->dfs_magico();
                }else{
                    goto defesa_normal;
                    break;
                }
                break;
            }
            break;
        }

        if(auxatkp>=auxdfsi){
            dmp=p->dano();

            cout << "Voce acerta um ataque, causando " << dmp << " dano!" << endl;
            i->vida-=dmp;
        }else if(auxatkp>0){
            cout << "Voce erra o ataque!" << endl;
        }

        if(i->vida<=0){
            return p->getNome();
        }

        if(auxatki>=auxdfsp){
            i->mana>0 ? dmi=i->dano()+(i->mana/2) : dmi=i->dano();

            cout << i->getNome() << " acerta um ataque, causando " << dmi << " dano!" << endl;
            p->vida-=dmi;
        }else if(auxatki>0){
            cout << i->getNome() << " erra o ataque!" << endl;
        }

        if(p->vida<=0){
            return i->getNome();
        }

        cout << "Vida atual de " << i->getNome() << ": " << i->vida << endl;
        cout << "Mana restante de " << i->getNome() << ": " << i->mana << endl;
        cout << "Sua vida atual: " << p->vida << endl;
        cout << "Pressione qualquer tecla para prosseguir..." << endl;
        getch();
        system("cls");
    }
}

// slipknot eh foda

string batalha_boss(monstros::boss* i, player* p){
    int opcao, acao, auxatki, auxatkp, auxdfsi, auxdfsp, dmp, dmi, acao_magica, c=1;

    cout << "Um BOSS do tipo " << i->getRaca() << " se aproxima!" << endl;
    cout << "Batalha de " << p->getNome() << " contra " << i->getNome() << endl;

    while(1){
        cout << "Selecione o que deseja fazer:" << endl;
        cout << "1 para atacar" << endl;
        cout << "2 para defender" << endl;
        cout << "3 para descansar" << endl;
        cin >> opcao;

        switch(opcao){
        case 1:
            auxatkp=p->ataque();
            auxdfsp=p->resistencia;
            break;
        case 2:
            auxatkp=0;
            auxdfsp=p->defesa();
            break;
        case 3:
            auxatkp=0;
            auxdfsp=p->resistencia;
            p->descanso();
            break;
        default:
            cout << "Invalido." << endl;
            continue;
        }

        acao=rand()%4;
        switch(acao){
        case 0: case 1: case 2:
            acao_magica=rand()%3;
            switch(acao_magica){
            case 0: case 1:
                auxatki=i->ataque();
                auxdfsi=i->resistencia;
                break;
            case 2:
                if(i->mana<=0){
                    auxatki=i->ataque();
                    auxdfsi=i->resistencia;
                }else{
                    auxatki=i->atk_magico();
                    auxdfsi=i->resistencia;
                }
            }
            break;
        case 3:
            acao_magica=rand()%3;
            switch(acao_magica){
            case 0: case 1:
                auxatki=0;
                auxdfsi=i->defesa();
                break;
            case 2:
                if(i->mana>0){
                    auxatki=0;
                    auxdfsi=i->dfs_magico();
                }else{
                    auxatki=0;
                    auxdfsi=i->defesa();
                }
            }
        }

        if(auxatkp>=auxdfsi){
            dmp=p->dano();

            cout << "Voce acerta um ataque, causando " << dmp << " dano!" << endl;
            i->vida-=dmp;
        }else if(auxatkp>0){
            cout << "Voce erra o ataque!" << endl;
        }

        if(i->vida<=0){
            return p->getNome();
        }

        if(auxatki>=auxdfsp){
            dmi=(i->mana>0) ? i->dano()+(i->mana/2) : i->dano();
            if(c%i->delay==0){
                dmi+=i->especial();
            }

            cout << i->getNome() << " acerta um ataque, causando " << dmi << " dano!" << endl;
        }else if(auxatki>0){
            dmi=0;
            if(c%i->delay==0){
                dmi+=i->especial();
            }

            cout << i->getNome() << " erra o ataque!" << endl;
        }
        p->vida-=dmi;

        if(p->vida<=0){
            return i->getNome();
        }

        cout << "Vida atual de " << i->getNome() << ": " << i->vida << endl;
        cout << "Mana restante de " << i->getNome() << ": " << i->mana << endl;
        cout << "Sua vida atual: " << p->vida << endl;
        cout << "Pressione qualquer tecla para prosseguir..." << endl;
        getch();
        system("cls");
        c++;
    }
}
